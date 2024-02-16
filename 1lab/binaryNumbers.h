#pragma once
#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<algorithm>
#include<string>
using namespace std;
vector<int> convert_straight(int Number);
vector<int> convert_inverse(int Number);
vector<int> convert_dop(int Number);
vector<int> addition(const vector<int>& a, const vector<int>& b);
vector<int> substraction(const vector<int>& a, const vector<int>& b);
vector<int> complement(const vector<int>& a);
vector<int> increment(const vector<int>& a);
int getSign(const vector<int>& a);
vector<int> multiplication(const vector<int>& a, const vector<int>& b);
vector<int> divide_binary(vector<int> dividend, vector<int> divisor, int precision);
void printBinary(const vector<int>& binary);
vector<int> fractionalBinary(double num);
vector<int> sumOfBinaryNumbers(const vector<double>& numbers);
void printBinaryy(const vector<int>& binary);
