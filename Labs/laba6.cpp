#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Класс для работы с BMP-файлом
class Bitmap {
public:
	Bitmap(const string& filename) {
		ifstream file(filename, ios::binary);
		if (!file) {
			width = height = -1;
			return;
		}

		// Считывание заголовка BMP для получения ширины и высоты
		file.seekg(18);
		file.read((char*)&width, sizeof(width));
		file.read((char*)&height, sizeof(height));
		file.close();
	}

	int getWidth() const { return width; }
	int getHeight() const { return height; }

private:
	int width;
	int height;
};

// Класс-прокси для получения информации о размере изображения
class ImageProxy {
public:
	ImageProxy(const string& filename) : filename(filename), width(-1), height(-1) {
		extractSizeFromFilename();
	}

	int getWidth() {
		if (!isSizeExtracted) loadSizeFromBitmap();
		return width;
	}

	int getHeight() {
		if (!isSizeExtracted) loadSizeFromBitmap();
		return height;
	}

private:
	string filename;
	int width;
	int height;
	bool isSizeExtracted = false;

	void extractSizeFromFilename() {
		int underscorePos = -1;
		int xPos = -1;
		for (int i = filename.length() - 1; i >= 0; --i) {
			if (filename[i] == 'x') {
				xPos = i;
			}
			else if (filename[i] == '_') {
				underscorePos = i;
				break;
			}
		}

		if (underscorePos != -1 && xPos != -1 && xPos > underscorePos) {
			try {
				width = 0;
				for (int i = underscorePos + 1; i < xPos; ++i) {
					if (isdigit(filename[i])) {
						width = width * 10 + (filename[i] - '0');
					}
					else {
						throw invalid_argument("Недопустимый символ в ширине");
					}
				}

				height = 0;
				for (int i = xPos + 1; i < filename.length(); ++i) {
					if (isdigit(filename[i])) {
						height = height * 10 + (filename[i] - '0');
					}
					else {
						throw invalid_argument("Недопустимый символ в высоте");
					}
				}

				isSizeExtracted = true;
			}
			catch (...) {
				isSizeExtracted = false;
			}
		}
	}

	void loadSizeFromBitmap() {
		Bitmap bmp(filename);
		width = bmp.getWidth();
		height = bmp.getHeight();
		isSizeExtracted = true;
	}
};

// Пример использования
int main() {
	setlocale(LC_ALL);
	ImageProxy image1("vasya_1024x768.bmp");
	cout << "vasya_1024x768.bmp: " << image1.getWidth() << "x" << image1.getHeight() << endl;

	ImageProxy image2("kolya_300x30");
	cout << "kolya_300x30: " << image2.getWidth() << "x" << image2.getHeight() << endl;

	ImageProxy image4("kostya_1600x800");
	cout << "kostya_1600x800: " << image4.getWidth() << "x" << image4.getHeight() << endl;

	ImageProxy image3("petya_200xmax.bmp");
	cout << "petya_200xmax.bmp: " << image3.getWidth() << "x" << image3.getHeight() << endl;

	return 0;
}
