# Log File Analyzer

Write a C++ program that reads a server log file and gathers some useful statistics. The log file consists of multiple lines, each describing an event that occurred on the server.

**Sample line format:**

```
[yyyy-mm-dd HH:MM:SS] <LOG TYPE>: <Message>
```

A sample log file is available in this challenge

## Basic Requirements

Your program must perform the following steps:

1. **Ask the user** to enter the name of the log file to analyze.

   * If the file does not exist, print an error message using `cerr` and prompt the user again.

2. **Read the file line by line**, collecting the following statistics:

   * Total number of lines in the file.
   * Frequency count of each log type (`ERROR`, `WARNING`, `INFO`, etc.).

3. **Extend your program** to display the **top 3 most common log messages** (regardless of log type) and how often they appear.

4. **Add filtering functionality**:

   * Allow the user to choose a specific log type to display (e.g., only `ERROR` logs).
   * Keep asking for a filter until the user types `'q'` to quit.

### Bonus Challenge

Add an extra filter option: Let the user display only logs that occurred **between two specific timestamps**.

## Constraints

* You may use **plain arrays** for this challenge (even though other data structures would be more efficient).
* **Do not use library functions** for parsing or processing — write your own algorithms (you may use standard functions for basic tasks like converting characters to lowercase).

## Sample Output

```
Enter a log file: server.log
Total lines: 59

Log type frequencies:
INFO: 33
WARNING: 11
ERROR: 15

Top 3 most common log messages:
1. User 'john' logged in - 5 times
2. User 'admin' logged out - 4 times
3. High memory usage detected - 3 times

Filter: error
Results:
[2024-09-19 08:18:12] ERROR: Failed to connect to database
...

Filter: q
```

*Note: User input should be case-insensitive.*

