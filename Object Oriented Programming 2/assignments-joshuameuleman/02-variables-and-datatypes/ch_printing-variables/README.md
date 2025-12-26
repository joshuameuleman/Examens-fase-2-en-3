# Printing variables

Expand the following code snippet by outputting each variable's value to the terminal. Also print a label before each value.

```cpp
int secondsInAMinute = 60;
int secondsInAnHours = 3600;
int daysInAYear = 365;
```


**answer**
```cpp
#include <iostream>
int main(){
    int secondsInAMinute = 60;
    std::cout<<secondsInAMinute<<std::endl;
    std::cout<<"How many seconds in a minute: "<<secondsInAMinute<<std::endl;
    int secondsInAnHours = 3600;
    std::cout<<secondsInAnHours<<std::endl;
    std::cout<<"How many seconds in a hour: "<<secondsInAnHours<<std::endl;
    int daysInAYear = 365;
    std::cout<<daysInAYear<<std::endl;
    std::cout<<"How many days in a year: "<<daysInAYear<<std::endl;

    return 0
}

```
