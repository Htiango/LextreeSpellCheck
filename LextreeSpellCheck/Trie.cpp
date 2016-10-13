//
//  Trie.cpp
//  LextreeSpellCheck
//
//  Created by hty on 12/10/2016.
//  Copyright © 2016 hty. All rights reserved.
//

#include "Trie.h"

Trie::Trie()
{
    pRoot = new TrieNode();     // we should pay attention to that the root only store '*'
}

Trie::~Trie()
{
    Destory(pRoot);
}

void Trie::Insert(string& str)
{
    int stringSize;
    stringSize = int (str.size());
    assert(stringSize != 0);
    int index;
    TrieNode* pLoc = pRoot;
    
    for (int i = 0; i < stringSize; i++) {
        index = (str[i] - 'a') * 2;
        if (index < 0 || index > MAX_BRANCH_NUM - 2) {
            return;
        }
        if (i == stringSize - 1)                // check if it is the last character. if so, add one to the index
        {
            index += 1;
        }
        
        if (NULL == pLoc->nextBranch[index])    // if this character of the words haven't been created, then creat it
        {
            pLoc->nextBranch[index] = new TrieNode;
            pLoc->nextBranch[index]->letter = str[i];
        }
        pLoc = pLoc->nextBranch[index];
    }
    return;
}


bool Trie::Search(string& str)
{
    int stringSize;
    stringSize = int (str.size());
    assert(stringSize != 0);
    int i = 0;
    int index = -1;
    TrieNode* pLoc = pRoot;
    
    while (pLoc && i < stringSize) {
        index = (str[i] - 'a') * 2;
        if (index < 0 || index > MAX_BRANCH_NUM - 2) {
            return false;
        }
        if (i == stringSize - 1)                // check if it is the last character. if so, add one to the index
        {
            index += 1;
        }
        
        pLoc = pLoc->nextBranch[index];
//        if (pLoc->letter != str[i]) {
//            return  false;
//        }
        i++;
    }
    return true;
}

void Trie::PrintALL()
{
    string str;
    Print(pRoot, str);
}

/* output all the words according to the sequence in the dictionary based on the root of pRoot */
bool Trie::Print(TrieNode* pRoot, string& str)
{
    if (NULL == pRoot)
    {
        return false;
    }
    // add character to the word string
    if (pRoot->letter != '\0')
    {
        stringstream ss;
        string character;
        ss << pRoot->letter;
        ss >> character;
        str += character;
    }
    
    
    // process the branch recursively
    int count = 0;
    
    for (int i = 0;i < MAX_BRANCH_NUM;i++)
    {
        string str2 = str;
        if (!(Print(pRoot->nextBranch[i], str2))) {
            count ++;
        }
    }
    
    if (count == MAX_BRANCH_NUM) {
        cout << str << endl;
    }
    
    return true;
}

/* destory trie tree */
void Trie::Destory(TrieNode* pRoot)
{
    if (NULL == pRoot)
    {
        return;
    }
    for (int i = 0;i < MAX_BRANCH_NUM;i++)
    {
        Destory(pRoot->nextBranch[i]);
    }
    // destory the space occupied by letter
    if (pRoot->letter != '\0')
    {
//        delete []pRoot->letter;
        pRoot->letter = NULL;
    }
    delete pRoot;           //destory the node
    pRoot = NULL;
}




