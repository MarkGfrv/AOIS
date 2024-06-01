#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include<stack>
#include<unordered_map>
#include<map>
#include<unordered_set>
#include<algorithm>
#include<sstream>
#include<set>
#include<iomanip>
using namespace std;
void negationn(stack<bool>& operandStack);
void con(stack<bool>& operandStack);
void dis(stack<bool>& operandStack);
void implic(stack<bool>& operandStack);
void equiv(stack<bool>& operandStack);
bool evaluateLogicalExpression(const vector<bool>& variables, const string& expression);
int countVariables(const string& expression);
void calculateSknfAndSdnf(const vector<bool>& variables, bool result, int rowNumber, const int numVariables, vector<string>& sknfClauses,
    vector<string>& sdnfClauses);
vector<string> glueSDNFBy2(vector<string>& sdnfClauses);
vector<string> glueSKNFBy2(vector<string>& sknfClauses);
unordered_set<string> extractVariables(const string& clause);
vector<string> addNotGlued(vector<string>& sdnfClauses);
bool evaluateClause(const string& clause, const unordered_map<char, bool>& variableAssignments);
void printTruthTable(const vector<string>& sknfClauses);
void parseClause(const string& clause, vector<pair<char, bool>>& variableStates);
string tryGlue(const string& clause1, const string& clause2);
vector<string> glueSDNFBy1(vector<string>& sdnfClauses);
void printImplicantConstituentTable(const vector<string>& implicants, const vector<string>& constituents);
vector<string> FirstMethod(vector<string>& sdnfClauses, vector<string>& sdnfClausess, vector<string>& sknfClauses, vector<string>& sknfClauses33);
vector<string> SecondMethod(vector<string>& sdnfClauses2, vector<string>& sdnfClauses222, vector<bool>& variables, int& numVariables, const string& expression, int rowNumber2, vector<string>& sknfClauses2, vector<string>& sknfClauses222);
vector<string> GetOnlyVariables(vector<string> sdnfClauses);
map<int, vector<string>> GetVariablesGroupedByClause(const vector<string>& sdnfClauses);
string GenerateExpression(bool a, bool b, bool c);
bool IsMatch(const string& expression, const vector<string>& clause);
string GetTable(const vector<string>& sdnfClauses);
vector<string> MinimizeKarnaughMap(string& numericForm, vector<string>& variableNames);
vector<string> MinimizeSknfKarnaughMap(string& numericForm, vector<string>& variableNames);
vector<string> ThirdMethod(vector<string>& sdnfClauses, vector<string>& sdnfClauses2, vector<bool>& variables, int& numVariables, const string& expression, int rowNumber2, vector<string>& sknfClauses, vector<string>& sknfClauses2);
void solveLogicalExpression(const string& expression);
