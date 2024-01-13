#include <iostream>

// Virtual base class
class A {
public:
    virtual void Show() const {
        std::cout << "A\n";
    }
};

// First derived class with virtual inheritance
class B : virtual public A {};

// Second derived class with virtual inheritance
class C : virtual public A {};

// Class derived from both classes B and C
class D : public B, public C {};

int mainDS() {
    D d;

    // Accessing members of A in D, no more ambiguity
    d.Show();

    return 0;
}
