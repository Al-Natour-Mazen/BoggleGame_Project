#include "pch.h"
#include "TrieNode.h"

TrieNode::TrieNode() {
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
    isEndOfWord = false;
}

TrieNode::~TrieNode()
{
    for (int i = 0; i < 26; i++)
    {
        if (children[i] != nullptr)
        {
            delete children[i];
            children[i] = nullptr;
        }
    }
}
