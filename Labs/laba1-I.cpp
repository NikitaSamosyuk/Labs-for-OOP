#include <iostream>
#include <initializer_list>

using namespace std;

template <typename T>
class Stack {
private:
    struct Node {
        T value;
        Node* next;

        Node(T val) : value(val), next(nullptr) {}
    };

    Node* topNode;
    int stackSize;

public:
    Stack() : topNode(nullptr), stackSize(0) {}

    // Конструктор копирования
    Stack(const Stack& other) : Stack() {
        Node* current = other.topNode;
        while (current) {
            push(current->value);
            current = current->next;
        }
    }

    // Конструктор перемещения
    Stack(Stack&& other) : topNode(other.topNode), stackSize(other.stackSize) {
        other.topNode = nullptr;
        other.stackSize = 0;
    }

    // Конструктор от std::initializer_list
    Stack(initializer_list<T> initList) : Stack() {
        for (const T& value : initList) {
            push(value);
        }
    }

    // Оператор присваивания (копирование)
    Stack& operator=(const Stack& other) {
        if (this == &other) return *this;

        clear();

        Node* current = other.topNode;
        while (current) {
            push(current->value);
            current = current->next;
        }

        return *this;
    }

    // Оператор присваивания (перемещение)
    Stack& operator=(Stack&& other) {
        if (this == &other) return *this;

        clear();

        topNode = other.topNode;
        stackSize = other.stackSize;

        other.topNode = nullptr;
        other.stackSize = 0;

        return *this;
    }

    // Оператор присваивания от std::initializer_list
    Stack& operator=(initializer_list<T> initList) {
        clear();
        for (const T& value : initList) {
            push(value);
        }
        return *this;
    }

    // Добавление элемента в стек
    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        ++stackSize;
    }

    // Удаление элемента из стека
    void pop() {
        if (stackSize == 0) {
            cerr << "Ошибка: Стек пуст" << endl;
            exit(1);
        }

        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        --stackSize;
    }

    // Элемент с вершины стека
    T& top() {
        if (stackSize == 0) {
            cerr << "Ошибка: Стек пуст" << endl;
            exit(1);
        }

        return topNode->value;
    }

    // Размер стека
    int size() const {
        return stackSize;
    }

    // Очистка стека
    void clear() {
        while (stackSize > 0) {
            pop();
        }
    }

    // Деструктор
    ~Stack() {
        clear();
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    Stack<int> intStack = { 10, 20, 30 };
    cout << "Вершина стека: " << intStack.top() << endl;

    intStack.pop();
    cout << "Вершина стека после удаления: " << intStack.top() << endl;

    Stack<string> strStack = { "кубик", "кружок", "треугольник" };
    cout << "Вершина стека: " << strStack.top() << endl;

    return 0;
}
