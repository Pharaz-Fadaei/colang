#ifndef UTILITY_CPP_
#define UTILITY_CPP_

#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>

class Utility
{
public:
    static std::string IntToString(int n)
    {
        std::ostringstream oss;
        oss << n;
        return oss.str();
    }
    static std::string DoubleToString(double x)
    {
        std::ostringstream  oss;
        oss << x;
        return oss.str();
    }
    static int StringToInt(std::string str)
    {
        std::istringstream iss(str);
        int n;
        iss >> n;
        return n;
    }
    static double StringToDouble(std::string str)
    {
        std::istringstream iss(str);
        double d;
        iss >> d;
        return d;
    }
    static void error(std::string errMsg)
    {
        std::cout << "Colang error: " << errMsg << std::endl;
        system("pause");
        exit(1);
    }


    static void x(std::string str)
    {
        std::cout << str << std::endl;
    }
};
#endif // UTILITY_CPP_
