# Status code

Create a small C++ application that returns a value other than `0`. Typically a negative number is returned to indicate that something went wrong. Run that application using a terminal and show the status code.

**answer** 

use in terminal 
```sh
g++ main.cpp -o main.exe ; ./main.exe ; echo $LASTEXITCODE
```