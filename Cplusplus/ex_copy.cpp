#include <iostream>
#include <string>

class String {
  private:
    char* m_Buffer;
    unsigned int m_Size;
  public:
    String(const char* string) {
        m_Size = strlen(string);
        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer, string, m_Size);
        m_Buffer[m_Size] = 0;
    }

    // Copy Constructor
    String(const String& other) 
        : m_Size(other.m_Size)
    {
        // Deep Copy
        m_Buffer = new char[m_Size + 1];
        memcpy(m_Buffer, other.m_Buffer, m_Size + 1);

        std::cout << "Copied String!" << std::endl;
    }

    ~String() {
        delete[] m_Buffer;
    }

    char& operator[](unsigned int index) {
        return m_Buffer[index];
    }

    friend std::ostream &operator<<(std::ostream& stream, const String &string);
};

std::ostream& operator<<(std::ostream& stream, const String& string) {
    stream << string.m_Buffer;
    return stream;
}

// const - can't modify param, &(ref) - prevent from copying
void PrintString(const String& string) {
    std::cout << string << std::endl;
}

int main() {
    String str0 = "Cherno";

    // assign a String to a String (Copy)
    String str1 = str0;

    str1[2] = 'a';

    PrintString(str0);
    PrintString(str1);
}