#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <cmath>
#include <vector>

class Figure {
protected:
    double centerX, centerY;  
    double circumradius;       
    int vertexCount;           

public:
    Figure(double x = 0, double y = 0, double radius = 1, int vertices = 5);
    
    Figure(const Figure& other);
    virtual ~Figure() = default;


    virtual std::pair<double, double> getGeometricCenter() const;
    virtual double calculateArea() const;
    virtual void outputVertices(std::ostream& os) const;
    virtual void inputData(std::istream& is);
    

    virtual operator double() const;
    

    virtual Figure* createCopy() const = 0;
    virtual bool isEqual(const Figure& other) const;


    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other) noexcept;


    friend std::ostream& operator<<(std::ostream& os, const Figure& fig);
    friend std::istream& operator>>(std::istream& is, Figure& fig);
};


class Pentagon : public Figure {
public:
    Pentagon(double x = 0, double y = 0, double radius = 1);
    Pentagon(const Pentagon& other);
    Figure* createCopy() const override;
};


class Hexagon : public Figure {
public:
    Hexagon(double x = 0, double y = 0, double radius = 1);
    Hexagon(const Hexagon& other);
    Figure* createCopy() const override;
};


class Octagon : public Figure {
public:
    Octagon(double x = 0, double y = 0, double radius = 1);
    Octagon(const Octagon& other);
    Figure* createCopy() const override;
};


class FigureCollection {
private:
    std::vector<Figure*> figuresList;

public:
    FigureCollection() = default;
    FigureCollection(const FigureCollection& other);
    FigureCollection(FigureCollection&& other) noexcept;
    ~FigureCollection();
    FigureCollection& operator=(const FigureCollection& other);
    FigureCollection& operator=(FigureCollection&& other) noexcept;
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