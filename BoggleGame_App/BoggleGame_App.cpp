// BoggleGame_App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../BoggleGame_Lib//BoggleGame.h"

int main()
{
    BoggleGame game("dico.txt", 4);
    game.StartGame();
    game.playGame();
    game.searchAllWordsInGrid();
    game.checkAllfindWordsIsInDict();
}