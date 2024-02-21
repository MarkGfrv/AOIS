#include<iostream>
#include"../Project9/Header.h"
int main() {
	setlocale(LC_ALL, "Russian");
	int choice;
	int Numberr1 = 13, Numberr2 = 21, Numberr3, Numberr4;
	Numberr3 = -Numberr1;
	Numberr4 = -Numberr2;

	vector<int> BinaryNumber = convertStraight(Numberr1);
	cout << "Двоичное представления числа " << Numberr1 << " прямым кодом:" << endl;
	printBinary(BinaryNumber);
	cout << endl;
	vector<int> BinaryNumber2 = convertInverse(Numberr1);
	cout << "Двоичное представления числа " << Numberr1 << " обратным кодом:" << endl;
	printBinary(BinaryNumber2);
	cout << endl;
	vector<int> BinaryNumber3 = convertDop(Numberr1);
	cout << "Двоичное представления числа " << Numberr1 << " дополнительным кодом:" << endl;
	printBinary(BinaryNumber3);
	cout << endl;

	vector<int> BinaryNumber4 = convertStraight(Numberr2);
	cout << "Двоичное представления числа " << Numberr2 << " прямым кодом:" << endl;
	printBinary(BinaryNumber4);
	cout << endl;
	vector<int> BinaryNumber5 = convertInverse(Numberr2);
	cout << "Двоичное представления числа " << Numberr2 << " обратным кодом:" << endl;
	printBinary(BinaryNumber5);
	cout << endl;
	vector<int> BinaryNumber6 = convertDop(Numberr2);
	cout << "Двоичное представления числа " << Numberr2 << " дополнительным кодом:" << endl;
	printBinary(BinaryNumber6);
	cout << endl;

	vector<int> BinaryNumber7 = convertStraight(Numberr3);
	cout << "Двоичное представления числа " << Numberr3 << " прямым кодом:" << endl;
	printBinary(BinaryNumber7);
	cout << endl;
	vector<int> BinaryNumber8 = convertInverse(Numberr3);
	cout << "Двоичное представления числа " << Numberr3 << " обратным кодом:" << endl;
	printBinary(BinaryNumber8);
	cout << endl;
	vector<int> BinaryNumber9 = convertDop(Numberr3);
	cout << "Двоичное представления числа " << Numberr3 << " дополнительным кодом:" << endl;
	printBinary(BinaryNumber9);
	cout << endl;

	vector<int> BinaryNumber10 = convertStraight(Numberr4);
	cout << "Двоичное представления числа " << Numberr4 << " прямым кодом:" << endl;
	printBinary(BinaryNumber10);
	cout << endl;
	vector<int> BinaryNumber11 = convertInverse(Numberr4);
	cout << "Двоичное представления числа " << Numberr4 << " обратным кодом:" << endl;
	printBinary(BinaryNumber11);
	cout << endl;
	vector<int> BinaryNumber12 = convertDop(Numberr4);
	cout << "Двоичное представления числа " << Numberr4 << " дополнительным кодом:" << endl;
	printBinary(BinaryNumber12);
	cout << endl;

	vector<int> sum1 = addition(BinaryNumber3, BinaryNumber6);
	vector<int> sum2 = addition(BinaryNumber3, BinaryNumber12);
	vector<int> sum3 = addition(BinaryNumber9, BinaryNumber6);
	vector<int> sum4 = addition(BinaryNumber9, BinaryNumber12);
	vector<int> diff1 = substraction(BinaryNumber3, BinaryNumber6);
	vector<int> diff2 = substraction(BinaryNumber3, BinaryNumber12);
	vector<int> diff3 = substraction(BinaryNumber9, BinaryNumber6);
	vector<int> diff4 = substraction(BinaryNumber9, BinaryNumber12);
	vector<int> mult = multiplication(BinaryNumber, BinaryNumber4);
	int product_sign = mult.front();
	vector<int> mult4 = multiplication(BinaryNumber, BinaryNumber10);
	int product_sign4 = mult4.front();
	vector<int> mult7 = multiplication(BinaryNumber7, BinaryNumber4);
	int product_sign7 = mult7.front();
	vector<int> mult10 = multiplication(BinaryNumber, BinaryNumber4);
	int product_sign10 = mult10.front();
	int precision = 5;
	vector<int> quotient_binary = divideBinary(BinaryNumber3, BinaryNumber6, precision);
	vector<int> quotient_binary2 = divideBinary(BinaryNumber3, BinaryNumber12, precision);
	vector<int> quotient_binary3 = divideBinary(BinaryNumber7, BinaryNumber4, precision);
	vector<int> quotient_binary4 = divideBinary(BinaryNumber7, BinaryNumber10, precision);
	double num1 = 4.625;
	double num2 = 3.5;
	pair<vector<int>, vector<int>> binaryy1 = doubleToBinary(num1);
	pair<vector<int>, vector<int>> binaryy2 = doubleToBinary(num2);
	vector<int> summ1 = addBinary(binaryy1.first, binaryy1.second, binaryy2.first, binaryy2.second, binaryy1.second.size(), binaryy2.second.size());
	int pointPos1 = binaryy1.second.size() > binaryy2.second.size() ? binaryy1.second.size() : binaryy2.second.size();
	int pos1 = summ1.size() - pointPos1 - 1;

	do {
		std::cout << "1. Сумма чисел\n"
			<< "2. Разность чисел\n"
			<< "3. Произведение чисел\n"
			<< "4. Деление чисел\n"
			<< "5. Сумма чисел с плавающей точкой\n"
			<< "6. Завершение программы\n"
			<< "Ваш выбор: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Сумма в двоичной системе счисления(дополнительный код) " << Numberr1 << " и " << Numberr2 << " равна: " << endl;
			printBinary(sum1);
			cout << endl;

			cout << "Сумма в двоичной системе счисления(дополнительный код) чисел " << Numberr1 << " и " << Numberr4 << " равна: " << endl;
			printBinary(sum2);
			cout << endl;

			cout << "Сумма в двоичной системе счисления(дополнительный код) чисел " << Numberr3 << " и " << Numberr2 << " равна: " << endl;
			printBinary(sum3);
			cout << endl;

			cout << "Сумма в двоичной системе счисления(дополнительный код) чисел " << Numberr3 << " и " << Numberr4 << " равна: " << endl;
			printBinary(sum4);
			cout << endl;
			break;

		case 2:
			cout << "Разность в двоичной системе счисления(дополнительный код) чисел " << Numberr1 << " и " << Numberr2 << " равна: " << endl;
			printBinary(diff1);
			cout << endl;

			cout << "Разность в двоичной системе счисления(дополнительный код) чисел " << Numberr1 << " и " << Numberr4 << " равна: " << endl;
			printBinary(diff2);
			cout << endl;

			cout << "Разность в двоичной системе счисления(дополнительный код) чисел " << Numberr3 << " и " << Numberr2 << " равна: " << endl;
			printBinary(diff3);
			cout << endl;

			cout << "Разность в двоичной системе счисления(дополнительный код) чисел " << Numberr3 << " и " << Numberr4 << " равна: " << endl;
			printBinary(diff4);
			cout << endl;
			break;

		case 3:
			cout << "Произведение в двоичной системе счисления(прямой код) чисел " << Numberr1 << " и " << Numberr2 << " равна: " << endl;
			printBinary(mult);
			cout << endl;
			cout << "Знак произведения: " << product_sign << endl;

			cout << "Произведение в двоичной системе счисления(прямой код) чисел " << Numberr1 << " и " << Numberr4 << " равна: " << endl;
			printBinary(mult4);
			cout << endl;
			cout << "Знак произведения: " << product_sign4 << endl;


			cout << "Произведение в двоичной системе счисления(прямой код) чисел " << Numberr3 << " и " << Numberr2 << " равна: " << endl;
			printBinary(mult7);
			cout << endl;
			cout << "Знак произведения: " << product_sign7 << endl;

			cout << "Произведение в двоичной системе счисления(прямой код) чисел " << Numberr3 << " и " << Numberr4 << " равна: " << endl;
			printBinary(mult10);
			cout << endl;
			cout << "Знак произведения: " << product_sign10 << endl;
			break;


		case 4:

			cout << "Результат деления чисел  " << Numberr1 << " и " << Numberr2 << " : " << endl;
			for (size_t i = 0; i < quotient_binary.size(); ++i) {
				cout << quotient_binary[i];
			}
			cout << endl;


			cout << "Результат деления чисел  " << Numberr1 << " и " << Numberr4 << " : " << endl;
			for (size_t i = 0; i < quotient_binary2.size(); ++i) {
				cout << quotient_binary2[i];
			}
			cout << endl;


			cout << "Результат деления чисел  " << Numberr3 << " и " << Numberr2 << " : " << endl;
			for (size_t i = 0; i < quotient_binary3.size(); ++i) {
				cout << quotient_binary3[i];
			}
			cout << endl;


			cout << "Результат деления чисел  " << Numberr3 << " и " << Numberr4 << " : " << endl;
			for (size_t i = 0; i < quotient_binary4.size(); ++i) {
				cout << quotient_binary4[i];
			}
			cout << endl;
			break;


		case 5:

			cout << "Числа " << num1 << " ; " << num2 << " в двоичной системе : \n";
			printBinary(binaryy1.first);
			cout << ".";
			printBinary(binaryy1.second);
			cout << endl;
			printBinary(binaryy2.first);
			cout << ".";
			printBinary(binaryy2.second);
			cout << endl;

			cout << "Сумма чисел " << num1 << " и " << num2 << " в двоичной системе: " << endl;
			for (int i = 0; i < summ1.size(); ++i) {
				if (i == pos1)
					cout << ".";
				cout << summ1[i];
			}
			cout << endl;
			break;
		case 6:
			std::cout << "Завершение программы.\n";
			break;
		default:
			std::cout << "Неверный ввод. Попробуйте снова.\n";
		}
	} while (choice != 6);
	return 0;
}
