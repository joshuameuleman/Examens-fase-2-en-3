# Wrong input

What happens when the user inputs something different than a number. For example a character `b` or a string `Hello`? Can you explain what happens? How can we detect this?

```cpp
cout << "Please enter a number: ";

int number;
cin >> number;
```

**answer**

it would trigger the failbit of cin.
the variable "number" will still be undefined.

```cpp
cout << "Please enter a number: ";
int number;
cin >> number;

if (cin.fail()) {
    cout << "Invalid input!" << endl;
}
```