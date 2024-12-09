#include <iostream>
#include <string>

template<typename T>
class UPtr {
private:
    class Node {
    public:
        T* ptr;

        Node(T* p = nullptr) : ptr(p) {}
        ~Node() { delete ptr; }

        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;

        Node(Node&& other) : ptr(other.ptr) {
            other.ptr = nullptr;
        }

        Node& move(Node&& other) {
            if (this != &other) {
                delete ptr;
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }
    };

    Node node;

public:
    UPtr(T* p = nullptr) : node(p) {}
    ~UPtr() = default;

    void reset(T* p = nullptr) {
        node = Node(p);
    }

    void swap(UPtr& other) {
        Node temp = std::move(node);
        node = std::move(other.node);
        other.node = std::move(temp);
    }

    T* get() const {
        return node.ptr;
    }

    T& razm() const {
        return *node.ptr;
    }

    T* incapsulation() const {
        return node.ptr;
    }
};

// Пример использования в клиенте main()
int main() {
    setlocale(LC_ALL, "RU");

    UPtr<int> ptrInt(new int(486748));
    std::cout << "int ЧИСЛО: " << ptrInt.razm() << std::endl;

    UPtr<double> ptrDouble(new double(1.68));
    std::cout << "double ЧИСЛО: " << ptrDouble.razm() << std::endl;

    UPtr<std::string> ptrString(new std::string("PRUVET"));
    std::cout << "string НАДПИСЬ: " << ptrString.razm() << std::endl;

    return 0;
}
