#include"../MinimizationProject/Minimization.h"
int main() {
    string expression = "a -> (b & c)";
    cout << "Entered expression: " << expression << endl;
    solveLogicalExpression(expression);

    return 0;
}
