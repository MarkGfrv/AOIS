#pragma once
#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
using namespace std;
class Matrix {
    int matrix[16][16];
public:
    Matrix() {
        InitializeMatrix();
    }

    void InitializeMatrix();

    void PrintMatrix();

    string PrintWord(int wordNumber);

    void WriteWord(string word, int wordNumber);

    string PrintAddressRow(int wordNumber);

    void WriteAddressRow(string row, int wordNumber);

    string F5(int wordNumber1, int wordNumber2, int resultRow);

    string F10(int wordNumber1, int wordNumber2, int resultRow);

    string F0(int resultRow);

    string F15(int resultRow);

    string Search(string key);

    string BinarySum(string num1, string num2);

    int GetIndex(string word);

    string Summa(string word);

    bool GetBit(char c);

    string SearchMatch(string word);
};
