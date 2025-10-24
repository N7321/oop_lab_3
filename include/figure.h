#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <cmath>
#include <vector>

class Figure {
protected:
    double x, y;
    double r;
    int n;

public:
    Figure(double x = 0, double y = 0, double r = 1, int n = 5);
    Figure(const Figure& other);
    virtual ~Figure() = default;

    virtual std::pair<double, double> center() const;
    virtual double square() const;
    virtual void showPoints(std::ostream& os) const;
    virtual void read(std::istream& is);
    virtual operator double() const;
    
    virtual Figure* copy() const = 0;
    virtual bool same(const Figure& other) const;

    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Figure& fig);
    friend std::istream& operator>>(std::istream& is, Figure& fig);
};

class Pentagon : public Figure {
public:
    Pentagon(double x = 0, double y = 0, double r = 1);
    Pentagon(const Pentagon& other);
    Figure* copy() const override;
};

class Hexagon : public Figure {
public:
    Hexagon(double x = 0, double y = 0, double r = 1);
    Hexagon(const Hexagon& other);
    Figure* copy() const override;
};

class Octagon : public Figure {
public:
    Octagon(double x = 0, double y = 0, double r = 1);
    Octagon(const Octagon& other);
    Figure* copy() const override;
};

class FigureList {
private:
    std::vector<Figure*> items;

public:
    FigureList() = default;
    FigureList(const FigureList& other);
    FigureList(FigureList&& other) noexcept;
    ~FigureList();
    
    FigureList& operator=(const FigureList& other);
    FigureList& operator=(FigureList&& other) noexcept;

    void add(Figure* fig);
    void remove(int i);
    void showAll() const;
    double allSquare() const;
    void showCenters() const;
    void showSquares() const;
    size_t count() const;
    Figure* get(size_t i) const;
};

#endif