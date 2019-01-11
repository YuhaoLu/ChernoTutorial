#include <iostream>
#include <string>
#include <memory>

class Entity {
  public:
    Entity() {
        std::cout << "Created Entity!" << std::endl;
    }

    ~Entity() {
        std::cout << "Destroyed Entity!" << std::endl;
    }
    
    void Print() {

    }
};

int main() {
    // smart ptr helps to release memory automatically, no need to call delete explicitly
    {
        std::shared_ptr<Entity> e2;
        std::weak_ptr<Entity> e3;
        {
            // error: no member named 'make_unique' in namespace 'std' ==> -std=c++14
            std::unique_ptr<Entity> e0 = std::make_unique<Entity>();
            
            // shared_pt keeps track of refcount
            std::shared_ptr<Entity> e1 = std::make_shared<Entity>();

            // increase refcount
            e2 = e1;

            // not increase refcount
            e3 = e1;

            e0->Print();
        }
    }
}