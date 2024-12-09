#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include <list>
#include <stdexcept>
#include <initializer_list>
#include "UPtr.h"
#include "HaveAProblems.h"

template<typename T> class DynamicList { // одномерный динамический массив
private:
    UPtr<std::list<T>> data;

public:
    // Конструктор 
    DynamicList() : data(new std::list<T>()) {}

    // Конструктор от initializer_list<T>
    DynamicList(std::initializer_list<T> list) : data(new std::list<T>(list)) {}

    // Конструктор копирования
    DynamicList(const DynamicList& other) : data(new std::list<T>(*other.data)) {}

    // Копирующий оператор присваивания
    DynamicList& operator=(const DynamicList& other) {
        if (this != &other) {
            data.reset(new std::list<T>(*other.data));
        }
        return *this;
    }

    // Конструктор перемещения
    DynamicList(DynamicList&& other) : data(std::move(other.data)) {}

    // Перемещающий оператор присваивания
    DynamicList& operator=(DynamicList&& other) {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

    // Метод для получения размера списка
    size_t getSize() const { return data->size(); }

    // Метод для добавления элемента в конец списка
    void push_back(const T& value) {
        data->push_back(value);
    }

    // Метод для доступа к элементам списка по индексу
    T& at(size_t index) {
        try {
            if (index >= getSize()) throw std::out_of_range("Индекс вне дипазона (ПРОГРАММА IS DEATH)");
            auto it = std::next(data->begin(), index);
            return *it;
        }
        catch (const std::out_of_range& e) {
            HaveAProblems::handleIndexOutOfRange();
            throw;
        }
    }

    const T& at(size_t index) const {
        try {
            if (index >= getSize()) throw std::out_of_range("Индекс вне диапазона (ПРОГРАММА IS DEATH)");
            auto it = std::next(data->begin(), index);
            return *it;
        }
        catch (const std::out_of_range& e) {
            HaveAProblems::handleIndexOutOfRange();
            throw;
        }
    }
};

#endif // DYNAMICLIST_H
