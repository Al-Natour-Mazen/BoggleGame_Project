#pragma once
#include <iostream>
#include <random>

class Grid {
private:
    char** letters;
    int size;
    bool searchWordStartingAt(const std::string& word, int row, int col, int wordIndex); // For the input user 
    void findWords(int row, int col, std::string currentWord, std::vector<std::string>& foundWords); // For find all words in grid
public:
    Grid(int size);
    ~Grid();
    void generateRandomGrid();
    void displayGrid();
    bool isWordInGrid(const std::string& word);// For the input user 
    void getAllWordsLongerThan3(std::vector<std::string>& foundWords); // For find all words in grid
};

