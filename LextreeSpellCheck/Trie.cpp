//
//  Trie.cpp
//  LextreeSpellCheck
//
//  Created by hty on 12/10/2016.
//  Copyright © 2016 hty. All rights reserved.
//

#include "Trie.h"

bool TrieNode::setPreNodeCost(double val)
{
    preNodeCost = val;
    return true;
}

int TrieNode::getPreNodeCost()
{
    return preNodeCost;
}

bool TrieNode::setCurNodeCost(double val)
{
    curNodeCost = val;
    return true;
}

int TrieNode::getCurNodeCost()
{
    return curNodeCost;
}

bool TrieNode::setNodeLetter(char c)
{
    letter = c;
    return true;
}

char TrieNode::getNodeLetter()
{
    return letter;
}

TrieNode* TrieNode::getParent()
{
    return parentBranch;
}

bool TrieNode::isLeaf()
{
    for (int i = 0; i < MAX_BRANCH_NUM; i++)
    {
        if (nextBranch[i] != NULL)
            return false;
    }
    return true;
}

void TrieNode::setVectorBool(int len)
{
    for (int i = 0; i < len; i++) {
        vectorBool.push_back(0);
    }
}

void TrieNode::setVectorNode(int len)
{
    for (int i = 0; i < len; i++) {
        vectorNode.push_back(NULL);
    }
}

string TrieNode::getWord()
{
    string str;
    vector<char> strVec;
    strVec.push_back(letter);
    TrieNode* node = getParent();
    while (node->getParent() != NULL)
    {
        strVec.push_back(node->letter);
        node = node->getParent();
    }
    int len = int(strVec.size());
    for (int i = len - 1; i >= 0; i--) {
        str += strVec[i];
    }
    
    return str;
}

Trie::Trie()
{
    pRoot = new TrieNode();     // we should pay attention to that the root only store '*'
    pRoot->setNodeLetter('*');
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
        if(str[i] == 39){
            index = MAX_BRANCH_NUM - 1;
        }
        else{
            index = (str[i] - 'a') * 2;
        }
        if (index < 0 || index > MAX_BRANCH_NUM - 1) {
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
            pLoc->nextBranch[index]->parentBranch = pLoc;
        }
        pLoc = pLoc->nextBranch[index];
        
        if (i == stringSize - 1) {
            pLoc->leaf = true;
        }
    }
    return;
}


bool Trie::Search(string& str)
{
    int stringSize;
    stringSize = int(str.size());
    assert(stringSize != 0);
    int i = 0;
    int index = -1;
    TrieNode* pLoc = pRoot;
    
    while (i < stringSize) {
        if(str[i] == 39){
            index = MAX_BRANCH_NUM - 1;
        }
        else{
            index = (str[i] - 'a') * 2;
        }
        if (index < 0 || index > MAX_BRANCH_NUM - 1) {
            return false;
        }
        if (i == stringSize - 1)                // check if it is the last character. if so, add one to the index
        {
            index += 1;
        }
        
        pLoc = pLoc->nextBranch[index];
        if (pLoc == NULL)
            return false;
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


TrieNode* Trie::getRoot()
{
    return pRoot;
}

void Trie::swapNodeCost(double minCost)
{
    swapNodeCostUtil(pRoot, minCost);
}

void Trie::swapNodeCostUtil(TrieNode* node, double minCost)
{
    if (node == NULL)
        return;
    
    int cur = node->getCurNodeCost();
    if(cur - minCost > BEAM)
        node->setPreNodeCost(INT_MAX / 2);
    else
        node->setPreNodeCost(cur);
    node->setCurNodeCost(INT_MAX / 2);
    
    for (int i = 0; i < MAX_BRANCH_NUM; i++)
    {
//        int pre = node->getPreNodeCost();
        swapNodeCostUtil(node->nextBranch[i], minCost);
    }
}


void Trie::setNodeVector(int len)
{
    setNodeVectorUtil(pRoot, len);
}

void Trie::setNodeVectorUtil(TrieNode *node, int len)
{
    if (node == NULL) {
        return;
    }
    
    node->setVectorBool(len);
    node->setVectorNode(len);
    
    for (int i = 0; i < MAX_BRANCH_NUM; i++) {
        setNodeVectorUtil(node->nextBranch[i], len);
    }
}







