#include<iostream>
#include"../Project8/Header.h"
int main() {
	setlocale(LC_ALL, "Russian");
	int choice;
	int Numberr1 = 13, Numberr2 = 21, Numberr3, Numberr4;
	Numberr3 = -Numberr1;
	Numberr4 = -Numberr2;

	vector<int> BinaryNumber = convert_straight(Numberr1);
	cout << "Двоичное представления числа " << Numberr1 << " прямым кодом:" << endl;
	printBinary(BinaryNumber);
	vector<int> BinaryNumber2 = convert_inverse(Numberr1);
	cout << "Двоичное представления числа " << Numberr1 << " обратным кодом:" << endl;
	printBinary(BinaryNumber2);
	vector<int> BinaryNumber3 = convert_dop(Numberr1);
	cout << "Двоичное представления числа " << Numberr1 << " дополнительным кодом:" << endl;
	printBinary(BinaryNumber3);

	vector<int> BinaryNumber4 = convert_straight(Numberr2);
	cout << "Двоичное представления числа " << Numberr2 << " прямым кодом:" << endl;
	printBinary(BinaryNumber4);
	vector<int> BinaryNumber5 = convert_inverse(Numberr2);
	cout << "Двоичное представления числа " << Numberr2 << " обратным кодом:" << endl;
	printBinary(BinaryNumber5);
	vector<int> BinaryNumber6 = convert_dop(Numberr2);
	cout << "Двоичное представления числа " << Numberr2 << " дополнительным кодом:" << endl;
	printBinary(BinaryNumber6);

	vector<int> BinaryNumber7 = convert_straight(Numberr3);
	cout << "Двоичное представления числа " << Numberr3 << " прямым кодом:" << endl;
	printBinary(BinaryNumber7);
	vector<int> BinaryNumber8 = convert_inverse(Numberr3);
	cout << "Двоичное представления числа " << Numberr3 << " обратным кодом:" << endl;
	printBinary(BinaryNumber8);
	vector<int> BinaryNumber9 = convert_dop(Numberr3);
	cout << "Двоичное представления числа " << Numberr3 << " дополнительным кодом:" << endl;
	printBinary(BinaryNumber9);

	vector<int> BinaryNumber10 = convert_straight(Numberr4);
	cout << "Двоичное представления числа " << Numberr4 << " прямым кодом:" << endl;
	printBinary(BinaryNumber10);
	vector<int> BinaryNumber11 = convert_inverse(Numberr4);
	cout << "Двоичное представления числа " << Numberr4 << " обратным кодом:" << endl;
	printBinary(BinaryNumber11);
	vector<int> BinaryNumber12 = convert_dop(Numberr4);
	cout << "Двоичное представления числа " << Numberr4 << " дополнительным кодом:" << endl;
	printBinary(BinaryNumber12);

	vector<int> sum = addition(BinaryNumber, BinaryNumber4);
	vector<int> sum2 = addition(BinaryNumber2, BinaryNumber5);
	vector<int> sum3 = addition(BinaryNumber3, BinaryNumber6);
	vector<int> sum4 = addition(BinaryNumber, BinaryNumber10);
	vector<int> sum5 = addition(BinaryNumber2, BinaryNumber11);
	vector<int> sum6 = addition(BinaryNumber3, BinaryNumber12);
	vector<int> sum7 = addition(BinaryNumber7, BinaryNumber4);
	vector<int> sum8 = addition(BinaryNumber8, BinaryNumber5);
	vector<int> sum9 = addition(BinaryNumber9, BinaryNumber6);
	vector<int> sum10 = addition(BinaryNumber7, BinaryNumber10);
	vector<int> sum11 = addition(BinaryNumber8, BinaryNumber11);
	vector<int> sum12 = addition(BinaryNumber9, BinaryNumber12);
	vector<int> diff = substraction(BinaryNumber, BinaryNumber4);
	vector<int> diff2 = substraction(BinaryNumber2, BinaryNumber5);
	vector<int> diff3 = substraction(BinaryNumber3, BinaryNumber6);
	vector<int> diff4 = substraction(BinaryNumber, BinaryNumber10);
	vector<int> diff5 = substraction(BinaryNumber2, BinaryNumber11);
	vector<int> diff6 = substraction(BinaryNumber3, BinaryNumber12);
	vector<int> diff7 = substraction(BinaryNumber7, BinaryNumber4);
	vector<int> diff8 = substraction(BinaryNumber8, BinaryNumber5);
	vector<int> diff9 = substraction(BinaryNumber9, BinaryNumber6);
	vector<int> diff10 = substraction(BinaryNumber7, BinaryNumber10);
	vector<int> diff11 = substraction(BinaryNumber8, BinaryNumber11);
	vector<int> diff12 = substraction(BinaryNumber9, BinaryNumber12);
	vector<int> mult = multiplication(BinaryNumber, BinaryNumber4);
	vector<int> mult2 = multiplication(BinaryNumber2, BinaryNumber5);
	vector<int> mult3 = multiplication(BinaryNumber3, BinaryNumber6);
	int product_sign = mult.front();
	int product_sign2 = mult2.front();
	int product_sign3 = mult3.front();
	vector<int> mult4 = multiplication(BinaryNumber, BinaryNumber10);
	int product_sign4 = mult4.front();
	vector<int> mult5 = multiplication(BinaryNumber2, BinaryNumber11);
	int product_sign5 = mult5.front();
	vector<int> mult6 = multiplication(BinaryNumber3, BinaryNumber12);
	int product_sign6 = mult6.front();
	vector<int> mult7 = multiplication(BinaryNumber7, BinaryNumber4);
	int product_sign7 = mult7.front();
	vector<int> mult8 = multiplication(BinaryNumber8, BinaryNumber5);
	int product_sign8 = mult8.front();
	vector<int> mult9 = multiplication(BinaryNumber9, BinaryNumber6);
	int product_sign9 = mult9.front();
	vector<int> mult10 = multiplication(BinaryNumber, BinaryNumber4);
	int product_sign10 = mult10.front();
	vector<int> mult11 = multiplication(BinaryNumber2, BinaryNumber5);
	int product_sign11 = mult11.front();
	vector<int> mult12 = multiplication(BinaryNumber3, BinaryNumber6);
	int product_sign12 = mult12.front();
	int precision = 5;
	vector<int> quotient_binary = divide_binary(BinaryNumber3, BinaryNumber6, precision);
	vector<int> quotient_binary2 = divide_binary(BinaryNumber3, BinaryNumber12, precision);
	vector<int> quotient_binary3 = divide_binary(BinaryNumber7, BinaryNumber4, precision);
	vector<int> quotient_binary4 = divide_binary(BinaryNumber7, BinaryNumber10, precision);
	double num1 = 13.100;
	double num2 = 21.101;
	double num3 = -num1, num4 = -num2;
	vector<double> numbers1 = { num1, num2 };
	vector<double> numbers2 = { num1, num4 };
	vector<double> numbers3 = { num3, num2 };
	vector<double> numbers4 = { num3, num4 };
	vector<double> numbers5 = { num1, num2, num3, num4 };
	vector<int> summ = sumOfBinaryNumbers(numbers1);
	vector<int> summ1 = sumOfBinaryNumbers(numbers2);
	vector<int> summ2 = sumOfBinaryNumbers(numbers3);
	vector<int> summ3 = sumOfBinaryNumbers(numbers4);


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
			cout << "Сумма в двоичной системе счисления(прямой код) чисел " << Numberr1 << " и " << Numberr2 << " равна: " << endl;
			printBinary(sum);
			cout << "Сумма в двоичной системе счисления(обратный код) чисел " << Numberr1 << " и " << Numberr2 << " равна: " << endl;
			printBinary(sum2);
			cout << "Сумма в двоичной системе счисления(дополнительный код) чисел " << Numberr1 << " и " << Numberr2 << " равна: " << endl;
			printBinary(sum3);

			cout << "Сумма в двоичной системе счисления(прямой код) чисел " << Numberr1 << " и " << Numberr4 << " равна: " << endl;
			printBinary(sum4);
			cout << "Сумма в двоичной системе счисления(обратный код) чисел " << Numberr1 << " и " << Numberr4 << " равна: " << endl;
			printBinary(sum5);
			cout << "Сумма в двоичной системе счисления(дополнительный код) чисел " << Numberr1 << " и " << Numberr4 << " равна: " << endl;
			printBinary(sum6);

			cout << "Сумма в двоичной системе счисления(прямой код) чисел " << Numberr3 << " и " << Numberr2 << " равна: " << endl;
			printBinary(sum7);
			cout << "Сумма в двоичной системе счисления(обратный код) чисел " << Numberr3 << " и " << Numberr2 << " равна: " << endl;
			printBinary(sum8);
			cout << "Сумма в двоичной системе счисления(дополнительный код) чисел " << Numberr3 << " и " << Numberr2 << " равна: " << endl;
			printBinary(sum9);

			cout << "Сумма в двоичной системе счисления(прямой код) чисел " << Numberr3 << " и " << Numberr4 << " равна: " << endl;
			printBinary(sum10);
			cout << "Сумма в двоичной системе счисления(обратный код) чисел " << Numberr3 << " и " << Numberr4 << " равна: " << endl;
			printBinary(sum11);
			cout << "Сумма в двоичной системе счисления(дополнительный код) чисел " << Numberr3 << " и " << Numberr4 << " равна: " << endl;
			printBinary(sum12);
			break;

		case 2:
			cout << "Разность в двоичной системе счисления(прямой код) чисел " << Numberr1 << " и " << Numberr2 << " равна: " << endl;
			printBinary(diff);
			cout << "Разность в двоичной системе счисления(обратный код) чисел " << Numberr1 << " и " << Numberr2 << " равна: " << endl;
			printBinary(diff2);
			cout << "Разность в двоичной системе счисления(дополнительный код) чисел " << Numberr1 << " и " << Numberr2 << " равна: " << endl;
			printBinary(diff3);

			cout << "Разность в двоичной системе счисления(прямой код) чисел " << Numberr1 << " и " << Numberr4 << " равна: " << endl;
			printBinary(diff4);
			cout << "Разность в двоичной системе счисления(обратный код) чисел " << Numberr1 << " и " << Numberr4 << " равна: " << endl;
			printBinary(diff5);
			cout << "Разность в двоичной системе счисления(дополнительный код) чисел " << Numberr1 << " и " << Numberr4 << " равна: " << endl;
			printBinary(diff6);

			cout << "Разность в двоичной системе счисления(прямой код) чисел " << Numberr3 << " и " << Numberr2 << " равна: " << endl;
			printBinary(diff7);
			cout << "Разность в двоичной системе счисления(обратный код) чисел " << Numberr3 << " и " << Numberr2 << " равна: " << endl;
			printBinary(diff8);
			cout << "Разность в двоичной системе счисления(дополнительный код) чисел " << Numberr3 << " и " << Numberr2 << " равна: " << endl;
			printBinary(diff9);

			cout << "Разность в двоичной системе счисления(прямой код) чисел " << Numberr3 << " и " << Numberr4 << " равна: " << endl;
			printBinary(diff10);
			cout << "Разность в двоичной системе счисления(обратный код) чисел " << Numberr3 << " и " << Numberr4 << " равна: " << endl;
			printBinary(diff11);
			cout << "Разность в двоичной системе счисления(дополнительный код) чисел " << Numberr3 << " и " << Numberr4 << " равна: " << endl;
			printBinary(diff12);
			break;

		case 3:
			cout << "Произведение в двоичной системе счисления(прямой код) чисел " << Numberr1 << " и " << Numberr2 << " равна: " << endl;
			printBinary(mult);
			cout << "Знак произведения: " << product_sign << endl;
			cout << "Произведение в двоичной системе счисления(обратный код) чисел " << Numberr1 << " и " << Numberr2 << " равна: " << endl;
			printBinary(mult2);
			cout << "Знак произведения: " << product_sign2 << endl;
			cout << "Произведение в двоичной системе счисления(дополнительный код) чисел " << Numberr1 << " и " << Numberr2 << " равна: " << endl;
			printBinary(mult3);
			cout << "Знак произведения: " << product_sign3 << endl;

			cout << "Произведение в двоичной системе счисления(прямой код) чисел " << Numberr1 << " и " << Numberr4 << " равна: " << endl;
			printBinary(mult4);
			cout << "Знак произведения: " << product_sign4 << endl;
			cout << "Произведение в двоичной системе счисления(обратный код) чисел " << Numberr1 << " и " << Numberr4 << " равна: " << endl;
			printBinary(mult5);
			cout << "Знак произведения: " << product_sign5 << endl;
			cout << "Произведение в двоичной системе счисления(дополнительный код) чисел " << Numberr1 << " и " << Numberr4 << " равна: " << endl;
			printBinary(mult6);
			cout << "Знак произведения: " << product_sign6 << endl;


			cout << "Произведение в двоичной системе счисления(прямой код) чисел " << Numberr3 << " и " << Numberr2 << " равна: " << endl;
			printBinary(mult7);
			cout << "Знак произведения: " << product_sign7 << endl;
			cout << "Произведение в двоичной системе счисления(обратный код) чисел " << Numberr3 << " и " << Numberr2 << " равна: " << endl;
			printBinary(mult8);
			cout << "Знак произведения: " << product_sign8 << endl;
			cout << "Произведение в двоичной системе счисления(дополнительный код) чисел " << Numberr3 << " и " << Numberr2 << " равна: " << endl;
			printBinary(mult9);
			cout << "Знак произведения: " << product_sign9 << endl;

			cout << "Произведение в двоичной системе счисления(прямой код) чисел " << Numberr3 << " и " << Numberr4 << " равна: " << endl;
			printBinary(mult10);
			cout << "Знак произведения: " << product_sign10 << endl;
			cout << "Произведение в двоичной системе счисления(обратный код) чисел " << Numberr3 << " и " << Numberr4 << " равна: " << endl;
			printBinary(mult11);
			cout << "Знак произведения: " << product_sign11 << endl;
			cout << "Произведение в двоичной системе счисления(дополнительный код) чисел " << Numberr3 << " и " << Numberr4 << " равна: " << endl;
			printBinary(mult12);
			cout << "Знак произведения: " << product_sign12 << endl;
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

			cout << "Числа " << num1 << " ; " << num2 << " ; " << num3 << " и " << num4 << " в двоичной системе : \n";
			for (double num : numbers5) {
				vector<int> binary = fractionalBinary(num);
				printBinaryy(binary);
			}

			cout << "Сумма чисел: " << num1 << " и " << num2 << endl;
			printBinaryy(summ);

			cout << "Сумма чисел: " << num1 << " и " << num4 << endl;
			printBinaryy(summ1);

			cout << "Сумма чисел: " << num2 << " и " << num3 << endl;
			printBinaryy(summ2);

			cout << "Сумма чисел: " << num4 << " и " << num3 << endl;
			printBinaryy(summ3);
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
