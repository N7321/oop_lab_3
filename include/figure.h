#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <cmath>
#include <vector>

class Figure {
protected:
    double x, y;
    double radius;
    int vertices;

public:
    Figure(double x = 0, double y = 0, double radius = 1, int vertices = 5);
    Figure(const Figure& other);
    virtual ~Figure() = default;

    virtual std::pair<double, double> geometricCenter() const;
    virtual double area() const;
    virtual void printVertices(std::ostream& os) const;
    virtual void readData(std::istream& is);
    virtual operator double() const;
    
    virtual Figure* clone() const = 0;
    virtual bool operator==(const Figure& other) const;

    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Figure& fig);
    friend std::istream& operator>>(std::istream& is, Figure& fig);
};

class Pentagon : public Figure {
public:
    Pentagon(double x = 0, double y = 0, double radius = 1);
    Pentagon(const Pentagon& other);
    Figure* clone() const override;
};

class Hexagon : public Figure {
public:
    Hexagon(double x = 0, double y = 0, double radius = 1);
    Hexagon(const Hexagon& other);
    Figure* clone() const override;
};

class Octagon : public Figure {
public:
    Octagon(double x = 0, double y = 0, double radius = 1);
    Octagon(const Octagon& other);
    Figure* clone() const override;
};

class FigureArray {
private:
    std::vector<Figure*> figures;

public:
    FigureArray() = default;                                 // Конструктор по умолчанию
    FigureArray(const FigureArray& other);                   // Copy конструктор
    FigureArray(FigureArray&& other) noexcept;               // Move конструктор
    ~FigureArray();
    
    FigureArray& operator=(const FigureArray& other);        // Copy присваивание
    FigureArray& operator=(FigureArray&& other) noexcept;    // Move присваивание

    void addFigure(Figure* fig);
    void removeFigure(int index);
    void printAll() const;
    double totalArea() const;
    void printAllCenters() const;
    void printAllAreas() const;
    size_t size() const;
    Figure* operator[](size_t index) const;
};

#endif