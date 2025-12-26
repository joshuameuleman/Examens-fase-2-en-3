#include "Date.h"
#include <iomanip>
#include <sstream>
#include <iostream>


using namespace DateLib;
using std::stringstream;
using std::setw;
using std::setfill;

namespace DateLib 
{

    bool Date::isValidDate(int day, int month, int year)
    {
        if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
        {
            return false;
        }

        // Check for months with 30 days
        if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            return day <= 30;
        }

        // Check for February and leap years
        if (month == 2)
        {
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            return day <= (isLeapYear ? 29 : 28);
        }

        return true; // All other months are valid
    }

    Date::Date() : day(1), month (1), year(2000) // Default date: 01/01/2000
    {
        std::cout << "Date constructor" << std::endl;
    }
    Date::Date(int day, int month, int year) //custom constructor
    {
        std::cout << "Date constructor" << std::endl;
        if (!isValidDate(day, month, year))
        {
            throw std::invalid_argument("Invalid date");
        }
        this->day = day;
        this->month = month;
        this->year = year;
    }

    void Date::setDay(int day)
    {
        this->day = day;
        if (!isValidDate(day, this->month, this->year))
        {
            throw std::invalid_argument("Invalid day");
        }
        
    }
    void Date:: setMonth (int month)
    {
        this->month = month;
        if (!isValidDate(this->day, month, this->year))
        {
            throw std::invalid_argument("Invalid month");
        }

    }

    void Date::setYear(int year)
    {
        this->year=year;
        if (!isValidDate(this->day, this->month, year))
        {
            throw std::invalid_argument("invalid year");
        }
    }


    std::string Date::getString() const
    {
        stringstream ss;
        ss << setfill('0') << setw(2) << day << "/"
           << setfill('0') << setw(2) << month << "/"
           << year;
        return ss.str();
    }

    // print Date destructor when any Destructor is called
    Date::~Date()
    {
        std::cerr << "Date destructor" << std::endl;
    }

};