#pragma once

#include <string>
using namespace std;

namespace DateLib
{
    class Date
    {
        public:
            Date();
            Date(int day, int month, int year);
            ~Date();
            string getString() const;

        private:
            int day;
            int month;
            int year;

            void setDay(int day);
            void setMonth(int month);
            void setYear(int year);
    };
}