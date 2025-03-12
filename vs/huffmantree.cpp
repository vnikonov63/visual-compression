#include "huffmantree.h"
#include <fstream>   // for std::ifstream, std::ofstream
#include <iostream>  // for std::cerr
#include <queue>     // for std::priority_queue

void populateCodes(Node* root, const string& prefix, map<char, string>& codes) {
    if (!root) return;

    if (!root->isDummy_) {
        codes[root->ch_] = prefix;
    }
    populateCodes(root->left_,  prefix + "0", codes);
    populateCodes(root->right_, prefix + "1", codes);
}

HuffmanTree::HuffmanTree(const QFile& inputFile)
{
    std::string inputFileName = inputFile.fileName().toStdString();

    std::ifstream file(inputFileName, std::ios::binary);
    if (!file.is_open()) {
        root = nullptr;
        return;
    }

    std::map<char,int> freqMap;
    char ch;
    int totalChars = 0;
    while (file.get(ch)) {
        freqMap[ch]++;
        totalChars++;
    }
    file.close();

    if (totalChars == 0) {
        root = nullptr;
        return;
    }

    std::priority_queue<Node*, std::vector<Node*>, Comparator> pq;
    for (auto& kv : freqMap) {
        Node* node = new Node(kv.first, kv.second);
        pq.push(node);
    }

    while (pq.size() > 1) {
        Node* left = pq.top();  pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* combined = new Node(left->freq_ + right->freq_);
        combined->left_  = left;
        combined->right_ = right;
        pq.push(combined);
    }

    root = pq.top();
    pq.pop();
}
