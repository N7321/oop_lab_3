#include "figure.h"
#include <gtest/gtest.h>
#include <sstream>

// Тесты для базового класса Figure
TEST(FigureTest, GeometricCenterCalculation) {
    Pentagon pentagon(1, 2, 5);
    auto center = pentagon.getGeometricCenter();
    EXPECT_DOUBLE_EQ(center.first, 1.0);
    EXPECT_DOUBLE_EQ(center.second, 2.0);
}

TEST(FigureTest, AreaComputation) {
    Hexagon hexagon(0, 0, 1);
    double computedArea = hexagon.calculateArea();
    EXPECT_GT(computedArea, 0);  // Площадь всегда должна быть положительной
    
    // Для шестиугольника с радиусом 1 площадь ≈ 2.598
    EXPECT_NEAR(computedArea, 2.598, 0.1);
}

TEST(FigureTest, DoubleConversionOperator) {
    Octagon octagon(0, 0, 2);
    double areaValue = static_cast<double>(octagon);
    EXPECT_GT(areaValue, 0);
}

// Тесты для класса Pentagon
TEST(PentagonTest, ObjectCreationAndCopy) {
    Pentagon firstPentagon(1, 1, 3);
    Pentagon secondPentagon = firstPentagon;  // Конструктор копирования
    
    EXPECT_TRUE(firstPentagon.isEqual(secondPentagon));
}

TEST(PentagonTest, CopyCreationMethod) {
    Pentagon originalPentagon(2, 3, 4);
    Figure* copiedFigure = originalPentagon.createCopy();
    
    EXPECT_TRUE(originalPentagon.isEqual(*copiedFigure));
    EXPECT_NE(&originalPentagon, copiedFigure);  // Должен быть создан новый объект
    
    delete copiedFigure;
}

// Тесты для класса Hexagon
TEST(HexagonTest, AreaCalculationAccuracy) {
    Hexagon hexagon(0, 0, 1);
    double computedArea = hexagon.calculateArea();
    // Площадь правильного шестиугольника: (3√3 * r²)/2
    double expectedArea = (3 * std::sqrt(3) * 1 * 1) / 2;
    EXPECT_NEAR(computedArea, expectedArea, 0.001);
}

TEST(HexagonTest, MoveOperations) {
    Hexagon firstHexagon(1, 2, 3);
    Hexagon secondHexagon = std::move(firstHexagon);  // Конструктор перемещения
    
    // После перемещения firstHexagon может быть в валидном, но неопределенном состоянии
    // Но secondHexagon должен работать корректно
    EXPECT_GT(secondHexagon.calculateArea(), 0);
}

// Тесты для класса Octagon
TEST(OctagonTest, CenterCoordinates) {
    Octagon octagon(0, 0, 5);
    auto centerPoint = octagon.getGeometricCenter();
    EXPECT_DOUBLE_EQ(centerPoint.first, 0.0);
    EXPECT_DOUBLE_EQ(centerPoint.second, 0.0);
}

TEST(OctagonTest, ObjectComparison) {
    Octagon firstOctagon(1, 1, 2);
    Octagon secondOctagon(1, 1, 2);
    Octagon thirdOctagon(2, 2, 3);
    
    EXPECT_TRUE(firstOctagon.isEqual(secondOctagon));
    EXPECT_FALSE(firstOctagon.isEqual(thirdOctagon));
}

// Тесты для класса FigureCollection
TEST(FigureCollectionTest, AddAndRemoveOperations) {
    FigureCollection collection;
    
    EXPECT_EQ(collection.getCount(), 0);
    
    collection.addFigure(new Pentagon(0, 0, 1));
    collection.addFigure(new Hexagon(1, 1, 2));
    
    EXPECT_EQ(collection.getCount(), 2);
    
    collection.removeFigureAt(0);
    EXPECT_EQ(collection.getCount(), 1);
}

TEST(FigureCollectionTest, TotalAreaComputation) {
    FigureCollection collection;
    
    collection.addFigure(new Pentagon(0, 0, 1));
    collection.addFigure(new Hexagon(0, 0, 1));
    
    double totalArea = collection.computeTotalArea();
    EXPECT_GT(totalArea, 0);
    
    // Общая площадь должна быть суммой площадей отдельных фигур
    double pentagonArea = collection.getFigureAt(0)->calculateArea();
    double hexagonArea = collection.getFigureAt(1)->calculateArea();
    EXPECT_DOUBLE_EQ(totalArea, pentagonArea + hexagonArea);
}

TEST(FigureCollectionTest, CopyConstructorBehavior) {
    FigureCollection firstCollection;
    firstCollection.addFigure(new Pentagon(1, 1, 2));
    firstCollection.addFigure(new Hexagon(2, 2, 3));
    
    FigureCollection secondCollection = firstCollection;  // Конструктор копирования
    
    EXPECT_EQ(firstCollection.getCount(), secondCollection.getCount());
    EXPECT_NE(firstCollection.getFigureAt(0), secondCollection.getFigureAt(0));  // Должны быть разные указатели
    EXPECT_TRUE(*firstCollection.getFigureAt(0)->isEqual(*secondCollection.getFigureAt(0)));  // Но объекты одинаковые
}

TEST(FigureCollectionTest, MoveConstructorBehavior) {
    FigureCollection firstCollection;
    firstCollection.addFigure(new Octagon(0, 0, 5));
    
    size_t originalSize = firstCollection.getCount();
    FigureCollection secondCollection = std::move(firstCollection);  // Конструктор перемещения
    
    EXPECT_EQ(secondCollection.getCount(), originalSize);
    EXPECT_EQ(firstCollection.getCount(), 0);  // firstCollection должен быть пустым
}

TEST(FigureCollectionTest, CopyAssignmentOperation) {
    FigureCollection firstCollection;
    firstCollection.addFigure(new Pentagon(1, 2, 3));
    
    FigureCollection secondCollection;
    secondCollection = firstCollection;  // Оператор присваивания копированием
    
    EXPECT_EQ(firstCollection.getCount(), secondCollection.getCount());
    EXPECT_TRUE(*firstCollection.getFigureAt(0)->isEqual(*secondCollection.getFigureAt(0)));
}

TEST(FigureCollectionTest, SelfAssignmentHandling) {
    FigureCollection collection;
    collection.addFigure(new Hexagon(0, 0, 1));
    
    collection = collection;  // Самоприсваивание
    
    EXPECT_EQ(collection.getCount(), 1);  // Коллекция должна остаться валидной
}

TEST(FigureCollectionTest, DisplayMethodsExecution) {
    FigureCollection collection;
    collection.addFigure(new Pentagon(0, 0, 1));
    
    // Проверяем что методы вывода не вызывают ошибок
    testing::internal::CaptureStdout();
    collection.displayAllFigures();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
    
    testing::internal::CaptureStdout();
    collection.displayAllCenters();
    output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
    
    testing::internal::CaptureStdout();
    collection.displayAllAreas();
    output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

// Тесты для операций ввода/вывода
TEST(IOStreamTest, OutputOperatorFunctionality) {
    Pentagon pentagon(1, 2, 3);
    
    testing::internal::CaptureStdout();
    std::cout << pentagon;
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Вершины 5-угольника") != std::string::npos);
    EXPECT_TRUE(output.find("Геометрический центр") != std::string::npos);
    EXPECT_TRUE(output.find("Площадь") != std::string::npos);
}

TEST(IOStreamTest, InputOperatorFunctionality) {
    std::istringstream inputStream("1.5 2.5 3.5");
    Pentagon pentagon;
    
    inputStream >> pentagon;
    
    auto center = pentagon.getGeometricCenter();
    EXPECT_DOUBLE_EQ(center.first, 1.5);
    EXPECT_DOUBLE_EQ(center.second, 2.5);
}

// Тест с различными типами фигур в коллекции
TEST(MixedFiguresTest, HandlingDifferentFigureTypes) {
    FigureCollection collection;
    
    collection.addFigure(new Pentagon(0, 0, 1));
    collection.addFigure(new Hexagon(0, 0, 1));
    collection.addFigure(new Octagon(0, 0, 1));
    
    EXPECT_EQ(collection.getCount(), 3);
    
    // Все фигуры должны иметь положительную площадь
    for (size_t i = 0; i < collection.getCount(); ++i) {
        EXPECT_GT(collection.getFigureAt(i)->calculateArea(), 0);
    }
    
    // Общая площадь должна быть корректно вычислена
    double totalArea = collection.computeTotalArea();
    EXPECT_GT(totalArea, 0);
}

// Тест обработки невалидных индексов
TEST(FigureCollectionTest, InvalidIndexRemoval) {
    FigureCollection collection;
    collection.addFigure(new Pentagon(0, 0, 1));
    
    // Не должно возникать ошибок при невалидных индексах
    collection.removeFigureAt(-1);
    collection.removeFigureAt(10);
    
    EXPECT_EQ(collection.getCount(), 1);  // Размер коллекции не должен измениться
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}