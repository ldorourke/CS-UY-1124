/*
 Warrior.cpp
 Lucas O'Rourke
 lor215
 
 The code for the Warrior class
 */

#include "Noble.h"
#include "Warrior.h"
#include <iostream>
using namespace std;

namespace WarriorCraft {
    
    string Warrior::get_name() const { //returns Warrior's name
        return name;
    }
    
    int Warrior::get_strength() const { //returns Warrior's strength
        return strength;
    }
    
    void Warrior::change_strength(double ratio) { //changes Warrior's strength
        strength -= strength*ratio; //subtracts the strength lost determined by the ratio
        if (strength == 0) {
            is_alive = false; //Warrior is dead if strength = 0
        }
    }
    
    void Warrior::runaway() { //Warriors runs away from his Noble
        if (noble != nullptr) {
            cout << name << " flees in terror, abandoning his lord, " << noble->get_name() << endl;
            noble->remove(name); //tells the Noble to remove him from the army
            noble = nullptr; //changes Noble pointer to nullptr
        }
    }
    
    void Warrior::change_noble(Noble* nob) { //if a Warrior is hired, they must know who their Noble is
        noble = nob;
    }
}