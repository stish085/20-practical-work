// 20 задание 3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
bool emptyFile()
{
    std::ifstream fail;
    fail.open("C:\\practice\\basket.txt ");
    if (fail.peek() == EOF)
    {
        fail.close();
        return false;
    }
    else
    {
        fail.close();
        return true;
    }
    
}
int main()
{
    int coll = 0;
    std::string fish,coughtFish;

    std::cout << "Enter fish:\n";
    std::cin >> fish;
    std::ifstream failFish;
    failFish.open("C:\\practice\\fish.txt");
    std::ofstream failCaughtFish;
    if (!failFish.is_open())
    {
        std::cout << "file not open";
        return 1;
    }
  
    while (!(failFish.eof()))
    {   
        failFish >> coughtFish;
        if (coughtFish==fish)
        {   
            coll++;
            failCaughtFish << fish << std::endl;
            if (emptyFile())
            {
            
               failCaughtFish.open("C:\\practice\\basket.txt", std::ios::app);
               if (!failCaughtFish.is_open())
               {
                std::cout << "file not open";
                return 1;
               }
               failCaughtFish  << fish << std::endl;
               failCaughtFish.close();
            }
            else
            {
                failCaughtFish.open("C:\\practice\\basket.txt");
                if (!failCaughtFish.is_open())
                {
                    std::cout << "the file for recording the caught fish did not open ", std::ios::app;
                    return 1;
                }
                failCaughtFish << std::endl<< fish << std::endl;
                failCaughtFish.close();
            }

        }
    }
    failFish.close();
    std::cout << "You cought " << coll << " fish.";
}

