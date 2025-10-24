#include "../include/figure.h"
#include <utility>

Figure::Figure(double x, double y, double r, int n)
    : x(x), y(y), r(r), n(n) {}

Figure::Figure(const Figure& other)
    : x(other.x), y(other.y), r(other.r), n(other.n) {}

std::pair<double, double> Figure::center() const {
    return {x, y};
}

double Figure::square() const {
    double a = 2 * M_PI / n;
    return 0.5 * n * r * r * sin(a);
}

void Figure::showPoints(std::ostream& os) const {
    double a = 2 * M_PI / n;
    os << "Точки " << n << "-угольника: ";
    for (int i = 0; i < n; ++i) {
        double ca = i * a;
        double px = x + r * cos(ca);
        double py = y + r * sin(ca);
        os << "(" << px << ", " << py << ") ";
    }
    os << std::endl;
}

void Figure::read(std::istream& is) {
    is >> x >> y >> r;
}

Figure::operator double() const {
    return square();
}

bool Figure::same(const Figure& other) const {
    return x == other.x && y == other.y && 
           r == other.r && n == other.n;
}

Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        r = other.r;
        n = other.n;
    }
    return *this;
}

Figure& Figure::operator=(Figure&& other) noexcept {
    if (this != &other) {
        x = std::move(other.x);
        y = std::move(other.y);
        r = std::move(other.r);
        n = std::move(other.n);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.showPoints(os);
    auto c = fig.center();
    os << "Центр: (" << c.first << ", " << c.second << ")" << std::endl;
    os << "Площадь: " << fig.square() << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.read(is);
    return is;
}

Pentagon::Pentagon(double x, double y, double r) 
    : Figure(x, y, r, 5) {}

Pentagon::Pentagon(const Pentagon& other) 
    : Figure(other) {}

Figure* Pentagon::copy() const {
    return new Pentagon(*this);
}

Hexagon::Hexagon(double x, double y, double r) 
    : Figure(x, y, r, 6) {}

Hexagon::Hexagon(const Hexagon& other) 
    : Figure(other) {}

Figure* Hexagon::copy() const {
    return new Hexagon(*this);
}

Octagon::Octagon(double x, double y, double r) 
    : Figure(x, y, r, 8) {}

Octagon::Octagon(const Octagon& other) 
    : Figure(other) {}

Figure* Octagon::copy() const {
    return new Octagon(*this);
}

FigureList::FigureList(const FigureList& other) {
    for (const auto f : other.items) {
        items.push_back(f->copy());
    }
}

FigureList::FigureList(FigureList&& other) noexcept 
    : items(std::move(other.items)) {
    other.items.clear();
}

FigureList::~FigureList() {
    for (auto f : items) {
        delete f;
    }
}

FigureList& FigureList::operator=(const FigureList& other) {
    if (this != &other) {
        for (auto f : items) {
            delete f;
        }
        items.clear();
        
        for (const auto f : other.items) {
            items.push_back(f->copy());
        }
    }
    return *this;
}

FigureList& FigureList::operator=(FigureList&& other) noexcept {
    if (this != &other) {
        for (auto f : items) {
            delete f;
        }
        
        items = std::move(other.items);
        other.items.clear();
    }
    return *this;
}

void FigureList::add(Figure* fig) {
    items.push_back(fig);
}

void FigureList::remove(int i) {
    if (i >= 0 && i < static_cast<int>(items.size())) {
        delete items[i];
        items.erase(items.begin() + i);
    }
}

void FigureList::showAll() const {
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << "Фигура " << i + 1 << ":" << std::endl;
        std::cout << *items[i] << std::endl;
    }
}

double FigureList::allSquare() const {
    double sum = 0;
    for (const auto f : items) {
        sum += f->square();
    }
    return sum;
}

void FigureList::showCenters() const {
    for (size_t i = 0; i < items.size(); ++i) {
        auto c = items[i]->center();
        std::cout << "Центр " << i + 1 << ": (" 
                  << c.first << ", " << c.second << ")" << std::endl;
    }
}

void FigureList::showSquares() const {
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << "Площадь " << i + 1 << ": " 
                  << items[i]->square() << std::endl;
    }
}

size_t FigureList::count() const {
    return items.size();
}

Figure* FigureList::get(size_t i) const {
    return items[i];
}