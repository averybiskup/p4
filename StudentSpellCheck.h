#ifndef STUDENTSPELLCHECK_H_
#define STUDENTSPELLCHECK_H_

#include "SpellCheck.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

struct node {
    node * children[27];
    bool end = true;
    char letter;
};

class Trie {
    public:
        void insert(string s) {
            node * cur = &root;
            
            for (int i = 0; i < s.size(); i++) {
                char c = tolower(s[i]); int index = int(c) - 97; 
                node* child = new node;
                child->letter = tolower(s[i]);

                cur->children[index] = child;
                cur->end = false;
                cur = child;
            } 
            cur->end = true;
        }

        bool check(string s) {
            node * cur = &root;

            int count = 0;
            for (int i = 0; i < s.size(); i++) {
                int index = s[i] - 97;

                if (cur->children[index]) {
                    cur = cur->children[index];
                    count++;
                }
                else {
                    break;
                }
            }
            return count == s.size();
        }

    private:
        node root;
};

class StudentSpellCheck : public SpellCheck {
public:
    StudentSpellCheck() { }
	virtual ~StudentSpellCheck();
	bool load(std::string dict_file);
	bool spellCheck(std::string word, int maxSuggestions, std::vector<std::string>& suggestions);
	void spellCheckLine(const std::string& line, std::vector<Position>& problems);

private:
    Trie t;
    

};

#endif  // STUDENTSPELLCHECK_H_
