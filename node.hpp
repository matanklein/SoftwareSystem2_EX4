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

    T get_value() const {
        return value;
    }

    void add_child(Node<T>* child) {
        children.push_back(child);
    }

    void remove_child(Node<T>* child) {
        for (int i = 0; i < children.size(); i++) {
            if (children[i] == child) {
                children.erase(children.begin() + i);
                return;
            }
        }
    }

    void clear_children() {
        children.clear();
    }

    size_t get_childrens() {
        return children.size();
    }



    
};

#endif 