#include<iostream>
#include"Header.h"
vector<int> convert_straight(int Number) {
	vector<int> binary;
	if (Number < 0) {
		binary.push_back(1);
		Number = -Number;
	}
	else {
		binary.push_back(0);
	}
	while (Number > 0) {
		int remain = Number % 2;
		binary.insert(binary.begin() + 1, remain);
		Number /= 2;
	}
	return binary;
}
vector<int> convert_inverse(int Number) {
	vector<int> binary = convert_straight(Number);
	if (binary[0] == 1 || binary[0] == 0) {
		for (size_t i = 1; i < binary.size(); ++i) {
			binary[i] = (binary[i] == 0) ? 1 : 0;
		}
	}
	return binary;
}
vector<int> convert_dop(int Number) {
	vector<int> binary = convert_inverse(Number);
	binary[0] = 1;
	int c = 1;
	for (int i = binary.size() - 1; i > 0; --i) {
		int sum = binary[i] + c;
		binary[i] = sum % 2;
		c = sum / 2;
		if (c == 0) {
			break;
		}
	}
	return binary;
}
vector<int> addition(const vector<int>& a, const vector<int>& b) {
	vector<int> result;
	int c = 0;
	for (int i = a.size() - 1; i >= 0; --i) {
		int sum = a[i] + b[i] + c;
		result.insert(result.begin(), sum % 2);
		c = sum / 2;
	}
	if (c > 0) {
		result.insert(result.begin(), c);
	}
	return result;
}
vector<int> substraction(const vector<int>& a, const vector<int>& b) {
	vector<int> result;
	int c = 0;
	for (int i = a.size() - 1; i >= 0; --i) {
		int diff = a[i] - b[i] - c;
		if (diff < 0) {
			diff += 2;
			c = 1;
		}
		else {
			c = 0;
		}
		result.insert(result.begin(), diff);
	}
	return result;
}
vector<int> complement(const vector<int>& a) {
	vector<int> result;
	for (int bit : a) {
		result.push_back(bit == 0 ? 1 : 0);
	}
	return result;
}
vector<int> increment(const vector<int>& a) {
	vector<int> result = a;
	int carry = 1;
	for (int i = a.size() - 1; i >= 0 && carry; --i) {
		result[i] += carry;
		carry = result[i] / 2;
		result[i] %= 2;
	}
	return result;
}
int getSign(const vector<int>& a) {
	return a.front();
}
vector<int> multiplication(const vector<int>& a, const vector<int>& b) {
	int size = a.size();
	vector<int> result(size * 2, 0);
	int sign_a = getSign(a);
	int sign_b = getSign(b);
	vector<int> a_abs = (sign_a == 1) ? increment(complement(a)) : a;
	vector<int> b_abs = (sign_b == 1) ? increment(complement(b)) : b;
	for (int i = 0; i < size; ++i) {
		if (b_abs[i] == 1) {
			vector<int> shiftedA = a_abs;
			for (int j = 0; j < size - 1 - i; ++j) {
				shiftedA.push_back(0);
			}
			for (int j = 0; j < shiftedA.size(); ++j) {
				result[i + j] += shiftedA[j];
				if (result[i + j] > 1) {
					result[i + j + 1] += result[i + j] / 2;
					result[i + j] %= 2;
				}
			}
		}
	}
	if ((sign_a == 1) != (sign_b == 1)) {
		return increment(complement(result));
	}
	int result_sign = (sign_a == sign_b) ? 0 : 1;
	result.insert(result.begin(), result_sign);
	return result;
}
vector<int> divide_binary(vector<int> dividend, vector<int> divisor, int precision) {
	vector<int> quotient;
	vector<int> remainder;
	remainder = dividend;

	for (int i = 0; i < precision; ++i) {
		int carry = 0;
		for (size_t j = 0; j < remainder.size(); ++j) {
			int temp = carry * 2 + remainder[j];
			remainder[j] = temp / 2;
			carry = temp % 2;
		}
		quotient.push_back(carry);
	}

	return quotient;
}
void printBinary(const vector<int>& binary) {
	for (int bit : binary) {
		cout << bit;
	}
	cout << endl;
}
vector<int> fractionalBinary(double num) {
	vector<int> binary;
	bool isNegative = (num < 0);
	if (isNegative)
		num = -num;

	binary.push_back(isNegative ? 1 : 0);

	int integerPart = static_cast<int>(num);
	double fractionalPart = num - integerPart;

	while (integerPart > 0) {
		binary.insert(binary.begin() + 1, integerPart % 2);
		integerPart /= 2;
	}

	binary.push_back(-1);

	int precision = 32;
	while (fractionalPart > 0 && precision--) {
		fractionalPart *= 2;
		binary.push_back(static_cast<int>(fractionalPart));
		fractionalPart -= static_cast<int>(fractionalPart);
	}

	return binary;
}


vector<int> sumOfBinaryNumbers(const vector<double>& numbers) {
	vector<int> sum(32, 0); 

	for (double num : numbers) {
		vector<int> binary = fractionalBinary(num);
		int carry = 0;
		for (int i = 31; i >= 0; --i) {
			int bitSum = sum[i] + binary[i] + carry;
			sum[i] = bitSum % 2;
			carry = bitSum / 2;
		}
	}

	return sum;
}


void printBinaryy(const vector<int>& binary) {
	bool isFractionalPart = false; 
	int fractionDigits = 0;

	for (int i = 0; i < binary.size(); ++i) {
		if (binary[i] == -1) {
			cout << ".";
			isFractionalPart = true;
		}
		else {
			cout << binary[i];
			if (isFractionalPart) {
				fractionDigits++;
				if (fractionDigits == 8) 
					break;
			}
		}
	}


	while (fractionDigits < 8) {
		cout << "0";
		fractionDigits++;
	}

	cout << endl;
}
