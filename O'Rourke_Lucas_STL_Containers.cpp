/*
 Lucas O'Rourke
 Tasks using iterators, sets, lists, and maps
 */

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <set>
#include <fstream>
#include <map>
using namespace std;



//eighth task
void print8(const list<int>& l) {
    for(list<int>::const_iterator i = l.begin(); i != l.end(); i++) {
        cout << *i << " ";
    }
    cout << endl;
}


//ninth task
void print9(const list<int>& l) {
    for (int x : l) {
        cout << x << " ";
    }
    cout << endl;
}


//tenth task
void print10(const list<int>& l) {
    for(auto i = l.begin(); i != l.end(); i++,i++) {
        cout << *i << " ";
    }
    cout << endl;
}


//eleventh task
list<int>::const_iterator find11(const list<int>& l, int targ) {
    for (list<int>::const_iterator i = l.begin(); i != l.end(); i++) {
        if (*i == targ) {
            return i;
        }
    }
    return l.end();
}


//twelfth task
auto find12(const list<int>& l, int targ) {
    for (auto i = l.begin(); i != l.end(); i++) {
        if (*i == targ) {
            return i;
        }
    }
    return l.end();
}


//fourteenth task
bool isEven(int n) {
    return n%2 == 0;
}


//seventeeth task
list<int>::iterator ourFind(list<int>::iterator start, list<int>::iterator end, int targ) {
    cout << "using ourFind\n";
    for (list<int>::iterator i = start; i != end; i++) {
        if (*i == targ) {
            return i;
        }
    }
    return end;
}

//eighteenth task
template <typename l, typename i>
l myFind(l start, l end, i targ) {
    cout << "in template\n";
    for (l q = start; q != end; q++) {
        if (*q == targ) {
            return q;
        }
    }
    return end;
}


int main() {
    //first task
    cout << "Task 1:\n";
    vector<int> vi {21, 1, 13, 8, 5, 34, 2, 1};
    for (int x : vi) {
        cout << x << " ";
    }
    cout << "\n==========" << endl;
    
    //second task
    cout << "Task 2:\n";
    list<int> li(vi.begin(), vi.end());
    for (list<int>::iterator p = li.begin(); p != li.end(); p++) {
        cout << *p << " ";
    }
    cout << "\n==========" << endl;
    
    //third task
    cout << "Task 3:\n";
    sort(vi.begin(), vi.end());
    for (int x : vi) {
        cout << x << " ";
    }
    cout << "\n==========" << endl;
    
    //fourth task
    cout << "Task 4:\n";
    for (size_t i = 0; i < vi.size(); i += 2) {
        cout << vi[i] << " ";
    }
    cout << "\n==========" << endl;
    
    //fifth task
    cout << "Task 5:\n";
    for (size_t i = 0; i < li.size(); i += 2) {
        //cout << li[i] << " ";
    }
    //cout << endl;
    cout << "\n==========" << endl;

    
    //sixth task
    cout << "Task 6:\n";
    for (vector<int>::iterator p = vi.begin(); p != vi.end(); p+=2) {
        cout << *p << " ";
    }
    cout << "\n==========" << endl;
    
    //seventh task
    cout << "Task 7:\n";
    for (list<int>::iterator p = li.begin(); p != li.end(); p++,p++) {
        cout << *p << " ";
    }
    cout << "\n==========" << endl;
    
    //eighth task
    cout << "Task 8:\n";
    print8(li);
    cout << "==========" << endl;
    
    
    //ninth task
    cout << "Task 9:\n";
    print9(li);
    cout << "==========" << endl;
    
    
    //tenth task
    cout << "Task 10:\n";
    print10(li);
    cout << "==========" << endl;
    
    
    //eleventh task
    cout << "Task 11:\n";
    auto x = (find11(li, 13));
    if (x != li.end()) {
        cout << "Found " << *x << endl;
    }
    else {
        cout << "Could not find 13" << endl;
    }
    x = (find11(li, 55));
    if (x != li.end()) {
        cout << "Found " << *x << endl;
    }
    else {
        cout << "Could not find 12" << endl;
    }
    cout << "==========" << endl;
    
    
    //twelfth task
    cout << "Task 12:\n";
    x = (find12(li, 13));
    if (x != li.end()) {
        cout << "Found " << *x << endl;
    }
    else {
        cout << "Could not find 13" << endl;
    }
    x = (find11(li, 12));
    if (x != li.end()) {
        cout << "Found " << *x << endl;
    }
    else {
        cout << "Could not find 12" << endl;
    }
    cout << "==========" << endl;
    
    
    //thirteenth task
    cout << "Task 13:\n";
    auto location = find(li.begin(), li.end(), 13);
    if (location != li.end()) {
        cout << "Found " << *location << endl;
    }
    else {
        cout << "Could not find 13" << endl;
    }
    auto location2 = find(li.begin(), li.end(), 12);
    if (location2 != li.end()) {
        cout << *location2 << endl;
    }
    else {
        cout << "could not find 12\n";
    }
    cout << "==========" << endl;

    
    //fourteenth task
    cout << "Task 14:\n";
    cout << "First even: " << *find_if(li.begin(), li.end(), isEven) << endl;
    cout << "==========" << endl;

    
    //fifteenth task
    cout << "Task 15:\n";
    cout << "First even: " << *find_if(li.begin(), li.end(), [](int n) { return n%2 == 0; }) << endl;
    cout << "==========" << endl;
    
    //sixteenth task
    cout << "Task 16:\n";
    int array[8];
    copy(vi.begin(), vi.end(), array);
    for (int x : array) {
        cout << x << " ";
    }
    cout << endl;
    cout << *find(array, array+8, 13) << endl;
    cout << *find(array, array+8, 55) << endl;
    cout << "==========" << endl;
    
    //seventeeth task
    cout << "Task 17:\n";
    cout << *ourFind(li.begin(), li.end(), 13) << endl;
    cout << *ourFind(li.begin(), li.end(), 55) << endl;
    cout << "==========" << endl;
    
    //eighteenth task
    cout << "Task 18:\n";
    cout << *myFind(li.begin(), li.end(), 13) << endl;
    cout << *myFind(li.begin(), li.end(), 55) << endl;
    cout << "==========" << endl;
    
    //nineteenth task
    cout << "Task 19:\n";
    ifstream ifs("STL_Containers_pooh-nopunc.txt");
    vector<string> words;
    string word;
    bool seen_word = false;
    while (ifs >> word) {
        for (size_t i = 0; i < words.size(); i++) {
            if (word == words[i]) {
                seen_word = true;
            }
        }
        if (seen_word == false) {
            words.push_back(word);
        }
        seen_word = false;
    }
    for (string x : words) {
        cout << x << " ";
    }
    ifs.close();
    cout << "\n========" << endl;
    
    
    //twentieth task
    cout << "Task 20:\n";
    set<string> mySet;
    ifstream fs("STL_Containers_pooh-nopunc.txt");
    string word2;
    while (fs >> word2) {
        auto x = find(mySet.begin(), mySet.end(), word2);
        if (x == mySet.end()) {
            mySet.insert(word2);
        }
    }
    for (string x : mySet) {
        cout << x << " ";
    }
    fs.close();
    cout << "\n=======" << endl;
    
    //twenty first task
    cout << "Task 21:\n";
    map<string, vector<int>> wordMap;
    ifstream ifs2("STL_Containers_pooh-nopunc.txt");
    string word3;
    int count = 0;
    while (ifs2 >> word3) {
        wordMap[word3].push_back(count);
        count += 1;
    }
    for (auto x : wordMap) {
        cout << x.first << ": ";
        for (size_t i = 0; i < x.second.size(); i++) {
            cout << x.second[i] << " ";
        }
        cout << endl;
    }
    cout << "\n======\n";
    
}