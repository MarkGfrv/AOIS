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
	for (int i = firstNumber.size() - 1; i >= 0; --i) {
		int sum = firstNumber[i] + secondNumber[i] + carry;
		result.insert(result.begin(), sum % 2);
		carry = sum / 2;
	}
	if (carry > 0) {
		result.insert(result.begin(), carry);
	}
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
void printBinaryy2(const vector<int>& binary) {
	for (int bit : binary) {
		cout << bit;
	}
}
vector<int> addBinary(const vector<int>& aInt, const vector<int>& aFrac, const vector<int>& bInt, const vector<int>& bFrac, int aFracSize, int bFracSize) {
	vector<int> result;
	int carry = 0;
	int maxSizeFrac = max(aFracSize, bFracSize);
	vector<int> tempAFrac(maxSizeFrac, 0);
	vector<int> tempBFrac(maxSizeFrac, 0);
	for (int i = aFrac.size() - 1, j = maxSizeFrac - 1; i >= 0; --i, --j) {
		tempAFrac[j] = aFrac[i];
	}
	for (int i = bFrac.size() - 1, j = maxSizeFrac - 1; i >= 0; --i, --j) {
		tempBFrac[j] = bFrac[i];
	}
	for (int i = maxSizeFrac - 1; i >= 0; --i) {
		int sum = tempAFrac[i] + tempBFrac[i] + carry;
		result.insert(result.begin(), sum % 2);
		carry = sum / 2;
	}
	int maxSizeInt = max(aInt.size(), bInt.size()) + 1; 
	vector<int> tempAInt(maxSizeInt, 0);
	vector<int> tempBInt(maxSizeInt, 0);
	for (int i = aInt.size() - 1, j = maxSizeInt - 1; i >= 0; --i, --j) {
		tempAInt[j] = aInt[i];
	}
	for (int i = bInt.size() - 1, j = maxSizeInt - 1; i >= 0; --i, --j) {
		tempBInt[j] = bInt[i];
	}
	for (int i = maxSizeInt - 1; i >= 0; --i) {
		int sum = tempAInt[i] + tempBInt[i] + carry;
		result.insert(result.begin(), sum % 2);
		carry = sum / 2;
	}
	if (carry) {
		result.insert(result.begin(), carry);
	}
	int pointPos = aFracSize > bFracSize ? aFracSize : bFracSize;
	result.insert(result.end() - pointPos, 1);

	return result;
}
pair<vector<int>, vector<int>> doubleToBinary(double number) {
	int intPart = static_cast<int>(number);
	double fracPart = number - intPart;
	vector<int> intBinary;
	vector<int> fracBinary;
	while (intPart > 0) {
		intBinary.insert(intBinary.begin(), intPart % 2);
		intPart /= 2;
	}
	int precision = 3; 
	for (int i = 0; i < precision; ++i) {
		fracPart *= 2;
		int digit = static_cast<int>(fracPart);
		fracBinary.push_back(digit);
		fracPart -= digit;
	}
	return make_pair(intBinary, fracBinary);
}


void printBinaryy(const vector<int>& binary) {
	bool isFractionalPart = false;
	int fractionDigits = 0;
	int pointIndex = -1;
	for (int i = 0; i < binary.size(); ++i) {
		if (binary[i] == -1) {
			pointIndex = i;
			break;
		}
	}

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
