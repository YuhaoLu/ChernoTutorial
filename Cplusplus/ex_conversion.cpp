#include <iostream>
#include <string>

class Entity {
  private:
    std::string m_Name;
    int m_Age;

  public:
    Entity(const std::string& name)
        : m_Name(name), m_Age(-1) {}
        
    // explicit - no inplicit type conversion
    explicit Entity(int age)
        : m_Name("Unknown"), m_Age(age) {}

};

void PrintEntity(const Entity& e) {
}

int main(int argc, char const *argv[])
{

    Entity a = std::string("Cherno");
    Entity b = 22;

    PrintEntity(22);
    PrintEntity(std::string("Cherno"));

}
