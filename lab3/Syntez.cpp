#include "Header.h"
void calculateSdnf(const vector<vector<bool>>& truthTable, const vector<char>& variableNames, vector<string>& sdnfClauses, const vector<size_t>& ignoredColumns) {
    if (truthTable.empty() || variableNames.empty()) {
        cout << "Некорректные данные" << endl;
        return;
    }
    for (size_t i = 0; i < ignoredColumns.size(); ++i) {
        if (ignoredColumns[i] >= truthTable[0].size()) {
            cout << "Некорректный номер игнорируемого столбца" << endl;
            return;
        }
    }

    size_t resultIndex = truthTable[0].size();
    for (size_t i = ignoredColumns.size(); i > 0; --i) {
        if (resultIndex - 1 == ignoredColumns[i - 1]) {
            resultIndex--;
        }
    }
    for (size_t i = 0; i < truthTable.size(); ++i) {
        if (truthTable[i][resultIndex]) {
            string sdnfClause = "(";
            for (size_t j = 0; j < truthTable[i].size(); ++j) {
                if (find(ignoredColumns.begin(), ignoredColumns.end(), j) != ignoredColumns.end()) {
                    continue;
                }
                if (!truthTable[i][j]) {
                    sdnfClause += "(!" + string(1, variableNames[j]) + ")";
                }
                else {
                    sdnfClause += string(1, variableNames[j]);
                }
                if (j != resultIndex - 1) {
                    sdnfClause += " & ";
                }
            }
            sdnfClause += ")";
            sdnfClauses.push_back(sdnfClause);
        }
    }
}
void calculateSdnfFor2Task(const vector<vector<bool>>& truthTable, const vector<char>& variableNames, vector<string>& sdnfClauses, size_t resultColumnIndex) {
    if (truthTable.empty() || variableNames.empty() || resultColumnIndex >= truthTable[0].size()) {
        cout << "Некорректные данные" << endl;
        return;
    }

    for (size_t i = 0; i < truthTable.size(); ++i) {
        if (truthTable[i][resultColumnIndex]) {
            string sdnfClause = "(";
            bool isFirstVariable = true;
            for (size_t j = 0; j < truthTable[i].size(); ++j) {
                if (j != resultColumnIndex) {
                    if (!truthTable[i][j]) {
                        if (!isFirstVariable) {
                            sdnfClause += " & ";
                        }
                        sdnfClause += "(!" + string(1, variableNames[j]) + ")";
                    }
                    else {
                        if (!isFirstVariable) {
                            sdnfClause += " & ";
                        }
                        sdnfClause += string(1, variableNames[j]);
                    }
                    isFirstVariable = false;
                }
            }
            sdnfClause += ")";
            sdnfClauses.push_back(sdnfClause);
        }
    }
}
vector<string> glueSDNFBy2(vector<string>& sdnfClauses) {
    vector<string> newSdnfClauses;
    for (size_t i = 0; i < sdnfClauses.size(); ++i) {
        for (size_t j = i + 1; j < sdnfClauses.size(); ++j) {
            vector<pair<char, bool>> variableStates1;
            vector<pair<char, bool>> variableStates2;
            bool negation1 = false;
            bool negation2 = false;

            // Parse the clauses and extract variable states
            for (char c : sdnfClauses[i]) {
                if (isalpha(c)) {
                    variableStates1.emplace_back(c, negation1);
                }
                else if (c == '!') {
                    negation1 = true;
                }
                else if (c == ' ') {
                    negation1 = false;
                }
            }
            for (char c : sdnfClauses[j]) {
                if (isalpha(c)) {
                    variableStates2.emplace_back(c, negation2);
                }
                else if (c == '!') {
                    negation2 = true;
                }
                else if (c == ' ') {
                    negation2 = false;
                }
            }

            // Check if both clauses have two identical pairs of variables at the same positions
            int pairCount = 0;
            bool sameSymbols = true; // Flag to check if remaining variables are same symbols
            for (size_t k = 0; k < variableStates1.size(); ++k) {
                if (variableStates1[k].first == variableStates2[k].first &&
                    variableStates1[k].second == variableStates2[k].second) {
                    pairCount++;
                }
                else if (variableStates1[k].first != variableStates2[k].first) {
                    sameSymbols = false;
                }
            }

            if (pairCount == 2 && sameSymbols) { // If two identical pairs found and remaining variables have same symbols
                string newClause;
                for (size_t k = 0; k < variableStates1.size(); ++k) {
                    if (variableStates1[k].first == variableStates2[k].first &&
                        variableStates1[k].second == variableStates2[k].second) {
                        if (!newClause.empty()) {
                            newClause += " & ";
                        }
                        if (variableStates1[k].second) {
                            newClause += '!';
                        }
                        newClause += variableStates1[k].first;
                    }
                }
                if (!newClause.empty()) { // Ensure the new clause is not empty
                    newSdnfClauses.push_back("(" + newClause + ")");
                }
            }
        }
    }

    // Remove duplicates
    unordered_set<string> uniqueClauses;
    vector<string> uniqueSdnfClauses;
    for (const auto& clause : newSdnfClauses) {
        if (uniqueClauses.find(clause) == uniqueClauses.end()) {
            uniqueClauses.insert(clause);
            uniqueSdnfClauses.push_back(clause);
        }
    }

    return uniqueSdnfClauses;
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
        if (glued[i]) continue;
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
vector<string> mergeSdnf(const vector<string>& sdnfClauses) {
    vector<string> newSdnfClauses;

    for (const auto& clause : sdnfClauses) {
        vector<pair<char, bool>> variableStates;
        bool negation = false;

        // Parse the clause and extract variable states
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

        // Generate new clauses by combining pairs of variables
        for (size_t i = 0; i < variableStates.size(); ++i) {
            for (size_t j = i + 1; j < variableStates.size(); ++j) {
                for (size_t k = j + 1; k < variableStates.size(); ++k) {
                    string newClause;
                    // Append first variable
                    if (variableStates[i].second) {
                        newClause += '!';
                    }
                    newClause += variableStates[i].first;
                    newClause += " & ";

                    // Append second variable
                    if (variableStates[j].second) {
                        newClause += '!';
                    }
                    newClause += variableStates[j].first;
                    newClause += " & ";

                    // Append third variable
                    if (variableStates[k].second) {
                        newClause += '!';
                    }
                    newClause += variableStates[k].first;
                    newSdnfClauses.push_back("(" + newClause + ")");
                }
            }
        }
    }

    // Remove duplicates
    unordered_map<string, int> clauseCount;
    for (const auto& clause : newSdnfClauses) {
        clauseCount[clause]++;
    }
    auto it = remove_if(newSdnfClauses.begin(), newSdnfClauses.end(), [&](const string& clause) {
        return clauseCount[clause] == 1;
        });
    newSdnfClauses.erase(it, newSdnfClauses.end());

    unordered_set<string> uniqueClauses;
    vector<string> uniqueSdnfClauses;
    for (const auto& clause : newSdnfClauses) {
        if (uniqueClauses.find(clause) == uniqueClauses.end()) {
            uniqueClauses.insert(clause);
            uniqueSdnfClauses.push_back(clause);
        }
    }

    return uniqueSdnfClauses;
}


void printSDNF(const vector<vector<bool>>& truthTable, const vector<vector<bool>>& truthTable2, const vector<vector<bool>>& truthTable3, const vector<vector<bool>>& truthTable4, const vector<char>& variableNames, size_t resultColumnIndex) {
    vector<string> sdnfClauses;
    vector<string> sdnfClauses2;
    vector<string> sdnfClauses3;
    vector<string> sdnfClauses4;
    calculateSdnfFor2Task(truthTable, variableNames, sdnfClauses, resultColumnIndex);
    calculateSdnfFor2Task(truthTable2, variableNames, sdnfClauses2, resultColumnIndex);
    calculateSdnfFor2Task(truthTable3, variableNames, sdnfClauses3, resultColumnIndex);
    calculateSdnfFor2Task(truthTable4, variableNames, sdnfClauses4, resultColumnIndex);
    cout << "SDNF for E:" << endl;
    for (size_t i = 0; i < sdnfClauses.size(); ++i) {
        cout << sdnfClauses[i];
        if (i != sdnfClauses.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    vector<string> result = mergeSdnf(sdnfClauses);
    cout << "Склеивание СДНФ: " << endl;
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i != result.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    vector<string> resk = glueSDNFBy2(result);
    cout << "Тупиковая форма СДНФ: " << endl;
    for (size_t i = 0; i < resk.size(); ++i) {
        cout << resk[i];
        if (i != resk.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    cout << "\n";
    cout << "SDNF for F:" << endl;
    for (size_t i = 0; i < sdnfClauses2.size(); ++i) {
        cout << sdnfClauses2[i];
        if (i != sdnfClauses2.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    vector<string> result2 = mergeSdnf(sdnfClauses2);
    cout << "Склеивание СДНФ: " << endl;
    for (size_t i = 0; i < result2.size(); ++i) {
        cout << result2[i];
        if (i != result2.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    vector<string> resk2 = glueSDNFBy2(result2);
    cout << "Тупиковая форма СДНФ: " << endl;
    for (size_t i = 0; i < resk2.size(); ++i) {
        cout << resk2[i];
        if (i != resk2.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    cout << "\n";
    cout << "SDNF for G:" << endl;
    for (size_t i = 0; i < sdnfClauses3.size(); ++i) {
        cout << sdnfClauses3[i];
        if (i != sdnfClauses3.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    vector<string> result3 = mergeSdnf(sdnfClauses3);
    cout << "Склеивание СДНФ: " << endl;
    for (size_t i = 0; i < result3.size(); ++i) {
        cout << result3[i];
        if (i != result3.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    vector<string> resk3 = glueSDNFBy2(result3);
    cout << "Тупиковая форма СДНФ: " << endl;
    for (size_t i = 0; i < resk3.size(); ++i) {
        cout << resk3[i];
        if (i != resk3.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    cout << "\n";
    cout << "SDNF for H:" << endl;
    for (size_t i = 0; i < sdnfClauses4.size(); ++i) {
        cout << sdnfClauses4[i];
        if (i != sdnfClauses4.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    vector<string> result4 = mergeSdnf(sdnfClauses4);
    cout << "Склеивание СДНФ: " << endl;
    for (size_t i = 0; i < result4.size(); ++i) {
        cout << result4[i];
        if (i != result4.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    vector<string> resk4 = glueSDNFBy2(result4);
    cout << "Тупиковая форма СДНФ: " << endl;
    for (size_t i = 0; i < resk4.size(); ++i) {
        cout << resk4[i];
        if (i != resk4.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
}
void printTable1() {
    int inputs[8][3] = {
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 0},
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1}
    };
    int outputs[8][2] = {
        {0, 0},
        {1, 1},
        {1, 1},
        {0, 1},
        {1, 0},
        {0, 0},
        {0, 0},
        {1, 1}
    };
    cout << "A   B   P     |   D   V\n";
    for (int i = 0; i < 8; ++i) {
        std::cout << inputs[i][0] << "   " << inputs[i][1] << "   " << inputs[i][2] << "     |   "
            << outputs[i][0] << "   " << outputs[i][1] << "\n";
    }
}
void printTable2() {
    int inputs[10][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 0, 1, 1},
        {0, 1, 0, 0},
        {0, 1, 0, 1},
        {0, 1, 1, 0},
        {0, 1, 1, 1},
        {1, 0, 0, 0},
        {1, 0, 0, 1}
    };
    int outputs[10][4] = {
        {0, 1, 0, 0},
        {0, 1, 0, 1},
        {0, 1, 1, 0},
        {0, 1, 1, 1},
        {1, 0, 0, 0},
        {1, 0, 0, 1},
        {1, 0, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 0},
        {1, 1, 0, 1}
    };

    // Вывод заголовков
    cout << "A   B   C   D     |   E   F   G   H\n";

    // Вывод таблицы
    for (int i = 0; i < 10; ++i) {
        std::cout << inputs[i][0] << "   " << inputs[i][1] << "   " << inputs[i][2] << "   " << inputs[i][3] << "     |   "
            << outputs[i][0] << "   " << outputs[i][1] << "   " << outputs[i][2] << "   " << outputs[i][3] << "\n";
    }
}
