/*
 hw02.cpp
 Lucas O'Rourke
 lor215
 
 This program is a mideval game with warriors who battle. It reads a file and creates warriors with their given strength
 and then the warriors battle based on what the file says to do. The warrior with a higher strength will kill the other
 warrior and it will lose the amount of strength that the other warrior had. If they have the same amount of strength,
 they both will die.
 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;



struct Warrior { // creates a Warrior that has a name and a strength
    string name;
    int strength;
};



void display_status(vector<Warrior>& warriors_collection);



void battle(const string& first_warrior, const string& second_warrior, vector<Warrior>& warriors_collection);



int main() {
    
    ifstream warriors_text("/Users/lucasorourke/Desktop/CS (C++)/Text Files/warriors.txt");
    
    if (!warriors_text) {
        cerr << "No file found" << endl;
        exit(1);
    }
    
    string command;
    
    vector<Warrior> warrior_collection;
    
    string name;
    string warrior_name;
    
    while (warriors_text >> command) { // reads the first word of each line
        if (command == "Warrior") { // creates warriors
            Warrior warrior;
            warriors_text >> warrior.name; // reads next word after command sets it as the Warrior's name
            warriors_text >> warrior.strength; // reads the integer on the line and sets it as the Warrior's strength
            warrior_collection.push_back(warrior);
        }
        
        else if (command == "Status") { // goes to display status function to show each warrior and remaining strengths
            display_status(warrior_collection);
        }
        
        else { // if the command is battle it will send two warriors to battle using the battle function
            string warrior1;
            string warrior2;
            
            warriors_text >> warrior1; // reads the next word after the command and makes it the first warrior
            warriors_text >> warrior2; // reads word after that and makes it the second warrior
            
            battle(warrior1, warrior2, warrior_collection);
        }
        
    }
    
    warriors_text.close();
    
}



void display_status(vector<Warrior>& warriors_collection) { // displays the warriors and their remaining strength
    cout << "There are " << warriors_collection.size() << " warriors" << endl;
    for (size_t i = 0; i < warriors_collection.size(); i++) { // displays each Warrior from the collection of warriors
        cout << "Warrior: " << warriors_collection[i].name << ", strength: " << warriors_collection[i].strength << endl;
    }
}



void battle(const string& first_warrior, const string& second_warrior, vector<Warrior>& warriors_collection) { // battles two
    // warriors and adjusts their strength after the battle
    
    size_t warrior1_ind = 1000;
    size_t warrior2_ind = 1000;
    
    for (size_t i = 0; i < warriors_collection.size(); i++) { // checks to see if the warriors are in the vector and then saves
        // their position to new variables if they are.
        if (first_warrior == warriors_collection[i].name) {
            warrior1_ind = i;
        }
        if (second_warrior == warriors_collection[i].name) {
            warrior2_ind = i;
        }
    }
    
    if (warrior1_ind == 1000 || warrior2_ind == 1000) { // checks to see if the warriors were found in the vector
        cout << "The warriors were not found" << endl;
        return;
    }
    
    
    cout << warriors_collection[warrior1_ind].name << " battles " << warriors_collection[warrior2_ind].name << endl;
    
    if (warriors_collection[warrior1_ind].strength == 0 && warriors_collection[warrior2_ind].strength == 0) {
        // checks to see if both warriors have 0 strength
        
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    
    else if (warriors_collection[warrior1_ind].strength == 0) { // checks to see if warrior 1 has 0 strength
        cout << "He's dead, " << warriors_collection[warrior2_ind].name << endl;
    }
    
    else if (warriors_collection[warrior2_ind].strength == 0) { // checks to see if warrior 2 has 0 strength
        cout << "He's dead, " << warriors_collection[warrior1_ind].name << endl;
    }
    
    else if (warriors_collection[warrior1_ind].strength > warriors_collection[warrior2_ind].strength) {
        // if warrior 1 has more strength than warrior 2, warrior 2 dies, and warrior 1 loses the amount of strength that
        // warrior 2 had before death
        
        cout << warriors_collection[warrior1_ind].name << " defeats " << warriors_collection[warrior2_ind].name << endl;
        warriors_collection[warrior1_ind].strength -= warriors_collection[warrior2_ind].strength;
        warriors_collection[warrior2_ind].strength = 0;
    }
    else if (warriors_collection[warrior2_ind].strength > warriors_collection[warrior1_ind].strength) { // same as above
        // if statement, but warrior 2 has higher strength in this case
        
        cout << warriors_collection[warrior2_ind].name << " defeats " << warriors_collection[warrior1_ind].name << endl;
        warriors_collection[warrior2_ind].strength -= warriors_collection[warrior1_ind].strength;
        warriors_collection[warrior1_ind].strength = 0;
    }
    
    else if (warriors_collection[warrior1_ind].strength == warriors_collection[warrior2_ind].strength) { // if both
        // warriors have the same amount of strength, then they kill each other
        
        cout << "Mutual Annihilation: " << warriors_collection[warrior1_ind].name << " and " << warriors_collection[warrior2_ind].name << " die at each other's hands" << endl;
        warriors_collection[warrior1_ind].strength = 0;
        warriors_collection[warrior2_ind].strength = 0;
    }
    
    
}

