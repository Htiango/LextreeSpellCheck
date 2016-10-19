//
//  Trie.h
//  LextreeSpellCheck
//
//  Created by hty on 12/10/2016.
//  Copyright © 2016 hty. All rights reserved.
//

#ifndef Trie_h
#define Trie_h

#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <assert.h>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

#define MAX_BRANCH_NUM  52   // we have 26 characters. double it so that can store the one that ends here

#define BEAM (10)

/* define the class for the node of the trie tree*/
class TrieNode
{
public:
    char letter;     // one letter of the word that store there
    TrieNode* nextBranch[MAX_BRANCH_NUM];   // the pointers' vectors that point to the next branch
    TrieNode* parentBranch;
    double preNodeCost;
    double curNodeCost;
    vector<TrieNode*> vectorNode;
    vector<bool> vectorBool;
    bool leaf;
    

public:
    TrieNode() : letter(NULL)
    {
        memset(nextBranch,NULL,sizeof(TrieNode*) * MAX_BRANCH_NUM);
        parentBranch = NULL;
        preNodeCost = curNodeCost = INT_MAX / 2;
        leaf = false;
    }
    bool setPreNodeCost(double val);
    int getPreNodeCost();
    bool setCurNodeCost(double val);
    int getCurNodeCost();
    bool setNodeLetter(char c);
    char getNodeLetter();
    TrieNode* getParent();
    bool isLeaf();              // return true is it's a leaf
    void setVectorNode(int len);
    void setVectorBool(int len);
    string getWord();
};


/* define the class for the trie tree */
class Trie{
public:
    Trie();
    ~Trie();
    void Insert(string& str);   // insert string str
    bool Search(string& str);
    void PrintALL();                // print out all the node in the trie tree
    TrieNode* getRoot();        //get root node
    void swapNodeCost(double minCost);
    void setNodeVector(int len);
private:
    TrieNode* pRoot;
    void swapNodeCostUtil(TrieNode* node, double minCost);
    void setNodeVectorUtil(TrieNode* node, int len);
private:
    void Destory(TrieNode* pRoot);
    bool Print(TrieNode* pRoot, string& str);
};



#endif /* Trie_h */
