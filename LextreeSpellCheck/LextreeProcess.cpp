#include "LextreeProcess.h"


bool readTestFile(string filePath, string inFileName, string outFileName, vector<string>& vec)
{
	convertFile(filePath, inFileName, outFileName);
	readFile(filePath, outFileName, vec);
	return true;
}

bool createTrie(string filePath, string inFileName, Trie& trie)
{
	string str;
	ifstream in(filePath + inFileName);
	while (in >> str)
	{
		trie.Insert(str);
	}
	return true;
}

void beamSearch(map<string, int>& resultSet, Trie& trie, string& input)
{
	input.insert(0, "*");
	const int input_len = int (input.size());
	TrieNode* node = trie.getRoot();
	string str = "";     //used to save the template in a map
    
    int minCost =INT_MAX / 2;
	for (int i = 0; i < input_len; i++)
	{
		if (i > 1)
			trie.swapNodeCost(minCost);     //swap the preNodeCost and curNodeCost when move to next input character
        minCost = INT_MAX / 2;
		beamSearchUtil(resultSet, node, input, str, i, minCost);
	}
}

void beamSearchUtil(map<string, int>& resultSet, TrieNode* node, string& input, string& tempStr, int pos, int& minCost)
{
	if (node == NULL)
		return;

	if (pos == 0)
	{
		if (node->getParent() == NULL)
			node->preNodeCost = 0;
		else
			node->preNodeCost = node->parentBranch->preNodeCost + 1;
	}
	else
	{
        if (node->getParent() == NULL){
            if (node->preNodeCost != INT_MAX / 2)
                node->curNodeCost = node->preNodeCost + 1;
        }
		else
        {
            if(node->preNodeCost != INT_MAX / 2 && node->parentBranch->preNodeCost != INT_MAX / 2)
                node->curNodeCost = min({ node->preNodeCost + 1, node->parentBranch->curNodeCost + 1,
                    node->parentBranch->preNodeCost + (input[pos] == node->getNodeLetter() ? 0 : 1) });
            else if(node->preNodeCost != INT_MAX / 2)
                node->curNodeCost = min({ node->preNodeCost + 1, node->parentBranch->curNodeCost + 1});
            else if(node->parentBranch->preNodeCost != INT_MAX / 2)
                node->curNodeCost = min({node->parentBranch->curNodeCost + 1,
                    node->parentBranch->preNodeCost + (input[pos] == node->getNodeLetter() ? 0 : 1) });
            else if(node->parentBranch->curNodeCost != INT_MAX / 2)
                node->curNodeCost = node->parentBranch->curNodeCost + 1;
        }
        if(minCost > node->curNodeCost)
            minCost = node->curNodeCost;
		if (pos == input.length() - 1)
			tempStr += node->getNodeLetter();
	}

	if (node->isLeaf() && pos == input.length() - 1)
	{
		//resultSet[tempStr] = node->curNodeCost;
		resultSet.insert(pair<string, int>(tempStr, node->curNodeCost));
	}

	for (int i = 0; i < MAX_BRANCH_NUM; i++) {
		
		string tempStr2 = tempStr;
		beamSearchUtil(resultSet, node->nextBranch[i], input, tempStr2, pos, minCost);
	}
	
}

void beamSearchLoop(Trie& trie, string& input, vector<TrieNode*>& minLeafNodeSet,vector<int>& minLeafCostSet)
{
    input.insert(0, "*");
    const int input_len = int (input.size());
    TrieNode* node = trie.getRoot();
    trie.setNodeVector(input_len);

    TrieNode* minLeafNode;
    int minCost,minLeafCost;
    
    for (int i = 0; i < input_len; i++) {
        
        minLeafCost = INT_MAX / 2;
        minLeafNode = NULL;
        
        minCost = INT_MAX / 2;
        
        char temp = input[i];
        
        if (i > 0)
        {
            beamSearchLoopUtil(minLeafNodeSet[i - 1], minLeafCostSet[i - 1], node, temp, input_len ,i, minCost, minLeafNode, minLeafCost);
            trie.swapNodeCost(minCost);
        }
        else
        {
            beamSearchLoopUtil(NULL, INT_MAX / 2, node, temp, input_len ,i, minCost, minLeafNode, minLeafCost);
        }
        minLeafNodeSet.push_back(minLeafNode);
        minLeafCostSet.push_back(minLeafCost);
    }
}

void beamSearchLoopUtil(TrieNode* minLeafNodePrev, int minLeafCostPrev,TrieNode* node, char input, int input_len, int pos, int& minCost , TrieNode*& minLeafNode, int& minLeafCost)
{
    if (node == NULL)
        return;
    
    // if it is the dummy state of the input string
    if (pos == 0)
    {
        if (node->getParent() == NULL)
            node->preNodeCost = 0;
        else
            node->preNodeCost = node->parentBranch->preNodeCost + 1;
        if (node->isLeaf()) {
            if (node->preNodeCost < minLeafCost)
            {
                minLeafCost = node->preNodeCost;
                minLeafNode = node;
            }
        }
        node->vectorNode[pos] = NULL;
        node->vectorBool[pos] = false;
    }
    
    // if it is not the dummy state of the input string
    else
    {
        // if it is the dummy state of the lextree
        if (node->getParent() == NULL)
        {
            if (node->preNodeCost != INT_MAX / 2)
            {
                node->curNodeCost = node->preNodeCost + 1;
            }
            node->vectorNode[pos] = node;
            node->vectorBool[pos] = false;
        }
        // if it is the first character of the lextree
        else if (node->getParent()->getParent() == NULL)
        {
            if(node->preNodeCost != INT_MAX / 2 && node->parentBranch->preNodeCost != INT_MAX / 2)
            {
                int prevCost = node->preNodeCost + 1;
                int prevParentCost = node->parentBranch->preNodeCost + (input == node->getNodeLetter() ? 0 : 1);
                int curParentCost = node->parentBranch->curNodeCost + 1;
                int prevLeafCost = minLeafCostPrev + (input == node->getNodeLetter() ? 0 : 1);
                node->curNodeCost = min({prevCost, prevParentCost, curParentCost, prevLeafCost});
                int cost = node->curNodeCost;
                if (cost == prevCost)
                {
                    node->vectorNode[pos] = node;
                    node->vectorBool[pos] = false;
                }
                else if(cost == prevParentCost)
                {
                    node->vectorNode[pos] = node->getParent();
                    node->vectorBool[pos] = false;
                }
                else if (cost == curParentCost){
                    node->vectorNode[pos] = node->getParent()->vectorNode[pos];
                    node->vectorBool[pos] = node->getParent()->vectorBool[pos];
                }
                else{
                    node->vectorNode[pos] = minLeafNodePrev;
                    node->vectorBool[pos] = true;
                }
            }
            else if(node->preNodeCost != INT_MAX / 2)
            {
                int prevCost = node->preNodeCost + 1;
                int curParentCost = node->parentBranch->curNodeCost + 1;
                int prevLeafCost = minLeafCostPrev + (input == node->getNodeLetter() ? 0 : 1);
                node->curNodeCost = min({prevCost, curParentCost, prevLeafCost});
                int cost = node->curNodeCost;
                if (cost == prevCost)
                {
                    node->vectorNode[pos] = node;
                    node->vectorBool[pos] = false;
                }
                else if (cost == curParentCost){
                    node->vectorNode[pos] = node->getParent()->vectorNode[pos];
                    node->vectorBool[pos] = node->getParent()->vectorBool[pos];
                }
                else{
                    node->vectorNode[pos] = minLeafNodePrev;
                    node->vectorBool[pos] = true;
                }
            }
            else if(node->parentBranch->preNodeCost != INT_MAX / 2)
            {
                int prevParentCost = node->parentBranch->preNodeCost + (input == node->getNodeLetter() ? 0 : 1);
                int curParentCost = node->parentBranch->curNodeCost + 1;
                int prevLeafCost = minLeafCostPrev + (input == node->getNodeLetter() ? 0 : 1);
                node->curNodeCost = min({prevParentCost, curParentCost, prevLeafCost});
                int cost = node->curNodeCost;
                if(cost == prevParentCost){
                    node->vectorNode[pos] = node->getParent();
                    node->vectorBool[pos] = false;
                }
                else if (cost == curParentCost){
                    node->vectorNode[pos] = node->getParent()->vectorNode[pos];
                    node->vectorBool[pos] = node->getParent()->vectorBool[pos];
                }
                else{
                    node->vectorNode[pos] = minLeafNodePrev;
                    node->vectorBool[pos] = true;
                }
            }
            else if(node->parentBranch->curNodeCost != INT_MAX / 2)
            {
                int curParentCost = node->parentBranch->curNodeCost + 1;
                int prevLeafCost = minLeafCostPrev + (input == node->getNodeLetter() ? 0 : 1);
                node->curNodeCost = min({curParentCost, prevLeafCost});
                int cost = node->curNodeCost;
                if (cost == curParentCost)
                {
                    node->vectorNode[pos] = node->getParent()->vectorNode[pos];
                    node->vectorBool[pos] = node->getParent()->vectorBool[pos];
                }
                else
                {
                    node->vectorNode[pos] = minLeafNodePrev;
                    node->vectorBool[pos] = true;
                }
            }
            else
            {
                int prevLeafCost = minLeafCostPrev;
                node->curNodeCost = prevLeafCost;
                node->vectorNode[pos] = minLeafNodePrev;
                node->vectorBool[pos] = true;
            }
        }
        // if it is the other node of the lextree
        else
        {
            if(node->preNodeCost != INT_MAX / 2 && node->parentBranch->preNodeCost != INT_MAX / 2)
            {
                int prevCost = node->preNodeCost + 1;
                int prevParentCost = node->parentBranch->preNodeCost + (input == node->getNodeLetter() ? 0 : 1);
                int curParentCost = node->parentBranch->curNodeCost + 1;
                node->curNodeCost = min({prevCost, prevParentCost, curParentCost});
                int cost = node->curNodeCost;
                if (cost == prevCost)
                {
                    node->vectorNode[pos] = node;
                    node->vectorBool[pos] = false;
                }
                else if(cost == prevParentCost)
                {
                    node->vectorNode[pos] = node->getParent();
                    node->vectorBool[pos] = false;
                }
                else
                {
                    node->vectorNode[pos] = node->getParent()->vectorNode[pos];
                    node->vectorBool[pos] = node->getParent()->vectorBool[pos];
                }
            }
            else if(node->preNodeCost != INT_MAX / 2)
            {
                int prevCost = node->preNodeCost + 1;
                int curParentCost = node->parentBranch->curNodeCost + 1;
                node->curNodeCost = min({prevCost, curParentCost});
                int cost = node->curNodeCost;
                if (cost == prevCost)
                {
                    node->vectorNode[pos] = node;
                    node->vectorBool[pos] = false;
                }
                else
                {
                    node->vectorNode[pos] = node->getParent()->vectorNode[pos];
                    node->vectorBool[pos] = node->getParent()->vectorBool[pos];
                }
            }
            else if(node->parentBranch->preNodeCost != INT_MAX / 2)
            {
                int prevParentCost = node->parentBranch->preNodeCost + (input == node->getNodeLetter() ? 0 : 1);
                int curParentCost = node->parentBranch->curNodeCost + 1;
                node->curNodeCost = min({prevParentCost, curParentCost});
                int cost = node->curNodeCost;
                if(cost == prevParentCost)
                {
                    node->vectorNode[pos] = node->getParent();
                    node->vectorBool[pos] = false;
                }
                else
                {
                    node->vectorNode[pos] = node->getParent()->vectorNode[pos];
                    node->vectorBool[pos] = node->getParent()->vectorBool[pos];
                }
            }
            else if(node->parentBranch->curNodeCost != INT_MAX / 2)
            {
                int curParentCost = node->parentBranch->curNodeCost + 1;
                node->curNodeCost = curParentCost;
                node->vectorNode[pos] = node->getParent()->vectorNode[pos];
                node->vectorBool[pos] = node->getParent()->vectorBool[pos];
            }
        }
        
        // to get the min cost of the whole node from this column of the lextree
        if(minCost > node->curNodeCost)
        {
            minCost = node->curNodeCost;
        }
        
        // if is leaf, update the min leaf cost and the min leaf when fits
        if (node->isLeaf())
        {
            if (node->curNodeCost < minLeafCost)
            {
                minLeafCost = node->curNodeCost;
                minLeafNode = node;
            }
        }
    }
    for (int i = 0; i < MAX_BRANCH_NUM; i++)
    {
        beamSearchLoopUtil(minLeafNodePrev, minLeafCostPrev, node->nextBranch[i], input,input_len, pos, minCost, minLeafNode, minLeafCost);
    }
}





