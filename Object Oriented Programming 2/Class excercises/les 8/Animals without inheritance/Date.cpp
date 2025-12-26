#include "Date.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace DateLib;

Date::Date() : Date(1, 1, 2024) {}

Date::Date(int day, int month, int year)
{
    setYear(year);
    setMonth(month);
    setDay(day);
    // cout << "Date constructor" << endl;
}

Date::~Date()
{
    // cout << "Date destructor" << endl;
}

void Date::setDay(int day)
{
    // TODO: extend the validation
    int maxDays = 31;

    if (day < 1 || day > maxDays)
    {
        throw invalid_argument("Invalid day");
    }
    this->day = day;
}

void Date::setMonth(int month)
{
    if (month < 1 || month > 12)
    {
        throw invalid_argument("Invalid month");
    }
    this->month = month;
}

void Date::setYear(int year)
{
    if (year == 0)
    {
        throw invalid_argument("Invalid year");
    }
    this->year = year;
}

string Date::getString() const
{
    stringstream ss;
    ss << setfill('0') << setw(2) << this->day << "/" << setfill('0') << setw(2) << this->month << "/" << this->year;
    return ss.str();
}