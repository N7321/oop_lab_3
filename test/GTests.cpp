#include "figure.h"
#include <gtest/gtest.h>
#include <sstream>

TEST(FigureTest, Center) {
    Pentagon p(1, 2, 5);
    auto c = p.center();
    EXPECT_DOUBLE_EQ(c.first, 1.0);
    EXPECT_DOUBLE_EQ(c.second, 2.0);
}

TEST(FigureTest, Square) {
    Hexagon h(0, 0, 1);
    double s = h.square();
    EXPECT_GT(s, 0);
    EXPECT_NEAR(s, 2.598, 0.1);
}

TEST(FigureTest, ToDouble) {
    Octagon o(0, 0, 2);
    double s = static_cast<double>(o);
    EXPECT_GT(s, 0);
}

TEST(PentagonTest, Create) {
    Pentagon p1(1, 1, 3);
    Pentagon p2 = p1;
    EXPECT_TRUE(p1.same(p2));
}

TEST(PentagonTest, Copy) {
    Pentagon p(2, 3, 4);
    Figure* f = p.copy();
    EXPECT_TRUE(p.same(*f));
    EXPECT_NE(&p, f);
    delete f;
}

TEST(HexagonTest, SquareCalc) {
    Hexagon h(0, 0, 1);
    double s = h.square();
    double want = (3 * std::sqrt(3) * 1 * 1) / 2;
    EXPECT_NEAR(s, want, 0.001);
}

TEST(HexagonTest, Move) {
    Hexagon h1(1, 2, 3);
    Hexagon h2 = std::move(h1);
    EXPECT_GT(h2.square(), 0);
}

TEST(OctagonTest, CenterCheck) {
    Octagon o(0, 0, 5);
    auto c = o.center();
    EXPECT_DOUBLE_EQ(c.first, 0.0);
    EXPECT_DOUBLE_EQ(c.second, 0.0);
}

TEST(OctagonTest, Compare) {
    Octagon o1(1, 1, 2);
    Octagon o2(1, 1, 2);
    Octagon o3(2, 2, 3);
    EXPECT_TRUE(o1.same(o2));
    EXPECT_FALSE(o1.same(o3));
}

TEST(FigureListTest, AddRemove) {
    FigureList l;
    EXPECT_EQ(l.count(), 0);
    l.add(new Pentagon(0, 0, 1));
    l.add(new Hexagon(1, 1, 2));
    EXPECT_EQ(l.count(), 2);
    l.remove(0);
    EXPECT_EQ(l.count(), 1);
}

TEST(FigureListTest, TotalSquare) {
    FigureList l;
    l.add(new Pentagon(0, 0, 1));
    l.add(new Hexagon(0, 0, 1));
    double total = l.allSquare();
    EXPECT_GT(total, 0);
    double s1 = l.get(0)->square();
    double s2 = l.get(1)->square();
    EXPECT_DOUBLE_EQ(total, s1 + s2);
}

TEST(FigureListTest, Copy) {
    FigureList l1;
    l1.add(new Pentagon(1, 1, 2));
    l1.add(new Hexagon(2, 2, 3));
    FigureList l2 = l1;
    EXPECT_EQ(l1.count(), l2.count());
    EXPECT_NE(l1.get(0), l2.get(0));
    EXPECT_TRUE(*l1.get(0)->same(*l2.get(0)));
}

TEST(FigureListTest, Move) {
    FigureList l1;
    l1.add(new Octagon(0, 0, 5));
    size_t n = l1.count();
    FigureList l2 = std::move(l1);
    EXPECT_EQ(l2.count(), n);
    EXPECT_EQ(l1.count(), 0);
}

TEST(FigureListTest, Assign) {
    FigureList l1;
    l1.add(new Pentagon(1, 2, 3));
    FigureList l2;
    l2 = l1;
    EXPECT_EQ(l1.count(), l2.count());
    EXPECT_TRUE(*l1.get(0)->same(*l2.get(0)));
}

TEST(FigureListTest, SelfAssign) {
    FigureList l;
    l.add(new Hexagon(0, 0, 1));
    l = l;
    EXPECT_EQ(l.count(), 1);
}

TEST(FigureListTest, Show) {
    FigureList l;
    l.add(new Pentagon(0, 0, 1));
    testing::internal::CaptureStdout();
    l.showAll();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(out.empty());
}

TEST(IOStreamTest, Out) {
    Pentagon p(1, 2, 3);
    testing::internal::CaptureStdout();
    std::cout << p;
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(out.find("Точки 5-угольника") != std::string::npos);
}

TEST(IOStreamTest, In) {
    std::istringstream in("1.5 2.5 3.5");
    Pentagon p;
    in >> p;
    auto c = p.center();
    EXPECT_DOUBLE_EQ(c.first, 1.5);
    EXPECT_DOUBLE_EQ(c.second, 2.5);
}

TEST(MixedTest, Types) {
    FigureList l;
    l.add(new Pentagon(0, 0, 1));
    l.add(new Hexagon(0, 0, 1));
    l.add(new Octagon(0, 0, 1));
    EXPECT_EQ(l.count(), 3);
    for (size_t i = 0; i < l.count(); ++i) {
        EXPECT_GT(l.get(i)->square(), 0);
    }
    double total = l.allSquare();
    EXPECT_GT(total, 0);
}

TEST(FigureListTest, BadRemove) {
    FigureList l;
    l.add(new Pentagon(0, 0, 1));
    l.remove(-1);
    l.remove(10);
    EXPECT_EQ(l.count(), 1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}