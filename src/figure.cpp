#include "../include/figure.h"
#include <utility>

// Реализация Figure
Figure::Figure(double x, double y, double radius, int vertices)
    : x(x), y(y), radius(radius), vertices(vertices) {}

Figure::Figure(const Figure& other)
    : x(other.x), y(other.y), radius(other.radius), vertices(other.vertices) {}

std::pair<double, double> Figure::geometricCenter() const {
    return {x, y};
}

double Figure::area() const {
    double angle = 2 * M_PI / vertices;
    return 0.5 * vertices * radius * radius * sin(angle);
}

void Figure::printVertices(std::ostream& os) const {
    double angle = 2 * M_PI / vertices;
    os << "Вершины " << vertices << "-угольника: ";
    for (int i = 0; i < vertices; ++i) {
        double currentAngle = i * angle;
        double vx = x + radius * cos(currentAngle);
        double vy = y + radius * sin(currentAngle);
        os << "(" << vx << ", " << vy << ") ";
    }
    os << std::endl;
}

void Figure::readData(std::istream& is) {
    is >> x >> y >> radius;
}

Figure::operator double() const {
    return area();
}

bool Figure::operator==(const Figure& other) const {
    return x == other.x && y == other.y && 
           radius == other.radius && vertices == other.vertices;
}

Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        radius = other.radius;
        vertices = other.vertices;
    }
    return *this;
}

Figure& Figure::operator=(Figure&& other) noexcept {
    if (this != &other) {
        x = std::move(other.x);
        y = std::move(other.y);
        radius = std::move(other.radius);
        vertices = std::move(other.vertices);
    }
    return *this;
}

// Реализация операторов ввода/вывода
std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.printVertices(os);
    auto center = fig.geometricCenter();
    os << "Геометрический центр: (" << center.first << ", " << center.second << ")" << std::endl;
    os << "Площадь: " << fig.area() << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.readData(is);
    return is;
}

// Реализация Pentagon
Pentagon::Pentagon(double x, double y, double radius) 
    : Figure(x, y, radius, 5) {}

Pentagon::Pentagon(const Pentagon& other) 
    : Figure(other) {}

Figure* Pentagon::clone() const {
    return new Pentagon(*this);
}

// Реализация Hexagon
Hexagon::Hexagon(double x, double y, double radius) 
    : Figure(x, y, radius, 6) {}

Hexagon::Hexagon(const Hexagon& other) 
    : Figure(other) {}

Figure* Hexagon::clone() const {
    return new Hexagon(*this);
}

// Реализация Octagon
Octagon::Octagon(double x, double y, double radius) 
    : Figure(x, y, radius, 8) {}

Octagon::Octagon(const Octagon& other) 
    : Figure(other) {}

Figure* Octagon::clone() const {
    return new Octagon(*this);
}

// Реализация FigureArray
// Реализация FigureArray

// Конструктор по умолчанию (уже неявно создается)
// FigureArray::FigureArray() = default;

// Copy конструктор
FigureArray::FigureArray(const FigureArray& other) {
    for (const auto fig : other.figures) {
        figures.push_back(fig->clone());  // Глубокое копирование
    }
}

// Move конструктор
FigureArray::FigureArray(FigureArray&& other) noexcept 
    : figures(std::move(other.figures)) {  // Перемещаем вектор
    other.figures.clear();  // Очищаем исходный вектор
}

// Деструктор
FigureArray::~FigureArray() {
    for (auto fig : figures) {
        delete fig;
    }
}

// Copy присваивание
FigureArray& FigureArray::operator=(const FigureArray& other) {
    if (this != &other) {
        // Очищаем текущие данные
        for (auto fig : figures) {
            delete fig;
        }
        figures.clear();
        
        // Копируем новые данные
        for (const auto fig : other.figures) {
            figures.push_back(fig->clone());
        }
    }
    return *this;
}

// Move присваивание
FigureArray& FigureArray::operator=(FigureArray&& other) noexcept {
    if (this != &other) {
        // Очищаем текущие данные
        for (auto fig : figures) {
            delete fig;
        }
        
        // Перемещаем данные из other
        figures = std::move(other.figures);
        other.figures.clear();
    }
    return *this;
}

// Остальные методы остаются без изменений
void FigureArray::addFigure(Figure* fig) {
    figures.push_back(fig);
}

void FigureArray::removeFigure(int index) {
    if (index >= 0 && index < static_cast<int>(figures.size())) {
        delete figures[index];
        figures.erase(figures.begin() + index);
    }
}

void FigureArray::printAll() const {
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Фигура " << i + 1 << ":" << std::endl;
        std::cout << *figures[i] << std::endl;
    }
}

double FigureArray::totalArea() const {
    double total = 0;
    for (const auto fig : figures) {
        total += fig->area();
    }
    return total;
}

void FigureArray::printAllCenters() const {
    for (size_t i = 0; i < figures.size(); ++i) {
        auto center = figures[i]->geometricCenter();
        std::cout << "Центр фигуры " << i + 1 << ": (" 
                  << center.first << ", " << center.second << ")" << std::endl;
    }
}

void FigureArray::printAllAreas() const {
    for (size_t i = 0; i < figures.size(); ++i) {
        std::cout << "Площадь фигуры " << i + 1 << ": " 
                  << figures[i]->area() << std::endl;
    }
}

size_t FigureArray::size() const {
    return figures.size();
}

Figure* FigureArray::operator[](size_t index) const {
    return figures[index];
}