#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include<stack>
#include<unordered_map>

using namespace std;

bool evaluateLogicalExpression(const vector<bool>& variables, const string& expression);
int countVariables(const string& expression);
void solveExpression(const string& expression);
