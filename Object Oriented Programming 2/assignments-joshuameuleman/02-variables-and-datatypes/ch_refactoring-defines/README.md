# Refactoring defines

Refactor the code snippet below that makes use of a `define` statement where a constant could have been used. Don't mind the arithmetics for now.

```cpp
#define PI 3.1415

double radius = 12.5;

double circleArea = PI * radius * radius;
```

**answer**

```cpp
const double pi=3.1415;

double radius = 12.5;

double circleArea = pi * radius * radius;
```