/*
 Lucas O'Rourke
 This implementation of linked lists requires my implementation of the copy constructor, assignment overloaded operator, and the destructor
 */

#include <iostream>
#include <vector>
using namespace std;



struct Node {
    Node (int data = 0, Node* link = nullptr) : data(data), link(link) {}
    int data;
    Node* link;
};



class Sequence {
public:
    Sequence() : head(nullptr), curr(nullptr) {}
    
    ~Sequence() {
        clear();
    }
    
    Sequence(const Sequence& rhs) {
        head = new Node(rhs.head->data);
        curr = head;
        Node* temp = rhs.head->link;
        Node* temp2 = nullptr;
        
        while (temp != nullptr) {
            curr->link = new Node(temp->data);
            curr = curr->link;
            if (rhs.curr == temp) {
                temp2 = temp;
            }
            temp = temp->link;
        }
        curr = temp2;
    }
    
    Sequence& operator=(const Sequence& rhs) {
        if (this != &rhs) {
            clear();
            Node* temp = rhs.head;
            //Node* temp2 = nullptr;
            head = new Node(temp->data);
            curr = head;
            temp = temp->link;
            while (temp != nullptr) {
                curr->link = new Node(temp->data);
                curr = curr->link;
                temp = temp->link;
            }
            curr = rhs.curr;
        }
        return *this;
    }
    
    void reset() {
        curr = head;
    }
    
    void add(int data) {
        Node* add = new Node(data);
        
        if (curr != nullptr) {
            Node* temp = curr->link;
            curr->link = add;
            add->link = temp;
            curr = curr->link;
        }
        else {
            add->link = head;
            head = add;
            curr = add;
        }
    }
    
    void remove() {
        if (valid()) {
            Node* temp = head;
            Node* temp2 = curr->link;
            while (temp->link != curr) {
                temp = temp->link;
            }
            delete curr;
            temp->link = temp2;
            curr = temp2;
        }
    }
    
    int data() {
        if (valid()) {
            return curr->data;
        }
        return -1;
    }
    
    void next() {
        if (valid()) {
            curr = curr->link;
        }
    }
    
    bool valid() {
        return (curr != nullptr);
    }
    
    void clear() {
        while (head != nullptr) {
            Node* temp = head->link;
            delete head;
            head = temp;
        }
        curr = nullptr;
    }
    
    void display() const {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->link;
        }
        cout << endl;
    }

private:
    Node* head;
    Node* curr;
    
};



int main() {
    Sequence s;
    for (int i = 0; i < 6; ++i) s.add(i);
    s.display();
    cout << "==========\n";
    s.reset();
    for (int i = 0; i < 3; ++i) s.next();
    s.add(42);
    s.display();
    cout << "==========\n";
    s.reset();
    
    //testing copy constructor copy constructor
    cout << "***TESTING COPY CONSTRUCTOR***\n";
    Sequence s1(s);
    s1.display();
    Sequence s2;
    s2 = s;
    s2.display();
    cout << "==========\n";
    
    for (int i = 0; i < 2; ++i) s.next();
    s.remove();
    s.display();
    cout << "==========\n";
    s.clear();
    s.display();
    cout << "==========\n";
}