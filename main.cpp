#include "include/figure.h"
#include <iostream>

using namespace std;

int main() {
    FigureCollection figureCollection;
    int userChoice;

    cout << "=== Программа для работы с геометрическими фигурами ===" << endl;

    while (true) {
        cout << "\nОсновное меню:" << endl;
        cout << "1. Добавить пятиугольник" << endl;
        cout << "2. Добавить шестиугольник" << endl;
        cout << "3. Добавить восьмиугольник" << endl;
        cout << "4. Показать информацию о всех фигурах" << endl;
        cout << "5. Показать геометрические центры" << endl;
        cout << "6. Показать площади всех фигур" << endl;
        cout << "7. Показать общую площадь" << endl;
        cout << "8. Удалить фигуру по индексу" << endl;
        cout << "0. Завершить программу" << endl;
        cout << "Введите номер действия: ";
        cin >> userChoice;

        if (userChoice == 0) {
            cout << "Работа программы завершена." << endl;
            break;
        }

        switch (userChoice) {
            case 1: {
                double centerX, centerY, radiusValue;
                cout << "Введите координаты центра (x y) и радиус: ";
                cin >> centerX >> centerY >> radiusValue;
                figureCollection.addFigure(new Pentagon(centerX, centerY, radiusValue));
                cout << "Пятиугольник успешно добавлен в коллекцию!" << endl;
                break;
            }
            case 2: {
                double centerX, centerY, radiusValue;
                cout << "Введите координаты центра (x y) и радиус: ";
                cin >> centerX >> centerY >> radiusValue;
                figureCollection.addFigure(new Hexagon(centerX, centerY, radiusValue));
                cout << "Шестиугольник успешно добавлен в коллекцию!" << endl;
                break;
            }
            case 3: {
                double centerX, centerY, radiusValue;
                cout << "Введите координаты центра (x y) и радиус: ";
                cin >> centerX >> centerY >> radiusValue;
                figureCollection.addFigure(new Octagon(centerX, centerY, radiusValue));
                cout << "Восьмиугольник успешно добавлен в коллекцию!" << endl;
                break;
            }
            case 4:
                cout << "\nИнформация о всех фигурах в коллекции:" << endl;
                figureCollection.displayAllFigures();
                break;
            case 5:
                cout << "\nГеометрические центры фигур:" << endl;
                figureCollection.displayAllCenters();
                break;
            case 6:
                cout << "\nПлощади всех фигур:" << endl;
                figureCollection.displayAllAreas();
                break;
            case 7:
                cout << "\nОбщая площадь всех фигур: " << figureCollection.computeTotalArea() << endl;
                break;
            case 8: {
                int indexToRemove;
                cout << "Введите индекс фигуры для удаления (1-" << figureCollection.getCount() << "): ";
                cin >> indexToRemove;
                if (indexToRemove >= 1 && indexToRemove <= static_cast<int>(figureCollection.getCount())) {
                    figureCollection.removeFigureAt(indexToRemove - 1);
                    cout << "Фигура успешно удалена!" << endl;
                } else {
                    cout << "Ошибка: неверный индекс!" << endl;
                }
                break;
            }
            default:
                cout << "Ошибка: неверный номер действия!" << endl;
                break;
        }
    }

    return 0;
}