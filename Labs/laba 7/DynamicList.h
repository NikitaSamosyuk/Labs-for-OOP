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
	size_t getSize() const {
		return data->size();
	}

	// ����� ��� ���������� �������� � ����� ������
	void push_back(const T& value) {
		data->push_back(value);
	}

	// ����� ��� ������� � ��������� ������ �� �������
	T& at(size_t index) {
		if (index >= getSize()) {
			throw CustomException("������ ��� ��������� (��������� IS DEATH)");
		}
		auto it = std::next(data->begin(), index);
		return *it;
	}

	const T& at(size_t index) const {
		if (index >= getSize()) {
			throw CustomException("������ ��� ��������� (��������� IS DEATH)");
		}
		auto it = std::next(data->begin(), index);
		return *it;
	}

	// �������� ��� ������������� ���������
	class PositiveIterator {
	public:
		PositiveIterator(typename std::list<T>::iterator begin, typename std::list<T>::iterator end)
			: current(begin), end(end) {
			// ������������� ����������+
			while (current != end && *current <= 0) {
				++current;
			}
		}

		bool hasNext() const {
			return current != end;
		}

		T& next() {
			if (current == end) {
				throw CustomException("������������� ������ �������...");
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

	// �������� ��� ������������� ���������
	class NegativeIterator {
	public:
		NegativeIterator(typename std::list<T>::iterator begin, typename std::list<T>::iterator end)
			: current(begin), end(end) {
			// ������������� ����������-
			while (current != end && *current >= 0) {
				++current;
			}
		}

		bool hasNext() const {
			return current != end;
		}

		T& next() {
			if (current == end) {
				throw CustomException("������������� ������ �������...");
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
