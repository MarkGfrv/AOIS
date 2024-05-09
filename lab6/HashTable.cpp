#include"Header.h"
int Table::hash(const string& key) {
	if (key.length() < 2) {
		cerr << "Key should have at least two characters." << endl;
		return -1;
	}
	int hashValue = (tolower(key[0]) - 'a' + 1) * 26 + (tolower(key[1]) - 'a' + 1);
	return hashValue % size;
}
int Table::quadraticSearch(int index, int attempt) {
	return (index + attempt * attempt) % size;
}
void Table::create(const string& key, const string& value) {
	int index = hash(key);
	int attempt = 0;
	int newIndex = index;
	while (!table[newIndex].empty() && table[newIndex].front().key != key) {
		++attempt;
		newIndex = quadraticSearch(index, attempt);
		if (newIndex == index) {
			cerr << "Table is already full!" << endl;
			return;
		}
	}
	if (table[newIndex].empty()) {
		table[newIndex].push_back(Value(key, value));
		cout << "Created key-value pair: " << key << "-" << value << endl;
	}
	else {
		cout << "Element with key " << key << " already exists." << endl;
	}
}
string Table::read(const string& key) {
	int index = hash(key);
	int attempt = 0;
	int newIndex = index;
	while (!table[newIndex].empty() && table[newIndex].front().key != key) {
		++attempt;
		newIndex = quadraticSearch(index, attempt);
		if (newIndex == index) {
			return "Key not found!";
		}
	}
	if (!table[newIndex].empty()) {
		return table[newIndex].front().value;
	}
	else {
		return "Key not found!";
	}
}
void Table::update(const string& key, string value) {
	int index = hash(key);
	int attempt = 0;
	int newIndex = index;
	while (!table[newIndex].empty() && table[newIndex].front().key != key) {
		++attempt;
		newIndex = quadraticSearch(index, attempt);
		if (newIndex == index) {
			cerr << "Key not found. Cannot update!" << endl;
			return;
		}
	}
	if (!table[newIndex].empty()) {
		table[newIndex].front().value = value;
		cout << "Updated value for key " << key << ": " << value << endl;
	}
	else {
		cerr << "Key not found. Cannot update!" << endl;
	}
}
void Table::remove(const string& key) {
	int index = hash(key);
	int attempt = 0;
	int newIndex = index;
	while (!table[newIndex].empty() && table[newIndex].front().key != key) {
		++attempt;
		newIndex = quadraticSearch(index, attempt);
		if (newIndex == index) {
			cerr << "Key not found. Cannot remove!" << endl;
			return;
		}
	}
	if (!table[newIndex].empty()) {
		table[newIndex].clear();
		cout << "Removed key " << key << " from the table." << endl;
	}
	else {
		cerr << "Key not found. Cannot remove!" << endl;
	}
}
void Table::display() {
	cout << "Key\tData" << endl;
	for (int i = 0; i < size; ++i) {
		for (auto& kv : table[i]) {
			cout << kv.key << "\t" << kv.value << endl;
		}
	}
}
void Table::displayBuckets() {
	cout << "Bucket\tKey\tData" << endl;
	for (int i = 0; i < size; ++i) {
		cout << "Bucket " << i << ": ";
		if (!table[i].empty()) {
			for (auto& kv : table[i]) {
				cout << kv.key << "\t" << kv.value << endl;
			}
		}
		else {
			cout << "Empty" << endl;
		}
	}
}
