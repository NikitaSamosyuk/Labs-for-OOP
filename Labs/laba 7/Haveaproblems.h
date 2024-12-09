#ifndef HAVEAPROBLEMS_H
#define HAVEAPROBLEMS_H

#include <stdexcept>
#include <string>
#include <iostream>

class HaveAProblems {
public:
	static void handle(const std::exception& e) {
		std::cerr << "����������: " << e.what() << std::endl;
	}

	static void handleIndexOutOfRange() {
		std::cerr << "����������: ������ ��� ��������� (��������� IS DEATH)" << std::endl;
	}
};

#endif // HAVEAPROBLEMS_H
