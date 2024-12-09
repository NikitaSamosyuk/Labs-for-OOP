#include <iostream>
#include <fstream>
#include <cstdlib>

void createInputFile(const std::string& filename) {
	std::ofstream outFile(filename);
	if (!outFile) {
		std::cout << "Ошибка открытия файла для записи!" << std::endl;
		return;
	}

	int randomNumbers[100];
	for (int i = 0; i < 100; ++i) {
		randomNumbers[i] = std::rand() % 101 - 50;  // Диапазон (-50, 50);
		outFile << randomNumbers[i] << std::endl;
	}

	outFile.close();
}

void processFile(const std::string& inputFilename, const std::string& outputFilename) {
	std::ifstream inFile(inputFilename);
	if (!inFile) {
		std::cout << "Ошибка открытия входного файла!" << std::endl;
		return;
	}

	int numbers[100];
	int count = 0;
	int number;

	while (inFile >> number && count < 100) {
		numbers[count++] = number;
	}

	inFile.close();

	if (count == 0) {
		std::cout << "Входной файл пуст!" << std::endl;
		return;
	}

	int lastNumber = numbers[count - 1];

	std::ofstream outFile(outputFilename);
	if (!outFile) {
		std::cout << "Ошибка открытия файла для записи!" << std::endl;
		return;
	}

	for (int i = 0; i < count; ++i) {
		outFile << (numbers[i] + lastNumber) << std::endl;
	}

	outFile.close();
}

int main() {
	setlocale(LC_ALL, "RU");
	const std::string inputFilename = "input.txt";
	const std::string outputFilename = "output.txt";

	createInputFile(inputFilename);
	processFile(inputFilename, outputFilename);

	std::cout << "Programa всё! Проверьте файлы input.txt и output.txt." << std::endl;

	return 0;
}