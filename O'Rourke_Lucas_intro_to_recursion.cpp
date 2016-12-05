/*
 Lucas O'Rourke
 More on linked lists using binary search method. Introduction to recursion
 
 */

#include <iostream>
#include <climits>
using namespace std;


struct Node {
    Node(int n = 0, Node* head = nullptr) : data(n), headPtr(head) {}
    int data;
    Node* headPtr;
};

struct TNode {
    TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
    int data;
    TNode *left, *right;
};

void listInsertHead(int entry, Node*& headPtr) {
    headPtr = new Node(entry, headPtr);
}

void display(Node* head) {
    while (head) {
        cout << head->data << " ";
        head = head->headPtr;
    }
}


//Number 1
void binary(int n) {
    if (n < 2) {
        cout << n;
    }
    else {
        binary(n/2);
        cout << n%2;
    }
}


//Number 2
Node* sum_list(Node* first, Node* second) {
    Node* result = new Node();
    result->data = first->data + second->data;
    
    if (first->headPtr != nullptr) {
        Node* first_next = first->headPtr;
        Node* second_next = second->headPtr;
        result->headPtr = sum_list(first_next, second_next);
        return result;
    }
    else {
        return result;
    }
}


//Number 3
int max(TNode* root) {
    if (root == nullptr) {
        return -1;
    }
    int left = max(root->left);
    int right = max(root->right);
    
    if (root->data > right && root->data > left) {
        return root->data;
    }
    else {
        if (right > left) {
            return right;
        }
        else {
            return left;
        }
    }
}


//Number 4
int sum_chars(string c) {
    int sum = 0;
    for (size_t i = 0; i < c.length(); i++) {
        sum += c[i];
    }
    return sum;
}


//Number 5
int bin_search(char c_string[], char target, int low, int high) {
    if (low > high) { return -1; }
    int mid = low + (high-low)/2;
    if (target == c_string[mid]) {
        return mid;
    }
    else if (target < c_string[mid]) {
        return bin_search(c_string, target, low, mid-1);
    }
    else {
        return bin_search(c_string, target, mid+1, high);
    }
}


//Number 6
void foo(int n) {
    if (n > 1) {
        cout << 'a';
        foo(n/2);
        cout << 'b';
        foo(n/2);
    }
    cout << 'c';
}


int main() {
    // Number 1
    binary(12);
    cout << endl;
    
    //Number 2
    Node* listOne = nullptr;
    listInsertHead(9, listOne);
    listInsertHead(3, listOne);
    Node* listTwo = nullptr;
    listInsertHead(3, listTwo);
    listInsertHead(2, listTwo);
    Node* result = sum_list(listOne, listTwo);
    display(result);
    cout << endl;
    
    //Number 3
    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
    cout << max(&f) << endl;

    //Number 4
    char c_string[15] = "I love C++";
    cout << sum_chars(c_string) << endl;
    
    //Number 5
    char string[6] = "abcde";
    cout << bin_search(string, 'e', 0, 5) << endl;
    
    //Number 6
    foo(4);
    cout << endl;
    
}