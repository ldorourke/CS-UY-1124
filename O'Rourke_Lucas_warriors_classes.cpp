/*
Lucas O'Rourke
lor215
hw03.cpp
This program reads a file full of warriors and creates a class for the warrior and that warrior's weapons.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


class Weapon {
    
public:
    Weapon(const string& warrior_weapon, int warrior_strength) : weapon_name(warrior_weapon), weapon_strength(warrior_strength) {}
    
    string get_weapon() const { // returns the weapons name
        return weapon_name;
    }
    
    int get_strength() const { // returns the weapons strength
        return weapon_strength;
    }
    
    void change_strength(int amt_dec) { // decrease the weapon's strength by the amount passed to it
        weapon_strength -= amt_dec;
    }
    
private:
    string weapon_name;
    int weapon_strength;
};



class Warrior {
    
public:
    
    Warrior(const string& war_name, const string& war_weapon, int war_strength) : name(war_name), weapon(war_weapon, war_strength) {}
    

    void status(const vector<Warrior>& war_collection) { // display method
        cout << "There are " << war_collection.size() << " warriors" << endl;
        for (size_t ind = 0; ind < war_collection.size(); ind++) {
            cout << "Warrior: " << war_collection[ind].name << ", weapon: " << war_collection[ind].weapon.get_weapon() << ", " << war_collection[ind].weapon.get_strength() << endl; // prints out each warriors' attributes
        }
    }
    
    
    string get_name() { // returns the name of the warrior
        return name;
    }
    
    
    void battle(Warrior& war2) {
        
        cout << name << " battles " << war2.name << endl;
        
        if (weapon.get_strength() == 0 && war2.weapon.get_strength() == 0) {
            // checks to see if both warriors' weapons have 0 strength
            
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        
        else if (weapon.get_strength() == 0) { // checks to see if warrior 1's weapon has 0 strength
            cout << "He's dead, " << war2.name << endl;
        }
        
        else if (war2.weapon.get_strength() == 0) { // checks to see if warrior 2's weapon has 0 strength
            cout << "He's dead, " << name << endl;
        }
        
        else if (weapon.get_strength() > war2.weapon.get_strength()) {
            // if warrior 1's weapon has more strength than warrior 2's, warrior 2 dies, and warrior 1's weapon loses the amount of strength that warrior 2's had before death
            
            cout << name << " defeats " << war2.name << endl;
            
            int war2_strength = war2.weapon.get_strength(); // gets the amount of strength warrior 2's weapon had
            
            // subtracts the amount of strength of warrior 2's weapon from warrior 1's and warrior 2's
            weapon.change_strength(war2_strength);
            war2.weapon.change_strength(war2_strength);
        }
        
        else if (war2.weapon.get_strength() > weapon.get_strength()) { // same as above
            // if statement, but warrior 2's weapon has higher strength in this case
            
            cout << war2.name << " defeats " << name << endl;
            
            int war1_strength = weapon.get_strength(); // gets amount of warrior 1's weapon strength
            
            // takes away warrior 1's weapon strength from both weapons strength
            war2.weapon.change_strength(war1_strength);
            weapon.change_strength(war1_strength);
        }
        
        else if (weapon.get_strength() == war2.weapon.get_strength()) { // if both
            // warriors' weapons have the same amount of strength, then they kill each other
            
            cout << "Mutual Annihilation: " << name << " and " << war2.name << " die at each other's hands" << endl;
            
            int war1_strength = weapon.get_strength();
            weapon.change_strength(war1_strength);
            war2.weapon.change_strength(war1_strength);
            
        }
    }
    
    
private:
    string name;
    Weapon weapon;

    
};



int main() {
    
    ifstream warrior_text("/Users/lucasorourke/Desktop/CS (C++)/Text Files/warriors_new.txt"); // opens file
    if (!warrior_text) { // checks to see if file found
        cerr << "No file found" << endl;
        exit(1);
    }
    
    
    string command;
    string name;
    string weapon;
    int weapon_strength = 0;
    
    vector<Warrior> warrior_collection; // creates a collection of warriors
    
    while (warrior_text >> command) { // first line is a command
        Warrior war(name, weapon, weapon_strength); // creates a Warrior
        if (command == "Warrior") {
            warrior_text >> name;
            warrior_text >> weapon;
            warrior_text >> weapon_strength;
            Warrior war(name, weapon, weapon_strength); // constructs a Warrior
            warrior_collection.push_back(war); // pushes back Warrior into the vector
        }
        
        else if (command == "Status") {
            war.status(warrior_collection); // Calls the status or display method in Warrior
        }
        
        else {
            string warrior1;
            string warrior2;
            
            warrior_text >> warrior1; // finds the two warriors names
            warrior_text >> warrior2;
            
            size_t warrior1_ind = 0;
            size_t warrior2_ind = 0;
            
            
            for (size_t i = 0; i < warrior_collection.size(); i++) { // checks to see if the warriors are in the vector and then saves their index to new variables if they are.
                if (warrior1 == warrior_collection[i].get_name()) {
                    warrior1_ind = i;
                }
                if (warrior2 == warrior_collection[i].get_name()) {
                    warrior2_ind = i;
                }
            }

            warrior_collection[warrior1_ind].battle(warrior_collection[warrior2_ind]); // sends the two warriors to battle

        }
        
    }
}
