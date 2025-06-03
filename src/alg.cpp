// Copyright 2022 NNTU-CS
#include "tree.h"
#include <algorithm>
#include <stdexcept>

PMTree::PMTree(const std::vector<char>& elements) {
    if (elements.empty()) {
        root = nullptr;
        totalPermutations = 0;
        return;
    }
    totalPermutations = factorial(elements.size());
    root = std::make_unique<Node>('\0'); // Dummy root
    
    for (char elem : elements) {
        root->children.push_back(std::make_unique<Node>(elem));
    }
    for (auto& child : root->children) {
        std::vector<char> remaining;
        for (char elem : elements) {
            if (elem != child->value) {
                remaining.push_back(elem);
            }
        }
        buildTree(child.get(), remaining);
    }
}
void PMTree::buildTree(Node* parent, const std::vector<char>& remaining) {
    if (remaining.empty()) {
        return;
    }
    for (char elem : remaining) {
        parent->children.push_back(std::make_unique<Node>(elem));
        std::vector<char> newRemaining;
        for (char e : remaining) {
            if (e != elem) {
                newRemaining.push_back(e);
            }
        }
        buildTree(parent->children.back().get(), newRemaining);
    }
}
std::vector<std::vector<char>> PMTree::getAllPerms() const {
    std::vector<std::vector<char>> result;
    if (!root) return result;
    
    std::vector<char> current;
    for (const auto& child : root->children) {
        collectPerms(child.get(), current, result);
    }
    return result;
}
void PMTree::collectPerms(const Node* node, std::vector<char>& current, 
                         std::vector<std::vector<char>>& result) const {
    current.push_back(node->value);
    if (node->children.empty()) {
        result.push_back(current);
    } else {
        for (const auto& child : node->children) {
            collectPerms(child.get(), current, result);
        }
    }
    current.pop_back();
}
std::vector<char> PMTree::getPerm1(int num) const {
    if (num < 1 || num > totalPermutations || !root) {
        return {};
    }
    std::vector<char> result;
    int remaining = num;
    for (const auto& child : root->children) {
        if (getPermByTraversal(child.get(), remaining, result)) {
            return result;
        }
    }
    return {};
}
bool PMTree::getPermByTraversal(const Node* node, int& remaining, 
                               std::vector<char>& result) const {
    result.push_back(node->value);
    if (node->children.empty()) {
        remaining--;
        if (remaining == 0) {
            return true;
        }
    } else {
        for (const auto& child : node->children) {
            if (getPermByTraversal(child.get(), remaining, result)) {
                return true;
            }
        }
    }
    result.pop_back();
    return false;
}
std::vector<char> PMTree::getPerm2(int num) const {
    if (num < 1 || num > totalPermutations || !root) {
        return {};
    }
    std::vector<char> result;
    if (getPermByNavigation(root.get(), num - 1, result)) {
        return result;
    }
    return {};
}
bool PMTree::getPermByNavigation(const Node* node, int remaining, 
                                std::vector<char>& result) const {
    if (!node->children.empty()) {
        int subtreeSize = factorial(node->children.size());
        for (const auto& child : node->children) {
            if (remaining < subtreeSize) {
                result.push_back(child->value);
                return getPermByNavigation(child.get(), remaining, result);
            }
            remaining -= subtreeSize;
        }
    }
    return remaining == 0;
}
int PMTree::factorial(int n) const {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}
std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    return tree.getAllPerms();
}
std::vector<char> getPerm1(const PMTree& tree, int num) {
    return tree.getPerm1(num);
}
std::vector<char> getPerm2(const PMTree& tree, int num) {
    return tree.getPerm2(num);
}
