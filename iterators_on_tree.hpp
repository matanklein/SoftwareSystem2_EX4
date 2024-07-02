#ifndef ITERATORS_ON_TREE_HPP
#define ITERATORS_ON_TREE_HPP

#include "node.hpp"
#include <queue>
#include <stack>
#include <vector>
using namespace std;

template <typename T>
class dfs_iterator {
    stack<Node<T>*> stack;
public:
    dfs_iterator(Node<T>* root) {
        if(root != nullptr){
            stack.push(root);
        }
    }

    T& operator*() {
        return stack.top()->value;
    }

     Node<T>* operator->() {
        return stack.top();
    }

    dfs_iterator& operator++() {
        Node<T>* node = stack.top();
        stack.pop();
        for (int i = node->children.size() - 1; i >= 0; i--) {
            stack.push(node->children[i]);
        }
        return *this;
    }

    bool operator==(const dfs_iterator& other) {
        return stack.size() == other.stack.size();
    }

    bool operator!=(const dfs_iterator& other) {
        return !(*this == other);
    }
};


template <typename T>
class bfs_iterator {
    queue<Node<T>*> queue;
public:
    bfs_iterator(Node<T>* root) {
        if(root != nullptr){
            queue.push(root);
        }
    }

    T& operator*() {
        return queue.front()->value;
    }

    Node<T>* operator->() {
        return queue.front();
    }

    bfs_iterator& operator++() {
        Node<T>* node = queue.front();
        queue.pop();
        for (int i = 0; i < node->children.size(); i++) {
            queue.push(node->children[i]);
        }
        return *this;
    }

    bool operator==(const bfs_iterator& other) {
        return queue.size() == other.queue.size();
    }

    bool operator!=(const bfs_iterator& other) {
        return !(*this == other);
    }
};

template <typename T>
class in_order_iterator {
    stack<Node<T>*> stack;
public:

    in_order_iterator(Node<T>* root) {
        Node<T>* current = root;
        while (current != nullptr) {
            stack.push(current);
            current = current->children[0];
        }
    }

    T& operator*() {
        return stack.top()->value;
    }

    Node<T>* operator->() {
        return stack.top();
    }

    in_order_iterator& operator++() {
        Node<T>* node = stack.top();
        stack.pop();
        Node<T>* current = node->children[1];
        while (current != nullptr) {
            stack.push(current);
            current = current->children[0];
        }
        return *this;
    }

    bool operator==(const in_order_iterator& other) {
        return stack.size() == other.stack.size();
    }

    bool operator!=(const in_order_iterator& other) {
        return !(*this == other);
    }
};

template <typename T>
class pre_order_iterator {
    stack<Node<T>*> stack;
public:
    pre_order_iterator(Node<T>* root) {
        if(root != nullptr){
            stack.push(root);
        }
    }

    T& operator*() {
        return stack.top()->value;
    }

    Node<T>* operator->() {
        return stack.top();
    }

    pre_order_iterator& operator++() {
        Node<T>* node = stack.top();
        stack.pop();
        for (int i = node->children.size() - 1; i >= 0; i--) {
            stack.push(node->children[i]);
        }
        return *this;
    }

    bool operator==(const pre_order_iterator& other) {
        return stack.size() == other.stack.size();
    }

    bool operator!=(const pre_order_iterator& other) {
        return !(*this == other);
    }
};

template <typename T>
class post_order_iterator {
    stack<Node<T>*> stack;
    vector<Node<T>*> visited;
public:

    post_order_iterator(Node<T>* root) {
        if(root != nullptr){
            visited.push_back(false);
            stack.push(root);
        }
    }

    T& operator*() {
        return stack.top()->value;
    }

    Node<T>* operator->() {
        return stack.top();
    }

    post_order_iterator& operator++() {
        while (!node_stack.empty()) {
            Node<T>* node = node_stack.top();
            bool visited = visited_stack.top();
            node_stack.pop();
            visited_stack.pop();

            if (visited) {
                // Node has been visited, return it
                return *this;
            } else {
                // Mark the node as visited and push it back onto the stack
                node_stack.push(node);
                visited_stack.push(true);

                // Push all children onto the stack
                for (int i = node->children.size() - 1; i >= 0; --i) {
                    node_stack.push(node->children[i]);
                    visited_stack.push(false);
                }
            }
        }
        return *this;
    }

    bool operator==(const post_order_iterator& other) {
        return stack.size() == other.stack.size();
    }

    bool operator!=(const post_order_iterator& other) {
        return !(*this == other);
    }
};

#endif