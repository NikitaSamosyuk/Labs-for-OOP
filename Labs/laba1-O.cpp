#include <iostream>
#include <string>

using namespace std;

namespace containers {

    template <typename T>
    class NameClass {
    public:
        // Вложенная структура Node
        struct Node {
            T value;
            Node* next;
            Node* prev;

        private:
            Node(T val) : value(val), next(nullptr), prev(nullptr) {}
            friend class NameClass<T>;
        };

    private:
        Node* head;
        Node* tail;
        size_t size;

    public:
        // Конструктор по умолчанию
        NameClass() : head(nullptr), tail(nullptr), size(0) {}

        // Конструктор копирования
        NameClass(const NameClass& other) : NameClass() {
            Node* current = other.head;
            while (current) {
                add(current->value);
                current = current->next;
            }
        }

        // Конструктор перемещения
        NameClass(NameClass&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
            other.head = other.tail = nullptr;
            other.size = 0;
        }

        // Оператор присваивания (копирование)
        NameClass& operator=(const NameClass& other) {
            if (this == &other) return *this;

            clear();

            Node* current = other.head;
            while (current) {
                add(current->value);
                current = current->next;
            }

            return *this;
        }

        // Оператор присваивания (перемещение)
        NameClass& operator=(NameClass&& other) noexcept {
            if (this == &other) return *this;

            clear();

            head = other.head;
            tail = other.tail;
            size = other.size;

            other.head = other.tail = nullptr;
            other.size = 0;

            return *this;
        }

        // Операция индексирования
        T& operator[](size_t index) {
            if (index >= size) {
                cerr << "Индекс выходит за пределы" << endl;
                exit(1);  // Простой выход при ошибке
            }

            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->value;
        }

        // Метод добавления элемента
        void add(const T& value) {
            Node* newNode = new Node(value);
            if (!head) {
                head = tail = newNode;
            }
            else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
            ++size;
        }

        // Метод удаления элемента с конца
        void remove() {
            if (size == 0) return;

            Node* temp = tail;
            tail = tail->prev;
            if (tail) {
                tail->next = nullptr;
            }
            else {
                head = nullptr;
            }

            delete temp;
            --size;
        }

        // Метод очистки списка
        void clear() {
            while (size > 0) {
                remove();
            }
        }

        // Метод для получения размера списка
        size_t getSize() const {
            return size;
        }

        // Деструктор
        ~NameClass() {
            clear();
        }
    };

    // Шаблон класса однонаправленного кольцевого списка (RList)
    template <typename T>
    class RList {
    public:
        struct Node {
            T value;
            Node* next;

            Node(T val) : value(val), next(nullptr) {}
        };

    private:
        Node* head;
        size_t size;

    public:
        RList() : head(nullptr), size(0) {}

        // Конструктор копирования
        RList(const RList& other) : RList() {
            Node* current = other.head;
            if (current) {
                do {
                    add(current->value);
                    current = current->next;
                } while (current != other.head);
            }
        }

        // Конструктор перемещения
        RList(RList&& other) noexcept : head(other.head), size(other.size) {
            other.head = nullptr;
            other.size = 0;
        }

        // Оператор присваивания (копирование)
        RList& operator=(const RList& other) {
            if (this == &other) return *this;

            clear();

            Node* current = other.head;
            if (current) {
                do {
                    add(current->value);
                    current = current->next;
                } while (current != other.head);
            }

            return *this;
        }

        // Оператор присваивания (перемещение)
        RList& operator=(RList&& other) noexcept {
            if (this == &other) return *this;

            clear();

            head = other.head;
            size = other.size;

            other.head = nullptr;
            other.size = 0;

            return *this;
        }

        // Метод добавления элемента
        void add(const T& value) {
            Node* newNode = new Node(value);
            if (!head) {
                head = newNode;
                newNode->next = head;
            }
            else {
                Node* temp = head;
                while (temp->next != head) {
                    temp = temp->next;
                }
                temp->next = newNode;
                newNode->next = head;
            }
            ++size;
        }

        // Метод удаления элемента
        void remove() {
            if (size == 0) return;

            Node* temp = head;
            if (size == 1) {
                head = nullptr;
            }
            else {
                Node* prev = nullptr;
                while (temp->next != head) {
                    prev = temp;
                    temp = temp->next;
                }
                prev->next = head;
                head = prev;
            }

            delete temp;
            --size;
        }

        // Метод для получения размера списка
        size_t getSize() const {
            return size;
        }

        // Операция индексирования
        T& operator[](size_t index) {
            if (index >= size) {
                cerr << "Индекс выходит за пределы" << endl;
                exit(1);  // Простой выход при ошибке
            }

            Node* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            return current->value;
        }

        // Метод очистки списка
        void clear() {
            while (size > 0) {
                remove();
            }
        }

        // Деструктор
        ~RList() {
            clear();
        }
    };
}

int main() {

    setlocale(0, "ru");
    using namespace containers;

    // Пример использования NameClass
    NameClass<int> intList;
    intList.add(1);
    intList.add(2);
    intList.add(3);
    cout << "List[2]: " << intList[2] << endl;

    intList.add(4);
    cout << "Добавлен элемент 4, размер List: " << intList.getSize() << endl;

    intList.remove();
    cout << "Удалён последний элемент, размер List: " << intList.getSize() << endl;

    // Пример использования RList
    RList<string> strList;
    strList.add("кубик");
    strList.add("кружок");
    strList.add("треугольнич");

    cout << "Размер RList: " << strList.getSize() << endl;
    cout << "strList[1]: " << strList[1] << endl;

    strList.remove();
    cout << "Удалён последний элемент, размер List: " << strList.getSize() << endl;

    return 0;
}
