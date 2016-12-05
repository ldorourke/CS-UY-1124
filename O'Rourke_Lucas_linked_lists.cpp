#include <cstdlib> // To allow NULL if no other includes
#include <iostream>
using namespace std;

struct Node {
    Node(int data = 0, Node* link = nullptr) : data(data), link(link) {}
    int data;
    Node* link;
};

void listInsertHead(int entry, Node*& headPtr) {
    headPtr = new Node(entry, headPtr);
}

Node* findPos(int data, Node* headptr) {
    Node* temp = headptr;
    while (temp) {
        if (temp->data == data) {
            return temp;
        }
        else {
            temp = temp->link;
        }
    }
    return nullptr;
}

void spliceList(Node* initialPtr, Node* splicePtr) {
    //if (splicePtr != nullptr) {
       // if (initialPtr == nullptr) {
         //   initialPtr->link = splicePtr;
        //}
        //else {
            Node* next = initialPtr->link;
            initialPtr->link = splicePtr;
            Node* p = splicePtr;
            while(p->link != nullptr) {
                p = p->link;
            }
            p->link = next;
        //}
   // }
}



Node* isSubList(Node* listPtr, Node* subPtr) {
    Node* foundPtr = nullptr;
    Node* origPtr = subPtr;
    
    while(listPtr != nullptr ) {
        if (listPtr->data == subPtr->data ) {
            if (subPtr->link == nullptr) {
                if (foundPtr == nullptr) {
                    foundPtr = listPtr;
                }
                return foundPtr;
            }
            else if (foundPtr == nullptr) {
                foundPtr = listPtr;
                listPtr = listPtr->link;
                subPtr = subPtr->link;
            }
            else {
                if (subPtr->link == nullptr) {
                    return foundPtr;
                }
                else {
                    subPtr = subPtr->link;
                    listPtr = listPtr->link;
                }
                
            }
        }
        else if (foundPtr != nullptr && listPtr->data != subPtr->data) {
            listPtr = foundPtr->link;
            subPtr = origPtr;
            foundPtr = nullptr;
        }
        else {
            listPtr = listPtr->link;
        }
    }
    cout << "Failed to match";
    return nullptr;
}

void display(Node* headPtr) {
    while (headPtr) {
        cout << headPtr->data << " ";
        headPtr = headPtr->link;
    }
}


int rec(int n) {
    if (n<10) { return n; }
    else {return (n%10) + rec(n/10);}
}

int main() {
    cout << rec(369) << endl;
    cout << "Part One: \n" << endl;
    Node* listOne = nullptr;
    Node* listTwo = nullptr;
    listInsertHead(1, listOne);
    listInsertHead(9, listOne);
    listInsertHead(7, listOne);
    listInsertHead(5, listOne);
    
    listInsertHead(2, listTwo);
    listInsertHead(3, listTwo);
    listInsertHead(6, listTwo);
    
    cout << "L1: ";
    display(listOne);
    cout << endl;
    
    cout << "L2: ";
    display(listTwo);
    cout << endl;
    
    cout << "Target: ";
    display(findPos(7, listOne));
    cout << endl;
    
    cout << "Splicing L2 at target in L1" << endl;
    spliceList(findPos(7, listOne), listTwo);
    
    cout << "L1: ";
    display(listOne);
    cout << endl;
    
    cout << "L2: ";
    display(listTwo);
    cout << endl;
    cout << "=====================\n\n";
    
    cout << "Part Two: \n\n";
    
    Node* listThree = nullptr;
    listInsertHead(6, listThree);
    listInsertHead(5, listThree);
    listInsertHead(4, listThree);
    listInsertHead(2, listThree);
    listInsertHead(3, listThree);
    listInsertHead(2, listThree);
    listInsertHead(3, listThree);
    listInsertHead(2, listThree);
    listInsertHead(1, listThree);
    cout << "Target: ";
    display(listThree);
    cout << endl;
    
    
    Node* listFour = nullptr;
    listInsertHead(1, listFour);
    cout << "\nAttempt to match: ";
    display(listFour);
    cout << endl;
    Node* printList = isSubList(listThree, listFour);
    display(printList);
    cout << endl;
    
    
    Node* listFive = nullptr;
    listInsertHead(9, listFive);
    listInsertHead(3, listFive);
    cout << "\nAttempt to match: ";
    display(listFive);
    cout << endl;
    printList = isSubList(listThree, listFive);
    display(printList);
    cout << endl;
    
    
    Node* listSix = nullptr;
    listInsertHead(3, listSix);
    listInsertHead(2, listSix);
    cout << "\nAttempt to match: ";
    display(listSix);
    cout << endl;
    printList = isSubList(listThree, listSix);
    display(printList);
    cout << endl;
    
    
    Node* listSeven = nullptr;
    listInsertHead(6, listSeven);
    listInsertHead(5, listSeven);
    listInsertHead(4, listSeven);
    listInsertHead(2, listSeven);
    cout << "\nAttempt to match: ";
    display(listSeven);
    cout << endl;
    printList = isSubList(listThree, listSeven);
    display(printList);
    cout << endl;
    
    
    Node* listEight = nullptr;
    listInsertHead( 4, listEight );
    listInsertHead( 2, listEight );
    listInsertHead( 3, listEight );
    listInsertHead( 2, listEight );
    cout << "\nAttempt to match: ";
    display(listEight);
    cout << endl;
    printList = isSubList(listThree, listEight);
    display(printList);
    cout << endl;
    
    
    Node* listNine = nullptr;
    listInsertHead( 7, listNine );
    listInsertHead( 6, listNine );
    listInsertHead( 5, listNine );
    cout << "\nAttempt to match: ";
    display(listNine);
    cout << endl;
    printList = isSubList(listThree, listNine);
    display(printList);
    cout << endl;
    cout << endl;
}

