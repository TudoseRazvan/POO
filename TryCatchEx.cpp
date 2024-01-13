#include <iostream>
#include <stdexcept>

// Functie care efectueaza impartirea si arunca o exceptie in caz de impartire la zero
double PerformDivision(double numerator, double denominator) {
    // Utilizam blocul try pentru a gestiona posibilele exceptii
    try {
        if (denominator == 0) {
            // Aruncam o exceptie daca incercam sa impartim la zero
            throw std::runtime_error("Division by zero is not allowed.");
        }
        // Daca nu exista exceptie, returnam rezultatul impartirii
        return numerator / denominator;
    }
    catch (const std::exception& e) {
        // Prindem si gestionam exceptiile standard C++
        std::cerr << "Exception caught: " << e.what() << std::endl;
        // Returnam un rezultat de valoare speciala pentru a indica o situatie exceptionala
        return std::numeric_limits<double>::quiet_NaN(); // NaN (Not a Number)
    }
}

int mainTCE() {
    // Utilizam functia PerformDivision in blocuri try-catch
    try {
        double result = PerformDivision(10.0, 2.0);
        std::cout << "Result: " << result << std::endl;

        result = PerformDivision(5.0, 0.0);  // Aici se va arunca o exceptie
        std::cout << "Result: " << result << std::endl;  // Aceasta linie nu va fi executata
    }
    catch (const std::exception& e) {
        // Prindem si gestionam exceptiile standard C++
        std::cerr << "Main function exception caught: " << e.what() << std::endl;
    }

    return 0;
}
