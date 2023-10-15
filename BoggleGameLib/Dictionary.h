#pragma once
#include <fstream>
#include <iostream>
#include <chrono>
#include <string>
#include "TrieNode.h"

class Dictionary
{
private:
    //std::vector<std::string> words;
    TrieNode* root;
    int totalWords;
public:
    Dictionary(const std::string& dictionaryFilePath);
      ~Dictionary();
    void insertNode(const std::string& word);
    void loadDictionary(const std::string& dictionaryFilePath);
    bool isWordInDictionary(const std::string& word);
};

