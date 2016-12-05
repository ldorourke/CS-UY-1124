#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <string>


struct Node { //Node for a linked list
    Node(int data = 0, Node* link = nullptr) : data(data), link(link) {}
    int data;
    Node* link;
};

void listInsertHead(int entry, Node*& headPtr); //prototype for inserting head to a list

class Polynomial {
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p); //output operator

public:
    //Constructors
    Polynomial();
    Polynomial(std::vector<int>);
    
    //Copy Control
    Polynomial(const Polynomial& p);
    ~Polynomial();
    Polynomial& operator=(const Polynomial& p);
    
    //Operator Overloading
    Polynomial& operator+=(const Polynomial& p);
    bool operator==(const Polynomial& p);
    bool operator!=(const Polynomial& p);
    
    int evaluate(int x);
    
private:
    Node* node;
    int degree;
    
};

Polynomial operator+(const Polynomial& rhs, const Polynomial& lhs); //prototyping plus operator


#endif
