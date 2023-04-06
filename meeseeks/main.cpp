/*
Name: Brandon Timok
Description: Program that uses multiple threads to do long
             addition with parallel processing.
Input: Reads in two very large numbers from std input.
Output: Prints the result of adding both numbers.
*/

#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <mutex>
#include <cmath>

void printVector(std::vector<short> Num);
void longAdd(int start,int end);
void addCarry();

// global variables

// vectors to hold numbers to add
std::vector<short> Num1;
std::vector<short> Num2;
std::vector<short> Sum;
std::vector<short> CarryOver;
std::vector<std::thread> threadPool;
std::string FirstNum;
std::string SecondNum;
std::mutex t_lock;
int extraCarry = 0;

int main() {

    int maxThreads = std::thread::hardware_concurrency();
    int threadAmt = 0;
    int start = 0;
    int range = 0;
    int end = 0;

    // prompt
    std::cout << '\n' << "Enter a number: ";
    std::cin >> FirstNum;
    std::cout << '\n' << "Enter a number: ";
    std::cin >> SecondNum;
    std::cout << '\n';

    // for loops to fill vectors with user input
    for (int i = 0; i < FirstNum.size(); ++i) {
        FirstNum[i] = FirstNum[i] - '0';
        Num1.push_back(FirstNum[i]);
    }
    for (int i = 0; i < SecondNum.size(); ++i) {
        SecondNum[i] = SecondNum[i] - '0';
        Num2.push_back(SecondNum[i]);
    }

    // calculate correct number of threads to spawn
    for (int i = 0; i <= maxThreads; ++i) {
        if (pow(2, i) <= maxThreads) {
            threadAmt = pow(2, i);
        }
    }

    CarryOver.resize(Num1.size());
    Sum.resize(Num1.size());
    range = (Num1.size()) / threadAmt;
    start = range - 1;
    end = range;

    for (int i = 0; i < maxThreads; ++i) {
        if (threadPool.size() < threadAmt) {
            threadPool.push_back(std::thread(longAdd, start, end));
            range += end;
            start = range - 1;
        } else {
            for (auto& t : threadPool) {
                t.join();
                threadPool.clear();
            }
        }
    }
    
    for (auto &t : threadPool) {
        t.join();
    }

    addCarry();
    if (extraCarry == 1) {
        Sum.insert(Sum.begin(), extraCarry);
    }

    // print out vectors to check values
    std::cout << "Result = ";
    printVector(Sum);
    std::cout << '\n';

    return 0;
}

/*
function: Performs long addition on two numbers from two vectors
parameters: takes in a starting and ending indicies to section large numbers into sections for threading
input: uses global variable vectors to perform calculations on
*/
void longAdd(int start, int end) {
    int carry = 0;
    for (int i = 0; i < end; i++) {
        int preSum = Num1[start] + Num2[start] + carry;
        if (preSum > 9) {
            Sum[start] = preSum % 10;
            carry = preSum / 10;
        } else {
            Sum[start] = preSum;
            carry = preSum / 10;
        }
        if (carry == 1 && i == end - 1) {
            if (start - 1 >= 0) {
                CarryOver[start - 1] = carry;
            } else {
                extraCarry = carry;
            }
        }
        start--;
    }
}

/*
function: performs the carryover calculations from long addition
parameters: no parameters
input: uses global variable vectors to perform calculations on
*/
void addCarry() {
    int carry = 0;
    for (int i = Num1.size() - 1; i >= 0; i--) {
        int preSum = Sum[i] + CarryOver[i] + carry;
        if (preSum > 9) {
            Sum[i] = preSum % 10;
            carry = preSum / 10;
        } else {
            Sum[i] = preSum;
            carry = preSum / 10;
        }
        if (carry == 1 && i == 0) {
            Sum.insert(Sum.begin(), carry);
        }
    }
}
/*
function: prints contents of vectors
parameters: takes in a vector
output: prints out vector contents
*/
void printVector(std::vector<short> Num) {
    for (int i = 0; i < Num.size(); ++i) {
        std::cout << Num[i];
    }
    std::cout << '\n';
}
