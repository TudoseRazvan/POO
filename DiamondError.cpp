#include <iostream>

// Base class
class A {
public:
    void Show() const {
        std::cout << "A\n";
    }
};

// First derived class
class B : public A {};

// Second derived class
class C : public A {};

// Class derived from both classes B and C
class D : public B, public C {};

int mainDE() {
    D d;

     //Error! Ambiguity in accessing members of A in D
     //d.Show(); 

    // Accessing members of A in B and C explicitly
    d.B::Show();
    d.C::Show();

    return 0;
}
