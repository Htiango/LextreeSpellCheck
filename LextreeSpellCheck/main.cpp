//
//  main.cpp
//  LextreeSpellCheck
//
//  Created by hty on 12/10/2016.
//  Copyright © 2016 hty. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Trie.h"

using namespace std;

int main(int argc, const char * argv[]) {
    Trie t;
    string str;
//    int count = -1;
    ifstream in("/Users/hty/Desktop/Speech Recognition/project/project5/LextreeSpellCheck/LextreeSpellCheck/dict_1.txt");
    
    while(in >> str)
    {
        t.Insert(str);
    }
    
    string test = "test";
    bool isFind = t.Search(test);
    t.PrintALL();
    return 0;
}
