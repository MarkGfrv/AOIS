#include "../Project16/Header.h"
int main() {
    setlocale(LC_ALL, "Russian");
    printTable1();
    cout << "\n";
    vector<vector<bool>> truthTableD = {
        {0, 0, 0, 0},
        {0, 0, 1, 1},
        {0, 1, 0, 1},
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 0},
        {1, 1, 1, 1}
    };
    vector<vector<bool>> truthTableV = {
        {0, 0, 0, 0},
        {0, 0, 1, 1},
        {0, 1, 0, 1},
        {0, 1, 1, 1},
        {1, 0, 0, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 0},
        {1, 1, 1, 1}
    };
    vector<vector<bool>> truthTableE = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 1, 0, 0, 1},
        {0, 1, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 1, 1, 1, 1},
        {1, 0, 0, 0, 1},
        {1, 0, 0, 1, 1}
    };
    vector<vector<bool>> truthTableF = {
       {0, 0, 0, 0, 1},
       {0, 0, 0, 1, 1},
       {0, 0, 1, 0, 1},
       {0, 0, 1, 1, 1},
       {0, 1, 0, 0, 0},
       {0, 1, 0, 1, 0},
       {0, 1, 1, 0, 0},
       {0, 1, 1, 1, 0},
       {1, 0, 0, 0, 1},
       {1, 0, 0, 1, 1}
    };
    vector<vector<bool>> truthTableG = {
       {0, 0, 0, 0, 0},
       {0, 0, 0, 1, 0},
       {0, 0, 1, 0, 1},
       {0, 0, 1, 1, 1},
       {0, 1, 0, 0, 0},
       {0, 1, 0, 1, 0},
       {0, 1, 1, 0, 1},
       {0, 1, 1, 1, 1},
       {1, 0, 0, 0, 0},
       {1, 0, 0, 1, 0}
    };
    vector<vector<bool>> truthTableH = {
       {0, 0, 0, 0, 0},
       {0, 0, 0, 1, 1},
       {0, 0, 1, 0, 0},
       {0, 0, 1, 1, 1},
       {0, 1, 0, 0, 0},
       {0, 1, 0, 1, 1},
       {0, 1, 1, 0, 0},
       {0, 1, 1, 1, 1},
       {1, 0, 0, 0, 0},
       {1, 0, 0, 1, 1}
    };

    vector<char> variableNames = { 'A', 'B', 'P' };
    vector<char> variableNames2 = { 'A', 'B', 'C', 'D' };
    vector<size_t> ignoredColumns1 = { truthTableD[0].size() - 1 };
    vector<size_t> ignoredColumns2 = { truthTableV[0].size() - 1 };
    vector<size_t> ignoredColumns3 = { 5, 6, 7 };
    vector<string> sdnfClauses;
    vector<string> sdnfClauses2;
    vector<string> sdnfClauses3;
    vector<string> sdnfClauses4;

    calculateSdnf(truthTableD, variableNames, sdnfClauses, ignoredColumns1);
    calculateSdnf(truthTableD, variableNames, sdnfClauses3, ignoredColumns1);
    calculateSdnf(truthTableV, variableNames, sdnfClauses2, ignoredColumns2);
    calculateSdnf(truthTableV, variableNames, sdnfClauses4, ignoredColumns2);

    cout << "SDNF для D:" << endl;
    for (size_t i = 0; i < sdnfClauses.size(); ++i) {
        cout << sdnfClauses[i];
        if (i != sdnfClauses.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    cout << "SDNF для V:" << endl;
    for (size_t i = 0; i < sdnfClauses2.size(); ++i) {
        cout << sdnfClauses2[i];
        if (i != sdnfClauses2.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    cout << "\n";
    vector<string> result1 = glueSDNFBy2(sdnfClauses);
    vector<string> result3 = glueSDNFBy1(result1);
    vector<string> result2 = addNotGlued(sdnfClauses3);
    result3.insert(result3.end(), result2.begin(), result2.end());
    cout << endl;
    cout << "Тупиковая форма СДНФ для D:" << endl;
    for (size_t i = 0; i < result3.size(); ++i) {
        cout << result3[i];
        if (i != result3.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    vector<string> result12 = glueSDNFBy2(sdnfClauses2);
    vector<string> result32 = glueSDNFBy1(result12);
    vector<string> result22 = addNotGlued(sdnfClauses4);
    result32.insert(result32.end(), result22.begin(), result22.end());
    cout << endl;
    cout << "Тупиковая форма СДНФ для V:" << endl;
    for (size_t i = 0; i < result32.size(); ++i) {
        cout << result32[i];
        if (i != result32.size() - 1) {
            cout << " | ";
        }
    }
    cout << "\n";
    cout << "\n";
    printTable2();
    cout << "\n";
    cout << "\n";
    size_t resultColumnIndex = truthTableE[0].size() - 1;
    printSDNF(truthTableE, truthTableF, truthTableG, truthTableH, variableNames2, resultColumnIndex);
    return 0;
}
