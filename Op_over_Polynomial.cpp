#include <iostream>
#include "Polynomial.h"
#include <cmath>
using namespace std;



void listInsertHead(int entry, Node*& headPtr) {
    headPtr = new Node(entry, headPtr); //adds new head pointer
}

Polynomial::Polynomial() : node(nullptr), degree(0) {} //default constructor for Polynomial


Polynomial::Polynomial(vector<int> v) { //Polynomial constructor given a vector of ints
    degree = -1;
    for (size_t i = 0; i < v.size(); i++) {
        listInsertHead(v[i], node);
        degree += 1;
    }
}

Polynomial::~Polynomial() { //destructor
    if (node != nullptr) {
    //delete all data if node is not nullptr
        while (node != nullptr) {
            Node* temp = node->link;
            delete node;
            node = temp;
        }
    }
}

Polynomial& Polynomial::operator=(const Polynomial& p) { //assignment operator
    if (this != &p) {
        if (node != nullptr) {
            //delete all data if node is not nullptr
            while (node != nullptr) {
                Node* temp = node->link;
                delete node;
                node = temp;
            }
        }
        
        //allocates new data
        node = new Node(p.node->data);
        Node* temp = p.node->link;
        Node* curr = node;
        while (temp != nullptr) { //copies data over
            curr->link = new Node(temp->data);
            curr = curr->link;
            temp = temp->link;
        }
        degree = p.degree;
    }
    return *this; //returns itself
}


Polynomial::Polynomial(const Polynomial& p) { //copy constructor
    //allocates new data
    node = new Node(p.node->data);
    Node* temp = p.node->link;
    Node* curr = node;
    while (temp != nullptr) { //copies data over
        curr->link = new Node(temp->data);
        curr = curr->link;
        temp = temp->link;
    }
    degree = p.degree;
}


Polynomial& Polynomial::operator+=(const Polynomial& p) { //overloaded += operator
    Node* temp1 = node;
    Node* temp2 = p.node;
    
    if (degree >= p.degree) { // lhs larger or equal
        while (temp2 != nullptr) {
            temp1->data += temp2->data;
            temp1 = temp1->link;
            temp2 = temp2->link;
        }
        return *this;
    }
    else { // rhs larger
        //adds data where they are the same
        for (size_t z = 0; z < degree; z++)  {
            temp1->data += temp2->data;
            temp1 = temp1->link;
            temp2 = temp2->link;
        }
        
        //stores the rest of the data
        temp1->data += temp2->data;
        for (size_t x = 0; x < p.degree - degree; x++) {
            temp1->link = new Node(temp2->link->data);
            temp1 = temp1->link;
            temp2 = temp2->link;
        }
        degree = p.degree;
        
        return *this;
    }
}


Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) { //overloaded addition operator
    Polynomial temp(lhs); //copies over lhs to a new Polynomial
    temp += rhs; //uses += operator
    return temp;
}


bool Polynomial::operator==(const Polynomial& p) { //checks to see if two polynomials are equal
    if (degree == p.degree) {
        Node* temp = node;
        Node* temp2 = p.node;
        while (temp->link != nullptr) { //checks to see if each coefficient is equal
            if (temp->data != temp2->data) {
                return false;
            }
            temp = temp->link;
            temp2 = temp2->link;
        }
        return true;
    }
    //false if degrees are not the same
    return false;
}

bool Polynomial::operator!=(const Polynomial& p) { //checks to see if two polynomials are not equal
    return !(*this == p); //uses == operator
}

int Polynomial::evaluate(int x) { //evaluates a polynomial at given value x
    if (degree == 0) { //if 0 degree polynomial, returns the data
        return node->data;
    }
    else { //adds up the result and returns it
        int result = node->data;
        Node* temp = node->link;
        int temp_deg = 1;
        while (temp_deg <= degree) {
            result += (pow(x, temp_deg))*temp->data; //exponentiates and multiplies by data
            temp = temp->link;
            temp_deg += 1;
        }
        return result;
    }
}

ostream& operator<<(ostream& os, const Polynomial& p) { //overloaded output opertaor
    int temp_degree = p.degree;
    Node* temp = p.node;
    Node* curr = p.node;
    Node* last = nullptr;
    
    if (p.node == nullptr) { //if not initialized with a Node, Polynomial is 0
        os << 0;
        return os;
    }
    
    while (last != p.node->link) {
        while (curr->link != last) { //sets curr to the last
            curr = curr->link;
        }
        if (temp_degree != 1) { //if the degree is greater than one
            if (curr->data != 0) {
                os << curr->data << "x^" << temp_degree << " + ";
            }
        }
        else {
            if (curr->data != 0) {
                os << curr->data << "x" << " + "; //when the degree is 1
            }
        }
        last = curr; //changes last to the link before it
        curr = temp->link;
        temp_degree -= 1;
    }
    
    os << p.node->data; //feeds in the head pointer to the o stream
    return os;
}