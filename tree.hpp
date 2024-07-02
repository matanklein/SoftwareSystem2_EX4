#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include "iterators_on_tree.hpp"
#include <vector>
using namespace std;

template <typename T, size_t K>
class ParentTree {

protected:
    Node<T>* root;

public:

    Tree() : root(nullptr) {}

    Tree(Node<T>* root) : root(root) {}

    void add_root(Node<T>* node) {
        root = node;
    }

    void add_sub_node(Node<T>* parent, Node<T>* child) {
        if(parent->get_childrens() >= K) {
            throw "Parent node has reached maximum children limit";
        }
        parent->add_child(child);
    }

    void remove_sub_node(Node<T>* parent, Node<T>* child) {
        parent->remove_child(child);
    }

    void clear_sub_nodes(Node<T>* parent) {
        parent->clear_children();
    }

    Node<T>* get_root() {
        return root;
    }


    

};

template <typename T, size_t K = 2>
class Tree : public ParentTree<T, k> {
public:
    Tree() : ParentTree<T, k>() {}

    Tree(Node<T>* root) : Tree<T, k>(root) {}

    dfs_iterator<T> begin_in_order() {
        return dfs_iterator<T>(this->root);
    }

    dfs_iterator<T> end_in_order() {
        return dfs_iterator<T>(nullptr);
    }

    dfs_iterator<T> begin_pre_order() {
        return dfs_iterator<T>(this->root);
    }

    dfs_iterator<T> end_pre_order() {
        return dfs_iterator<T>(nullptr);
    }

    dfs_iterator<T> begin_post_order() {
        return dfs_iterator<T>(this->root);
    }

    dfs_iterator<T> end_post_order() {
        return dfs_iterator<T>(nullptr);
    }

};

template <typename T>
class Tree<T, 2> : public ParentTree<T, 2> {
    public:
    Tree() : ParentTree<T, 2>() {}

    Tree(Node<T>* root) : ParentTree<T, 2>(root) {}

    in_order_iterator begin_in_order() {
        return in_order_iterator(this->root);
    }

    in_order_iterator end_in_order() {
        return in_order_iterator(nullptr);
    }

    pre_order_iterator begin_pre_order() {
        return pre_order_iterator(this->root);
    }

    pre_order_iterator end_pre_order() {
        return pre_order_iterator(nullptr);
    }

    post_order_iterator begin_post_order() {
        return post_order_iterator(this->root);
    }

    post_order_iterator end_post_order() {
        return post_order_iterator(nullptr);
    }
};



#endif