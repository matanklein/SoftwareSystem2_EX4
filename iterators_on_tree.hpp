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
        // push all the left children of the root
        stck.push(nullptr);
        while (root != nullptr)
        {
            stck.push(root);
            if (root->get_childrens() > 0 && root->get_children().at(0) != nullptr)
            { // has left child
                root = root->get_children().at(0);
            }
            else
            {
                root = nullptr; // end the loop
            }
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
        // if the node has a right child, push it and all its left children
        if (node->get_childrens() > 1 && node->get_children().at(1) != nullptr)
        {
            Node<T> *right_child = node->get_children().at(1);
            stck.push(right_child);
            // push all the left children of the right child
            Node<T> *right_child_left_child = right_child;
            while (right_child_left_child->get_childrens() > 0 && right_child_left_child->get_children().at(0) != nullptr)
            {
                right_child_left_child = right_child_left_child->get_children().at(0);
                stck.push(right_child_left_child);
            }
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
            stck.push(node->children[(size_t)i]);
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
private:
    vector<Node<T> *> post_order; // the post order of the tree
    int index;                    // the index of the current node in the post order

public:
    post_order_iterator(Node<T> *root) : index(-1)
    {
        if (root != nullptr)
        {
            stack<Node<T> *> stck;
            stck.push(root);
            Node<T> *prev = nullptr;

            while (!stck.empty())
            {
                if (stck.top() == nullptr)
                {
                    stck.pop();
                    continue;
                }
                Node<T> *current = stck.top();
                // if we are going down the tree
                if (prev == nullptr || (prev->get_childrens() > 0 && prev->get_children().at(0) == current) || (prev->get_childrens() > 1 && prev->get_children().at(1) == current))
                {
                    if (current->get_childrens() > 0 && current->get_children().at(0) != nullptr)
                    {
                        stck.push(current->get_children().at(0));
                    }
                    else if (current->get_childrens() > 1 && current->get_children().at(1) != nullptr)
                    {
                        stck.push(current->get_children().at(1));
                    }
                    else
                    {
                        post_order.push_back(current);
                        stck.pop();
                    }
                }
                else if (current->get_childrens() > 0 && prev == current->get_children().at(0))
                {
                    if (current->get_childrens() > 1 && current->get_children().at(1) != nullptr)
                    { // has right child
                        stck.push(current->get_children().at(1));
                    }
                    else
                    {
                        post_order.push_back(current);
                        stck.pop();
                    }
                }
                else if (current->get_childrens() > 1 && prev == current->get_children().at(1))
                {
                    post_order.push_back(current);
                    stck.pop();
                }
                prev = current;
            }

            if (!post_order.empty())
            {
                index = 0;
            }
        }
    }

    T &operator*()
    {
        return post_order[index]->value;
    }

    Node<T> *operator->()
    {
        return post_order[index];
    }

    post_order_iterator &operator++()
    {
        if (index >= 0 && index < (int)post_order.size())
        {
            index++;
        }
        return *this;
    }

    bool operator==(const post_order_iterator &other) const
    {
        return (index == other.index) && (post_order.size() == other.post_order.size());
    }

    bool operator!=(const post_order_iterator &other) const
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