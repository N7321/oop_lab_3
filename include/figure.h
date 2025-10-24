#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <cmath>
#include <vector>

// Базовый класс для геометрических фигур
class Figure {
protected:
    double centerX, centerY;  // Более описательные имена
    double circumradius;       // Радиус описанной окружности
    int vertexCount;           // Количество вершин

public:
    // Конструктор с параметрами по умолчанию
    Figure(double x = 0, double y = 0, double radius = 1, int vertices = 5);
    
    // Конструктор копирования
    Figure(const Figure& other);
    
    // Виртуальный деструктор для корректного удаления наследников
    virtual ~Figure() = default;

    // Основные операции с фигурой
    virtual std::pair<double, double> getGeometricCenter() const;
    virtual double calculateArea() const;
    virtual void outputVertices(std::ostream& os) const;
    virtual void inputData(std::istream& is);
    
    // Оператор приведения к double (площадь)
    virtual operator double() const;
    
    // Виртуальные методы для работы с полиморфизмом
    virtual Figure* createCopy() const = 0;
    virtual bool isEqual(const Figure& other) const;

    // Операторы присваивания
    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other) noexcept;

    // Дружественные операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Figure& fig);
    friend std::istream& operator>>(std::istream& is, Figure& fig);
};

// Класс правильного пятиугольника
class Pentagon : public Figure {
public:
    Pentagon(double x = 0, double y = 0, double radius = 1);
    Pentagon(const Pentagon& other);
    Figure* createCopy() const override;
};

// Класс правильного шестиугольника
class Hexagon : public Figure {
public:
    Hexagon(double x = 0, double y = 0, double radius = 1);
    Hexagon(const Hexagon& other);
    Figure* createCopy() const override;
};

// Класс правильного восьмиугольника
class Octagon : public Figure {
public:
    Octagon(double x = 0, double y = 0, double radius = 1);
    Octagon(const Octagon& other);
    Figure* createCopy() const override;
};

// Контейнер для хранения коллекции фигур
class FigureCollection {
private:
    std::vector<Figure*> figuresList;

public:
    // Конструкторы и деструктор
    FigureCollection() = default;
    FigureCollection(const FigureCollection& other);
    FigureCollection(FigureCollection&& other) noexcept;
    ~FigureCollection();
    
    // Операторы присваивания
    FigureCollection& operator=(const FigureCollection& other);
    FigureCollection& operator=(FigureCollection&& other) noexcept;

    // Методы для работы с коллекцией
    void addFigure(Figure* newFigure);
    void removeFigureAt(int index);
    void displayAllFigures() const;
    double computeTotalArea() const;
    void displayAllCenters() const;
    void displayAllAreas() const;
    size_t getCount() const;
    Figure* getFigureAt(size_t index) const;
};

#endif