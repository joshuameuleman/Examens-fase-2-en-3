# pragma once

class Item
{
    public:
        Item() = default;
        virtual ~Item() = default;
        virtual void printInfo() const = 0;
        virtual double value() const = 0;
};

