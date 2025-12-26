# Movie collection

Now we will combine the functionality from the previous exercise with OOP to build a movie collection system, work fully according to the rules of best practices.

## Objectives

Create two classes:

### `MovieCollection` class
- **Attributes:**
  - `name`: the name of the collection
  - `movies`: a pointer to the start of a linked list of `Movie` objects, created on the heap

- **Methods:**
  - `addMovie`: Adds a movie to the end of the list. All details are passed as arguments (no Movie object is passed).
  - `removeMovie`: Removes a specific movie based on director and title.
  - `showFirstMovie`: Displays the first movie in the list.
  - `showNextMovie`: Navigates to and displays the next movie.
  - `showMovies`: Displays all movies in the collection.
  - `clearMovies`: Deletes all movies from the collection and frees memory.

### `Movie` class
- **Attributes:**
  - `directorName`
  - `title`
  - `genre`
  - `duration`
  - A pointer to the next `Movie` object (so the list can be navigated)

## What to do in `main()`

1. Create a `MovieCollection` object with a specific name.
2. Add several movies using `addMovie()`. Pass all required attributes as arguments.
3. Remove a specific movie using `removeMovie()`, based on director and title.
4. Use `showFirstMovie()` to display the first movie in the collection.
5. Use `showNextMovie()` to navigate through the list and show the next movie.
6. Use `showMovies()` to print all movies in the collection.
7. Use `clearMovies()` to delete all movies and free memory.

## Extensions (Optional, in order of priority)

- **Circular navigation**: Update `showNextMovie()` so that when reaching the last movie, the next call loops back to the first movie.
- **Sorting movies**:
  - Option 1: Keep the list sorted by director and title during insertion.
  - Option 2: Add a `sortMovies()` method that constructs a new sorted linked list and deletes the old one.

  For string comparison in C++, you can refer to:  
  [https://www.geeksforgeeks.org/comparing-two-strings-cpp](https://www.geeksforgeeks.org/comparing-two-strings-cpp)

- **Double linked list**:
  - Add backward links to your `Movie` class to enable navigation to previous movies.
  - Implement a `showPreviousMovie()` method.

## Memory Management

Use tools like **Valgrind** to analyze memory usage. Ensure that the number of allocations matches the number of frees.  
Make sure `clearMovies()` is called at the end of the program to clean up all memory.


