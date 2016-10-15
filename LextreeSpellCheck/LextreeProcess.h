#ifndef LEXTREE_PROCESS

#include <algorithm>
#include <map>
#include "Trie.h"
#include "readFile.h"



bool readTestFile(string filePath, string inFileName, string outFileName, vector<string>& vec);
bool createTrie(string filePath, string inFileName, Trie& trie);
void beamSearch(map<string, int>& resultSet, Trie& trie, string& input);
void beamSearchUtil(map<string, int>& resultSet, TrieNode* node, string& input, string& tempStr, int pos, int& minCost);
void beamSearchLoop(Trie& trie, string& input);
void beamSearchLoopUtil(TrieNode* minLeafNodePrev, int minLeafCostPrev,TrieNode* node, char input, int input_len, int pos, int& minCost , TrieNode*& minLeafNode, int& minLeafCost);
#endif //LEXTREE_PROCESS
