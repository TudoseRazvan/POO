#include <iostream>
#include <stdexcept>
using namespace std;

// Clasa custom de exceptii pentru impartire la zero
class DivisionByZeroException : public runtime_error {
public:
    DivisionByZeroException() : runtime_error("Division by zero is not allowed.") {}
};

// Clasa care efectueaza operatia de impartire si arunca exceptii
class Divider {
public:
    static double PerformDivision(double numerator, double denominator) {
        try {
            if (denominator == 0) {
                // Aruncam o exceptie de tipul nostru
                throw DivisionByZeroException();
            }
            return numerator / denominator;
        }
        catch (const DivisionByZeroException& e) {
            // Prindem si gestionam exceptia noastra
            cerr << "Custom Exception caught: " << e.what() << endl;
            // Returnam un rezultat special pentru a indica situatia exceptionala
            return numeric_limits<double>::quiet_NaN();
        }
    }
};

int mainCE() {
    try {
        double result = Divider::PerformDivision(10.0, 2.0);
        cout << "Result: " << result << endl;

        result = Divider::PerformDivision(5.0, 0.0);  // Aici se va arunca o exceptie
        cout << "Result: " << result << endl;  // Aceasta linie nu va fi executata
    }
    catch (const DivisionByZeroException& e) {
        // Prindem si gestionam exceptia noastra
        cerr << "Main function custom exception caught: " << e.what() << endl;
    }

    return 0;
}
