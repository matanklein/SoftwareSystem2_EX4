
#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

using namespace std;

int main()
{

    Node<double> root_node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(&root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(&root_node, &n1);
    tree.add_sub_node(&root_node, &n2);
    tree.add_sub_node(&n1, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);
   
    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */
    int i = 0;

    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << "\t";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;

    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << "\t";
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout << endl;

    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        i++;
        if(i > 5){
            break;
        }
        cout << node->get_value() << "\t";

    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    cout << endl;

    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << "\t";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    for (auto node : tree)
    {
        cout << node << "\t";
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;


    //cout << tree; // Should print the graph using GUI.

    Node<double> root_node1(1.1);
    Node<double> nd1(1.2);
    Node<double> nd2(1.3);
    Node<double> nd3(1.4);
    Node<double> nd4(1.5);
    Node<double> nd5(1.6);

    Tree<double,3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(&root_node1);
    three_ary_tree.add_sub_node(&root_node1, &nd1);
    three_ary_tree.add_sub_node(&root_node1, &nd2);
    three_ary_tree.add_sub_node(&root_node1, &nd3);
    three_ary_tree.add_sub_node(&nd1, &nd4);
    three_ary_tree.add_sub_node(&nd2, &nd5);

     // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */
    return 0;
}
