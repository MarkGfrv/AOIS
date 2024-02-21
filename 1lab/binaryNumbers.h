#pragma once
#include<iostream>
#include<vector>
#include<cmath>
#include<iomanip>
#include<algorithm>
#include<string>
using namespace std;
vector<int> convertStraight(int Number);
vector<int> convertInverse(int Number);
vector<int> convertDop(int Number);
vector<int> addition(const vector<int>& a, const vector<int>& b);
vector<int> substraction(const vector<int>& a, const vector<int>& b);
vector<int> complement(const vector<int>& a);
vector<int> increment(const vector<int>& a);
int getSign(const vector<int>& a);
vector<int> multiplication(const vector<int>& a, const vector<int>& b);
vector<int> divideBinary(vector<int> dividend, vector<int> divisor, int precision);
void printBinary(const vector<int>& binary);
vector<int> addBinary(const vector<int>& aInt, const vector<int>& aFrac, const vector<int>& bInt, const vector<int>& bFrac, int aFracSize, int bFracSize);
pair<vector<int>, vector<int>> doubleToBinary(double number);
