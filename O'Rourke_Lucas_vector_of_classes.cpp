./*
 Lucas O'Rourke
 lor215
 hw05.cpp
 
This program has two classes: Nobles and Warriors. The Nobles hire Warriors to their army, or add them to their vector or Warriors. The Nobles fights each other using the army that they hired and the army with a larger combined strength wins.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>H
using namespace std;


class Warrior {
public:
    Warrior(const string& war_name, int war_strength) : name(war_name), strength(war_strength) {}
    
    string get_name() const { //getter function accesses private variable and returns name
        return name;
    }
    
    int get_strength() const { //getter function returns strength
        return strength;
    }
    
    void change_strength(double first, double second) { //changes the strength based on the calculated proportion
        strength -= strength*(first/second);
    }
    
    void change_strength_defeat() { //sets the warrior strength = to 0 when defeated
        strength = 0;
    }
    
private:
    string name;
    int strength;
};



class Noble {
public:
    Noble(const string& noble_name) : name(noble_name), is_alive(true) {}
    
    string get_name() const { //getter function to return name
        return name;
    }
    
    void hire(Warrior*& war) { //pushes back the warrior pointer into the army of Warriors
        army.push_back(war);
    }
    
    void fire(Warrior*& war) { //removes the warrior pointer from the army of Warriors
        cout << "You don't work for me anymore " << war->get_name() << "! -- " << name << endl;
        for (size_t i = 0; i < army.size(); i++) {
            if (army[i] == war) { //finds the correct warrior to remove from the army collection
                army[i] = army[army.size() - 1];
                army.pop_back();
            }
        }
    }
    
    void display() const { //displays the name and strength of the Noble's army of Warriors
        cout << name << " has an army of " << army.size() << endl;
        for (size_t i = 0; i < army.size(); i++) {
            cout << "\t" << army[i]->get_name() << ": " << army[i]->get_strength() << endl;
        }
    }
    
    void battle(Noble*& noble2) {
        int army_strength_nob1 = 0;
        int army_strength_nob2 = 0;
        
        for (size_t i = 0; i < army.size(); i++) {
            int ind_strength = army[i]->get_strength();
            army_strength_nob1 += ind_strength; // finds the strength of the first Noble's army
        }
        
        for (size_t ind = 0; ind < noble2->army.size(); ind ++) {
            double ind_strength = noble2->army[ind]->get_strength();
            army_strength_nob2 += ind_strength; // finds the strength of the second Noble's army
        }
        
        // the battles begin!!!
        cout << name << " battles " << noble2->name << endl;
        
        if (army_strength_nob1 == 0 && army_strength_nob2 == 0) { //checks to see if both armies have no strength
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        
        else if (army_strength_nob1 == 0) { //checks to see if the first Noble's army has no strength
            cout << "He's dead " << noble2->name << endl;
        }
        
        else if (army_strength_nob2 == 0) { //checks to see if the second Noble's army has no strength
            cout << "He's dead " << name << endl;
        }
        
        else if (army_strength_nob1 > army_strength_nob2) { //if the first Noble's army has more strength than the second
            cout << name << " defeats " << noble2->name << endl;
            
            for (size_t i = 0; i < army.size(); i++) { //changes the strength of each winning Warrior
                army[i]->change_strength(army_strength_nob2, army_strength_nob1);
            }
            for (size_t ind = 0; ind < noble2->army.size(); ind++) { //changes each losing Warrior's strength to 0
                noble2->army[ind]->change_strength_defeat();
                noble2->is_alive = false;
            }
        }
        
        else if (army_strength_nob2 > army_strength_nob1) { //if the second Noble's army has more strength than the first
            cout << noble2->name << " defeats " << name << endl;
        
            for (size_t i = 0; i < noble2->army.size(); i++) { //changes the strength of each winning Warrior
                noble2->army[i]->change_strength(army_strength_nob1, army_strength_nob2);
            }
            for (size_t ind = 0; ind < army.size(); ind++) { //changes each losing Warrior's strength to 0
                army[ind]->change_strength_defeat();
                is_alive = false;
            }
        }
        
        else if (army_strength_nob1 == army_strength_nob2) { //if each Noble's army has equal strength
            cout << "Mutual Annihalation: " << name << " and " << noble2->name << " die at each other's hands" << endl;
            for (size_t i = 0; i < army.size(); i++) {
                army[i]->change_strength_defeat(); //changes each Warrior's strength to 0
                is_alive = false;
            }
            
            for (size_t ind = 0; ind < noble2->army.size(); ind++) { //changes each Warrior's strength to 0
                noble2->army[ind]->change_strength_defeat();
                noble2->is_alive = false;
            }
        }
    }
    
private:
    string name;
    vector<Warrior*> army;
    bool is_alive;
};



int main() {
    
    ifstream warrior_txt("/Users/lucasorourke/Desktop/CS (C++)/Text Files/nobleWarriors.txt");
    
    if(!warrior_txt) { //checks to see if the file is found
        cerr << "No text file found" << endl;
        exit(1);
    }
    
    vector<Noble*> nobles;
    vector<Warrior*> warriors;
    vector<Warrior*> out_of_work;
    string command;
    
    while (warrior_txt >> command) { //first word of each line is the command
        if (command == "Noble") { //creates a Noble
            string name;
            warrior_txt >> name; //finds nobles name
            bool already_created = false;
            for (size_t i = 0; i < nobles.size(); i++) { //checks to see if Noble has already been created using a boolean flag variable
                if (nobles[i]->get_name() == name) {
                    already_created = true;
                }
            }
            if (already_created == true) {
                cout << "Noble " << name << " has already been created" << endl;
            }
            else {
                Noble* new_noble = new Noble(name); //creates a new Noble pointer on the heap
                nobles.push_back(new_noble); //pushes back the pointer into the collection
            }
        }
        
        else if (command == "Warrior") { //creates a Warrior
            string name;
            int strength;
            warrior_txt >> name; //finds Warrior name
            warrior_txt >> strength; //finds Warrior strength
            bool already_created = false;
            for (size_t i = 0; i < warriors.size(); i++) { //checks to see if Warrior has already been created using a boolean flag variable
                if (warriors[i]->get_name() == name) {
                    already_created = true;
                }
            }
            if (already_created == true) {
                cout << "Warrior " << name << " has already been created" << endl;
            }
            else {
                Warrior* new_war = new Warrior(name, strength); //creates a new Warrior pointer on the heap
                warriors.push_back(new_war); //pushes back the pointer into the collection of all Warriors
                out_of_work.push_back(new_war); //also pushes back into the collection of currently out of work Warriors
            }
        }
        
        else if (command == "Hire") { //hires a Warrior to a Noble's army
            string noble_name;
            string warrior_name;
            warrior_txt >> noble_name;
            warrior_txt >> warrior_name;
            Warrior* war_ptr = nullptr; //initializes Warrior pointer
            Noble* nob_ptr = nullptr; //initializes Noble pointer
            
            for (size_t i = 0; i < nobles.size(); i++) { //finds the Noble in the Noble collection
                if (nobles[i]->get_name() == noble_name) {
                    nob_ptr = nobles[i]; //sets that Noble to the pointer created above
                }
            }
            for (size_t ind = 0; ind < warriors.size(); ind++) { //finds the Warrior in the collection
                if (warriors[ind]->get_name() == warrior_name) {
                    war_ptr = warriors[ind]; //sets Warrior to pointer created above
                }
            }
            
        
            //checks to see if Warrior or Noble does not exist
            if (war_ptr == nullptr) {
                cerr << "Sorry, " << warrior_name << " does not exist" << endl;
            }
            else if (nob_ptr == nullptr) {
                cerr << "Sorry, " << noble_name << " does not exist" << endl;
            }
            else if (nob_ptr == nullptr && war_ptr == nullptr) {
                cerr << "Sorry, " << warrior_name << " and " << noble_name << " do not exist" << endl;
            }
            
            else if (war_ptr != nullptr && nob_ptr != nullptr) { //if none are null, the Noble hires the Warrior
                nob_ptr->hire(war_ptr);
                for (size_t i = 0; i < out_of_work.size(); i++) { //removes that Warrior pointer from the out of work Warriors since he has been hired
                    if (out_of_work[i] == war_ptr) {
                        out_of_work[i] = out_of_work[out_of_work.size() - 1];
                        out_of_work.pop_back();
                    }
                }
            }
        }
        
        else if (command == "Fire") { //fires, or removes a Warrior, from the Noble's army
            string noble_name;
            string warrior_name;
            warrior_txt >> noble_name;
            warrior_txt >> warrior_name;
            Warrior* war_ptr = nullptr; //creates null Warrior pointer
            Noble* nob_ptr = nullptr; //creates null Noble pointer
            
            for (size_t i = 0; i < nobles.size(); i++) { //finds the Noble pointer in the collection
                if (nobles[i]->get_name() == noble_name) {
                    nob_ptr = nobles[i]; //if found, sets Noble pointer to one created above
                }
            }
            for (size_t ind = 0; ind < warriors.size(); ind++) { //finds the Warrior pointer in the collection
                if (warriors[ind]->get_name() == warrior_name) {
                    war_ptr = warriors[ind]; //if found, sets Warrior pointer to one created above
                }
            }
            
            //checks to see if Warrior or Noble does not exist
            if (war_ptr == nullptr) {
                cerr << "Sorry, " << warrior_name << " does not exist" << endl;
            }
            else if (nob_ptr == nullptr) {
                cerr << "Sorry, " << noble_name << " does not exist" << endl;
            }
            else if (nob_ptr == nullptr && war_ptr == nullptr) {
                cerr << "Sorry, " << warrior_name << " and " << noble_name << " do not exist" << endl;
            }
            
            else if (war_ptr != nullptr && nob_ptr != nullptr) { //if none are null, Noble fires Warrior
                nob_ptr->fire(war_ptr);
                out_of_work.push_back(war_ptr); //the Warrior is now out of work again
            }
        }
        
        else if (command == "Battle") {
            string noble1;
            string noble2;
            warrior_txt >> noble1;
            warrior_txt >> noble2;
            
            //two Noble pointers created and set to null
            Noble* ptr1 = nullptr;
            Noble* ptr2 = nullptr;
            
            for (size_t i = 0; i < nobles.size(); i++) { //finds the first Noble in the collection
                if (nobles[i]->get_name() == noble1) {
                    ptr1 = nobles[i]; //sets it equal to the created pointer
                }
            }
            for (size_t i = 0; i < nobles.size(); i++) { //finds the second Noble in the collection
                if (nobles[i]->get_name() == noble2) {
                    ptr2 = nobles[i]; //sets it equal to the created pointer
                }
            }
            
            //checks to see if one or both Nobles do not exist
            if (ptr1 == nullptr) {
                cerr << "Sorry, " << noble1 << " does not exist!" << endl;
            }
            else if (ptr2 == nullptr) {
                cerr << "Sorry, " << noble2 << " does not exist!" << endl;
            }
            else if (ptr1 == nullptr && ptr2 == nullptr) {
                cerr << "Sorry, " << noble1 << " and " << noble2 << " do not exist!" << endl;
            }
            
            else if (ptr1 != nullptr && ptr2 != nullptr) { //if they both exist, sends them to battle
                ptr1->battle(ptr2);
            }
        }
        
        else if (command == "Status") { //displays each Noble and their army of Warriors
            cout << "Status\n======" << endl;
            cout << "Nobles:" << endl;
            
            if (nobles.size() == 0) { //checks to see if the Noble collection is empty
                cout << "NONE" << endl;
            }
            
            else {
                for (size_t i = 0; i < nobles.size(); i++) {
                    nobles[i]->display(); //displays each Noble
                }
            }
            cout << "Unemployed Warriors:" << endl;
            if (out_of_work.size() == 0) { //checks to see if out of work Warrior collection is empty
                cout << "NONE" << endl;
            }
            else {
                for (size_t i = 0; i < out_of_work.size(); i++) { //displays each out of work Warrior and its strength
                    cout << out_of_work[i]->get_name() << ": " << out_of_work[i]->get_strength() << endl;
                }
            }
            
        }
        
        else { //if the command is "Clear"
            for (size_t i = 0; i < nobles.size(); i++) {
                delete nobles[i]; //deletes each Noble off the heap
            }
            for(size_t ind = 0; ind < warriors.size(); ind++) {
                delete warriors[ind]; //deletes each Warrior off the heap
            }
            nobles.clear(); //empties Noble collection
            warriors.clear(); //empties Warrior collection
            out_of_work.clear(); //empties out of work Warrior collection
        }
    }
    warrior_txt.close();
    
}
