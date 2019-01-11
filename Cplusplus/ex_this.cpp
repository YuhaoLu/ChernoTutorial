#include <iostream>
#include <string>

void PrintEntity(const Entity& e);

class Entity {
  public:
    int x, y;

    Entity(int x, int y) {
        this->x = x;
        this->y = y;

        Entity& e = *this;

        PrintEntity(*this);
    }

    int GetX() const {
        const Entity& e = *this;
    }
};

void PrintEntity(const Entity& e){

}

int main() {

}