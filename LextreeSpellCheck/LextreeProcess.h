#ifndef LEXTREE_PROCESS

#include <algorithm>
#include <map>
#include "Trie.h"
#include "readFile.h"

#define LOOP_PENALTY  1
#define OTHER_PENALTY 2

bool readTestFile(string filePath, string inFileName, string outFileName, vector<string>& vec);
bool createTrie(string filePath, string inFileName, Trie& trie);
void beamSearch(map<string, double>& resultSet, Trie& trie, string& input);
void beamSearchUtil(map<string, double>& resultSet, TrieNode* node, string& input, string& tempStr, int pos, double& minCost);
void beamSearchLoop(Trie& trie, string& input, vector<TrieNode*>& minLeafNodeSet,vector<double>& minLeafCostSet);
void beamSearchLoopUtil(TrieNode* minLeafNodePrev, double minLeafCostPrev,TrieNode* node, char input, int input_len, int pos, double& minCost , TrieNode*& minLeafNode, double& minLeafCost);
#endif //LEXTREE_PROCESS
