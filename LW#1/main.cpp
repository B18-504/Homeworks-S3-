// interface.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define green 2
#define white 15
#define red 4

#include <iostream>
#include <windows.h>
#include <conio.h>
#include "arraySequence.cpp"
#include "listSequence.cpp"
#include "Sorts.h"
#include "Test.h"

int __marked = 0;
bool __inputType = true; //True - ввод с клавиатуры, false - автоматический ввод
bool __showTime = false; //True - показываем время работы, false - не показываем время работы
bool __showResult = true; //Показывть результат сортировки
const std::string __nameOfinputType[2] = {"автоматический ввод", "ввод с клавиатуры" };
const std::string __yesNo[2] = {"нет", "да"};
const std::string __title = "Menu:";
const std::string __menu[8] = { "quickSort", "heapSort", "binSort", "Тип ввода: ", "Выводить время исполнения алгоритма: ", "Выводить результат сортировки: ", "Сравнить время исполнения алгоритмов", "Провести автоматические тесты"};
const int __len = 8;
const int __positionOfQuickSort = 0;
const int __positionOfHeapSort = 1;
const int __positionBinSort = 2;
const int __positionOfInputType = 3;
const int __positionOfShowTime = 4;
const int __positionOfShowResult = 5;
const int __positionOfEqual = 6;
const int __positionOfAutoTest = 7;

void SetColor(int text) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, text);
}

void printScreen() {
	system("cls");
	std::cout << __title << '\n';
	for (int i = 0; i < __len; i++) {
		if (i == __marked) SetColor(green);
		std::cout << i + 1 << ". " << __menu[i];
		if (i == __positionOfInputType) std::cout << __nameOfinputType[__inputType];
		if (i == __positionOfShowTime) std::cout << __yesNo[__showTime];
		if (i == __positionOfShowResult) std::cout << __yesNo[__showResult];
		std::cout << '\n';
		if (i == __marked) SetColor(white);
	}
	std::cout << "\nДля выхода нажмите ESC\n";
}

template<typename T>
void test(Sequence<T>* (*function)(Sequence<T>*, bool (*comp)(T, T))) {
	arraySequence<T>* sequence = new arraySequence<T>;
	system("cls");
	SetColor(green);
	std::cout << "Число элементов: ";
	SetColor(white);
	int n;
	std::cin >> n;
	
	if (__inputType) {
		T item;
		
		for (int i = 0; i < n; i++) {
			std::cin >> item;
			sequence->Append(item);
		}
	}
	else {
		srand(clock());
		for (int i = 0; i < n; i++) {
			sequence->Append(rand()/1000);
		}
	}

	SetColor(green);
	std::cout << "Исходная последовательность: ";
	SetColor(white);

	for (int i = 0; i < n; i++) {
		std::cout << sequence->get(i) << " ";
	}
	std::cout << "\n\n";

	unsigned int startTime = clock();

	Sequence<T>* result = function(sequence, comp);

	unsigned int stopTime = clock();
	if (__showResult) {
		SetColor(green);
		std::cout << "Отсортированная последовательность: ";
		SetColor(white);

		for (int i = 0; i < n; i++) {
			std::cout << result->get(i) << " ";
		}
		std::cout << "\n\n";
	}

	if (__showTime) std::cout << "Время исполнения алгоритма: " << stopTime - startTime << "ms\n\n";

	std::cout << "\nДля возврата к меню нажмите ESC\n";
	while (_getch() != 27);
	system("cls");
}

template<typename T>
void equal() {
	arraySequence<T>* sequence = new arraySequence<T>;
	system("cls");
	SetColor(green);
	std::cout << "Число элементов: ";
	SetColor(white);
	int n;
	std::cin >> n;

	if (__inputType) {
		T item;

		for (int i = 0; i < n; i++) {
			std::cin >> item;
			sequence->Append(item);
		}
	}
	else {
		srand(clock());
		for (int i = 0; i < n; i++) {
			sequence->Append(rand() / 1000);
		}
	}

	SetColor(green);
	std::cout << "Исходная последовательность: ";
	SetColor(white);

	for (int i = 0; i < n; i++) {
		std::cout << sequence->get(i) << " ";
	}
	std::cout << "\n\n";

	unsigned int startTime, stopTime;

	startTime = clock();
	quickSort(sequence, comp);
	stopTime = clock();
	std::cout << "Время исполнения алгоритма quickSort: " << stopTime - startTime << "ms\n";

	startTime = clock();
	heapSort(sequence, comp);
	stopTime = clock();
	std::cout << "Время исполнения алгоритма heapSort: " << stopTime - startTime << "ms\n";
	
	startTime = clock();
	binSort(sequence, comp);
	stopTime = clock();
	std::cout << "Время исполнения алгоритма binSort: " << stopTime - startTime << "ms\n";

	std::cout << "\nДля возврата к меню нажмите ESC\n";
	while (_getch() != 27);
	system("cls");
}

void readKey() {
	while (true) {
		printScreen();

		switch (_getch())
		{

		case 224:
			switch (_getch())
			{
			case 72:
				if (__marked > 0) __marked--;
				break;
			case 80:
				if (__marked < __len - 1) __marked++;
			case 75:
				if (__marked == __positionOfInputType) __inputType = !__inputType;
				if (__marked == __positionOfShowTime) __showTime = !__showTime;
				if (__marked == __positionOfShowResult) __showResult = !__showResult;
			case 77:
				if (__marked == __positionOfInputType) __inputType = !__inputType;
				if (__marked == __positionOfShowTime) __showTime = !__showTime;
				if (__marked == __positionOfShowResult) __showResult = !__showResult;
			default:
				break;
			}
			break;

		case 13:
			switch (__marked)
			{
			case __positionOfQuickSort:
				test(quickSort<int>);
				break;
			case __positionOfHeapSort:
				test(heapSort<int>);
				break;
			case __positionBinSort:
				test(binSort<int>);
				break;
			case __positionOfEqual:
				equal<int>();
				break;
			case __positionOfAutoTest:
				system("cls");
				test();
				std::cout << "\nДля возврата к меню нажмите ESC\n";
				while (_getch() != 27);
				break;
			default:
				break;
			}
			break;

		case 27:
			return;

		default:
			break;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	readKey();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
