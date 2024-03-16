#include"LogicalExxpresion.h"
void negationn(stack<bool>& operandStack) {
    bool operand = operandStack.top();
    operandStack.pop();
    operandStack.push(!operand);
}
void con(stack<bool>& operandStack) {
    bool operand2 = operandStack.top();
    operandStack.pop();
    bool operand1 = operandStack.top();
    operandStack.pop();
    operandStack.push(operand1 && operand2);
}
void dis(stack<bool>& operandStack) {
    bool operand2 = operandStack.top();
    operandStack.pop();
    bool operand1 = operandStack.top();
    operandStack.pop();
    operandStack.push(operand1 || operand2);
}
void implic(stack<bool>& operandStack) {
    bool operand2 = operandStack.top();
    operandStack.pop();
    bool operand1 = operandStack.top();
    operandStack.pop();
    operandStack.push(!operand1 || operand2);
}
void equiv(stack<bool>& operandStack) {
    bool operand2 = operandStack.top();
    operandStack.pop();
    bool operand1 = operandStack.top();
    operandStack.pop();
    operandStack.push(operand1 == operand2);
}
bool evaluateLogicalExpression(const vector<bool>& variables, const string& expression) {
    stack<bool> operandStack;
    stack<char> operatorStack;
    unordered_map<char, int> precedence;
    precedence['!'] = 5;
    precedence['&'] = 4;
    precedence['|'] = 3;
    precedence['-'] = 2;
    precedence['~'] = 1;
    for (char c : expression) {
        if (isalpha(c)) {
            int index = c - 'a';
            operandStack.push(variables[index]);
        }
        else if (c == '(') {
            operatorStack.push(c);
        }
        else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                char op = operatorStack.top();
                operatorStack.pop();
                if (op == '!') {
                    negationn(operandStack);
                }
                else if (op == '&') {
                    con(operandStack);
                }
                else if (op == '|') {
                    dis(operandStack);
                }
                else if (op == '-') {
                    implic(operandStack);
                }
                else if (op == '~') {
                    equiv(operandStack);
                }
            }
            if (!operatorStack.empty()) {
                operatorStack.pop();
            }
        }
        else if (c == '!' || c == '&' || c == '|' || c == '-' || c == '~') {
            while (!operatorStack.empty() && operatorStack.top() != '(' && precedence[c] <= precedence[operatorStack.top()]) {
                char op = operatorStack.top();
                operatorStack.pop();

                if (op == '!') {
                    negationn(operandStack);
                }
                else if (op == '&') {
                    con(operandStack);
                }
                else if (op == '|') {
                    dis(operandStack);
                }
                else if (op == '-') {
                    implic(operandStack);
                }
                else if (op == '~') {
                    equiv(operandStack);
                }
            }
            operatorStack.push(c);
        }
    }
    while (!operatorStack.empty()) {
        char op = operatorStack.top();
        operatorStack.pop();

        if (op == '!') {
            negationn(operandStack);
        }
        else if (op == '&') {
            con(operandStack);
        }
        else if (op == '|') {
            dis(operandStack);
        }
        else if (op == '-') {
            implic(operandStack);
        }
        else if (op == '~') {
            equiv(operandStack);
        }
    }
    return operandStack.top();
}

int countVariables(const string& expression) {
    int count = 0;
    for (char c : expression) {
        if (isalpha(c)) {
            count++;
        }
    }
    return count;
}
void printVariables(int numVariables) {
    cout << "Variables: ";
    for (int i = 0; i < numVariables; ++i) {
        cout << static_cast<char>('a' + i) << " ";
    }
    cout << endl;
}
void printTruthTable(const vector<bool>& variables, bool result) {
    for (bool varValue : variables) {
        cout << (varValue ? 1 : 0) << "\t";
    }
    cout << (result ? 1 : 0) << endl;
}
void calculateSknfAndSdnf(const vector<bool>& variables, bool result, int rowNumber, const int numVariables, vector<string>& sknfClauses,
vector<string>& sdnfClauses, vector<int>& sknfNumbers, vector<int>& sdnfNumbers) {
    if (!result) {
        string sknfClause = "(";
        for (int j = 0; j < numVariables; ++j) {
            sknfClause += (variables[j] ? "!" : "") + string(1, 'a' + j);
            if (j != numVariables - 1) {
                sknfClause += " | ";
            }
        }
        sknfClause += ")";
        sknfClauses.push_back(sknfClause);
        sknfNumbers.push_back(rowNumber);
    }
    else {
        string sdnfClause = "(";
        for (int j = 0; j < numVariables; ++j) {
            sdnfClause += (variables[j] ? "" : "!") + string(1, 'a' + j);
            if (j != numVariables - 1) {
                sdnfClause += " & ";
            }
        }
        sdnfClause += ")";
        sdnfClauses.push_back(sdnfClause);
        sdnfNumbers.push_back(rowNumber);
    }
}
void solveLogicalExpression(const string& expression) {
    int numVariables = countVariables(expression);
    vector<bool> variables(numVariables, false);
    printVariables(numVariables);

    if (numVariables < 3 || numVariables > 5) {
        cout << "Invalid number of variables. The expression should have 3 to 5 variables." << endl;
        return;
    }
    cout << "Truth table:" << endl;
    vector<string> sknfClauses;
    vector<string> sdnfClauses;
    vector<int> sknfNumbers;
    vector<int> sdnfNumbers;
    string index = "";
    int rowNumber = 0;
    for (int i = 0; i < pow(2, numVariables); ++i) {
        for (int j = 0; j < numVariables; ++j) {
            variables[j] = ((i >> (numVariables - j - 1)) & 1) == 1;
        }
        bool result = evaluateLogicalExpression(variables, expression);
        index += to_string(result ? 1 : 0);
        printTruthTable(variables, result);
        calculateSknfAndSdnf(variables, result, rowNumber, numVariables, sknfClauses, sdnfClauses, sknfNumbers, sdnfNumbers);
        rowNumber++;
    }
    cout << "\nSKNF: ";
    for (size_t i = 0; i < sknfClauses.size(); ++i) {
        cout << sknfClauses[i];
        if (i != sknfClauses.size() - 1) {
            cout << " & ";
        }
    }
    cout << "\nNumSKNF: (";
    for (size_t i = 0; i < sknfNumbers.size(); ++i) {
        cout << sknfNumbers[i];
        if (i != sknfNumbers.size() - 1) {
            cout << ",";
        }
    }
    cout << ")";
    cout << "\nSDNF: ";
    for (size_t i = 0; i < sdnfClauses.size(); ++i) {
        cout << sdnfClauses[i];
        if (i != sdnfClauses.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\nNumSDNF: (";
    for (size_t i = 0; i < sdnfNumbers.size(); ++i) {
        cout << sdnfNumbers[i];
        if (i != sdnfNumbers.size() - 1) {
            cout << ",";
        }
    }
    cout << ")" << endl;
    cout << "Index form: " << index << endl;
    int numericForm = 0;
    int indexLength = index.length();
    for (int i = 0; i < indexLength; ++i) {
        numericForm += (index[i] - '0') * static_cast<int>(pow(2, indexLength - i - 1));
    }
    cout << "Numeric form: " << numericForm << endl;
}
