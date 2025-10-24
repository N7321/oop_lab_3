#include "include/figure.h"
#include <iostream>

using namespace std;

int main() {
    FigureArray figures;
    int choice;

    cout << "=== Программа для работы с фигурами ===" << endl;

    while (true) {
        cout << "\nМеню:" << endl;
        cout << "1. Добавить пятиугольник" << endl;
        cout << "2. Добавить шестиугольник" << endl;
        cout << "3. Добавить восьмиугольник" << endl;
        cout << "4. Показать все фигуры" << endl;
        cout << "5. Показать геометрические центры" << endl;
        cout << "6. Показать площади" << endl;
        cout << "7. Показать общую площадь" << endl;
        cout << "8. Удалить фигуру по индексу" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Выход из программы." << endl;
            break;
        }

        if (choice == 1) {
            double x, y, radius;
            cout << "Введите координаты центра (x y) и радиус: ";
            cin >> x >> y >> radius;
            figures.addFigure(new Pentagon(x, y, radius));
            cout << "Пятиугольник добавлен!" << endl;
        } else if (choice == 2) {
            double x, y, radius;
            cout << "Введите координаты центра (x y) и радиус: ";
            cin >> x >> y >> radius;
            figures.addFigure(new Hexagon(x, y, radius));
            cout << "Шестиугольник добавлен!" << endl;
        } else if (choice == 3) {
            double x, y, radius;
            cout << "Введите координаты центра (x y) и радиус: ";
            cin >> x >> y >> radius;
            figures.addFigure(new Octagon(x, y, radius));
            cout << "Восьмиугольник добавлен!" << endl;
        } else if (choice == 4) {
            cout << "\nВсе фигуры:" << endl;
            figures.printAll();
        } else if (choice == 5) {
            cout << "\nГеометрические центры:" << endl;
            figures.printAllCenters();
        } else if (choice == 6) {
            cout << "\nПлощади фигур:" << endl;
            figures.printAllAreas();
        } else if (choice == 7) {
            cout << "\nОбщая площадь всех фигур: " << figures.totalArea() << endl;
        } else if (choice == 8) {
            int index;
            cout << "Введите индекс фигуры для удаления (1-" << figures.size() << "): ";
            cin >> index;
            figures.removeFigure(index - 1);
            cout << "Фигура удалена!" << endl;
        } else {
            cout << "Неверный выбор!" << endl;
        }
    }

    return 0;
}