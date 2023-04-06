/*
Name: Brandon Timok
Description: Program that spellchecks a file from stdin using vectors and linear searches
Input: Takes in a file from standard input
Output: Outputs all misspelled words and suggested replacement words
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <algorithm>

void loadfile(std::string filename, std::vector<std::string>& dictionary);
void spellcheck(std::string filename, std::vector<std::string>& dictionary);
std::vector<std::string> generateSuggestedWords(std::string word);

int main() {

    std::vector<std::string> dictionary;
    std::string fileIN;

    // load dicitonary file into unordered map
    loadfile("usa.txt", dictionary);

    std::cout << "Enter filename: ";
    std::cin >> fileIN;

    spellcheck(fileIN, dictionary);


    return 0;
}

/*
Function: Loads dictionary into a vector of strings
Parameters: Takes in a file for the dictionary and a vector of strings
*/
void loadfile(std::string filename, std::vector<std::string>& dictionary) {
    std::ifstream file(filename);
    std::string word;

    while (file >> word) {
        dictionary.push_back(word);
    }

    file.close();
}

/*
Function: Generates all possible suggested words with one letter difference
Parameters: Takes in a string (misspelled word)
Returns: Returns a vector of strings filled with suggested words for the current misspelled word
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
Function: Checks file for misspelled words and generates suggested words
Parameters: Takes in a file to spellcheck and a vector for the dictionary
*/ 
void spellcheck(std::string filename, std::vector<std::string>& dictionary) {
    std::ifstream file(filename);
    std::string word;
    std::vector<std::string> checkedWords;
    std::vector<std::string> misspelledWords;
    std::vector<std::vector<std::string>> suggestedWords;

    while (file >> word) {
        // Convert word to uppercase
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (std::find(dictionary.begin(), dictionary.end(), word) == dictionary.end()
            && std::find(checkedWords.begin(), checkedWords.end(), word) == checkedWords.end()) {
            
            std::vector<std::string> suggestions = generateSuggestedWords(word);
            misspelledWords.push_back(word);
            suggestedWords.push_back({});


            // Check each suggested word to see if it's in the dictionary
            for (auto suggestion : suggestions) {
                if (std::find(dictionary.begin(), dictionary.end(), suggestion) != dictionary.end()) {
                    suggestedWords.back().push_back(suggestion);
                }
            }

            // Sort the list of suggested words for the current misspelled word
            sort(suggestedWords.back().begin(), suggestedWords.back().end());
        }

        // Mark current word as checked
        checkedWords.push_back(word);
    }

    file.close();

    // Print misspelled words and their suggested words
    for (auto i = 0; i < misspelledWords.size(); i++) {
        // Convert misspelled word to uppercase
        std::string misspelledWord = misspelledWords[i];
        std::transform(misspelledWord.begin(), misspelledWord.end(), misspelledWord.begin(), ::toupper);
        
        // Print the misspelled word
        std::cout << misspelledWord << " is misspelled\n\n";

        // Converts the misspelled word to lowercase to pair with suggestedwords
        std::transform(misspelledWord.begin(), misspelledWord.end(), misspelledWord.begin(), ::tolower);
        
        // Print the suggested words for the current misspelled word
        if (suggestedWords[i].size() == 0) {
            std::cout << "No suggestions" << std::endl;
        } else {
            std::cout << "Suggested words\n";
            for (auto suggestedWord : suggestedWords[i]) {
                std::string upperSuggestedWord = suggestedWord;
                std::transform(upperSuggestedWord.begin(), upperSuggestedWord.end(), upperSuggestedWord.begin(), ::toupper);
                std::cout << upperSuggestedWord << std::endl;
            }
        }
        std::cout << std::endl;
    }
}
