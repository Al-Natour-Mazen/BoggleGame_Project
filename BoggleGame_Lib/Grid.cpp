#include "pch.h"
#include "Grid.h"

Grid::Grid(int size) {
    this->size = size;
    letters = new char* [size];
    for (int i = 0; i < size; i++) {
        letters[i] = new char[size];
    }
}

Grid::~Grid() {
    for (int i = 0; i < size; i++) {
        delete[] letters[i];
    }
    delete[] letters;
}
 
void Grid::generateRandomGrid() {
    std::random_device rd;  
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> distribution('A', 'Z');

    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            letters[row][col] = static_cast<char>(distribution(gen));
        }
    }
}

void Grid::displayGrid() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << letters[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

/*
    We check if a word is present in a grid by calling the "searchWordStartingAt" function.
    for each possible position in the grid
*/
bool Grid::isWordInGrid(const std::string& word) {
    std::string lowercaseWord = word;
    std::transform(lowercaseWord.begin(), lowercaseWord.end(), lowercaseWord.begin(), ::tolower);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (searchWordStartingAt(lowercaseWord, i, j, 0)) {
                return true;
            }
        }
    }
    return false;
}

/*
    We search for a word in a grid by checking if the word can start at the position (row, col) and
    exploring all possible directions while maintaining case consistency and marking
    the letters visited to avoid repetition.
*/
bool Grid::searchWordStartingAt(const std::string& word, int row, int col, int wordIndex) {
    if (wordIndex == word.length()) {
        return true;  // Base case: the entire word has been found.
    }

    if (row < 0 || row >= size || col < 0 || col >= size) {
        return false;  // Out of bounds.
    }

    // Check if the current letter matches (case insensitive).
    if (std::tolower(letters[row][col]) != std::tolower(word[wordIndex])) {
        return false;
    }

    // Save the original letter before marking it visited.
    char temp = letters[row][col];

    // Mark the current letter as visited.
    letters[row][col] = '\0';

    /*
        G : Gauche
        D : Droite
        H : Haut
        B : Bas
        - : pas de deplacement
    */
    int dr[] = { -1, -1, -1, 0, 1, 1, 1, 0 };
   //dr (vertical/row) = H, HG, B, BG, -, BD, H, HD
    int dc[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
   //dc (horizonatal/column) = G, HG, H, HD, -, BD, B, BG

    for (int i = 0; i < 8; ++i) {
        if (searchWordStartingAt(word, row + dr[i], col + dc[i], wordIndex + 1)) {
            // We found the word starting at this position.
            // Restore the original letter before returning.
            letters[row][col] = temp;
            return true;
        }
    }

    // Restore the original letter.
    letters[row][col] = temp;
    return false;
}

void Grid::findWords(int row, int col, std::string currentWord, std::vector<std::string>& foundWords) {
    if (row < 0 || col < 0 || row >= size || col >= size || letters[row][col] == ' ')
        return;

   
    currentWord += letters[row][col];


    if (currentWord.length() > 3) {
        foundWords.push_back(currentWord);
    }

 
    char currentLetter = letters[row][col];
    letters[row][col] = ' ';

    int rowOffsets[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int colOffsets[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    for (int i = 0; i < 8; i++) {
        int newRow = row + rowOffsets[i];
        int newCol = col + colOffsets[i];
        findWords(newRow, newCol, currentWord, foundWords);
    }

    letters[row][col] = currentLetter;
}


void Grid::getAllWordsLongerThan3(std::vector<std::string>& foundWords) {
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            std::string currentWord = "";
            findWords( row, col, currentWord, foundWords);
        }
    }
}