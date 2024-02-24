#include<iostream>
#include"Header.h"
vector<int> convertStraight(int Number) {
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
vector<int> convertInverse(int Number) {
	vector<int> binary = convertStraight(Number);
	if (binary[0] == 0) {
		return binary;
	}
	else {
		if (binary[0] == 1 || binary[0] == 0) {
			for (size_t i = 1; i < binary.size(); ++i) {
				binary[i] = (binary[i] == 0) ? 1 : 0;
			}
		}
		return binary;
	}
}
vector<int> convertDop(int Number) {
	vector<int> binary = convertStraight(Number);
	if (binary[0] == 0) {
		return binary;
	}
	else {
		vector<int> binary = convertInverse(Number);
		binary[0] = 1;
		int carry = 1;
		for (int i = binary.size() - 1; i > 0; --i) {
			int sum = binary[i] + carry;
			binary[i] = sum % 2;
			carry = sum / 2;
			if (carry == 0) {
				break;
			}
		}
		return binary;
	}
}
vector<int> addition(const vector<int>& firstNumber, const vector<int>& secondNumber) {
	vector<int> result;
	int carry = 0;
	int maxLength = max(firstNumber.size(), secondNumber.size());

	for (int i = 0; i < maxLength; ++i) {
		int bit1 = (i < firstNumber.size()) ? firstNumber[firstNumber.size() - 1 - i] : 0;
		int bit2 = (i < secondNumber.size()) ? secondNumber[secondNumber.size() - 1 - i] : 0;
		int sum = bit1 + bit2 + carry;
		result.insert(result.begin(), sum % 2);
		carry = sum / 2;
	}
	if (carry)
		result.insert(result.begin(), carry);

	return result;
}
vector<int> substraction(const vector<int>& firstNumber, const vector<int>& secondNumber) {
	vector<int> result;
	int carry = 0;
	for (int i = firstNumber.size() - 1; i >= 0; --i) {
		int diff = firstNumber[i] - secondNumber[i] - carry;
		if (diff < 0) {
			diff += 2;
			carry = 1;
		}
		else {
			carry = 0;
		}
		result.insert(result.begin(), diff);
	}
	return result;
}
vector<int> complement(const vector<int>& firstNumber) {
	vector<int> result;
	for (int bit : firstNumber) {
		result.push_back(bit == 0 ? 1 : 0);
	}
	return result;
}
vector<int> increment(const vector<int>& firstNumber) {
	vector<int> result = firstNumber;
	int carry = 1;
	for (int i = firstNumber.size() - 1; i >= 0 && carry; --i) {
		result[i] += carry;
		carry = result[i] / 2;
		result[i] %= 2;
	}
	return result;
}
int getSign(const vector<int>& firstNumber) {
	return firstNumber.front();
}
vector<int> multiplication(const vector<int>& firstNumber, const vector<int>& secondNumber) {
	int size = firstNumber.size();
	vector<int> result(size * 2, 0);
	int sign_a = getSign(firstNumber);
	int sign_b = getSign(secondNumber);
	vector<int> a_abs = (sign_a == 1) ? increment(complement(firstNumber)) : firstNumber;
	vector<int> b_abs = (sign_b == 1) ? increment(complement(secondNumber)) : secondNumber;
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
vector<int> divideBinary(vector<int> dividend, vector<int> divisor, int precision) {
	vector<int> quotient;
	vector<int> remainder;
	remainder = dividend;
	for (int i = 0; i < precision; ++i) {
		int carry = 0;
		for (size_t j = 0; j < remainder.size(); ++j) {
			int source = carry * 2 + remainder[j];
			remainder[j] = source / 2;
			carry = source % 2;
		}
		quotient.push_back(carry);
	}
	return quotient;
}
void printBinary(const vector<int>& binary) {
	for (int bit : binary) {
		cout << bit;
	}
}
vector<int> addBinary(vector<int> num1, vector<int> num2) {
	vector<int> result(32, 0);
	int carry = 0;

	for (int i = 31; i >= 0; i--) {
		int bitSum = num1[i] + num2[i] + carry;
		result[i] = bitSum % 2;
		carry = bitSum / 2;
	}

	return result;
}
vector<int> doubleToBinary(double num) {
	vector<int> binary;
	int sign = (num >= 0) ? 0 : 1;
	num = fabs(num);
	int exponent = 0;

	if (num >= 1) {
		while (num >= 2) {
			num /= 2;
			exponent++;
		}
	}
	else {
		while (num < 1) {
			num *= 2;
			exponent--;
		}
	}
	exponent += 127; 
	double mantissa = num - 1.0;
	binary.push_back(sign);
	for (int i = 7; i >= 0; i--) {
		binary.push_back((exponent >> i) & 1);
	}
	for (int i = 0; i < 23; i++) {
		mantissa *= 2;
		if (mantissa >= 1) {
			binary.push_back(1);
			mantissa -= 1;
		}
		else {
			binary.push_back(0);
		}
	}
	return binary;
}


