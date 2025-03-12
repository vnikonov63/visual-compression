#include <QFile>
#include <string>
#include <map>

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

using namespace std;

struct Node {
    int freq_;
    char ch_;
    Node* left_;
    Node* right_;
    bool isDummy_;
    Node(char c, int f) : freq_(f), ch_(c), left_(nullptr), right_(nullptr), isDummy_(false) {}
    Node(int f) : freq_(f), ch_('\0'), left_(nullptr), right_(nullptr), isDummy_(true) {}
};

struct Comparator {
    bool operator()(Node* a, Node* b) {
        if (a->freq_ != b->freq_) {
            return a->freq_ > b->freq_;
        }

        return a->ch_ > b->ch_;
    }
};

class HuffmanTree
{
public:
    HuffmanTree(const QFile& inputFile);
    Node* GetRoot() {return root;}
private:
    Node* root;
};

#endif // HUFFMANTREE_H
