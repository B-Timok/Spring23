/*
Name: Brandon Timok
Description: Program that recursively finds an optimal path for Link to reach
             Ganon on a 7x7 grid.
Input: Reads a file from std input containing a patterned grid for link to traverse
Output: Prints out a grid with an optimal path for Link to reach Ganon that touches
        all open spaces at least once on the way.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// global variables
const int GRID_SIZE = 7;
int startX = 0;
int startY = 0;
int endX = 0;
int endY = 0;
int vacantSpaces = 0;
char stepCount = '0';
int stepCounter = 1;
int pathCounter = 0;
bool valid = false;


bool validPath(char grid[GRID_SIZE][GRID_SIZE], int x, int y, int stepCounter);
void printGrid(char grid[GRID_SIZE][GRID_SIZE]);
char pathLabel(char stepCount);

int main() {

    // grid for zelda path
    char grid[GRID_SIZE][GRID_SIZE] = {0};

    // variable for the file name from stdin
    std::string file_name;
    
    std::cout << '\n';
    std::cout << "Enter config file: ";
    std::cin >> file_name;
    std::cout << '\n';
    std::cout << "Please enter starting coordinates: ";
    std::cin >> startX >> startY;
    std::cout << '\n';
    std::cout << "Please enter end coordinates: ";
    std::cin >> endX >> endY;
    std::cout << '\n';

    // stream to read file
    std::ifstream myfile (file_name);

    // string to read lines into
    std::string line = "";

    int row = 0;

    // while file is open get lines to store in grid[][]
    if (myfile.is_open()) {
        // loop to get one line of the file at a time
        while (std::getline(myfile, line)) {
            for (int col = 0; col < GRID_SIZE; col++) {
                grid[row][col] = line[col];
                // if (line[col] == ' ') {
                //     vacantSpaces++;
                // }
            }
            // once first row is filled, increment row and go again
            row++;
        }
    }
    //close once done reading from file
    myfile.close();

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == ' ') {
                vacantSpaces++;
            }
        }
    }

    grid[startX][startY] = '0';

    validPath(grid, startX, startY, stepCounter);


    // print grid after path has been established
    printGrid(grid);

    return 0;
}

/*
Function ID: function to print the grid
Parameters: takes in a grid of appropriate size
*/
void printGrid(char grid[][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

/*
Function ID: function to skip from '9' to 'A' when marking spaces
Parameters: takes in a char variable for marking spaces
Returns: returns the correct char to mark the space
*/
char pathLabel(char stepCount) {
    if (stepCount == ':') {
        stepCount = 'A';
    } else if (stepCount == '@') {
        stepCount = '9';
    }
    return stepCount;
}

/*
Function ID: function to find a valid path from Link to Gannon recursively
Parameters: takes in a grid, starting coordinates x and y, and an int to keep
            track of spaces marked
Returns: returns a bool saying whether the path is valid or not
*/

bool validPath(char grid[][GRID_SIZE], int x, int y, int stepCounter) {

    // first base case
    if ((x == endX && y == endY) && stepCounter == vacantSpaces) {
        return true;
    }

    // second base case
    if (x == endX && y == endY) {
        return false;
    }

    // check above, left, below, and right for open spaces
    if (x > 0 && (grid[x-1][y] == ' ')) {
        stepCount++;
        stepCount = pathLabel(stepCount);
        grid[x-1][y] = stepCount;
        stepCounter++;
        x = x-1;
        if (validPath(grid, x, y, stepCounter)) {
            return true;
        } else {
            stepCount--;
            stepCount = pathLabel(stepCount);
            stepCounter--;
            grid[x][y] = ' ';
            x++;
        }
    } 
    if ((x < GRID_SIZE - 1) && grid[x+1][y] == ' ') {
        stepCount++;
        stepCount = pathLabel(stepCount);
        grid[x+1][y] = stepCount;
        stepCounter++;
        x = x+1;
        if (validPath(grid, x, y, stepCounter)) {
            return true;
        } else {
            stepCount--;
            stepCount = pathLabel(stepCount);
            stepCounter--;
            grid[x][y] = ' ';
            x--;
        }
    }
    if ((y < GRID_SIZE - 1) && grid[x][y+1] == ' ') {
        stepCount++;
        stepCount = pathLabel(stepCount);
        grid[x][y+1] = stepCount;
        stepCounter++;
        y = y+1;
        if (validPath(grid, x, y, stepCounter)) {
            return true;
        } else {
            stepCount--;
            stepCount = pathLabel(stepCount);
            stepCounter--;
            grid[x][y] = ' ';
            y--;
        }
    }
    if (y > 0 && (grid[x][y-1] == ' ')) {
        stepCount++;
        stepCount = pathLabel(stepCount);
        grid[x][y-1] = stepCount;
        stepCounter++;
        y = y-1;
        if (validPath(grid, x, y, stepCounter)) {
            return true;
        } else {
            stepCount--;
            stepCount = pathLabel(stepCount);
            stepCounter--;
            grid[x][y] = ' ';
            y++;
        }
    }

    return false;
}
