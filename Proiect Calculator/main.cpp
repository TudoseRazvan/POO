#define _CRT_SECURE_NO_WARNINGS 
#include "ExpressionEvaluator.h"
#include <iostream>

using namespace std;

void runCalculator() {
    CalculatorFinal test(" ");

    string expression;
    while (true) {
        cout << "Introduceti expresia matematica ('exit' pentru a iesi): ";
        getline(cin, expression);

        if (expression == "exit") {
            break;
        }

        test.setExpression(expression);
        double result = test.evaluateExpression();

        char formattedResult[100];
        removeZeroes(result, formattedResult, sizeof(formattedResult));

        std::cout << "Rezultatul expresiei este: " << formattedResult << std::endl;
        cout << "Expresie: " << test.getExpression() << endl;
        cout << test.getExpressionHistory() << endl;
    }
}

int main() {
    cout << "Bine ati venit!" << endl;
    runCalculator();

    cout << "Programul s-a incheiat.\n";
    return 0;
}