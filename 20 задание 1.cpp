// 20 задание 1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
bool date(std::string data)
{   
    int day, month, year;
    if (data[0]==0 )
    {
        day = std::stoi(data.substr(1, 1));
    }
    else
    {
     day = std::stoi(data.substr(0,2));

    }
    if(data[3]==0)
    {
        month = std::stoi(data.substr(4, 1));
    }
    else
    {
     month = std::stoi(data.substr(3, 2));

    }

     year = std::stoi(data.substr(6, 4));
    if ( (day>0 && day<31) && (month>0 && month<12) && (year>0 && year<2025))
    {
        return true;
    }
    else
        return false;
}
bool summa(int sum)
{
    if (sum >0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool nameFimale(std::string name,std::string fimale)
{
    if ((char(name[0])>64 && char(name[0])<91) && (char(fimale[0]) > 64 && char(fimale[0]) < 91))
    {
        return true;
    }
    else
    {
        return false;
    }
    
}
int main()
{
    std::cout << "Hello World!\n";
    std::string name, fimale,data;
    int sum,s,enter;
    std::ifstream fileF;
    fileF.open("C:\\practice\\statement.txt");
    if (fileF.peek()==EOF)
    {
        enter = 0;

    }
    else
    {
        enter = 1;
    }
    fileF.close();
    std::ofstream file;
    file.open("C:\\practice\\statement.txt", std::ios::app);
   
    if (!file.is_open())
    {
        std::cout << "!!!";
        return 1;
    }
    do {
        std::cout << "Enter information:" << std::endl;
    std::cin >> name >> fimale >> data >> sum;
    if (date(data)==false ||  nameFimale(name,fimale) == false || summa(sum)== false)
    {
        std::cout << " you enter false infomation. Try again, nothing was written to the file"  << std::endl;

    }
    else
    {
            if (enter == 1)
            {
            file << std::endl << name << " " << fimale << " " << data << " " << sum;

            }
            else
            {
                file  << name << " " << fimale << " " << data << " " << sum;
                enter = 1;
            }
        
    }

    std::cout << " If you want to finish entering data, enter 1 else enter 0 " << std::endl ;
    std::cin >> s;

    } while (s!=1);
       file.close();
    return 0;
    
}

