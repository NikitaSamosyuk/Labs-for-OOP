#include <iostream>
#include "DynamicList.h"
#include "Haveaproblems.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Ru");
    try {

        // Динамические списки 
        DynamicList<int> intList{ 1, 2, 3, 4, 5, };
        DynamicList<double> doubleList{ 1.1, 2.1, 3.1, 4.1, 5.1 };
        DynamicList<string> stringList{ "один", "два", "четыре", "восемь", "шеснадцать" };

        cout << "размер списка int: " << intList.getSize() << endl;
        for (size_t i = 0; i < intList.getSize(); ++i) {
            cout << intList.at(i) << " ";
        }
        cout << endl;

        cout << "размер списка double: " << doubleList.getSize() << endl;
        for (size_t i = 0; i < doubleList.getSize(); ++i) {
            cout << doubleList.at(i) << " ";
        }
        cout << endl;

        cout << "размер списка string: " << stringList.getSize() << endl;
        for (size_t i = 0; i < stringList.getSize(); ++i) {
            cout << stringList.at(i) << " ";
        }
        cout << endl;

    
        intList.push_back(666);
        cout << "Новый размер списка int: " << intList.getSize() << endl;
        for (size_t i = 0; i < intList.getSize(); ++i) {
            cout << intList.at(i) << " ";
        }
        cout << endl;

        // Проверка выхода за пределы списка
        cout << intList.at(10) << endl; // ВЫЗЫВАЕТ (ПРОГРАММА IS DEATH)

    }
    catch (const exception& e) {
        HaveAProblems::handle(e);
    }

    return 0;
}
