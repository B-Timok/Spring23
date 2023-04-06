# Spring23
C++ Programs from my second year of coding.

The Programs in this repository are mainly developed from my studies in Data Structures.

This file will contain short summaries of each program in this repository.

"Zelda"

This program recursively finds an optimal path for Link to reach Ganon on a 7x7 grid. It reads a file from standard input containing a 
patterned grid for Link to traverse and prints out a grid with an optimal path for Link to reach Ganon that touches all open spaces at least once on the way. The program 
asks for the starting and ending coordinates from the user and uses them to find the path. It uses global variables to keep track of various parameters like the size of
the grid, the start and end coordinates, the number of vacant spaces, and the step count. It defines three functions, printGrid(), pathLabel(), and validPath(), 
to print the grid, label the path, and validate the path, respectively.

"Meeseeks"

This program performs long addition on two very large numbers using multiple threads for parallel processing. The user inputs the numbers and the program calculates the
correct number of threads to spawn based on the available hardware concurrency. The two numbers are divided into sections for each thread to work on, and each thread 
performs long addition on its assigned section. The resulting sums from each thread are then added together, with any carry-over calculations done in a separate 
function. The final sum is printed out as a vector.

"Flash"

This program uses a binary tree data structure to store and manipulate a set of nodes entered by the user. The program prompts the user to enter node names 
until they enter "-1", and then builds a binary tree using the entered names. The program then finds the longest zigzag path in the tree and prints it to the console, or
indicates that no such path exists. The program utilizes the binTree header file to define the binary tree class and its methods.

"Spellchecker"

This program is a command-line tool that spellchecks a text file provided via stdin using an unordered map-based dictionary. The program takes in a dictionary file, 
loads it into an unordered map, then checks a provided text file for misspelled words. For each misspelled word, the program generates a list of suggested replacement
words by creating all possible words with one letter difference. The program then outputs all misspelled words and their suggested replacement words to the console. The
program is implemented in C++ using the STL library.
