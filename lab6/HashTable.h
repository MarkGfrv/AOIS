#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<string>
using namespace std;
class Value {
public:
	string key;
	string value;
	Value(const string& k, const string& v) : key(k), value(v) {}
};
class Table {
private:
	int size;
	vector<list<Value>> table;
	int hash(const string& key);
	int quadraticSearch(int index, int attempt);
public:
	Table(int s) : size(s) {
		table.resize(size);
	}
	void create(const string& key, const string& value);
	string read(const string& key);
	void update(const string& key, string value);
	void remove(const string& key);
	void display();
	void displayBuckets();
};
