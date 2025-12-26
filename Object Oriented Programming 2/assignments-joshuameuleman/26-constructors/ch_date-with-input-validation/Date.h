
#pragma once
#include <iostream>
#include <string>


namespace DateLib {

class Date {
public:
    Date();
    Date(int day, int month, int year);
    ~Date();// destructor
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);
    std::string getString() const;

private:
    int day;
    int month;
    int year;
    bool isValidDate(int day, int month, int year);
};
};