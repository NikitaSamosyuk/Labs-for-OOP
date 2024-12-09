#ifndef HAVEAPROBLEMS_H
#define HAVEAPROBLEMS_H

#include <stdexcept>
#include <string>
#include <iostream>

class HaveAProblems {
public:
	static void handle(const std::exception& e) {
		std::cerr << "Исключение: " << e.what() << std::endl;
	}

	static void handleIndexOutOfRange() {
		std::cerr << "Исключение: Индекс вне диапазона (ПРОГРАММА IS DEATH)" << std::endl;
	}
};

#endif // HAVEAPROBLEMS_H
