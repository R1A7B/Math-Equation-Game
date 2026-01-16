#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>

/*
I wrote 4 functions for writing the output. The first 3 mirror each other on each side of the box, so writing functions will save time and space from not repeating the same method 2x in the main function. 
OutputTopBottomLine are the lines at the very top and bottom of the output, the "+--...---+"
BoxTopBottomLine is for the the boxes surrounding the digits for the user's guess
BoxMiddleLines is for the lines just above and below the line printing the digits themselves
BoxMiddleLine is the line for printing the digits of the user's input
*/

void printOutputTopBottomLine(int length) {
    std::cout << "+";
           for(int i = 0; i < length; i++) {
                if(i == length - 1) {
                    std::cout << "-----";
                }
                else {
                    std::cout << "------";
                }
                
           }
    std::cout << "+\n";
}

void printBoxTopBottomLine(std::vector<int> rv) {
    std::cout << "|";
        for(int i = 0; i < rv.size(); i++) {
            if(i == rv.size() - 1) {
                if(rv[i] == 0) {
                    std::cout << "*****";
                }
                else if(rv[i] == 1) {
                    std::cout << ".....";
                }
                else {
                    std::cout << "     ";
                }
            }
            else {
                if(rv[i] == 0) {
                    std::cout << "***** ";
                }
                else if(rv[i] == 1) {
                    std::cout << "..... ";
                }
                else {
                    std::cout << "      ";
                }
            }
        }
    std::cout << "|\n";
}

void printBoxMiddleLines(std::vector<int> rv) {
    std::cout << "|";
        for(int i = 0; i < rv.size(); i++) {
            if(i == rv.size() - 1) {
                if(rv[i] == 0) {
                    std::cout << "*   *";
                }
                else if(rv[i] == 1) {
                    std::cout << ".   .";
                }
                else {
                    std::cout << "     ";
                }
            }
            else {
                if(rv[i] == 0) {
                    std::cout << "*   * ";
                }
                else if(rv[i] == 1) {
                    std::cout << ".   . ";
                }
                else {
                    std::cout << "      ";
                }
            }
        }
    std::cout << "|\n";
}

void printBoxMiddleLine(std::vector<int> rv, std::string userInput) {
    std::cout << "|";
        for(int i = 0; i < rv.size(); i++) {
            if(i == rv.size() - 1) {
                if(rv[i] == 0) {
                    std::cout << "* " << userInput[i] << " *";
                }
                else if(rv[i] == 1) {
                    std::cout << ". " << userInput[i] << " .";
                }
                else {
                    std::cout << "  " << userInput[i] << "  ";
                }
            }
            else {
                if(rv[i] == 0) {
                    std::cout << "* " << userInput[i] << " * ";
                }
                else if(rv[i] == 1) {
                    std::cout << ". " << userInput[i] << " . ";
                }
                else {
                    std::cout << "  " << userInput[i] << "   ";
                }
            }
        }
    std::cout << "|\n";
}

bool hasOneOperator(std::string uEquation) {
    return uEquation.find('+') != std::string::npos || uEquation.find('-') != std::string::npos || uEquation.find('*') != std::string::npos || uEquation.find('/') != std::string::npos;
}

bool isOperator(char c) {
    return c == '=' || c == '+' || c == '-' || c == '*' || c == '/';
}

bool isValidEquation(std::string uEquation) {
    // need to loop through string until I find delimiters
    std::vector<int> numbers;
    std::vector<char> operators;
    int fIndex;
    int lIndex;
    for(int i = 0; i < uEquation.length(); i++) {
        if(isOperator(uEquation[i])) {
            // Check if the first character is an operator. If it's anything besides a - for a negative number, return false. If it's a -, we will record it as part of the number to be a negative number
            if(i == 0 && uEquation[i] != '-') {
                return false;
            }
            else if (i == 0) {
                fIndex = 0;
            }
            else {
                // Create exception case for negative numbers   
                if(isOperator(uEquation[i-1]) && uEquation[i] == '-') {
                    fIndex = i;
                }
                else if(isOperator(uEquation[i-1])) {
                    return false;
                }
                else {
                    operators.push_back(uEquation[i]);
                    lIndex = i;
                    numbers.push_back(std::stoi(uEquation.substr(fIndex, lIndex-fIndex)));
                }
            }
        }
        else {
            if(i == 0) {
                fIndex = 0;
            }
            else if(isOperator(uEquation[i-1])) {
                //Exception cases for negative numbers
                if(uEquation[i-1] == '-') {
                    // Case where negative number is first number
                    if(i != 1) {
                        if(!isOperator(uEquation[i-2])) {
                            fIndex= i;
                        }
                    }
                }
                else {
                    fIndex = i;
                }
            }
            // Exception case for final char in the string
            if(i == uEquation.length() - 1) {
                lIndex = i+1;
                numbers.push_back(std::stoi(uEquation.substr(fIndex, lIndex-fIndex)));
            }
        }
    }

    int leftSide = numbers[0];
    int rightSide = 0;
    bool left = true;
    for(int i = 0; i < operators.size(); i++) {
        if (operators[i] == '=') {
            left = false;
            rightSide = numbers[i+1];
        }
        else {
            if(left) {
                if(operators[i] == '*') {
                    leftSide = leftSide * numbers[i+1];
                }
                else if(operators[i] == '/') {
                    leftSide = leftSide/numbers[i+1];
                }
                else if(operators[i] == '+') {
                    leftSide = leftSide + numbers[i+1];
                }
                else {
                    leftSide = leftSide - numbers[i+1];
                }
            }
            else {
                if(operators[i] == '*') {
                    rightSide = rightSide * numbers[i+1];
                }
                else if(operators[i] == '/') {
                    rightSide = rightSide/numbers[i+1];
                }
                else if(operators[i] == '+') {
                    rightSide = rightSide + numbers[i+1];
                }
                else {
                    rightSide = rightSide - numbers[i+1];
                }
            }
        }
    }
    return leftSide == rightSide;
}

int main(int argc, char* argv[]) {
    // Basic Error checking if it's not an openable file or the wrong amount of arguments were sent
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " machine_equation_game-file.txt\n";
        return 1;
    }  
    std::ifstream me_str(argv[1]);
    if (!me_str) {
        std::cerr << "Can not open the machine equation game file: " << argv[1] << "\n";
        return 1;
    }

    // Collect all the possible numbers from the guessing game file
    std::string line;
    std::vector<std::string> lines;
    while(getline(me_str, line)) {
        lines.push_back(line);
    }
    

    // Choosing a random line to collect our random number. srand(time(0)) guarantees a unique number each time by changing the seed.   
    srand(time(0));
    int rLine = rand() % size(lines);
    std::string rNumber = lines[rLine];

    // Prompt for user input and what they should be guessing for
    std::cout << "Let's play a guessing game!\nThe secret is an equation with " << rNumber.length() << " characters.\n";

    std::cout << "your guess: ";
    std::string userInput;
    std::cin >> userInput;

    // Check if the user's guess matches the random number
    int guesses = 1;
    while(userInput.compare(rNumber) != 0) {
        // Check if the guess matches the same length as the random number
        if(userInput.length() != rNumber.length()) {
            std::cerr << "ERROR: wrong length\n";
        }
        /*
        Check if it is a valid equation; 2 steps
        1. Check if there are = and +,-,*, or / operators
        2. Check if the equation is correct
        */
        else if (userInput.find('=') == std::string::npos || !hasOneOperator(userInput) || !isValidEquation(userInput)) {
            std::cerr << "ERROR: invalid equation\n";
        }
        else {
            // Going to make a result vector for printing the results. 0 is a perfect match, 1 means the number exists somewhere else in the random number, 2 means it does not exist in the random number
            // First, I will check if the digit in each place matches with the first run. Whenever it finds a match, I will remove that digit from the number by making it an empty space in the copy
            std::vector<int> resultVector;
            std::string rNumberCopy = rNumber;
            for(int i = 0; i < userInput.length(); i++) {
                if(userInput[i] == rNumber[i]) {
                    resultVector.push_back(0);
                    rNumberCopy[i] = ' ';
                }
                else {
                    resultVector.push_back(2);
                }
            }
            /*
            In this second run, I am now going to check if there are any more instances of the digit in the number. If there is, it will replace the 2 with a 1 in the result vector to say that the digit exists in a 
            different place inside the number, and it will replace that digit inside the number with another empty space so that if the same digit is seen again, it will not incorrectly report that 2 instances of
            that digit are inside the number unless there still exists another instance of that digit after one was removed
            */
            for(int i = 0; i < userInput.length(); i++) {
                if(rNumberCopy.find(userInput[i]) != std::string::npos && resultVector[i] != 0) {
                    resultVector[i] = 1;
                    rNumberCopy[rNumber.find(userInput[i])] = ' ';
                }
            }
            guesses++;
           // Output if the guess was not correct
           printOutputTopBottomLine(resultVector.size());
           printBoxTopBottomLine(resultVector);
           printBoxMiddleLines(resultVector);
           printBoxMiddleLine(resultVector, userInput);
           printBoxMiddleLines(resultVector);
           printBoxTopBottomLine(resultVector);
           printOutputTopBottomLine(resultVector.size());
        }
        // Prompt for a new guess
        std::cout << "your guess: ";
        std::cin >> userInput;
    }
    // Output if the guess was correct
    std::cout << "CONGRATULATIONS!\nYou solved the puzzle after making " << guesses;
    if(guesses == 1) {
        std::cout << " guess!\n";
    }
    else{
        std::cout << " guesses!\n";
    }
    
    me_str.close();

    return 0;
}