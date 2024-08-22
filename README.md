# Basic project context
This is a project by Martin Borgén to implement a sodoku solver. 

The purpose is to practice following proper practice w.r.t. organization
and discipline when setting up a project. 

The goal is to have a project suitable for a portfolio, with clear structure, 
commit messages, git usage, etc. to show my ability to develop software 
in a professional setting. 

The first part is to make a Sodoku -class that provides useful functionality for 
a sodoku solving program. Secondly, a sodoku solving algorithm is implemented, 
at time of writing a brute-force depth-first search because of its simplicity.

A solver is purposefully not included in the sodoku class, as typicall thats the 
problem for the user to solve :)

## Usage

The sodoku class is intended to be initialized with a size, normally (9, 3) - at the moment there is no default, but this would be the default. 
THe default is only a 2D matrix of zeroes. 

Then a 2D vector of int can be passed to it with the assignment operator to se the initial values.

```
std::vector<std::vector<int>> initial_values = {{0,5,0, 8,0,0, 0,0,0},
                                                {0,0,7, 6,0,3, 0,0,0},
                                                {2,0,0, 0,0,0, 9,0,0},
                                                {0,0,2, 9,0,0, 0,3,5},
                                                {0,0,0, 3,5,0, 4,0,0},
                                                {3,6,0, 0,8,4, 0,0,7},
                                                {5,0,0, 1,0,0, 0,4,6},
                                                {7,0,4, 0,6,2, 0,0,0},
                                                {1,0,0, 4,9,0, 0,8,0}};
Sodoku example_sodoku(9, 3);
example_sodoku = intial_values;
```

The class provides methods to get the numbers in rows, columns and boxes, as well as contiains-methods if a number is in a row, column, or box. 

`example_sodoku.box_contains(0, 0, 5)` would return `true` for instance. 

The main.cpp shows a basic file reader (.txt with commas separating numbers), as well as a print_sodoku -function and a brute-force solver. 
