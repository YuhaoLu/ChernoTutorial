#include <iostream>

struct Entity {
    int x, y;
};

struct Vector2 {
    float x, y;
};

struct Vector4 {
    // different interpretation of the same data content
    union {
        struct {
            float x, y, z, w;
        };
        struct {
            Vector2 a, b;
        };
    };
};

void PrintVector2(const Vector2& vector) {
    std::cout << vector.x << ", " << vector.y << std::endl;
}

int main() {
    Entity e = {5, 8};

    int* position = (int*)&e;
    std::cout << position[0] << ", " << position[1] << std::endl;

    int y = *(int *) ((char *)&e + 4);
    std::cout << y << std::endl;

    std::cout << "------------------------" << std::endl;
    Vector4 vector = {1.0f, 2.0f, 3.0f, 4.0f};
    PrintVector2(vector.a);
    vector.z = 50.0f;
    PrintVector2(vector.b);
}