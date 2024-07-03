#include "tree.hpp"
#include "node.hpp"
#include "complex.hpp"
#include "iterators_on_tree.hpp"
#include "doctest.h"
#include <vector>
#include <iostream>

using namespace std;

TEST_CASE("node"){
    Node<int> node(5);
    CHECK(node.get_value() == 5);
}

TEST_CASE("add_child"){
    Node<int> node(5);
    Node<int> child(6);
    node.add_child(&child);
    CHECK(node.get_childrens() == 1);
}

TEST_CASE("remove_child"){
    Node<int> node(5);
    Node<int> child(6);
    node.add_child(&child);
    node.clear_children();
    CHECK(node.get_childrens() == 0);
}

TEST_CASE("clear_children"){
    Node<int> node(5);
    Node<int> child(6);
    node.add_child(&child);
    node.clear_children();
    CHECK(node.get_childrens() == 0);
}

TEST_CASE("implicit binary tree"){
    Tree<int> tree;
    Node<int> root(1);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);

    tree.add_root(&root);
    tree.add_sub_node(&root, &n1);
    tree.add_sub_node(&root, &n2);
    CHECK_THROWS(tree.add_sub_node(&root, &n3));
}

TEST_CASE("explicit binary tree"){
    Tree<int, 2> tree;
    Node<int> root(1);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);

    tree.add_root(&root);
    tree.add_sub_node(&root, &n1);
    tree.add_sub_node(&root, &n2);
    CHECK_THROWS(tree.add_sub_node(&root, &n3));
}

TEST_CASE("complex tree"){
    Tree<Complex> tree;
    Node<Complex> root(Complex(1, 1));
    Node<Complex> n1(Complex(2, 2));
    Node<Complex> n2(Complex(3, 3));
    Node<Complex> n3(Complex(4, 4));
    Node<Complex> n4(Complex(5, 5));
    Node<Complex> n5(Complex(6, 6));

    tree.add_root(&root);
    tree.add_sub_node(&root, &n1);
    tree.add_sub_node(&root, &n2);
    tree.add_sub_node(&n1, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);

    CHECK(tree.get_root()->get_value() == Complex(1, 1));
    CHECK(tree.get_root()->get_childrens() == 2);
    CHECK(tree.get_root()->children[0]->get_value() == Complex(2, 2));
    CHECK(tree.get_root()->children[0]->get_childrens() == 2);
    CHECK(tree.get_root()->children[0]->children[0]->get_value() == Complex(4, 4));
    CHECK(tree.get_root()->children[0]->children[1]->get_value() == Complex(5, 5));
    CHECK(tree.get_root()->children[1]->get_value() == Complex(3, 3));
    CHECK(tree.get_root()->children[1]->get_childrens() == 1);
}

TEST_CASE("check pre order iterator"){
    Tree<int> tree;
    Node<int> root(1);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    Node<int> n4(5);
    Node<int> n5(6);

    tree.add_root(&root);
    tree.add_sub_node(&root, &n1);
    tree.add_sub_node(&root, &n2);
    tree.add_sub_node(&n1, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);

    vector<int> pre_order = {1, 2, 4, 5, 3, 6};
    size_t i = 0;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        CHECK(node->get_value() == pre_order[i]);
        i++;
    }
}

TEST_CASE("check post order iterator"){
    Tree<int> tree;
    Node<int> root(1);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    Node<int> n4(5);
    Node<int> n5(6);

    tree.add_root(&root);
    tree.add_sub_node(&root, &n1);
    tree.add_sub_node(&root, &n2);
    tree.add_sub_node(&n1, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);

    vector<int> post_order = {4, 5, 2, 6, 3, 1};
    size_t i = 0;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        if(i >= post_order.size()){
            break;
        }
        CHECK(node->get_value() == post_order[i]);
        i++;
    }
}

TEST_CASE("check in order iterator"){
    Tree<int> tree;
    Node<int> root(1);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    Node<int> n4(5);
    Node<int> n5(6);

    tree.add_root(&root);
    tree.add_sub_node(&root, &n1);
    tree.add_sub_node(&root, &n2);
    tree.add_sub_node(&n1, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);

    vector<int> in_order = {4, 2, 5, 1, 6, 3};
    size_t i = 0;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        CHECK(node->get_value() == in_order[i]);
        i++;
    }
}

TEST_CASE("check bfs iterator"){
    Tree<int> tree;
    Node<int> root(1);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    Node<int> n4(5);
    Node<int> n5(6);

    tree.add_root(&root);
    tree.add_sub_node(&root, &n1);
    tree.add_sub_node(&root, &n2);
    tree.add_sub_node(&n1, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);

    vector<int> bfs = {1, 2, 3, 4, 5, 6};
    size_t i = 0;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        CHECK(node->get_value() == bfs[i]);
        i++;
    }
}

TEST_CASE("check dfs iterator"){
    Tree<int> tree;
    Node<int> root(1);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    Node<int> n4(5);
    Node<int> n5(6);

    tree.add_root(&root);
    tree.add_sub_node(&root, &n1);
    tree.add_sub_node(&root, &n2);
    tree.add_sub_node(&n1, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);

    vector<int> dfs = {1, 2, 4, 5, 3, 6};
    size_t i = 0;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        CHECK(node->get_value() == dfs[i]);
        i++;
    }
}

TEST_CASE("check min heap iterator"){
    Tree<int> tree;
    Node<int> root(1);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    Node<int> n4(5);
    Node<int> n5(6);

    tree.add_root(&root);
    tree.add_sub_node(&root, &n1);
    tree.add_sub_node(&root, &n2);
    tree.add_sub_node(&n1, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);

    vector<int> min_heap = {1, 2, 3, 4, 5, 6};
    size_t i = 0;
    for (auto node = tree.begin(); node != tree.end(); ++node)
    {
        CHECK(node->get_value() == min_heap[i]);
        i++;
    }
}

TEST_CASE("check three ary tree"){
    Tree<int, 3> tree;
    Node<int> root(1);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    Node<int> n4(5);
    Node<int> n5(6);

    tree.add_root(&root);
    tree.add_sub_node(&root, &n1);
    tree.add_sub_node(&root, &n2);
    tree.add_sub_node(&root, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);

    vector<int> bfs = {1, 2, 3, 4, 5, 6};
    size_t i = 0;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        CHECK(node->get_value() == bfs[i]);
        i++;
    }
}

TEST_CASE("check string tree"){
    Tree<string> tree;
    Node<string> root("1");
    Node<string> n1("2");
    Node<string> n2("3");
    Node<string> n3("4");
    Node<string> n4("5");
    Node<string> n5("6");

    tree.add_root(&root);
    tree.add_sub_node(&root, &n1);
    tree.add_sub_node(&root, &n2);
    tree.add_sub_node(&n1, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);
    
    vector<string> bfs = {"1", "2", "3", "4", "5", "6"};
    size_t i = 0;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        CHECK(node->get_value() == bfs[i]);
        i++;
    }
}

