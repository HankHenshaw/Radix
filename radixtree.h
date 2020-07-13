#pragma once

#include <string>
#include <array>
#include <vector>
#include <memory>

class RadixTree
{
public:
    struct Node {
        static const int SIZE = 26;
        std::string label;
        bool isEnd;
        std::array<std::shared_ptr<Node>, SIZE> child;
    public:
        Node() : label(""), isEnd(false) {}
        Node(const std::string &str, bool val) : label(str),  isEnd(val) {}
        bool insert(const std::string &str);
    };
private:
    Node *root;
public:
    RadixTree() : root(new Node) {};
    ~RadixTree() {delete root;}
    bool insert(const std::string &str);
    bool find(const std::string &str);
//    void remove(const std::string &str);
    void print() const;
};
