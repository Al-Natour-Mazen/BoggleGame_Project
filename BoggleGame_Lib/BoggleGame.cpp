#include "pch.h"
#include "BoggleGame.h"


BoggleGame::BoggleGame( const std::string& dictionaryFileName, int gridSize) : grid(gridSize), dictionary(dictionaryFileName){}


void BoggleGame::StartGame() {
    grid.generateRandomGrid();
    std::cout << "============================================================\n";
    std::cout << "La grille est generee : " << std::endl;
    std::cout << "============================================================\n";
    grid.displayGrid();
}

void BoggleGame::playGame() {
    std::cout << "============================================================\n";
    std::cout << "C'est parti ! Vous avez 3 minutes pour trouver des mots.\n";
    std::cout << "============================================================\n";
    // l'heure actuelle
    auto startTime = std::chrono::steady_clock::now();
    auto endTime = startTime + std::chrono::minutes(1); // 3 minutes de jeu

    std::vector<std::string> foundWords;
    std::string userInput;

    while (std::chrono::steady_clock::now() < endTime) {
        std::cout << "Saisissez un mot : ";
        std::cin >> userInput;
        std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);

        if (userInput == "quit") {
            std::cout << "Fin du jeu." << std::endl;
            break;
        }

        if (grid.isWordInGrid(userInput)) {
            if (std::find(foundWords.begin(), foundWords.end(), userInput) == foundWords.end()) {
                if (dictionary.isWordInDictionary(userInput)) {
                    std::cout << "<> :)  Mot valide trouve [ " << userInput << " ]" << std::endl;
                    foundWords.push_back(userInput);
                }
                else {
                    std::cout << "<> :(  Mot trouve, mais invalide dans le dictionnaire [ " << userInput << " ]" << std::endl;
                }
            }
            else {
                std::cout << "<> -_-  Vous avez deja trouve ce mot [ " << userInput << " ]" << std::endl;
            }
        }
        else {
            std::cout << "<> o_O  Mot non trouve dans la grille [ " << userInput << " ]" << std::endl;
        }
        std::cout << "\n";
    }

   
    if(!foundWords.empty())
    {
        std::cout << "============================================================\n";
        std::cout << "Temps ecoule ! Voici les mots que vous avez trouves :" << std::endl;
        std::cout << "============================================================\n";
        for (const std::string& word : foundWords) {
            std::cout << " - " << word << std::endl;
        }
    }else
    {
        std::cout << "=========================================\n";
        std::cout << "Temps ecoule ! Vous avez rien trouve :(" << std::endl;
        std::cout << "=========================================\n";
    }
  

}

void BoggleGame::searchAllWordsInGrid() {
   
    // Mesurer le temps de début
    auto start = std::chrono::high_resolution_clock::now();

    grid.getAllWordsLongerThan3(allWordsInGrid);

    // Mesurer le temps de fin
    auto end = std::chrono::high_resolution_clock::now();

    // la durée de l'exécution
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "\n>> Temps d'execution afin de chercher tout les mots (sup a 3) dans toute la grille: " << duration.count() << " seconds." << std::endl;
    
    /* FOR DISPLAY ALL WORDS IN THE GRID UNCOMMENT THIS :
    std::cout << "============================================================\n";
    std::cout << "Mots de longueur superieure a 3 dans la grille : " << std::endl;
    std::cout << "============================================================\n";
    for (const std::string& word : allWordsInGrid) {
        std::cout << word << " ";
    }
    */
}


void BoggleGame::checkAllfindWordsIsInDict() {
    std::vector<std::string> wordsInDictionary;

    for (const std::string& word : allWordsInGrid) {
        // Convertir le mot en minuscules
        std::string lowercaseWord = word;
        for (char& c : lowercaseWord) {
            c = std::tolower(c);
        }

        if (dictionary.isWordInDictionary(lowercaseWord)) {
            wordsInDictionary.push_back(word);
        }
    }

    if(!wordsInDictionary.empty())
    {
        std::cout << "==============================================================================\n";
        std::cout << "Mots de longueur superieure a 3 dans la grille qui sont dans le dictionnaire : " << std::endl;
        std::cout << "===============================================================================\n";

        for (const std::string& word : wordsInDictionary) {
            std::cout << word << " ";
        }
    }
    else
    {
        std::cout << "===================================================\n";
        std::cout << " Il y avait aucun mot possible dans cette partie ;) " << std::endl;
        std::cout << "===================================================\n";
    }

   
}

