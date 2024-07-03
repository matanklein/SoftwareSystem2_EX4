/**
 * @author: matank214@gmail.com
 */

#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include "iterators_on_tree.hpp"
#include <vector>
using namespace std;

template <typename T, size_t K>
class ParentTree
{

protected:
    Node<T> *root;

public:
    ParentTree() : root(nullptr) {}

    ParentTree(Node<T> *root) : root(root) {}

    ~ParentTree()
    {
        dfs_iterator<T> it = begin_dfs_scan();
        while (it != end_dfs_scan())
        {
            it->clear_children();
            ++it;
        }
        root = nullptr;
    }

    void add_root(Node<T> *node)
    {
        root = node;
    }

    void add_sub_node(Node<T> *parent, Node<T> *child)
    {
        if (parent->get_childrens() >= K)
        {
            throw "Parent node has reached maximum children limit";
        }
        parent->add_child(child);
    }

    void clear_sub_nodes(Node<T> *parent)
    {
        parent->clear_children();
    }

    Node<T> *get_root()
    {
        return root;
    }

    bfs_iterator<T> begin_bfs_scan()
    {
        return bfs_iterator<T>(root);
    }

    bfs_iterator<T> end_bfs_scan()
    {
        return bfs_iterator<T>(nullptr);
    }

    dfs_iterator<T> begin_dfs_scan()
    {
        return dfs_iterator<T>(root);
    }

    dfs_iterator<T> end_dfs_scan()
    {
        return dfs_iterator<T>(nullptr);
    }

    bfs_iterator<T> begin()
    {
        return bfs_iterator<T>(root);
    }

    bfs_iterator<T> end()
    {
        return bfs_iterator<T>(nullptr);
    }
};

// General tree
template <typename T, size_t K = 2>
class Tree : public ParentTree<T, K>
{
public:
    dfs_iterator<T> begin_in_order()
    {
        return dfs_iterator<T>(this->root);
    }

    dfs_iterator<T> end_in_order()
    {
        return dfs_iterator<T>(nullptr);
    }

    dfs_iterator<T> begin_pre_order()
    {
        return dfs_iterator<T>(this->root);
    }

    dfs_iterator<T> end_pre_order()
    {
        return dfs_iterator<T>(nullptr);
    }

    dfs_iterator<T> begin_post_order()
    {
        return dfs_iterator<T>(this->root);
    }

    dfs_iterator<T> end_post_order()
    {
        return dfs_iterator<T>(nullptr);
    }
};

// Specialization for binary tree
template <typename T>
class Tree<T, 2> : public ParentTree<T, 2>
{
public:
    in_order_iterator<T> begin_in_order()
    {
        return in_order_iterator<T>(this->root);
    }

    in_order_iterator<T> end_in_order()
    {
        return in_order_iterator<T>(nullptr);
    }

    pre_order_iterator<T> begin_pre_order()
    {
        return pre_order_iterator<T>(this->root);
    }

    pre_order_iterator<T> end_pre_order()
    {
        return pre_order_iterator<T>(nullptr);
    }

    post_order_iterator<T> begin_post_order()
    {
        return post_order_iterator<T>(this->root);
    }

    post_order_iterator<T> end_post_order()
    {
        return post_order_iterator<T>(nullptr);
    }

    min_heap_iterator<T> begin_min_heap()
    {
        return min_heap_iterator<T>(this->root);
    }

    min_heap_iterator<T> end_min_heap()
    {
        return min_heap_iterator<T>(nullptr);
    }
};

#endif