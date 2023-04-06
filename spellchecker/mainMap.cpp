/*
Name: Brandon Timok
Description: Program that spellchecks a file from stdin using unordered maps
Input: Takes in a file from standard input
Output: Outputs all misspelled words and suggested replacement words
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <algorithm>

void loadfile(std::string filename, std::unordered_map<std::string, bool>& dictionary);
void spellcheck(std::string filename, std::unordered_map<std::string, bool>& dictionary);
std::vector<std::string> generateSuggestedWords(std::string word);

int main() {

    std::unordered_map<std::string, bool> dictionary;
    std::string fileIN;

    // load dicitonary file into unordered map
    loadfile("usa.txt", dictionary);

    std::cout << "Enter filename: ";
    std::cin >> fileIN;
    std::cout << "\n";

    spellcheck(fileIN, dictionary);


    return 0;
}

/* 
Function: Loads dictionary into unordered_map
Parameters: Takes in a file from stdin and an unordered map for the dictionary
*/ 
void loadfile(std::string filename, std::unordered_map<std::string, bool>& dictionary) {
    std::ifstream file(filename);
    std::string word;

    while (file >> word) {
        dictionary[word] = true;
    }

    file.close();
}

/*
Function: Generate all possible suggested words with one letter difference
Parameters: Takes in a string (misspelled word)
*/
std::vector<std::string> generateSuggestedWords(std::string word) {
    std::vector<std::string> suggestions;

    // Sublist of words with different first characters
    for (char c = 'a'; c <= 'z'; c++) {
        std::string suggestion = c + word.substr(1);
        suggestions.push_back(suggestion);
    }

    // Sublist of all words with different second characters
    for (int i = 1; i < word.length(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            std::string suggestion = word.substr(0, i) + c;
            if (i < word.length() - 1) {
                suggestion += word.substr(i + 1);
            }
            suggestions.push_back(suggestion);
        }
    }

    // Sublist of words with different letters added in front
    for (char c = 'a'; c <= 'z'; c++) {
        std::string suggestion = c + word;
        suggestions.push_back(suggestion);
    }

    // Sublist if words with different letters added between the first and second letter
    for (int i = 1; i < word.length(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            std::string suggestion = word.substr(0, i) + c + word.substr(i);
            suggestions.push_back(suggestion);
        }
    }

    // Sublist of words with different letter added to the end
    for (char c = 'a'; c <= 'z'; c++) {
        std::string suggestion = word + c;
        suggestions.push_back(suggestion);
    }

    return suggestions;
}

/*
Function: Checks file for misspelled words and generate suggested words
Parameters: Takes in a file to spellcheck and an unordered map for the dictionary
*/
void spellcheck(std::string filename, std::unordered_map<std::string, bool>& dictionary) {
    std::ifstream file(filename);
    std::string word;
    std::unordered_map<std::string, bool> checkedWords;
    std::unordered_map<std::string, std::vector<std::string>> suggestedWords;
    std::vector<std::string> misspelledWords;

    while (file >> word) {
        // Convert word to uppercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (!dictionary[word] && !checkedWords[word]) {
            std::vector<std::string> suggestions = generateSuggestedWords(word);
            misspelledWords.push_back(word);

            // Check each suggested word to see if it's in the dictionary
            for (auto suggestion : suggestions) {
                if (dictionary[suggestion]) {
                    suggestedWords[word].push_back(suggestion);
                }
            }

            // Sort the list of suggested words for the current misspelled word
            sort(suggestedWords[word].begin(), suggestedWords[word].end());
        }

        // Mark current word as checked
        checkedWords[word] = true;
    }

    file.close();

    // Print misspelled words and their suggested words
    for (auto misspelledWord : misspelledWords) {
        // Convert misspelled word to uppercase
        std::transform(misspelledWord.begin(), misspelledWord.end(), misspelledWord.begin(), ::toupper);
        
        // Print the misspelled word
        std::cout << misspelledWord << " is misspelled\n\n";

        // Converts misspelled words to lowercase to pair with suggestedwords
        std::transform(misspelledWord.begin(), misspelledWord.end(), misspelledWord.begin(), ::tolower);
        
        // Print the suggested words for the current misspelled word
        if (suggestedWords[misspelledWord].size() == 0) {
            std::cout << "No suggestions" << std::endl;
        } else {
            std::cout << "Suggested words\n";
            for (auto suggestedWord : suggestedWords[misspelledWord]) {
                std::transform(suggestedWord.begin(), suggestedWord.end(), suggestedWord.begin(), ::toupper);
                std::cout << suggestedWord << std::endl;
            }
        }
        std::cout << std::endl;
    }
}
