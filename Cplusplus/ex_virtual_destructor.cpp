#include <iostream>

class Base {
  public:
    Base() { 
        std::cout << "Base Constructor\n"; 
    }
    /* To sum up, always make base classes' destructors virtual when they're meant to be manipulated polymorphically. */
    virtual ~Base() { 
        std::cout << "Base Destructor\n"; 
    }
};

class Derived: public Base {
  private:
    int* m_Array;
  public:
    Derived() {
        m_Array = new int[5];
        std::cout << "Derived Constructor\n";
    }
    ~Derived() {
        delete[] m_Array;
        std::cout << "Derived Destructor\n";
    }
};

int main() {
    Base* base = new Base();
    delete base;
    std::cout << "-------------------------\n";

    Derived* derived = new Derived();
    delete derived;
    std::cout << "-------------------------\n";

    /*
      In most implementations, the call to the destructor will be resolved like any non-virtual code,
      meaning that the destructor of the base class will be called but not the one of the derived class, 
      resulting in a resources leak.
    */
    Base* poly = new Derived();
    delete poly;
}