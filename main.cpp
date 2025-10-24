#include "include/figure.h"
#include <iostream>

using namespace std;

int main() {
    FigureList list;
    int cmd;

    cout << "=== Работа с фигурами ===" << endl;

    while (true) {
        cout << "\nМеню:" << endl;
        cout << "1. Добавить пятиугольник" << endl;
        cout << "2. Добавить шестиугольник" << endl;
        cout << "3. Добавить восьмиугольник" << endl;
        cout << "4. Показать все" << endl;
        cout << "5. Показать центры" << endl;
        cout << "6. Показать площади" << endl;
        cout << "7. Общая площадь" << endl;
        cout << "8. Удалить фигуру" << endl;
        cout << "0. Выход" << endl;
        cout << "Выбор: ";
        cin >> cmd;

        if (cmd == 0) {
            cout << "Выход" << endl;
            break;
        }

        if (cmd == 1) {
            double a, b, c;
            cout << "Введите x y r: ";
            cin >> a >> b >> c;
            list.add(new Pentagon(a, b, c));
            cout << "Добавлен" << endl;
        } else if (cmd == 2) {
            double a, b, c;
            cout << "Введите x y r: ";
            cin >> a >> b >> c;
            list.add(new Hexagon(a, b, c));
            cout << "Добавлен" << endl;
        } else if (cmd == 3) {
            double a, b, c;
            cout << "Введите x y r: ";
            cin >> a >> b >> c;
            list.add(new Octagon(a, b, c));
            cout << "Добавлен" << endl;
        } else if (cmd == 4) {
            cout << "\nВсе фигуры:" << endl;
            list.showAll();
        } else if (cmd == 5) {
            cout << "\nЦентры:" << endl;
            list.showCenters();
        } else if (cmd == 6) {
            cout << "\nПлощади:" << endl;
            list.showSquares();
        } else if (cmd == 7) {
            cout << "\nОбщая площадь: " << list.allSquare() << endl;
        } else if (cmd == 8) {
            int idx;
            cout << "Номер для удаления (1-" << list.count() << "): ";
            cin >> idx;
            list.remove(idx - 1);
            cout << "Удален" << endl;
        } else {
            cout << "Нет такого" << endl;
        }
    }

    return 0;
}