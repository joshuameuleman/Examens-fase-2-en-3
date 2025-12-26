# Incrementing an expression

Knowing what you know now, could you answer the following question? Would it be possible to use the increment operator on an expression as demonstrated in the following code snippet?

```cpp
int x = 12;
int y = 34;

int z = (x + y)++;
```

**answer**

No it is not possible



the increment operator must need a modifiable value so it can't modify an expression

what can you do 

is 

```cpp
int x = 12;
int y = 34;

int sum = (x + y);
int z=++sum
```