// Copyright 2022 NNTU-CS
#include <algorithm>
#include <memory>
#include <vector>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& elements) {
  if (elements.empty()) {
    root = nullptr;
    totalPermutations = 0;
    return;
  }
  
  totalPermutations = factorial(elements.size());
  root = std::make_unique<Node>('\0');
  
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
  int remaining = num - 1;
  for (const auto& child : root->children) {
    int childPerms = factorial(root->children.size() - 1);
    if (remaining < childPerms) {
      result.push_back(child->value);
      if (getPermByNavigation(child.get(), remaining, result)) {
        return result;
      }
      break;
    }
    remaining -= childPerms;
  }
  return result;
}

bool PMTree::getPermByNavigation(const Node* node, int remaining,
                                std::vector<char>& result) const {
  if (node->children.empty()) {
    return true;
  }
  
  int childPerms = factorial(node->children.size() - 1);
  for (const auto& child : node->children) {
    if (remaining < childPerms) {
      result.push_back(child->value);
      return getPermByNavigation(child.get(), remaining, result);
    }
    remaining -= childPerms;
  }
  return false;
}

int PMTree::factorial(int n) const {
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
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
