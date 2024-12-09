#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include <list>
#include <stdexcept>
#include <initializer_list>
#include "UPtr.h"
#include "HaveAProblems.h"

template<typename T> class DynamicList { // ���������� ������������ ������
private:
    UPtr<std::list<T>> data;

public:
    // ����������� 
    DynamicList() : data(new std::list<T>()) {}

    // ����������� �� initializer_list<T>
    DynamicList(std::initializer_list<T> list) : data(new std::list<T>(list)) {}

    // ����������� �����������
    DynamicList(const DynamicList& other) : data(new std::list<T>(*other.data)) {}

    // ���������� �������� ������������
    DynamicList& operator=(const DynamicList& other) {
        if (this != &other) {
            data.reset(new std::list<T>(*other.data));
        }
        return *this;
    }

    // ����������� �����������
    DynamicList(DynamicList&& other) : data(std::move(other.data)) {}

    // ������������ �������� ������������
    DynamicList& operator=(DynamicList&& other) {
        if (this != &other) {
            data = std::move(other.data);
        }
        return *this;
    }

    // ����� ��� ��������� ������� ������
    size_t getSize() const { return data->size(); }

    // ����� ��� ���������� �������� � ����� ������
    void push_back(const T& value) {
        data->push_back(value);
    }

    // ����� ��� ������� � ��������� ������ �� �������
    T& at(size_t index) {
        try {
            if (index >= getSize()) throw std::out_of_range("������ ��� �������� (��������� IS DEATH)");
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
            if (index >= getSize()) throw std::out_of_range("������ ��� ��������� (��������� IS DEATH)");
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
