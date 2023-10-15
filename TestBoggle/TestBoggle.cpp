// TestBoggle.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <BoggleGameLib/BoggleGame.h>

int main()
{
    BoggleGame game("dico.txt",5);
    game.StartGame();
    game.displayAllWordsGrid();
    game.findAllWords();
    //game.playGame();
}
