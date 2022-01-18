//
// Created by liuziwei on 2022/1/18.
//

#ifndef TT_TRIE_H
#define TT_TRIE_H
#include <vector>
#include <string>
#include <array>
class Trie{
public:
    Trie(){
        flag_ = false;
        value_ = 0;
    }
    ~Trie();
    void insert(std::string word, int value){
        Trie* node = this;
        for (int i = 0; i < word.size(); i++){
            char c = word[i];
            if (node->children_[c] == nullptr){
                node->children_[c] = new Trie();
            }
            node = node->children_[c];
        }
        node->flag_ = true;
        value_ = value;
    }
    bool find(std::string word){
        Trie* node = this;
        for(int i = 0; i < word.size(); i++){
            char c = word[i];
            if (node->children_[c] == nullptr){
                return false;
            }
            node = node->children_[c];
        }
        return node->flag_;
    }
    bool startWith(std::string prefix) {
        Trie *node = this;
        for(int i = 0; i < prefix.size(); i++){
            char c = prefix[i];
            if (node->children_[c] == nullptr){
                return false;
            }
            node = node->children_[c];
        }
        return node->flag_;
    }
private:
    std::array<Trie*, 256> children_;
    bool flag_;
    int value_;
};
#endif //TT_TRIE_H
