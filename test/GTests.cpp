#include "figure.h"
#include <gtest/gtest.h>
#include <sstream>

// Тесты для Figure (базовый класс).
TEST(FigureTest, GeometricCenter) {
    Pentagon p(1, 2, 5);
    auto center = p.geometricCenter();
    EXPECT_DOUBLE_EQ(center.first, 1.0);
    EXPECT_DOUBLE_EQ(center.second, 2.0);
}

TEST(FigureTest, AreaCalculation) {
    Hexagon h(0, 0, 1);
    double area = h.area();
    EXPECT_GT(area, 0).  // Площадь должна быть положительной.
    
    // Для шестиугольника с радиусом 1 площадь ≈ 2.598.
    EXPECT_NEAR(area, 2.598, 0.1);
}

TEST(FigureTest, DoubleConversion) {
    Octagon o(0, 0, 2);
    double area = static_cast<double>(o);
    EXPECT_GT(area, 0);
}

// Тесты для Pentagon.
TEST(PentagonTest, CreationAndCopy) {
    Pentagon p1(1, 1, 3);
    Pentagon p2 = p1;  // Copy конструктор.
    
    EXPECT_TRUE(p1 == p2);
}

TEST(PentagonTest, Clone) {
    Pentagon p(2, 3, 4);
    Figure* clone = p.clone();
    
    EXPECT_TRUE(p == *clone);
    EXPECT_NE(&p, clone);  // Должен быть другой объект.
    
    delete clone;
}

// Тесты для Hexagon.
TEST(HexagonTest, Area) {
    Hexagon h(0, 0, 1);
    double area = h.area();
    // Площадь правильного шестиугольника: (3√3 * r²)/2.
    double expected = (3 * std::sqrt(3) * 1 * 1) / 2;
    EXPECT_NEAR(area, expected, 0.001);
}

TEST(HexagonTest, MoveSemantics) {
    Hexagon h1(1, 2, 3);
    Hexagon h2 = std::move(h1);  // Move конструктор.
    
    // После move h1 может быть в валидном, но unspecified состоянии.
    // Но h2 должен работать корректно.
    EXPECT_GT(h2.area(), 0);
}

// Тесты для Octagon.
TEST(OctagonTest, VerticesCount) {
    Octagon o(0, 0, 5);
    auto center = o.geometricCenter();
    EXPECT_DOUBLE_EQ(center.first, 0.0);
    EXPECT_DOUBLE_EQ(center.second, 0.0);
}

TEST(OctagonTest, Comparison) {
    Octagon o1(1, 1, 2);
    Octagon o2(1, 1, 2);
    Octagon o3(2, 2, 3);
    
    EXPECT_TRUE(o1 == o2);
    EXPECT_FALSE(o1 == o3);
}

// Тесты для FigureArray.
TEST(FigureArrayTest, AddAndRemove) {
    FigureArray array;
    
    EXPECT_EQ(array.size(), 0);
    
    array.addFigure(new Pentagon(0, 0, 1));
    array.addFigure(new Hexagon(1, 1, 2));
    
    EXPECT_EQ(array.size(), 2);
    
    array.removeFigure(0);
    EXPECT_EQ(array.size(), 1);
}

TEST(FigureArrayTest, TotalArea) {
    FigureArray array;
    
    array.addFigure(new Pentagon(0, 0, 1));
    array.addFigure(new Hexagon(0, 0, 1));
    
    double total = array.totalArea();
    EXPECT_GT(total, 0);
    
    // Общая площадь должна быть суммой площадей.
    double pentagonArea = array[0]->area();
    double hexagonArea = array[1]->area();
    EXPECT_DOUBLE_EQ(total, pentagonArea + hexagonArea);
}

TEST(FigureArrayTest, CopyConstructor) {
    FigureArray array1;
    array1.addFigure(new Pentagon(1, 1, 2));
    array1.addFigure(new Hexagon(2, 2, 3));
    
    FigureArray array2 = array1;  // Copy конструктор.
    
    EXPECT_EQ(array1.size(), array2.size());
    EXPECT_NE(array1[0], array2[0]);  // Должны быть разные указатели.
    EXPECT_TRUE(*array1[0] == *array2[0]);  // Но объекты одинаковые.
}

TEST(FigureArrayTest, MoveConstructor) {
    FigureArray array1;
    array1.addFigure(new Octagon(0, 0, 5));
    
    size_t originalSize = array1.size();
    FigureArray array2 = std::move(array1);  // Move конструктор.
    
    EXPECT_EQ(array2.size(), originalSize);
    EXPECT_EQ(array1.size(), 0);  // array1 должен быть пустым.
}

TEST(FigureArrayTest, CopyAssignment) {
    FigureArray array1;
    array1.addFigure(new Pentagon(1, 2, 3));
    
    FigureArray array2;
    array2 = array1;  // Copy присваивание.
    
    EXPECT_EQ(array1.size(), array2.size());
    EXPECT_TRUE(*array1[0] == *array2[0]);
}

TEST(FigureArrayTest, SelfAssignment) {
    FigureArray array;
    array.addFigure(new Hexagon(0, 0, 1));
    
    array = array;  // Self-assignment.
    
    EXPECT_EQ(array.size(), 1);  // Должен остаться валидным.
}

TEST(FigureArrayTest, PrintMethods) {
    FigureArray array;
    array.addFigure(new Pentagon(0, 0, 1));
    
    // Тестируем что методы не падают.
    testing::internal::CaptureStdout();
    array.printAll();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
    
    testing::internal::CaptureStdout();
    array.printAllCenters();
    output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
    
    testing::internal::CaptureStdout();
    array.printAllAreas();
    output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

// Тесты для потокового ввода/вывода.
TEST(IOStreamTest, OutputOperator) {
    Pentagon p(1, 2, 3);
    
    testing::internal::CaptureStdout();
    std::cout << p;
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Вершины 5-угольника") != std::string::npos);
    EXPECT_TRUE(output.find("Геометрический центр") != std::string::npos);
    EXPECT_TRUE(output.find("Площадь") != std::string::npos);
}

TEST(IOStreamTest, InputOperator) {
    std::istringstream input("1.5 2.5 3.5");
    Pentagon p;
    
    input >> p;
    
    auto center = p.geometricCenter();
    EXPECT_DOUBLE_EQ(center.first, 1.5);
    EXPECT_DOUBLE_EQ(center.second, 2.5);
}

// Тест на смешанные фигуры в массиве.
TEST(MixedFiguresTest, DifferentTypesInArray) {
    FigureArray array;
    
    array.addFigure(new Pentagon(0, 0, 1));
    array.addFigure(new Hexagon(0, 0, 1));
    array.addFigure(new Octagon(0, 0, 1));
    
    EXPECT_EQ(array.size(), 3);
    
    // Все фигуры должны иметь положительную площадь.
    for (size_t i = 0; i < array.size(); ++i) {
        EXPECT_GT(array[i]->area(), 0);
    }
    
    // Общая площадь должна быть корректной.
    double total = array.totalArea();
    EXPECT_GT(total, 0);
}

// Тест на удаление по невалидному индексу.
TEST(FigureArrayTest, RemoveInvalidIndex) {
    FigureArray array;
    array.addFigure(new Pentagon(0, 0, 1));
    
    // Не должно падать при невалидном индексе.
    array.removeFigure(-1);
    array.removeFigure(10);
    
    EXPECT_EQ(array.size(), 1);  // Размер не должен измениться.
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}.