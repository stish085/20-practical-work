// 20 задание 2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <cstdlib>  
#include <ctime>    

int main() {
    int width, height;

   
    std::cout << "Enter the width of the image(in pixels) : ";
    std::cin >> width;

    std::cout << "Enter the height of the image (in pixels): ";
    std::cin >> height;

    
    if (width <= 0 || height <= 0) {
        std::cerr << "Error: dimensions must be positive numbers" << std::endl;
        return 1;
    }

    
    std::srand(std::time(nullptr));

  
    std::ofstream file("C:\\practice\\pic.txt");
    if (!file) {
        std::cerr << "Couldn't open the file for writing" << std::endl;
        return 1;
    }

    
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int pixel = std::rand() % 2;  
            file << pixel;
        }
        file << std::endl;  
    }

    file.close();
    std::cout << "The binary image has been successfully created and saved to the pic.txt file." << std::endl;

    return 0;
}
