#pragma once
#include <iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<unordered_set>
using namespace std;
void calculateSdnf(const vector<vector<bool>>& truthTable, const vector<char>& variableNames, vector<string>& sdnfClauses, const vector<size_t>& ignoredColumns);
void calculateSdnfFor2Task(const vector<vector<bool>>& truthTable, const vector<char>& variableNames, vector<string>& sdnfClauses, size_t resultColumnIndex);
vector<string> glueSDNFBy2(vector<string>& sdnfClauses);
unordered_set<string> extractVariables(const string& clause);
vector<string> addNotGlued(vector<string>& sdnfClauses);
void parseClause(const string& clause, vector<pair<char, bool>>& variableStates);
string tryGlue(const string& clause1, const string& clause2);
vector<string> glueSDNFBy1(vector<string>& sdnfClauses);
vector<string> mergeSdnf(const vector<string>& sdnfClauses);
void printSDNF(const vector<vector<bool>>& truthTable, const vector<vector<bool>>& truthTable2, const vector<vector<bool>>& truthTable3, const vector<vector<bool>>& truthTable4, const vector<char>& variableNames, size_t resultColumnIndex);
void printTable1();
void printTable2();
