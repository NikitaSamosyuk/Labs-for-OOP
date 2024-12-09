#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

using namespace std;

class CustomException : public exception {
private:
    string message;
    double value;
    int errorCode;

public:
    CustomException(const string& msg, double val, int code)
        : message(msg), value(val), errorCode(code) {}

    const char* what() const {
        return message.c_str();
    }

    double getValue() const {
        return value;
    }

    int getErrorCode() const {
        return errorCode;
    }
};

double calculateZ1(double b) {
    if (b * b - 4 < 0 || b + 2 == 0) {
        throw CustomException("Недопустимое значение при вычислении Z1", b, 1);
    }
    return (sqrt(2 * b + 2 * sqrt(b * b - 4))) / (sqrt(b * b - 4) + b + 2);
}

double calculateZ2(double b) {
    if (b + 2 < 0) {
        throw CustomException("Недопустимое значение под корнем при вычислении Z2", b, 2);
    }
    return 1 / sqrt(b + 2);
}

int main() {
    setlocale(0, "ru");
    try {
        double b;
        cout << "Введите значение b: ";
        cin >> b;

        double z1 = calculateZ1(b);
        double z2 = calculateZ2(b);

        cout << "Z1 = " << z1 << endl;
        cout << "Z2 = " << z2 << endl;

        if ((z1 - z2 < 1e-5) && (z2 - z1 < 1e-5)) {
            cout << "Значения Z1 и Z2 приблизительно равны" << endl;
        }
        else {
            cout << "Значения Z1 и Z2 различаются" << endl;
        }
    }
    catch (const CustomException& e) {
        cerr << "Ошибка: " << e.what() << endl;
        cerr << "Значение: " << e.getValue() << endl;
        cerr << "Код ошибки: " << e.getErrorCode() << endl;
    }
    catch (const exception& e) {
        cerr << "Неизвестная ошибка: " << e.what() << endl;
    }

    return 0;
}
