/**
 * @author: matank214@gmail.com
 */

#ifndef ITERATORS_ON_TREE_HPP
#define ITERATORS_ON_TREE_HPP

#include "node.hpp"

#include <queue>
#include <stack>
#include <vector>
using namespace std;

template <typename T>
class dfs_iterator
{
    stack<Node<T> *> stck;

public:
    dfs_iterator(Node<T> *root)
    {
        if (root != nullptr)
        {
            stck.push(root);
        }
    }

    T &operator*()
    {
        return stck.top()->value;
    }

    Node<T> *operator->()
    {
        return stck.top();
    }

    dfs_iterator &operator++()
    {
        Node<T> *node = stck.top();
        stck.pop();
        for (int i = node->children.size() - 1; i >= 0; i--)
        {
            stck.push(node->children[(size_t)i]);
        }
        return *this;
    }

    bool operator==(const dfs_iterator &other)
    {
        return stck.size() == other.stck.size();
    }

    bool operator!=(const dfs_iterator &other)
    {
        return !(*this == other);
    }
};

template <typename T>
class bfs_iterator
{
    queue<Node<T> *> queue1;

public:
    bfs_iterator(Node<T> *root)
    {
        if (root != nullptr)
        {
            queue1.push(root);
        }
    }

    T &operator*()
    {
        return queue1.front()->value;
    }

    Node<T> *operator->()
    {
        return queue1.front();
    }

    bfs_iterator &operator++()
    {
        Node<T> *node = queue1.front();
        queue1.pop();
        for (size_t i = 0; i < node->children.size(); i++)
        {
            queue1.push(node->children[i]);
        }
        return *this;
    }

    bool operator==(const bfs_iterator &other)
    {
        return queue1.size() == other.queue1.size();
    }

    bool operator!=(const bfs_iterator &other)
    {
        return !(*this == other);
    }
};

template <typename T>
class in_order_iterator
{
    stack<Node<T> *> stck;

public:
    in_order_iterator(Node<T> *root)
    {
        Node<T> *current = root;
        while (current != nullptr)
        {
            stck.push(current);
            current = current->children[0];
        }
    }

    T &operator*()
    {
        return stck.top()->value;
    }

    Node<T> *operator->()
    {
        return stck.top();
    }

    in_order_iterator &operator++()
    {
        Node<T> *node = stck.top();
        stck.pop();
        Node<T> *current = node->children[1];
        while (current != nullptr)
        {
            stck.push(current);
            current = current->children[0];
        }
        return *this;
    }

    bool operator==(const in_order_iterator &other)
    {
        return stck.size() == other.stck.size();
    }

    bool operator!=(const in_order_iterator &other)
    {
        return !(*this == other);
    }
};

template <typename T>
class pre_order_iterator
{
    stack<Node<T> *> stck;

public:
    pre_order_iterator(Node<T> *root)
    {
        if (root != nullptr)
        {
            stck.push(root);
        }
    }

    T &operator*()
    {
        return stck.top()->value;
    }

    Node<T> *operator->()
    {
        return stck.top();
    }

    pre_order_iterator &operator++()
    {
        Node<T> *node = stck.top();
        stck.pop();
        for (int i = node->children.size() - 1; i >= 0; i--)
        {
            stck.push(node->children[(sie_t)i]);
        }
        return *this;
    }

    bool operator==(const pre_order_iterator &other)
    {
        return stck.size() == other.stck.size();
    }

    bool operator!=(const pre_order_iterator &other)
    {
        return !(*this == other);
    }
};

template <typename T>
class post_order_iterator
{
    stack<Node<T> *> stck;
    vector<bool> visited;

public:
    post_order_iterator(Node<T> *root)
    {
        if (root != nullptr)
        {
            visited.push_back(false);
            stck.push(root);
        }
    }

    T &operator*()
    {
        return stck.top()->value;
    }

    Node<T> *operator->()
    {
        return stck.top();
    }

    post_order_iterator &operator++()
    {
        while (!stck.empty())
        {
            Node<T> *node = stck.top();
            bool nodeVisited = visited.back();
            stck.pop();
            visited.pop_back();

            if (nodeVisited)
            {
                // Node has been visited, return it
                return *this;
            }
            else
            {
                // Mark the node as visited and push it back onto the stck
                stck.push(node);
                visited.push_back(true);

                // Push all children onto the stck
                for (size_t i = node->children.size(); i > 0; --i)
                {
                    stck.push(node->children[i - 1]);
                    visited.push_back(false);
                }
            }
        }
        return *this;
    }

    bool operator==(const post_order_iterator &other)
    {
        return stck.size() == other.stck.size();
    }

    bool operator!=(const post_order_iterator &other)
    {
        return !(*this == other);
    }
};

template <typename T>
class min_heap_iterator
{
    vector<Node<T> *> heap;

public:
    min_heap_iterator(Node<T> *root)
    {
        if (root != nullptr)
        {
            dfs_iterator<T> dfs(root);
            while (dfs != nullptr)
            {
                heap.push_back(*dfs);
                ++dfs;
            }
            std::make_heap(heap.begin(), heap.end(), [](Node<T> *a, Node<T> *b)
                           { return a->value > b->value; });
        }
    }

    T &operator*()
    {
        return heap.front()->value;
    }

    Node<T> *operator->()
    {
        return heap.front();
    }

    min_heap_iterator &operator++()
    {
        std::pop_heap(heap.begin(), heap.end(), [](Node<T> *a, Node<T> *b)
                      { return a->value > b->value; });
        heap.pop_back();
        return *this;
    }

    bool operator==(const min_heap_iterator &other) const
    {
        return heap.size() == other.heap.size();
    }

    bool operator!=(const min_heap_iterator &other) const
    {
        return !(*this == other);
    }
};

#endif