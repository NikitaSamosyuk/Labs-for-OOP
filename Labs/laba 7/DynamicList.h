#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include <list>
#include <stdexcept>
#include <initializer_list>
#include "UPtr.h"
#include "HaveAProblems.h"
#include "customexception.h"

template<typename T>
class DynamicList {
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
	size_t getSize() const {
		return data->size();
	}

	// Метод для добавления элемента в конец списка
	void push_back(const T& value) {
		data->push_back(value);
	}

	// Метод для доступа к элементам списка по индексу
	T& at(size_t index) {
		if (index >= getSize()) {
			throw CustomException("Индекс вне диапазона (ПРОГРАММА IS DEATH)");
		}
		auto it = std::next(data->begin(), index);
		return *it;
	}

	const T& at(size_t index) const {
		if (index >= getSize()) {
			throw CustomException("Индекс вне диапазона (ПРОГРАММА IS DEATH)");
		}
		auto it = std::next(data->begin(), index);
		return *it;
	}

	// Итератор для положительных элементов
	class PositiveIterator {
	public:
		PositiveIterator(typename std::list<T>::iterator begin, typename std::list<T>::iterator end)
			: current(begin), end(end) {
			// Положительный ЭЛЕМЕНТТТТ+
			while (current != end && *current <= 0) {
				++current;
			}
		}

		bool hasNext() const {
			return current != end;
		}

		T& next() {
			if (current == end) {
				throw CustomException("Положительных больше нетуууу...");
			}
			T& value = *current;
			do {
				++current;
			} while (current != end && *current <= 0);
			return value;
		}

	private:
		typename std::list<T>::iterator current, end;
	};

	PositiveIterator positiveIterator() {
		return PositiveIterator(data->begin(), data->end());
	}

	// Итератор для отрицательных элементов
	class NegativeIterator {
	public:
		NegativeIterator(typename std::list<T>::iterator begin, typename std::list<T>::iterator end)
			: current(begin), end(end) {
			// Отрицательный ЭЛЕМЕНТТТТ-
			while (current != end && *current >= 0) {
				++current;
			}
		}

		bool hasNext() const {
			return current != end;
		}

		T& next() {
			if (current == end) {
				throw CustomException("Отрицательных больше нетуууу...");
			}
			T& value = *current;
			do {
				++current;
			} while (current != end && *current >= 0);
			return value;
		}

	private:
		typename std::list<T>::iterator current, end;
	};

	NegativeIterator negativeIterator() {
		return NegativeIterator(data->begin(), data->end());
	}
};

#endif // DYNAMICLIST_H
