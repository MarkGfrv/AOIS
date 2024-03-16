#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include<stack>
#include<unordered_map>

using namespace std;

void negationn(stack<bool>& operandStack);
void con(stack<bool>& operandStack);
void dis(stack<bool>& operandStack);
void implic(stack<bool>& operandStack);
void equiv(stack<bool>& operandStack);
bool evaluateLogicalExpression(const vector<bool>& variables, const string& expression);
int countVariables(const string& expression);
void solveLogicalExpression(const string& expression);
void printVariables(int numVariables);
void printTruthTable(const vector<bool>& variables, bool result);
void calculateSknfAndSdnf(const vector<bool>& variables, bool result, int rowNumber, const int numVariables, vector<string>& sknfClauses,
vector<string>& sdnfClauses, vector<int>& sknfNumbers, vector<int>& sdnfNumbers);
