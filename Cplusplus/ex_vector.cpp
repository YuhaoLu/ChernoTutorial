#include <iostream>
#include <string>
#include <vector>

struct Vertex {
    float x, y, z;
    
    Vertex(float x, float y, float z)
        : x(x), y(y), z(z)
    {
    }

    Vertex(const Vertex& vertex) 
        : x(vertex.x), y(vertex.y), z(vertex.z)
    {
        std::cout << "Copied" << std::endl;
    }
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex) {
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z << std::endl;
    return stream;
}

int main() {

    // Allocated in the Heap Segment
    std::vector<Vertex> vertices;
    vertices.reserve(3);

    // vertices.push_back(Vertex(1, 2, 3));
    // vertices.push_back(Vertex(4, 5, 6));
    // vertices.push_back(Vertex(7, 8, 9));

    vertices.emplace_back(1, 2, 3);
    vertices.emplace_back(4, 5, 6);
    vertices.emplace_back(7, 8, 9);

    for (int i = 0; i < vertices.size(); i++) {
        std::cout << vertices[i] << std::endl;
    }

    vertices.erase(vertices.begin() + 1);

    for (Vertex &v : vertices) {
        std::cout << v << std::endl;
    }

    // vertices.clear();
}