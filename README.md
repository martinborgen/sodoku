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
The class provides methods to get the numbers in ros, columns and boxes, as well as contiains-methods if a number is in a row, column, or box. 

The main.cpp shows a basic file reader (.txt with commas separating numbers), as well as a print_sodoku -function and a brute-force solver. 
