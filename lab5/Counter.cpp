#include "Header.h"
void calculateSdnf(const vector<vector<bool>>& truthTable, const vector<char>& variableNames, vector<string>& sdnfClauses, size_t resultColumnIndex) {
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
    unordered_set<string> mergedClauses;

    for (size_t i = 0; i < sdnfClauses.size(); ++i) {
        for (size_t j = i + 1; j < sdnfClauses.size(); ++j) {
            vector<pair<char, bool>> variableStates1;
            vector<pair<char, bool>> variableStates2;
            bool negation1 = false;
            bool negation2 = false;
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
            int pairCount = 0;
            bool sameSymbols = true;
            for (size_t k = 0; k < variableStates1.size(); ++k) {
                if (variableStates1[k].first == variableStates2[k].first &&
                    variableStates1[k].second == variableStates2[k].second) {
                    pairCount++;
                }
                else if (variableStates1[k].first != variableStates2[k].first) {
                    sameSymbols = false;
                }
            }
            if (pairCount == 2 && sameSymbols) {
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
                if (!newClause.empty()) {
                    newSdnfClauses.push_back("(" + newClause + ")");
                    mergedClauses.insert(sdnfClauses[i]);
                    mergedClauses.insert(sdnfClauses[j]);
                }
            }
        }
    }
    for (const auto& clause : sdnfClauses) {
        if (mergedClauses.find(clause) == mergedClauses.end()) {
            newSdnfClauses.push_back(clause);
        }
    }
    unordered_set<string> uniqueClauses(newSdnfClauses.begin(), newSdnfClauses.end());
    newSdnfClauses.assign(uniqueClauses.begin(), uniqueClauses.end());

    return newSdnfClauses;
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
                for (size_t k = j + 1; k < variableStates.size(); ++k) {
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
                    newClause += " & ";
                    if (variableStates[k].second) {
                        newClause += '!';
                    }
                    newClause += variableStates[k].first;
                    newSdnfClauses.push_back("(" + newClause + ")");
                }
            }
        }
    }
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

void printSDNF(vector<vector<bool>> truthTableI, vector<vector<bool>> truthTableH, vector<vector<bool>> truthTableG, vector<char> variableNames, size_t resultColumnIndex) {
    vector<string> sdnfClauses1;
    vector<string> sdnfClauses2;
    vector<string> sdnfClauses3;
    calculateSdnf(truthTableI, variableNames, sdnfClauses1, resultColumnIndex);
    calculateSdnf(truthTableH, variableNames, sdnfClauses2, resultColumnIndex);
    calculateSdnf(truthTableG, variableNames, sdnfClauses3, resultColumnIndex);
    cout << "\n";
    cout << "SDNF for I:" << endl;
    for (size_t i = 0; i < sdnfClauses1.size(); ++i) {
        cout << sdnfClauses1[i];
        if (i != sdnfClauses1.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    vector<string> result1 = mergeSdnf(sdnfClauses1);
    cout << "\n";
    vector<string> resk1 = glueSDNFBy2(result1);
    vector<string> result6 = glueSDNFBy1(resk1);
    cout << "Тупиковая форма СДНФ: " << endl;
    for (size_t i = 0; i < result6.size(); ++i) {
        cout << result6[i];
        if (i != result6.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "SDNF for H:" << endl;
    for (size_t i = 0; i < sdnfClauses2.size(); ++i) {
        cout << sdnfClauses2[i];
        if (i != sdnfClauses2.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    vector<string> result2 = mergeSdnf(sdnfClauses2);
    cout << "\n";
    vector<string> resk2 = glueSDNFBy2(result2);
    vector<string> result5 = glueSDNFBy1(resk2);
    cout << "Тупиковая форма СДНФ: " << endl;
    for (size_t i = 0; i < result5.size(); ++i) {
        cout << result5[i];
        if (i != result5.size() - 1) {
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
    cout << "\n";
    vector<string> resk3 = glueSDNFBy2(result3);
    vector<string> result4 = glueSDNFBy1(resk3);
    cout << "Тупиковая форма СДНФ: " << endl;
    for (size_t i = 0; i < result4.size(); ++i) {
        cout << result4[i];
        if (i != result4.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    cout << "\n";
}
void printTable() {
    const int rows = 10;
    const int cols = 16;

    char labels[rows] = { 'V', 'C', 'B', 'A', 'F', 'E', 'D', 'I', 'H', 'G' };
    int table[rows][cols] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
        {1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0},
        {0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    for (int i = 0; i < rows; ++i) {
        std::cout << labels[i] << "  ";
        for (int j = 0; j < cols; ++j) {
            std::cout << table[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
