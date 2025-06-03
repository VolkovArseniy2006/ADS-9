// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <chrono>
#include <random>
int main() {
    std::vector<char> elements = {'1', '2', '3'};
    PMTree tree(elements);
    auto allPerms = getAllPerms(tree);
    std::cout << "All permutations:\n";
    for (const auto& perm : allPerms) {
        for (char c : perm) {
            std::cout << c;
        }
        std::cout << "\n";
    }
    std::cout << "\nSpecific permutations:\n";
    std::cout << "Permutation 1: ";
    auto perm1 = getPerm1(tree, 1);
    for (char c : perm1) std::cout << c;
    std::cout << "\n";
    std::cout << "Permutation 2: ";
    auto perm2 = getPerm2(tree, 2);
    for (char c : perm2) std::cout << c;
    std::cout << "\n";
    return 0;
}
