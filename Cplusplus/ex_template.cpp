#include <iostream>
#include <string>

// Don't make it too complicate, suitable for multiple type processing like logging
template <typename T, int N>
class Array {
  private:
    T m_Array[N];

  public:
    int GetSize() const {
        return N;
    }
};

template <typename T>
void Print(T value) {
    std::cout << value << std::endl;
}

int main() {
    Print<int>(5);
    Print("Hello");
    Print(5.5f);

    Array<int, 5> arr;
}