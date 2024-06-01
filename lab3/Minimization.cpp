#include"Minimization.h"
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
void calculateSknfAndSdnf(const vector<bool>& variables, bool result, int rowNumber, const int numVariables, vector<string>& sknfClauses,
    vector<string>& sdnfClauses) {
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
    }
}
vector<string> glueSDNFBy2(vector<string>& sdnfClauses) {
    vector<string> newSdnfClauses;
    for (const auto& clause : sdnfClauses) {
        vector<pair<char, bool>> variableStates;
        bool negation = false;
        for (char c : clause) {
            if (isalpha(c)) {
                variableStates.emplace_back(c, negation);
            }
            else if (c == '!') {
                negation = true;
            }
            else if (c == ' ') {
                negation = false;
            }
        }
        for (size_t i = 0; i < variableStates.size(); ++i) {
            for (size_t j = i + 1; j < variableStates.size(); ++j) {
                string newClause;
                if (variableStates[i].second) {
                    newClause += '!';
                }
                newClause += variableStates[i].first;
                newClause += " & ";
                if (variableStates[j].second) {
                    newClause += '!';
                }
                newClause += variableStates[j].first;
                newSdnfClauses.push_back("(" + newClause + ")");
            }
        }
    }
    unordered_map<string, int> clauseCount;
    for (const auto& clause : newSdnfClauses) {
        clauseCount[clause]++;
    }
    sdnfClauses = newSdnfClauses;
    auto it = remove_if(sdnfClauses.begin(), sdnfClauses.end(), [&](const string& clause) {
        return clauseCount[clause] == 1;
        });
    sdnfClauses.erase(it, sdnfClauses.end());
    unordered_set<string> uniqueClauses;
    vector<string> uniqueSdnfClauses;
    for (const auto& clause : sdnfClauses) {
        if (uniqueClauses.find(clause) == uniqueClauses.end()) {
            uniqueClauses.insert(clause);
            uniqueSdnfClauses.push_back(clause);
        }
    }
    sdnfClauses = uniqueSdnfClauses;
    return sdnfClauses;
}
vector<string> glueSKNFBy2(vector<string>& sknfClauses) {
    vector<string> newSknfClauses;
    for (const auto& clause : sknfClauses) {
        vector<pair<char, bool>> variableStates;
        bool negation = false;
        for (char c : clause) {
            if (isalpha(c)) {
                variableStates.emplace_back(c, negation);
            }
            else if (c == '!') {
                negation = true;
            }
            else if (c == ' ') {
                negation = false;
            }
        }
        for (size_t i = 0; i < variableStates.size(); ++i) {
            for (size_t j = i + 1; j < variableStates.size(); ++j) {
                string newClause;
                if (variableStates[i].second) {
                    newClause += '!';
                }
                newClause += variableStates[i].first;
                newClause += " | ";
                if (variableStates[j].second) {
                    newClause += '!';
                }
                newClause += variableStates[j].first;
                newSknfClauses.push_back("(" + newClause + ")");
            }
        }
    }
    unordered_map<string, int> clauseCount;
    for (const auto& clause : newSknfClauses) {
        clauseCount[clause]++;
    }
    sknfClauses = newSknfClauses;
    auto it = remove_if(sknfClauses.begin(), sknfClauses.end(), [&](const string& clause) {
        return clauseCount[clause] == 1;
        });
    sknfClauses.erase(it, sknfClauses.end());
    unordered_set<string> uniqueClauses;
    vector<string> uniqueSdnfClauses;
    for (const auto& clause : sknfClauses) {
        if (uniqueClauses.find(clause) == uniqueClauses.end()) {
            uniqueClauses.insert(clause);
            uniqueSdnfClauses.push_back(clause);
        }
    }
    sknfClauses = uniqueSdnfClauses;
    return sknfClauses;
}
unordered_set<string> extractVariables(const string& clause) {
    unordered_set<string> variables;
    string variable;
    bool negation = false;
    for (char c : clause) {
        if (isalpha(c)) {
            variable = negation ? "!" + string(1, c) : string(1, c);
            variables.insert(variable);
        }
        else if (c == '!') {
            negation = true;
        }
        else {
            negation = false;
        }
    }
    return variables;
}

vector<string> addNotGlued(vector<string>& sdnfClauses) {
    vector<string> minimizedClauses;
    for (const string& clause : sdnfClauses) {
        bool addClause = true;
        unordered_set<string> variables = extractVariables(clause);
        for (const string& otherClause : sdnfClauses) {
            if (clause != otherClause) {
                unordered_set<string> otherVariables = extractVariables(otherClause);
                int commonVariables = 0;
                for (const string& var : variables) {
                    if (otherVariables.find(var) != otherVariables.end()) {
                        commonVariables++;
                    }
                }
                if (commonVariables >= 2) {
                    addClause = false;
                    break;
                }
            }
        }
        if (addClause) {
            minimizedClauses.push_back(clause);
        }
    }
    return minimizedClauses;
}
bool evaluateClause(const string& clause, const unordered_map<char, bool>& variableAssignments) {
    bool result = false;
    bool negation = false;
    for (char c : clause) {
        if (c == '(' || c == ')' || c == ' ') {
            continue;
        }
        else if (c == '!') {
            negation = true;
        }
        else if (isalpha(c)) {
            bool value = variableAssignments.at(c);
            if (negation) {
                result &= !value;
                negation = false;
            }
            else {
                result |= value;
            }
        }
        else if (c == '|' || c == '&') {
            continue;
        }
    }
    return result;
}
void printTruthTable(const vector<string>& sknfClauses) {
    unordered_map<char, bool> variableAssignments;
    for (const string& clause : sknfClauses) {
        for (char c : clause) {
            if (isalpha(c)) {
                variableAssignments[c] = false;
            }
        }
    }
    cout << "Truth Table:\n";
    for (const auto& variable : variableAssignments) {
        cout << variable.first << " ";
    }
    cout << "| Result\n";
    int numVariables = variableAssignments.size();
    int numCombinations = pow(2, numVariables);
    for (int i = 0; i < numCombinations; ++i) {
        int combination = i;
        for (auto& variable : variableAssignments) {
            variable.second = combination & 1;
            combination >>= 1;
        }
        for (const auto& variable : variableAssignments) {
            cout << variable.second << " ";
        }
        bool result = true;
        for (const string& clause : sknfClauses) {
            result &= evaluateClause(clause, variableAssignments);
        }
        cout << "| " << result << endl;
    }
}
void parseClause(const string& clause, vector<pair<char, bool>>& variableStates) {
    bool negation = false;
    for (char c : clause) {
        if (isalpha(c)) {
            variableStates.emplace_back(c, negation);
        }
        else if (c == '!') {
            negation = true;
        }
        else if (c == ' ') {
            negation = false;
        }
    }
}
string tryGlue(const string& clause1, const string& clause2) {
    vector<pair<char, bool>> variableStates1;
    vector<pair<char, bool>> variableStates2;
    parseClause(clause1, variableStates1);
    parseClause(clause2, variableStates2);
    bool canGlue = false; 
    string gluedClause;
    if (variableStates1[0].first == variableStates2[0].first) {
        if (variableStates1[1].first == variableStates2[1].first &&
            variableStates1[1].second != variableStates2[1].second) {
            canGlue = true; 
            gluedClause += (variableStates1[0].second ? "!" : "") + string(1, variableStates1[0].first);
        }
    }
    if (canGlue) {
        return "(" + gluedClause + ")";
    }
    else {
        return ""; 
    }
}
vector<string> glueSDNFBy1(vector<string>& sdnfClauses) {
    vector<string> newSdnfClauses;

    vector<bool> glued(sdnfClauses.size(), false);
    for (size_t i = 0; i < sdnfClauses.size(); ++i) {
        for (size_t j = 0; j < sdnfClauses.size(); ++j) {
            if (i == j || glued[j]) continue; 
            string gluedClause = tryGlue(sdnfClauses[i], sdnfClauses[j]);
            if (!gluedClause.empty()) {
                newSdnfClauses.push_back(gluedClause);
                glued[i] = true; 
                glued[j] = true;
                break; 
            }
        }
        if (!glued[i]) {
            newSdnfClauses.push_back(sdnfClauses[i]); 
        }
    }
    unordered_set<string> uniqueClauses;
    for (const auto& clause : newSdnfClauses) {
        uniqueClauses.insert(clause);
    }
    newSdnfClauses.assign(uniqueClauses.begin(), uniqueClauses.end());
    return newSdnfClauses;
}
void printImplicantConstituentTable(const vector<string>& implicants, const vector<string>& constituents) {
    cout << setw(20) << right << "Implicant | ";
    for (const auto& constituent : constituents) {
        cout << setw(20) << left << constituent;
    }
    cout << endl;
    cout << setw(20) << right << "------------------";
    for (size_t i = 0; i < constituents.size(); ++i) {
        cout << "------------------";
    }
    cout << endl;
    vector<vector<char>> table(implicants.size(), vector<char>(constituents.size(), '-'));
    for (size_t i = 0; i < implicants.size(); ++i) {
        string implicant = implicants[i];
        size_t start = implicant.find("(");
        size_t end = implicant.find(")");
        string literals = implicant.substr(start + 1, end - start - 1);
        vector<string> implicantVariables;
        stringstream ss(literals);
        string literal;
        while (getline(ss, literal, '&')) {
            implicantVariables.push_back(literal);
        }
        for (size_t j = 0; j < constituents.size(); ++j) {
            const string& constituent = constituents[j];
            bool allVariablesPresent = true;
            for (const string& implicantVar : implicantVariables) {
                if (constituent.find(implicantVar) == string::npos && constituent.find("!" + implicantVar) == string::npos) {
                    allVariablesPresent = false;
                    break;
                }
            }
            if (allVariablesPresent) {
                table[i][j] = 'X';
            }
        }
    }
    for (size_t i = 0; i < implicants.size(); ++i) {
        cout << setw(20) << right << implicants[i] << " | ";
        for (size_t j = 0; j < constituents.size(); ++j) {
            cout << setw(20) << left << (table[i][j] == 'X' ? "X" : "-");
        }
        cout << endl;
    }
}
vector<string> FirstMethod(vector<string>& sdnfClauses, vector<string>& sdnfClausess, vector<string>& sknfClauses, vector<string>& sknfClauses33) {
    cout << "Расчётный метод:" << endl;
    cout << "SDNF:";
    for (size_t i = 0; i < sdnfClauses.size(); ++i) {
        cout << sdnfClauses[i];
        if (i != sdnfClauses.size() - 1) {
            cout << " | ";
        }
    }
    vector<string> result1 = glueSDNFBy2(sdnfClauses);
    vector<string> result3 = glueSDNFBy1(result1);
    vector<string> result2 = addNotGlued(sdnfClausess);
    result1.insert(result1.end(), result2.begin(), result2.end());
    cout << endl;
    cout << "Результат склеивания:" << endl;
    for (size_t i = 0; i < result1.size(); ++i) {
        cout << result1[i];
        if (i != result1.size() - 1) {
            cout << " | ";
        }
    }
    result3.insert(result3.end(), result2.begin(), result2.end());
    cout << endl;
    cout << "Результат склеивания по одной переменной:" << endl;
    for (size_t i = 0; i < result3.size(); ++i) {
        cout << result3[i];
        if (i != result3.size() - 1) {
            cout << " | ";
        }
    }
    cout << endl;
    cout << "\nSKNF:";
    for (size_t i = 0; i < sknfClauses.size(); ++i) {
        cout << sknfClauses[i];
        if (i != sknfClauses.size() - 1) {
            cout << " & ";
        }
    }
    vector<string> sknf1 = glueSKNFBy2(sknfClauses);
    vector<string> sknf3 = glueSDNFBy1(sknf1);
    vector<string> sknf2 = addNotGlued(sknfClauses33);
    sknf1.insert(sknf1.end(), sknf2.begin(), sknf2.end());
    cout << "\nРезультат склеивания: " << endl;
    for (size_t i = 0; i < sknf1.size(); ++i) {
        cout << sknf1[i];
        if (i != sknf1.size() - 1) {
            cout << " & ";
        }
    }
    sknf3.insert(sknf3.end(), sknf2.begin(), sknf2.end());
    cout << "\nРезультат склеивания по одной переменной: " << endl;
    for (size_t i = 0; i < sknf3.size(); ++i) {
        cout << sknf3[i];
        if (i != sknf3.size() - 1) {
            cout << " & ";
        }
    }
    cout << "\n";
    return sknf3;
}
vector<string> SecondMethod(vector<string>& sdnfClauses2, vector<string>& sdnfClauses222, vector<bool>& variables, int& numVariables, const string& expression, int rowNumber2, vector<string>& sknfClauses2, vector<string>& sknfClauses222) {
    cout << "Расчётно - табличный метод:" << endl;
    cout << "SDNF: ";
    for (size_t i = 0; i < sdnfClauses2.size(); ++i) {
        cout << sdnfClauses2[i];
        if (i != sdnfClauses2.size() - 1) {
            cout << " | ";
        }
    }
    vector<string> result12 = glueSDNFBy2(sdnfClauses2);
    vector<string> result32 = glueSDNFBy1(result12);
    vector<string> result22 = addNotGlued(sdnfClauses222);
    result12.insert(result12.end(), result22.begin(), result22.end());
    cout << endl;
    cout << "Результат склеивания:" << endl;
    for (size_t i = 0; i < result12.size(); ++i) {
        cout << result12[i];
        if (i != result12.size() - 1) {
            cout << " | ";
        }
    }
    result32.insert(result32.end(), result22.begin(), result22.end());
    cout << endl;
    cout << "Результат склеивания по одной переменной:" << endl;
    for (size_t i = 0; i < result32.size(); ++i) {
        cout << result32[i];
        if (i != result32.size() - 1) {
            cout << " | ";
        }
    }
    cout << endl;
    cout << "Таблица:" << endl;
    vector<string> sknfClauses32;
    vector<string> sdnfClauses32;
    int rowNumber3 = 0;
    for (int i = 0; i < pow(2, numVariables); ++i) {
        for (int j = 0; j < numVariables; ++j) {
            variables[j] = ((i >> (numVariables - j - 1)) & 1) == 1;
        }
        bool result = evaluateLogicalExpression(variables, expression);
        calculateSknfAndSdnf(variables, result, rowNumber2, numVariables, sknfClauses32, sdnfClauses32);
        rowNumber3++;
    }
    printImplicantConstituentTable(result32, sdnfClauses32);
    cout << "\n";
    cout << "\n";
    cout << "SKNF: ";
    for (size_t i = 0; i < sknfClauses2.size(); ++i) {
        cout << sknfClauses2[i];
        if (i != sknfClauses2.size() - 1) {
            cout << " & ";
        }
    }
    vector<string> resultKnf = glueSKNFBy2(sknfClauses2);
    vector<string> resultKnf3 = glueSDNFBy1(resultKnf);
    vector<string> resultKnf2 = addNotGlued(sknfClauses222);
    resultKnf.insert(resultKnf.end(), resultKnf2.begin(), resultKnf2.end());
    cout << endl;
    cout << "Результат склеивания:" << endl;
    for (size_t i = 0; i < resultKnf.size(); ++i) {
        cout << resultKnf[i];
        if (i != resultKnf.size() - 1) {
            cout << " & ";
        }
    }
    resultKnf3.insert(resultKnf3.end(), resultKnf2.begin(), resultKnf2.end());
    cout << "\nРезультат склеивания по одной переменной: " << endl;
    for (size_t i = 0; i < resultKnf3.size(); ++i) {
        cout << resultKnf3[i];
        if (i != resultKnf3.size() - 1) {
            cout << " & ";
        }
    }
    cout << "\n";
    cout << "Таблица:" << endl;
    vector<string> sknfClausesKnf;
    vector<string> sdnfClausesDnf;
    int rowNumber5 = 0;
    for (int i = 0; i < pow(2, numVariables); ++i) {
        for (int j = 0; j < numVariables; ++j) {
            variables[j] = ((i >> (numVariables - j - 1)) & 1) == 1;
        }
        bool result = evaluateLogicalExpression(variables, expression);
        calculateSknfAndSdnf(variables, result, rowNumber2, numVariables, sknfClausesKnf, sdnfClausesDnf);
        rowNumber3++;
    }
    printImplicantConstituentTable(resultKnf3, sknfClausesKnf);
    return resultKnf3;
}
vector<string> GetOnlyVariables(vector<string> sdnfClauses) {
    vector<string> variables;
    for (const auto& clause : sdnfClauses) {
        bool negated = false; 
        string var; 
        for (char c : clause) {
            if (isalpha(c)) {
                if (negated) {
                    var += "!" + string(1, c); 
                    negated = false;
                }
                else {
                    var += c; 
                }
            }
            else if (c == '!') {
                negated = true; 
            }
            else if (!isspace(c)) { 
                if (!var.empty()) {
                    variables.push_back(var);
                    var.clear();
                }
            }
        }
        if (!var.empty()) {
            variables.push_back(var);
        }
    }
    return variables;
}
map<int, vector<string>> GetVariablesGroupedByClause(const vector<string>& sdnfClauses) {
    map<int, vector<string>> variablesGrouped;
    for (int i = 0; i < sdnfClauses.size(); ++i) {
        const string& clause = sdnfClauses[i];
        vector<string> variablesInClause;
        bool negated = false;
        string var;
        for (char c : clause) {
            if (isalpha(c)) {
                if (negated) {
                    var += "!" + string(1, c);
                    negated = false;
                }
                else {
                    var += c;
                }
            }
            else if (c == '!') {
                negated = true;
            }
            else if (!isspace(c)) {
                if (!var.empty()) {
                    variablesInClause.push_back(var);
                    var.clear();
                }
            }
        }
        if (!var.empty()) {
            variablesInClause.push_back(var);
        }
        variablesGrouped[i] = variablesInClause;
    }
    return variablesGrouped;
}
string GenerateExpression(bool a, bool b, bool c) {
    string result;
    if (!a) result += "!a ";
    else result += "a ";
    if (!b) result += "!b ";
    else result += "b ";
    if (!c) result += "!c";
    else result += "c";
    return result;
}
bool IsMatch(const string& expression, const vector<string>& clause) {
    vector<string> exprVars;
    string var;
    bool negated = false;
    for (char c : expression) {
        if (isalpha(c)) {
            if (negated) {
                var = "!" + string(1, c);
                negated = false;
            }
            else {
                var = string(1, c);
            }
            exprVars.push_back(var);
        }
        else if (c == '!') {
            negated = true;
        }
        else if (isspace(c) && !var.empty()) {
            var.clear();
        }
    }
    sort(exprVars.begin(), exprVars.end());
    vector<string> sortedClause = clause;
    sort(sortedClause.begin(), sortedClause.end());
    return exprVars == sortedClause;
}
string GetTable(const vector<string>& sdnfClauses) {
    map<int, vector<string>> groupedVariables = GetVariablesGroupedByClause(sdnfClauses);
    cout << "a\\bc |    00    |    01    |    11    |    10    |" << endl;
    cout << "---------------------------------------------------" << endl;
    string karaughMap;
    for (bool a : {false, true}) {
        cout << (a ? "1" : "0") << "      | ";
        for (int i = 0; i < 4; ++i) {
            bool b = (i & 2) != 0;
            bool c = (i & 1) != 0;
            string expr;
            if (i == 2) {
                expr = GenerateExpression(a, b, !c);
            }
            else if (i == 3) {
                expr = GenerateExpression(a, b, !c);
            }
            else {
                expr = GenerateExpression(a, b, c);
            }
            bool match = false;
            for (const auto& pair : groupedVariables) {
                if (IsMatch(expr, pair.second)) {
                    match = true;
                    break;
                }
            }
            karaughMap += (match ? "1" : "0");
            cout << (match ? "1" : "0");
            if (i != 3) cout << " | ";
        }
        cout << endl;
    }
    return karaughMap;
}
vector<string> MinimizeKarnaughMap(string& numericForm, vector<string>& variableNames) {
    string k1 = numericForm.substr(0, 4);
    string k2 = numericForm.substr(4);
    vector<string> result;
    int countOne = 0, count2One = 0;
    for (int i = 0; i < 4; i++) {
        if (k1[i] == '1') {
            countOne += 1;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (k2[i] == '1') {
            count2One += 1;
        }
    }
    vector<vector<int>> map = {
        {k1[0] - '0', k1[1] - '0', k1[2] - '0', k1[3] - '0'},
        {k2[0] - '0', k2[1] - '0', k2[2] - '0', k2[3] - '0'}
    };
    if (map[0][0] == 1 && map[0][1] == 1 && map[0][2] == 1 && map[0][3] == 1) {
        result.push_back("!" + variableNames[0]);
        map[0][0] = map[0][1] = map[0][2] = map[0][3] = 0;
    }
    if (map[0][0] == 1 && map[1][0] == 1 && map[0][3] == 1 && map[1][3] == 1) {
        result.push_back("!" + variableNames[2]);
        map[0][0] = map[1][0] = map[0][3] = map[1][3] = 0;
    }
    if (map[0][0] == 1 && map[0][1] == 1 && map[1][0] == 1 && map[1][1] == 1) {
        result.push_back("!" + variableNames[1]);
        map[0][0] = map[0][1] = map[1][0] = map[1][1] = 0;
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (map[i][j] == 1) {
                int count = 0;
                int start = j;
                while (j < 4 && map[i][j] == 1) {
                    count++;
                    j++;
                }
                if (count > 1 && count < 4) {
                    result.push_back("!" + variableNames[i]);
                    for (int k = start; k < j; ++k) {
                        map[i][k] = 0;
                    }
                }
            }
        }
    }
    if (map[1][2] == 1) {
        result.push_back("(" + variableNames[1] + " & " + variableNames[2] + ")");
        map[1][2] = 0;
    }
    if (countOne == 3 || count2One == 3) {
        if (k1[k1.size() - 1] == k1[0] == 1 || k2[k2.size() - 1] == k2[0] == 1) {
            result.push_back("!" + variableNames[2]);
        }
    }
    return result;
}
vector<string> MinimizeSknfKarnaughMap(string& numericForm, vector<string>& variableNames) {
    string k1 = numericForm.substr(0, 4);
    string k2 = numericForm.substr(4);
    vector<string> result;
    int countOne = 0, count2One = 0;
    for (int i = 0; i < 4; i++) {
        if (k1[i] == '1') {
            countOne += 1;
        }
    }
    for (int i = 0; i < 4; i++) {
        if (k2[i] == '1') {
            count2One += 1;
        }
    }
    vector<vector<int>> map = {
        {k1[0] - '0', k1[1] - '0', k1[2] - '0', k1[3] - '0'},
        {k2[0] - '0', k2[1] - '0', k2[2] - '0', k2[3] - '0'}
    };
    if (map[0][0] == 0 && map[0][1] == 0 && map[0][2] == 0 && map[0][3] == 0) {
        result.push_back(variableNames[0]);
        map[0][0] = map[0][1] = map[0][2] = map[0][3] = 1;
    }
    if (map[0][0] == 0 && map[1][0] == 0 && map[0][3] == 0 && map[1][3] == 0) {
        result.push_back(variableNames[2]);
        map[0][0] = map[1][0] = map[0][3] = map[1][3] = 1;
    }
    if (map[0][0] == 0 && map[0][1] == 0 && map[1][0] == 0 && map[1][1] == 0) {
        result.push_back(variableNames[1]);
        map[0][0] = map[0][1] = map[1][0] = map[1][1] = 1;
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (map[i][j] == 0) {
                int count = 0;
                int start = j;
                while (j < 4 && map[i][j] == 0) {
                    count++;
                    j++;
                }
                if (count > 1 && count < 4) {
                    result.push_back(variableNames[i]);
                    for (int k = start; k < j; ++k) {
                        map[i][k] = 1;
                    }
                }
            }
        }
    }
    if (map[1][2] == 0) {
        result.push_back("(" + variableNames[1] + " | " + variableNames[2] + ")");
        map[1][2] = 1;
    }
    if (countOne == 1 || count2One == 1) {
        if (k1[k1.size() - 1] == k1[0] == 0 || k2[k2.size() - 1] == k2[0] == 0) {
            result.push_back(variableNames[2]);
        }
    }
    return result;
}
vector<string> ThirdMethod(vector<string>& sdnfClauses, vector<string>& sdnfClauses2, vector<bool>& variables, int& numVariables, const string& expression, int rowNumber2, vector<string>& sknfClauses, vector<string>& sknfClauses2) {
    vector<string> variableNames;
    for (char c : expression) {
        if (isalpha(c)) {
            variableNames.push_back(string(1, c));
        }
    }
    cout << "\n";
    cout << "Табличный метод:\n";
    cout << "СДНФ:\n";
    cout << "\n";
    cout << "Карта Вейча-Карно:\n";
    string tableSdnf = GetTable(sdnfClauses2);
    cout << "\n";
    vector<string> k = MinimizeKarnaughMap(tableSdnf, variableNames);
    cout << "\n";
    cout << "Тупиковая форма СДНФ:\n";
    for (size_t i = 0; i < k.size(); ++i) {
        cout << k[i];
        if (i < k.size() - 1) {
            cout << " | ";
        }
    }
    cout << endl;
    cout << "\n";
    cout << "СКНФ:\n";
    cout << "\n";
    cout << "Карта Вейча-Карно:\n";
    string tableSknf = GetTable(sknfClauses2);
    cout << "\n";
    vector<string> k2 = MinimizeSknfKarnaughMap(tableSknf, variableNames);
    cout << "\n";
    cout << "Тупиковая форма СКНФ:\n";
    for (size_t i = 0; i < k2.size(); ++i) {
        cout << k2[i];
        if (i < k2.size() - 1) {
            cout << " & ";
        }
    }
    cout << endl;
    return k;
}
void solveLogicalExpression(const string& expression) {
    setlocale(LC_ALL, "Russian");
    int numVariables = countVariables(expression);
    vector<bool> variables(numVariables, false);
    vector<string> sknfClauses;
    vector<string> sknfClauses2;
    vector<string> sdnfClauses;
    vector<string> sdnfClauses2;
    int rowNumber = 0;
    for (int i = 0; i < pow(2, numVariables); ++i) {
        for (int j = 0; j < numVariables; ++j) {
            variables[j] = ((i >> (numVariables - j - 1)) & 1) == 1;
        }
        bool result = evaluateLogicalExpression(variables, expression);
        calculateSknfAndSdnf(variables, result, rowNumber, numVariables, sknfClauses, sdnfClauses);
        calculateSknfAndSdnf(variables, result, rowNumber, numVariables, sknfClauses2, sdnfClauses2);
        rowNumber++;
    }
    cout << "\nSKNF: ";
    for (size_t i = 0; i < sknfClauses.size(); ++i) {
        cout << sknfClauses[i];
        if (i != sknfClauses.size() - 1) {
            cout << " & ";
        }
    }
    cout << "\nSDNF: ";
    for (size_t i = 0; i < sdnfClauses.size(); ++i) {
        cout << sdnfClauses[i];
        if (i != sdnfClauses.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    cout << "\n";
    FirstMethod(sdnfClauses, sdnfClauses2, sknfClauses, sknfClauses2);
    vector<string> sknfClauses3;
    vector<string> sdnfClauses3;
    vector<string> sknfClauses4;
    vector<string> sdnfClauses4;
    int rowNumber2 = 0;
    for (int i = 0; i < pow(2, numVariables); ++i) {
        for (int j = 0; j < numVariables; ++j) {
            variables[j] = ((i >> (numVariables - j - 1)) & 1) == 1;
        }
        bool result = evaluateLogicalExpression(variables, expression);
        calculateSknfAndSdnf(variables, result, rowNumber2, numVariables, sknfClauses3, sdnfClauses3);
        calculateSknfAndSdnf(variables, result, rowNumber2, numVariables, sknfClauses4, sdnfClauses4);
        rowNumber2++;
    }
    cout << endl;
    cout << endl;
    SecondMethod(sdnfClauses3, sdnfClauses4, variables, numVariables, expression, rowNumber2, sknfClauses3, sknfClauses4);
    vector<string> sknfClauses5;
    vector<string> sdnfClauses5;
    vector<string> sknfClauses6;
    vector<string> sdnfClauses6;
    int rowNumber3 = 0;
    for (int i = 0; i < pow(2, numVariables); ++i) {
        for (int j = 0; j < numVariables; ++j) {
            variables[j] = ((i >> (numVariables - j - 1)) & 1) == 1;
        }
        bool result = evaluateLogicalExpression(variables, expression);
        calculateSknfAndSdnf(variables, result, rowNumber2, numVariables, sknfClauses5, sdnfClauses5);
        calculateSknfAndSdnf(variables, result, rowNumber2, numVariables, sknfClauses6, sdnfClauses6);
        rowNumber2++;
    }
    cout << endl;
    cout << endl;
    ThirdMethod(sdnfClauses5, sdnfClauses6, variables, numVariables, expression, rowNumber2, sknfClauses5, sknfClauses6);
}
