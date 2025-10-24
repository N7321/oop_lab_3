#include "../include/figure.h"
#include <utility>

// Реализация базового класса Figure
Figure::Figure(double x, double y, double radius, int vertices)
    : centerX(x), centerY(y), circumradius(radius), vertexCount(vertices) {}

Figure::Figure(const Figure& other)
    : centerX(other.centerX), centerY(other.centerY), 
      circumradius(other.circumradius), vertexCount(other.vertexCount) {}

std::pair<double, double> Figure::getGeometricCenter() const {
    return {centerX, centerY};
}

double Figure::calculateArea() const {
    double angleStep = 2 * M_PI / vertexCount;
    return 0.5 * vertexCount * circumradius * circumradius * sin(angleStep);
}

void Figure::outputVertices(std::ostream& os) const {
    double angleStep = 2 * M_PI / vertexCount;
    os << "Вершины " << vertexCount << "-угольника: ";
    for (int i = 0; i < vertexCount; ++i) {
        double currentAngle = i * angleStep;
        double vertexX = centerX + circumradius * cos(currentAngle);
        double vertexY = centerY + circumradius * sin(currentAngle);
        os << "(" << vertexX << ", " << vertexY << ") ";
    }
    os << std::endl;
}

void Figure::inputData(std::istream& is) {
    is >> centerX >> centerY >> circumradius;
}

Figure::operator double() const {
    return calculateArea();
}

bool Figure::isEqual(const Figure& other) const {
    return centerX == other.centerX && centerY == other.centerY && 
           circumradius == other.circumradius && vertexCount == other.vertexCount;
}

Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        centerX = other.centerX;
        centerY = other.centerY;
        circumradius = other.circumradius;
        vertexCount = other.vertexCount;
    }
    return *this;
}

Figure& Figure::operator=(Figure&& other) noexcept {
    if (this != &other) {
        centerX = std::move(other.centerX);
        centerY = std::move(other.centerY);
        circumradius = std::move(other.circumradius);
        vertexCount = std::move(other.vertexCount);
    }
    return *this;
}

// Реализация операторов ввода и вывода
std::ostream& operator<<(std::ostream& os, const Figure& fig) {
    fig.outputVertices(os);
    auto center = fig.getGeometricCenter();
    os << "Геометрический центр: (" << center.first << ", " << center.second << ")" << std::endl;
    os << "Площадь: " << fig.calculateArea() << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Figure& fig) {
    fig.inputData(is);
    return is;
}

// Реализация класса Pentagon
Pentagon::Pentagon(double x, double y, double radius) 
    : Figure(x, y, radius, 5) {}

Pentagon::Pentagon(const Pentagon& other) 
    : Figure(other) {}

Figure* Pentagon::createCopy() const {
    return new Pentagon(*this);
}

// Реализация класса Hexagon
Hexagon::Hexagon(double x, double y, double radius) 
    : Figure(x, y, radius, 6) {}

Hexagon::Hexagon(const Hexagon& other) 
    : Figure(other) {}

Figure* Hexagon::createCopy() const {
    return new Hexagon(*this);
}

// Реализация класса Octagon
Octagon::Octagon(double x, double y, double radius) 
    : Figure(x, y, radius, 8) {}

Octagon::Octagon(const Octagon& other) 
    : Figure(other) {}

Figure* Octagon::createCopy() const {
    return new Octagon(*this);
}

// Реализация класса FigureCollection

// Конструктор копирования
FigureCollection::FigureCollection(const FigureCollection& other) {
    for (const auto figurePtr : other.figuresList) {
        figuresList.push_back(figurePtr->createCopy());
    }
}

// Конструктор перемещения
FigureCollection::FigureCollection(FigureCollection&& other) noexcept 
    : figuresList(std::move(other.figuresList)) {
    other.figuresList.clear();
}

// Деструктор
FigureCollection::~FigureCollection() {
    for (auto figurePtr : figuresList) {
        delete figurePtr;
    }
}

// Оператор присваивания копированием
FigureCollection& FigureCollection::operator=(const FigureCollection& other) {
    if (this != &other) {
        // Очищаем текущие данные
        for (auto figurePtr : figuresList) {
            delete figurePtr;
        }
        figuresList.clear();
        
        // Копируем данные из другого объекта
        for (const auto figurePtr : other.figuresList) {
            figuresList.push_back(figurePtr->createCopy());
        }
    }
    return *this;
}

// Оператор присваивания перемещением
FigureCollection& FigureCollection::operator=(FigureCollection&& other) noexcept {
    if (this != &other) {
        // Очищаем текущие данные
        for (auto figurePtr : figuresList) {
            delete figurePtr;
        }
        
        // Перемещаем данные из другого объекта
        figuresList = std::move(other.figuresList);
        other.figuresList.clear();
    }
    return *this;
}

// Добавление новой фигуры в коллекцию
void FigureCollection::addFigure(Figure* newFigure) {
    figuresList.push_back(newFigure);
}

// Удаление фигуры по индексу
void FigureCollection::removeFigureAt(int index) {
    if (index >= 0 && index < static_cast<int>(figuresList.size())) {
        delete figuresList[index];
        figuresList.erase(figuresList.begin() + index);
    }
}

// Вывод информации о всех фигурах
void FigureCollection::displayAllFigures() const {
    for (size_t i = 0; i < figuresList.size(); ++i) {
        std::cout << "Фигура " << i + 1 << ":" << std::endl;
        std::cout << *figuresList[i] << std::endl;
    }
}

// Вычисление общей площади всех фигур
double FigureCollection::computeTotalArea() const {
    double total = 0;
    for (const auto figurePtr : figuresList) {
        total += figurePtr->calculateArea();
    }
    return total;
}

// Вывод центров всех фигур
void FigureCollection::displayAllCenters() const {
    for (size_t i = 0; i < figuresList.size(); ++i) {
        auto center = figuresList[i]->getGeometricCenter();
        std::cout << "Центр фигуры " << i + 1 << ": (" 
                  << center.first << ", " << center.second << ")" << std::endl;
    }
}

// Вывод площадей всех фигур
void FigureCollection::displayAllAreas() const {
    for (size_t i = 0; i < figuresList.size(); ++i) {
        std::cout << "Площадь фигуры " << i + 1 << ": " 
                  << figuresList[i]->calculateArea() << std::endl;
    }
}

// Получение количества фигур в коллекции
size_t FigureCollection::getCount() const {
    return figuresList.size();
}

// Доступ к фигуре по индексу
Figure* FigureCollection::getFigureAt(size_t index) const {
    return figuresList[index];
}