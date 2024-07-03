/**
 * @author: matank214@gmail.com
 */

#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
using namespace std;

template <typename T>
class Node {
public:
    T value;
    vector<Node<T>*> children;

    Node(T value) : value(value) {}

    T get_value(){
        return value;
    }

    const T get_value() const{
        
        return value;
    }

    void add_child(Node<T>* child) {
        children.push_back(child);
    }

    void clear_children() {
        children.clear();
    }

    size_t get_childrens() {
        return children.size();
    }

    const vector<Node<T>*>& get_children() const{
        return children;
    }



    
};

#endif 