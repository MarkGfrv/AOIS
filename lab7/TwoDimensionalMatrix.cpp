#include"Matrix.h"
void Matrix::InitializeMatrix() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            matrix[i][j] = 0;
        }
    }
}
void Matrix::PrintMatrix() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
string Matrix::PrintWord(int wordNumber) {
    string word;
    int firstNumber = matrix[wordNumber][wordNumber];
    word += to_string(firstNumber);
    cout << firstNumber << " ";
    for (int i = wordNumber + 1; i < 16; i++) {
        word += to_string(matrix[i][wordNumber]);
        cout << matrix[i][wordNumber] << " ";
    }
    for (int i = 0; i < wordNumber; i++) {
        word += to_string(matrix[i][wordNumber]);
        cout << matrix[i][wordNumber] << " ";
    }
    return word;
}
void Matrix::WriteWord(string word, int wordNumber) {
    vector<int> numbers;
    int firstNumber = matrix[wordNumber][wordNumber];
    for (int i = 0; i < word.size(); i++) {
        numbers.push_back(stoi(string(1, word[i])));
    }
    if (numbers.size() < 16) {
        while (numbers.size() < 16) {
            numbers.push_back(0);
        }
    }
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
    int index = 0;
    for (int i = wordNumber; i < 16; i++) {
        if (index <= numbers.size()) {
            matrix[i][wordNumber] = numbers[index++];
        }
        else
            break;
    }
    for (int i = 0; i < wordNumber; i++) {
        if (index <= numbers.size()) {
            matrix[i][wordNumber] = numbers[index++];
        }
        else
            break;
    }
}
string Matrix::PrintAddressRow(int wordNumber) {
    string row;
    for (int i = 0; i < 16 - wordNumber; i++) {
        row += to_string(matrix[wordNumber + i][i]);
        cout << matrix[wordNumber + i][i] << " ";
    }
    for (int i = 0; i < 16 - (16 - wordNumber); i++) {
        row += to_string(matrix[i][(16 - wordNumber) + i]);
        cout << matrix[i][(16 - wordNumber) + i] << " ";
    }
    return row;
}
void Matrix::WriteAddressRow(string row, int wordNumber) {
    vector<int> numbers;
    int index = 0;
    for (int i = 0; i < row.size(); i++) {
        numbers.push_back(stoi(string(1, row[i])));
    }
    if (numbers.size() < 16) {
        while (numbers.size() < 16) {
            numbers.push_back(0);
        }
    }
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i] << " ";
    }
    for (int i = 0; i < 16 - wordNumber; i++) {
        matrix[wordNumber + i][i] = numbers[index++];
    }
    for (int i = 0; i < 16 - (16 - wordNumber); i++) {
        matrix[i][(16 - wordNumber) + i] = numbers[index++];
    }
}
string Matrix::F5(int wordNumber1, int wordNumber2, int resultRow) {
    string word2;
    int firstNumber = matrix[wordNumber2][wordNumber2];
    word2 += to_string(firstNumber);
    for (int i = wordNumber2 + 1; i < 16; i++) {
        word2 += to_string(matrix[i][wordNumber2]);
    }
    for (int i = 0; i < wordNumber2; i++) {
        word2 += to_string(matrix[i][wordNumber2]);
    }
    cout << "На позиции " << wordNumber2 << " находится слово:\n";
    WriteWord(word2, resultRow);
    cout << "\n";
    cout << "Слово записано в столбец " << resultRow << "\n";
    return word2;
}
string Matrix::F10(int wordNumber1, int wordNumber2, int resultRow) {
    string word2;
    string negatedWord2;
    int firstNumber = matrix[wordNumber2][wordNumber2];
    word2 += to_string(firstNumber);
    for (int i = wordNumber2 + 1; i < 16; i++) {
        word2 += to_string(matrix[i][wordNumber2]);
    }
    for (int i = 0; i < wordNumber2; i++) {
        word2 += to_string(matrix[i][wordNumber2]);
    }
    for (char el : word2) {
        if (el == '0') {
            negatedWord2 += '1';
        }
        else if (el == '1') {
            negatedWord2 += '0';
        }
    }
    WriteWord(negatedWord2, resultRow);
    cout << "\n";
    cout << "Слово записано в столбец " << resultRow << "\n";
    return negatedWord2;
}
string Matrix::F0(int resultRow) {
    string zeroNumber;
    for (int i = 0; i < 16; i++)
        zeroNumber += '0';
    WriteWord(zeroNumber, resultRow);
    return zeroNumber;
}
string Matrix::F15(int resultRow) {
    string unitNumber;
    for (int i = 0; i < 16; i++)
        unitNumber += '1';
    WriteWord(unitNumber, resultRow);
    return unitNumber;
}
string Matrix::Search(string key) {
    for (int j = 0; j < 16; j++) {
        string word;
        for (int i = 0; i < 16; i++) {
            word += to_string(matrix[(i + j) % 16][j]);
        }
        if (word.substr(0, 3) == key) {
            cout << "Найдено слово: " << word << " в столбце: " << j << endl;
            return word;
        }
    }
    cout << "Слово с ключом " << key << " не найдено." << endl;
    return "";
}
string Matrix::BinarySum(string num1, string num2) {
    int carry = 0;
    string sum;
    int length = max(num1.length(), num2.length());
    if (num1.length() < length) {
        num1 = string(length - num1.length(), '0') + num1;
    }
    if (num2.length() < length) {
        num2 = string(length - num2.length(), '0') + num2;
    }
    for (int i = length - 1; i >= 0; i--) {
        int digit1 = num1[i] - '0';
        int digit2 = num2[i] - '0';
        int digitSum = digit1 + digit2 + carry;
        sum = to_string(digitSum % 2) + sum;
        carry = digitSum / 2;
    }
    if (carry > 0) {
        sum = to_string(carry) + sum;
    }
    return sum;
}
int Matrix::GetIndex(string word) {
    for (int j = 0; j < 16; j++) {
        string currentWord;
        for (int i = 0; i < 16; i++) {
            currentWord += to_string(matrix[(i + j) % 16][j]);
        }
        if (currentWord == word) {
            return j;
        }
    }
    return -1;
}
string Matrix::Summa(string word) {
    string A;
    string B;
    int index = GetIndex(word);
    for (int i = 3; i < 7; i++) {
        A += string(1, word[i]);
    }
    for (int i = 7; i < 11; i++) {
        B += string(1, word[i]);
    }
    string sum = BinarySum(A, B);
    for (int i = 0; i < sum.size(); i++) {
        cout << sum[i] << " ";
    }
    cout << "\n";
    if (sum.size() != 5) {
        sum.insert(0, "0");
    }
    for (int i = 0; i < sum.size(); i++) {
        cout << sum[i] << " ";
    }
    cout << "\n";
    int wordIndex = 15;
    for (int j = sum.size() - 1; j >= 0 && wordIndex >= 11; j--) {
        word[wordIndex--] = sum[j];
    }
    cout << "Новое слово:\n";
    cout << "\n";
    WriteWord(word, index);
    return word;
}
bool Matrix::GetBit(char c) {
    return c == '1';
}
string Matrix::SearchMatch(string word) {
    int n = 16;
    int maxMatches = -1;
    string bestMatch;
    int bestMatchColumn = -1;
    for (int j = 0; j < 16; j++) {
        vector<bool> g(n + 1, false);
        vector<bool> l(n + 1, false);
        int matchCount = 0;
        for (int i = n - 1; i >= 0; i--) {
            int colIndex = (i + j) % 16;
            bool a_i = GetBit(word[i]);
            bool S_ji = matrix[colIndex][j];
            g[i] = g[i + 1] || (!a_i && S_ji && !l[i + 1]);
            l[i] = l[i + 1] || (a_i && !S_ji && !g[i + 1]);
            if (a_i == S_ji) {
                matchCount++;
            }
        }
        if (g[0] == l[0]) {
            string foundWord;
            for (int i = 0; i < 16; i++) {
                foundWord += to_string(matrix[(i + j) % 16][j]);
            }
            cout << "Найдено слово: " << foundWord << " в столбце: " << j << endl;
            return foundWord;
        }
        if (matchCount > maxMatches) {
            maxMatches = matchCount;
            bestMatchColumn = j;
        }
    }
    if (bestMatchColumn != -1) {
        string bestMatchWord;
        for (int i = 0; i < 16; i++) {
            bestMatchWord += to_string(matrix[(i + bestMatchColumn) % 16][bestMatchColumn]);
        }
        cout << "Точное совпадение не найдено. Наилучшее совпадение: " << bestMatchWord << " в столбце: " << bestMatchColumn << endl;
        return bestMatchWord;
    }
    cout << "Слово " << word << " не найдено." << endl;
    return "";
}
