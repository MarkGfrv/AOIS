#include"../Project18/Header.h"
int main() {
	setlocale(LC_ALL, "Russian");
	Table ht(10);
	string k, m, l;
	string h, n;
	int choice;
	cout << "Enter 1 to add the element(enter key-value)\n";
	cout << "Enter 2 to update value(add new value for the key)\n";
	cout << "Enter 3 to remove the value\n";
	cout << "Enter 4 to see hash table\n";
	cout << "Enter 5 to see table with buckets:\n";
	cout << "Enter 6 to exit\n";
	cin >> choice;
	switch (choice) {
	case 1:
		cout << "Enter the key:\n";
		cin >> k;
		cout << "Enter the value:\n";
		cin >> h;
		ht.create(k, h);
		cout << "Value for key " << k << " is " << h << endl;
		break;
	case 2:
		cout << "Enter the key:\n";
		cin >> m;
		cout << "Enter new value for the key:\n";
		cin >> n;
		ht.update(m, n);
		break;
	case 3:
		cout << "Enter key for removal:\n";
		cin >> l;
		ht.remove(l);
		cout << "Value for the key " << l << " after removal is " << ht.read(l) << endl;
		break;
	case 4:
		ht.display();
		break;
	case 5:
		ht.displayBuckets();
		break;
	case 6:
		return 0;
		break;
	}
	while (choice > 0 && choice < 7) {
		cout << "\n";
		cout << "Enter 1 to add the element(enter key-value)\n";
		cout << "Enter 2 to update value(add new value for the key)\n";
		cout << "Enter 3 to remove the value\n";
		cout << "Enter 4 to see hash table\n";
		cout << "Enter 5 to see table with buckets:\n";
		cout << "Enter 6 to exit\n";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Enter the key:\n";
			cin >> k;
			cout << "Enter the value:\n";
			cin >> h;
			ht.create(k, h);
			cout << "Value for key " << k << " is " << h << endl;
			break;
		case 2:
			cout << "Enter the key:\n";
			cin >> m;
			cout << "Enter new value for the key:\n";
			cin >> n;
			ht.update(m, n);
			break;
		case 3:
			cout << "Enter key for removal:\n";
			cin >> l;
			ht.remove(l);
			cout << "Value for the key " << l << " after removal is " << ht.read(l) << endl;
			break;
		case 4:
			ht.display();
			break;
		case 5:
			ht.displayBuckets();
			break;
		case 6:
			return 0;
			break;
			cin >> choice;
		}
	}
	return 0;
}
