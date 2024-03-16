#include"../Project11/LogicalExxpresion.h"
int main() {
    string expression = "(a -> b) | (c & !d)";

    solveExpression(expression);

    return 0;
}