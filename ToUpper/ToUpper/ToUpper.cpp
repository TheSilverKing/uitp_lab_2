#include <iostream>

char ToUpper(char input_symbol) {
    int result_symbol;
    if ((int)input_symbol > 96 && (int)input_symbol < 123) 
    {
        return input_symbol - 32;
    }
    return input_symbol;
}

int main()
{
    char sym;
    std::cout << "Enter the letter: " << std::endl;
    std::cin >> sym;
    char result = ToUpper(sym);
    std::cout << result << std::endl;
}

