# Word Counter

## Objective

Write a C++ program that reads a text file and counts the number of words in it. Extend the program to also display the frequency of each word (case-insensitive) and the number of sentences. This challenge focuses on file I/O, string processing, and manual data handling using only arrays.

---

## Requirements

Your program must perform at least the following steps:

1. **Ask the user for the name of the text file to read.**  
   You should prepare a sample text file yourself with multiple sentences.  
   If the file does not exist, display an error using `cerr` and exit with a non-zero error code.

2. **Open the specified file and read it character by character.**

3. **Count the number of words in the file.**  
   A word is defined as a sequence of characters separated by spaces, tabs, or newlines.

4. **Display the total number of words at the end.**

---

## Extension

Extend your program with the following features:

- **Display a list of all words (case-insensitive), along with how many times each word occurs.**  
  > Use only arrays for storing words and their frequencies.  
  > Do not use STL containers (like `map`, `vector`, etc.) or external libraries.  
  > You may use a function to convert letters to lowercase (like `tolower()`), but write all other logic yourself.

- **Count and display the total number of sentences in the file.**  
  A sentence ends with a period (`.`), exclamation mark (`!`), or question mark (`?`).

---

## Example Output

Given a text file with this single sentence: `The quick brown fox jumps over the lazy dog.` The program output should be:

```text
Enter a file: Myfile.txt
Total words: 9

Word frequency:
the: 2
quick: 1
brown: 1
fox: 1
jumps: 1
over: 1
lazy: 1
dog: 1

Total sentences: 1
```


> 💡 Be sure to test your program with a longer file containing multiple sentences.



