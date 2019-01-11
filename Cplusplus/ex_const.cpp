#include <iostream>
#include <string>

class Entity {
private: 
    int m_X, m_Y;
    mutable int var;
public:
    // Cannot modify member varibles, used for const ref parameter
    int GetX() const {
        return m_X;
    }

    int GetX() {
        return m_X;
    }

    void SetX(int X) {
        m_X = X;
    }
};


void PrintEntity(const Entity& e) {
    std::cout << e.GetX() << std::endl;
}

int main()
{
    const int MAX_AGE = 90;
    // Cannot modify the data saved at the pointer addr
    const int* a = new int;
    int const* b = new int;

    // Cannot modify pointer's pointing addr
    int* const c = new int;
    
    a = (int*) &MAX_AGE;
    b = nullptr;
    *c = 10;

    std::cout << "*a = " << *a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "*c = " << *c << std::endl;

    return 0;
}
