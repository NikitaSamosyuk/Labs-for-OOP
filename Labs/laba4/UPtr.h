#ifndef UPTR_H
#define UPTR_H

template<typename T>
class UPtr {
private:
    T* ptr;

public:
    UPtr(T* p = nullptr) : ptr(p) {}
    ~UPtr() { delete ptr; }

    UPtr(const UPtr&) = delete;
    UPtr& operator=(const UPtr&) = delete;

    UPtr(UPtr&& other) : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    UPtr& operator=(UPtr&& other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    void swap(UPtr& other) {
        T* temp = ptr;
        ptr = other.ptr;
        other.ptr = temp;
    }

    T* get() const { return ptr; }

    T& operator*() const { return *ptr; }

    T* operator->() const { return ptr; }
};

#endif // UPTR_H
