/**
 * @author: matank214@gmail.com
 */

#ifndef TREE_HPP
#define TREE_HPP

#pragma once

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <cmath>

#include "node.hpp"
#include "iterators_on_tree.hpp"
#include <vector>
#include <iostream>
#include "CustomEllipseItem.hpp"

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

    friend operator<<(ostream &os, ParentTree<T, K> &tree)
    {
        tree.draw(300, 50);
        return os;
    }

    void draw(int x, int y, int circleSize = 75, int horizontalSpacing = 350, int verticalSpacing = 150) const {
        int argc = 0;
        char** argv = {nullptr};
        QApplication app(argc, argv);
        QGraphicsScene scene;
        QGraphicsView view(&scene);
        view.setBackgroundBrush(Qt::white);

        vector<QGraphicsItem*> items;

        draw(&scene, root, x, y, circleSize, horizontalSpacing, verticalSpacing, items);

        view.show();

        app.exec();

        app.quit();
    }

    private:

    void draw(QGraphicsScene* scene, Node<T>* node, int x, int y, int circleSize, int horizontalSpacing, int verticalSpacing, vector<QGraphicsItem*>& items, int depth = 0) const {
        if (!node) return;

        // Create and add the custom ellipse item to the scene
        CustomEllipseItem* ellipse = new CustomEllipseItem(x, y, circleSize, circleSize, QString::fromStdString(node->to_str()));
        items.push_back(ellipse);
        scene->addItem(ellipse);

        // add a text item to the scene that contains the node's data
        QGraphicsTextItem* text = scene->addText(QString::fromStdString(node->to_short_string()));
        text->setPos(x + circleSize / 2 - text->boundingRect().width() / 2, y + circleSize / 2 - text->boundingRect().height() / 2);

        // calculate the horizontal spacing between children nodes
        int depthFactor = std::pow(2, depth);                                                   // Exponential growth factor(2^depth)
        int adjustedHorizontalSpacing = std::max(horizontalSpacing / depthFactor, circleSize);  // Ensure spacing doesn't become too small

        // Calculate the x position of the first child node
        int childX = x - (node->get_childrens().size() - 1) * adjustedHorizontalSpacing / 2;

        // Draw the children nodes
        for (Node<T>* child : node->get_childrens()) {
            if (child == nullptr) {  // if the child is nullptr, just add the horizontal spacing and continue
                childX += adjustedHorizontalSpacing;
                continue;
            }

            // Draw the line between the parent and the child
            scene->addLine(x + circleSize / 2, y + circleSize, childX + circleSize / 2, y + verticalSpacing, QPen(Qt::black));

            // Recursively draw child nodes with more aggressively adjusted spacing
            draw(scene, child, childX, y + verticalSpacing, circleSize, horizontalSpacing, verticalSpacing, items, depth + 1);
            childX += adjustedHorizontalSpacing;
        }
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