#include <iostream>
#include <vector>

void ForEach(const std::vector<int>& values, void (*func)(int)) {
    for(int value : values) {
        func(value);
    }
}

int main() {
    std::vector<int> values = {1, 5, 4, 2, 3};
    auto it = std::find_if(values.begin(), values.end(), [](int value) { return value > 3; });
    std::cout << "Value > 3: " << *it << std::endl;
    
    ForEach(values, 
           // lamda func
           // [=] - pass everything by value, [&] - pass everything by ref
           [](int value){std::cout << "Values: " << value << std::endl;}
           );
}