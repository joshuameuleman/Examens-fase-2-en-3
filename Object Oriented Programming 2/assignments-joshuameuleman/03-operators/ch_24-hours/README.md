# 24 hours

Consider the following example, a code snippet from a student, programming a clock which can display the time in `24h` format. The student however has a small problem where the hours sometimes become bigger than `23`. Can you think of a single operator statement to limit the hours to a value between `0` and `23`?

```cpp
int hours = 25;

// How can we limit hours here so it wraps around to 1?


```

**answer**

we can use the modulus operator " %24 "