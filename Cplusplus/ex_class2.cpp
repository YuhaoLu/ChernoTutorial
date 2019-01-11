#include <iostream>
#include <string>

class Entity
{
  private:
    int m_Score;
    std::string m_Name;
  public:
    // member initializer list (in order)
    Entity() : m_Score(0), m_Name("Unknown") {}

    Entity(const std::string& name) : m_Name(name) {}

    const std::string &GetName() const
    {
         return m_Name;
    }
};

int main()
{
    Entity e0;
    std::cout << e0.GetName() << std::endl;
    
    // stack
    Entity e1("Cherno");
    std::cout << e1.GetName() << std::endl;

    // heap
    Entity* e2 = new Entity("Yuhao");
    Entity* e3 = new Entity[10];
    delete e2;
    delete[] e3;

    int* b = new int;
    int* c = new int[50];
    delete b;
    delete[] c;
}