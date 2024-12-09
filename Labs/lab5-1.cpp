#include <iostream>
#include <iomanip>

int main() {
	setlocale(LC_ALL, "RU");
	char VvedenSimv;
	std::cout << "Введите символы :" << std::endl;

	while (std::cin >> VvedenSimv) {
		// Преобразуем символ в нижний регистр, если это буква верхнего регистра
		if (VvedenSimv >= 'A' && VvedenSimv <= 'Z') {
			VvedenSimv = VvedenSimv + ('a' - 'A');
		}

		std::cout << "Символ: " << VvedenSimv
			<< ", Шестнадцатеричный код: " << std::hex << int(VvedenSimv)
			<< ", Восьмеричный код: " << std::oct << int(VvedenSimv)
			<< std::dec << std::endl;
	}

	return 0;
}
