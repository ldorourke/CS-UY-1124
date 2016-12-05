/*
 Noble.cpp
 Lucas O'Rourke
 lor215

 The code for the Noble class
 */

#include "Noble.h"
#include "Warrior.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

namespace WarriorCraft {
    
    void Noble::hire(Warrior& war) { //pushes back the address of the Warrior into the army of Warrior pointers
        army.push_back(&war);
        war.change_noble(this); //tells the Warrior that he is now in an army
    }
    
    
    void Noble::fire(Warrior& war) { //fires a Warrior from the army
        cout << "You don't work for me anymore, " << war.get_name() << "! -- " << name << endl;
        for(size_t i = 0; i < army.size(); i++) { //finds the Warrior in the army vector and then removes him
            if (army[i]->get_name() == war.get_name()) {
                army[i] = army[army.size() - 1];
                army.pop_back();
            }
        }
        war.change_noble(nullptr); //changes the Warrior's Noble pointer to nullptr
    }
    
    string Noble::get_name() const { //returns the Noble's name
        return name;
    }
    
    
    int Noble::get_strength() const { //returns the Noble's strength
        int strength = 0;
        if (army.size() > 0) {
            for (size_t i = 0; i < army.size(); i++) { //loops through each Warrior in the army and adds up all their strengths
                strength += army[i]->get_strength();
            }
        }
        return strength;
    }
    
    
    bool Noble::check_alive() const { //checks to see if the Noble is alive or not
        return is_alive;
    }
    
    
    void Noble::change_strength(double ratio) { //changes each Warriors strength
        for (size_t i = 0; i < army.size(); i++) {
            army[i]->change_strength(ratio);
        }
    }
    
    
    void Noble::change_bool() { //changes the Noble's bool to false, killing him
        is_alive = false;
    }
    
    void Noble::remove(const string& name) { //if a Warrior runs away, the Noble removes it from his army
        for (size_t i = 0; i < army.size(); i++) {
            if (army[i]->get_name() == name) {
                army[i] = army[army.size() - 1];
                army.pop_back();
            }
        }
    }
    
    
    void Noble::battle(Noble& nob2) { //sends two Nobles to battle
        cout << name << " battles " << nob2.get_name() << endl;
        
        //finds strength of each Noble
        int strength = get_strength();
        int strength2 = nob2.get_strength();
    
        if (is_alive == false && nob2.check_alive() == false) { //if both Nobles are dead already
            cout << "Oh, NO! They're both dead! YUCK!" << endl;
        }
        
        else if (is_alive == false) { //if first Noble is dead
            cout << "He's dead, " << nob2.get_name() << endl;
        }
        
        else if (nob2.check_alive() == false) { //if second Noble is dead
            cout << "He's dead, " << name << endl;
        }
        
        else if (strength > strength2) { //if the first Noble's strength is greater than the second's
            cout << name << " defeats " << nob2.get_name() << endl;
            double ratio = strength2/strength; //calculates the amount of strength lost for each Warrior
            nob2.change_bool(); //kills the second Noble
            change_strength(ratio);
            nob2.change_strength(1); //takes away 100% of the Warriors' strength
        }
        
        else if (strength2 > strength) { //if second Noble's strength is greater than the first's
            cout << nob2.get_name() << " defeats " << name << endl;
            double ratio = strength/strength2;
            change_bool(); //kills the first Noble
            change_strength(1); //takes away 100% of the Warriors'strength
            nob2.change_strength(ratio);
        }
        
        else if (strength == strength2) { //if both Noble's have the same amount of strength
            cout << "Mutual Annihlation: " << name << " and " << nob2.get_name() << " die at each other's hands" << endl;
           
            //kills both Nobles
            change_bool();
            nob2.change_bool();
            
            //takes away 100% of both Noble's Warriors' strength
            change_strength(1);
            nob2.change_strength(1);
        }
    }
    
    
    ostream& operator<<(ostream& os, const Noble& name) { //overloads the output operator
        
        //sends the Noble's name, army size, and each Warrior's information into the ostream and returns it
        os << name.get_name() << " has an army of " << name.army.size() << endl;
        for (size_t i = 0; i < name.army.size(); i++) {
            os << "\t" << name.army[i]->get_name() << ": " << name.army[i]->get_strength() << endl;
        }
        return os;
    }
    
}
