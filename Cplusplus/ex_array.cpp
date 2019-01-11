#include <iostream>
#include <array>
#include <algorithm>

template <size_t size>
void PrintArray(const std::array<int, size>& data)
{
    for (size_t i = 0; i < data.size(); i++) {
        std::cout << data[i] << std::endl;
    }
}

int main()
{
    // Allocated in the Stack Segment
    std::array<int, 5> data;
    data[0] = 5;
    data[1] = 4;
    data[2] = 3;
    data[3] = 2;
    data[4] = 1;
    PrintArray(data);

    // 2D Array -> translate it into 1D Array, keep the cache hot
    int* array =  new int[5 * 5];
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            array[x + y * 5] = 2;
        }
    }

    // Sorting
    std::array<int, 5> values = {{3, 5, 1, 4, 2}};
    PrintArray(values);
    std::sort(values.begin(), 
              values.end(), 
              [](int a, int b) {
                  return a < b;
              });
    PrintArray(values);
}