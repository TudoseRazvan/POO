#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

class ExpressionEvaluator {
public:
    //Constructor fara parametrii
    ExpressionEvaluator() : expression(nullptr) {}

    //Constructor cu parametrii
    static double evaluate(const char* expression) {
        return evaluateExpression(expression, 0, std::strlen(expression));
    }

    // Operator de indexare []
    char operator[](size_t index) const {
        if (index < strlen(expression)) {
            return expression[index];
        }
        else {
            std::cerr << "Index invalid pentru operatorul [].";
            return '\0';
        }
    }

    void setExpression(const char* newExpression) {
        delete[] expression;
        expression = new char[strlen(newExpression) + 1];
        strcpy_s(expression, strlen(newExpression) + 1, newExpression);
    }

    static const char* concatenate(const char* expr1, const char* expr2) {
        size_t len1 = std::strlen(expr1);
        size_t len2 = std::strlen(expr2);
        char* result = new char[len1 + len2 + 1];

        strcpy_s(result, len1 + 1, expr1);
        strcpy_s(result + len1, len2 + 1, expr2);

        return result;
    }

    const char* getExpression() const {
        return expression;
    }

    //Operator+
    ExpressionEvaluator operator+(const ExpressionEvaluator& other) const {
        ExpressionEvaluator result;
        result.setExpression(concatenate(expression, other.getExpression()));
        return result;
    }

    //Destructor
    ~ExpressionEvaluator() {
        delete[] expression;
    }

    friend istream& operator>>(std::istream& in, ExpressionEvaluator& evaluator);
    friend ostream& operator<<(std::ostream& out, const ExpressionEvaluator& evaluator);

private:
    static double evaluateExpression(const char* expression, int start, int end) {
        double result = 0.0;
        double currentOperand = 0.0;
        char currentOperator = '+';
        int nested = 0; // Ordinea parantezelor

        for (int i = start; i < end; ++i) {
            char currentChar = expression[i];

            if (std::isdigit(currentChar) || currentChar == '.') {
                double decimalValue = 0.0;
                double decimalMultiplier = 0.1;
                bool isDecimal = false;

                while (std::isdigit(currentChar) || currentChar == '.') {
                    if (currentChar == '.') {
                        isDecimal = true;
                    }
                    else {
                        if (!isDecimal) {
                            currentOperand = currentOperand * 10 + (currentChar - '0');
                        }
                        else {
                            decimalValue += (currentChar - '0') * decimalMultiplier;
                            decimalMultiplier *= 0.1;
                        }
                    }
                    ++i;
                    currentChar = expression[i];
                }

                currentOperand += decimalValue;
                --i;
            }
            else if (currentChar == '(' || currentChar == '[') {
                ++nested;
                int closingIndex = findClosing(expression, i, end, currentChar);
                currentOperand = evaluateExpression(expression, i + 1, closingIndex);
                i = closingIndex;
            }
            else if (currentChar == ')' || currentChar == ']') {
                --nested;
            }
            else if ((currentChar == '^' || currentChar == '#') && nested == 0) {
                char currentOperator = currentChar;
                int operandStart = i + 1;
                int operandEnd = findNextOperandEnd(expression, operandStart, end);

                double operand = evaluateExpression(expression, operandStart, operandEnd);
                if (currentOperator == '^') {
                    currentOperand = std::pow(currentOperand, operand);
                }
                else if (currentOperator == '#') {
                    currentOperand = std::pow(operand, 1.0 / currentOperand);
                }
                i = operandEnd - 1;
            }
            else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
                result = applyOperator(result, currentOperand, currentOperator);
                currentOperator = currentChar;
                currentOperand = 0.0;
            }
        }

        result = applyOperator(result, currentOperand, currentOperator);
        return result;
    }

    char* expression;
    static double applyOperator(double operand1, double operand2, char op) {
        switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 != 0) {
                return operand1 / operand2;
            }
            else {
                std::cerr << "Nu se poate imparti la zero." << std::endl;
                return 0.0;
            }
        case '^':
            return std::pow(operand1, operand2); 
        case '#':
            return std::pow(operand1, 1.0 / operand2);
        default:
            return 0.0;
        }
    }

    static int findClosing(const char* expression, int start, int end, char open) {
        char close = (open == '(') ? ')' : ']';
        int nested = 1;

        for (int i = start + 1; i < end; ++i) {
            if (expression[i] == open) {
                ++nested;
            }
            else if (expression[i] == close) {
                --nested;
                if (nested == 0) {
                    return i;
                }
            }
        }
        return -1;
    }

    static int findNextOperandEnd(const char* expression, int start, int end) {
        for (int i = start; i < end; ++i) {
            if (!std::isdigit(expression[i]) && expression[i] != '.') {
                return i - 1;
            }
        }
        return end - 1;
    }

    static const char* substring(const char* expression, int startIndex, int endIndex) {
        int length = endIndex - startIndex + 1;
        char* sub = new char[length + 1];
        std::strncpy(sub, expression + startIndex, length);
        sub[length] = '\0';
        return sub;
    }
};

std::ostream& operator<<(std::ostream& out, const ExpressionEvaluator& evaluator) {
    out << "ExpressionEvaluator: Implementati afisarea aici";
    return out;
}

std::istream& operator>>(std::istream& in, ExpressionEvaluator& evaluator) {
    std::cout << "Introduceti expresia pentru ExpressionEvaluator: ";
    in >> evaluator;
    return in;
}

class Calculator {
private:
    string expression;
    double result;

public:
    //Constructor fara parametrii
    Calculator() : expression(" "), result(0.0) {}

    //Constructor cu parametrii
    Calculator(const string& expr) : expression(expr) {}

    //Cast implicit
    operator double() const {
        return static_cast<double>(expression.length());
    }

    //Pre-incrementare
    Calculator& operator++() {
        result += 1.0;
        return *this;
    }

    virtual double evaluateExpression() = 0;

    const string& getExpression() const {
        return expression;
    }

    void setExpression(const string& newExpression) {
        expression = newExpression;
    }

    char operator[](size_t index) const {
        if (index < expression.length()) {
            return expression[index];
        }
        else {
            cerr << "Index invalid pentru operatorul [].";
            return '\0';
        }
    }

    bool isEmpty() const {
        return expression.empty();
    }

    friend istream& operator>>(istream& in, Calculator& calc);
    friend ostream& operator<<(ostream& out, const Calculator& calc);

};

istream& operator>>(istream& in, Calculator& calc) {
    cout << "Introduceti expresia matematica: ";
    getline(in, calc.expression);

    // Curatare buffer
    in.ignore(numeric_limits<streamsize>::max(), '\n');

    return in;
}


ostream& operator<<(ostream& out, const Calculator& calc) {
    out << "Expresie: " << calc.getExpression();
    return out;
}

class BasicOperations : public Calculator {
public:
    //Constructor fara parametrii
    BasicOperations() : Calculator(" ") {}
    //Constructor cu parametrii
    BasicOperations(const string& expr) : Calculator(expr) {}

    double evaluateExpression() override {
        string expr = getExpression();
        return evaluateModifiedExpression(expr);
    }

protected:
    double evaluateModifiedExpression(const string& expr) {
        size_t startPos = 0;
        string modifiedExpr = expr;

        while (startPos < modifiedExpr.length()) {
            size_t powerPos = modifiedExpr.find('^', startPos);
            size_t rootPos = modifiedExpr.find('#', startPos);

            if (powerPos == string::npos && rootPos == string::npos) {
                return ExpressionEvaluator::evaluate(modifiedExpr.c_str());
            }

            if ((rootPos < powerPos && rootPos != string::npos) || powerPos == string::npos) {
                double base = stod(modifiedExpr.substr(startPos, rootPos - startPos));
                double order = stod(modifiedExpr.substr(rootPos + 1));
                double result = pow(base, 1.0 / order);

                modifiedExpr.replace(startPos, rootPos - startPos + to_string(result).length() + 1, to_string(result));
            }
            else {
                size_t endPos = findExpressionEnd(modifiedExpr, powerPos + 1);
                double base = evaluateModifiedExpression(modifiedExpr.substr(startPos, powerPos - startPos));
                double exponent = evaluateModifiedExpression(modifiedExpr.substr(powerPos + 1, endPos - powerPos - 1));
                double result = pow(base, exponent);

                modifiedExpr.replace(startPos, endPos - startPos + to_string(result).length() + 1, to_string(result));
            }

            startPos = 0;
        }

        return 0.0;
    }

private:
    size_t findExpressionEnd(const string& expr, size_t start) {
        int count = 0;
        for (size_t i = start; i < expr.length(); ++i) {
            if (expr[i] == '(') {
                ++count;
            }
            else if (expr[i] == ')') {
                --count;
                if (count == 0) {
                    return i;
                }
            }
        }
        return expr.length();
    }
};

ostream& operator<<(std::ostream& out, const BasicOperations& basicOp) {
    out << "BasicOperations: Implementati afisarea aici";
    return out;
}

istream& operator>>(istream& in, BasicOperations& basicOp) {
    std::cout << "Introduceti datele pentru BasicOperations: ";
    in >> basicOp;
    return in;
}


class ScientificCalculator : public BasicOperations {
public:
    ScientificCalculator(const string& expr) : BasicOperations(expr) {}
    double evaluateExpression() override {
        return evaluateModifiedExpression(getExpression());
    }

    friend ostream& operator<<(ostream& out, const ScientificCalculator& scientificCalc);
    friend istream& operator>>(istream& in, ScientificCalculator& scientificCalc);

private:
    double evaluateModifiedExpression(const string& expr) {
        // Reutilizeaza logica de la BasicOperations
        return BasicOperations::evaluateModifiedExpression(expr);
    }
};

ostream& operator<<(ostream& out, const ScientificCalculator& scientificCalc) {
    out << "ScientificCalculator: Implementati afisarea aici";
    return out;
}

istream& operator>>(istream& in, ScientificCalculator& scientificCalc) {
    std::cout << "Introduceti datele pentru ScientificCalculator: ";
    in >> scientificCalc;
    return in;
}

class CalculatorFinal : public ScientificCalculator {
private:
    char* expressionHistory; //Sir de caractere alocat dinamic
    double* numericVector; // Vector numeric alocat dinamic

public:
    //Constructor fara parametrii
    CalculatorFinal() : ScientificCalculator(""), expressionHistory(nullptr), numericVector(nullptr) {}

    //Constructor cu parametrii
    CalculatorFinal(const string& expr) : ScientificCalculator(expr), expressionHistory(nullptr), numericVector(nullptr) {}

    //Destructor
    ~CalculatorFinal() {
        delete[] expressionHistory;
        delete[] numericVector;
    }

    double evaluateExpression() override {
        double result = ScientificCalculator::evaluateExpression();

        // Adauga expresia in istoric
        appendToHistory(getExpression().c_str());
        processNumericVector();

        return result;
    }

    // Metoda pentru adaugarea expresiei in istoric
    void appendToHistory(const char* expression) {
        if (expressionHistory == nullptr) {
            expressionHistory = new char[strlen(expression) + 1];
            strcpy(expressionHistory, expression);
        }
        else {
            char* newHistory = new char[strlen(expressionHistory) + strlen(expression) + 2];
            strcpy(newHistory, expressionHistory);
            strcat(newHistory, "\n");
            strcat(newHistory, expression);

            delete[] expressionHistory;
            expressionHistory = newHistory;
        }
    }

    // Metoda vector numeric alocat dinamic
    void processNumericVector() {
        numericVector = new double[10];

        for (int i = 0; i < 10; ++i) {
            numericVector[i] = i * 1.5;
        }
    }

    // Operator= (de atribuire)
    CalculatorFinal& operator=(const CalculatorFinal& other) {
        if (this != &other) {
            ScientificCalculator::operator=(other);
            delete[] expressionHistory;
            delete[] numericVector;
            expressionHistory = nullptr;
            numericVector = nullptr;
            copyFrom(other);
        }
        return *this;
    }

    // Operatorul==
    bool operator==(const CalculatorFinal& other) const {
        // Compara istoricul pentru a verifica daca sunt identice
        if (expressionHistory == nullptr && other.expressionHistory == nullptr) {
            return true;
        }

        if (expressionHistory == nullptr || other.expressionHistory == nullptr) {
            return false;
        }

        return std::strcmp(expressionHistory, other.expressionHistory) == 0;
    }

    // Operatorul!
    bool operator!() const {
        return expressionHistory == nullptr || expressionHistory[0] == '\0';
    }

    // Getter istoric
    const char* getExpressionHistory() const {
        return expressionHistory;
    }

    // Setter istoric
    void setExpressionHistory(const char* newHistory) {
        delete[] expressionHistory;
        expressionHistory = new char[strlen(newHistory) + 1];
        strcpy(expressionHistory, newHistory);
    }

    friend ostream& operator<<(ostream& out, const CalculatorFinal& calcWithHistory);
    friend istream& operator>>(istream& in, CalculatorFinal& calcWithHistory);

private:
    // Metoda pentru a realiza o copie de la alt obiect
    void copyFrom(const CalculatorFinal& other) {
        expressionHistory = new char[strlen(other.expressionHistory) + 1];
        strcpy(expressionHistory, other.expressionHistory);
    }
};

ostream& operator<<(ostream& out, const CalculatorFinal& calcFinal) {
    if (calcFinal.getExpressionHistory() != nullptr) {
        out << "Istoricul operatiilor:" << endl;
        out << calcFinal.getExpressionHistory();
    }
    else {
        out << "Istoricul este gol.";
    }
    return out;
}

istream& operator>>(istream& in, CalculatorFinal& calcFinal) {
    cout << "Introduceti datele pentru CalculatorFinal: ";
    in >> calcFinal;
    return in;
}

//Elimina zerourile
void removeZeroes(double number, char* result, int bufLen) {
    int written = snprintf(result, bufLen, "%.15g", number);
    bool dotFound = false;
    int lastZero = -1;

    for (int i = 0; i < written; ++i) {
        if (result[i] == '.') {
            dotFound = true;
        }
        else if (dotFound && result[i] == '0') {
            lastZero = i;
        }
        else {
            lastZero = -1;
        }
    }

    if (lastZero != -1) {
        result[lastZero] = '\0';
        if (result[lastZero - 1] == '.') {
            result[lastZero - 1] = '\0';
        }
    }
}

#endif