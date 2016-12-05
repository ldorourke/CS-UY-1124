/*
 Lucas O'Rourke
 lor215
 hw04.cpp
 
 This program has two classes: Nobles and Warriors. The Nobles hire Warriors to their army, or add them to their vector or Warriors. The Nobles fights each other using the army that they hired and the army with a larger combined strength wins.
 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;



class Warrior {
    
public:
    Warrior(const string& the_name, int the_strength) : name(the_name), strength(the_strength) {} //constructor initializes the name and strength of each warrior
    
    string get_name() const { //getter function accesses private variable and returns name
        return name;
    }
    
    int get_strength() const { //getter function returns strength
        return strength;
    }
    
    void change_strength(int amt_lost) { //changes the strength based on the calculated proportion
        strength -= strength*amt_lost;
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
    Noble(const string& the_name) : name(the_name) {} //constructor initializes the name of each noble
    
    void hire(Warrior& the_warrior) { //pushes back the address of the Warrior to the vector of Warrior pointers
        warrior_collection.push_back(&the_warrior);
    }
    
    void display() { //loops through every Warrior in the vector and calls its get_name and get_strength methods
        cout << name << " has an army of " << warrior_collection.size() << endl;
        for (size_t i = 0; i < warrior_collection.size(); i++) {
            cout << "\t" << warrior_collection[i]->get_name() << ": " << warrior_collection[i]->get_strength() << endl;
        }
    }
    
    void fire(const Warrior& the_warrior) { //this method removes a certain Warrior from the vector
        cout << the_warrior.get_name() << ", you're fired! -- " << name << endl;
        size_t end_ind = warrior_collection.size() - 1; // finds the end index

        for (size_t i = 0; i < warrior_collection.size(); i++) {
            if (the_warrior.get_name() == warrior_collection[i]->get_name()) { //finds the Warrior in the collection
                warrior_collection[i] = warrior_collection[end_ind]; //swaps the last value to the value that is going to be removed
                
                warrior_collection.pop_back(); //pops off the last thing in the vector
            }
        }
    }
    
    void battle(Noble& noble2) {
        int army_strength_nob1 = 0;
        int army_strength_nob2 = 0;
        
        for (size_t i = 0; i < warrior_collection.size(); i++) {
            int ind_strength = warrior_collection[i]->get_strength();
            army_strength_nob1 += ind_strength; // finds the strength of the first Noble's army
        }
        
        for (size_t ind = 0; ind < noble2.warrior_collection.size(); ind ++) {
            int ind_strength = noble2.warrior_collection[ind]->get_strength();
            army_strength_nob2 += ind_strength; // finds the strength of the second Noble's army
        }
        
        // the battles begin!!!
        cout << name << " battles " << noble2.name << endl;
        
        if (army_strength_nob1 == 0 && army_strength_nob2 == 0) { //checks to see if both armies have no strength
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        
        else if (army_strength_nob1 == 0) { //checks to see if the first Noble's army has no strength
            cout << "He's dead " << noble2.name << endl;
        }
        
        else if (army_strength_nob2 == 0) { //checks to see if the second Noble's army has no strength
            cout << "He's dead " << name << endl;
        }
        
        else if (army_strength_nob1 > army_strength_nob2) { //if the first Noble's army has more strength than the second
            cout << name << " defeats " << noble2.name << endl;
            int strength_loss = army_strength_nob2/army_strength_nob1; //finds the portion of strength that will be taken from the winning army
            
            for (size_t i = 0; i < warrior_collection.size(); i++) { //changes the strength of each winning Warrior
                warrior_collection[i]->change_strength(strength_loss);
            }
            for (size_t ind = 0; ind < noble2.warrior_collection.size(); ind++) { //changes each losing Warrior's strength to 0
                noble2.warrior_collection[ind]->change_strength_defeat();
            }
        }
        
        else if (army_strength_nob2 > army_strength_nob1) { //if the second Noble's army has more strength than the first
            cout << noble2.name << " defeats " << name << endl;
            int strength_loss = army_strength_nob1/army_strength_nob2; //finds the portion of strength that will be taken from winning army
            
            for (size_t i = 0; i < noble2.warrior_collection.size(); i++) { //changes the strength of each winning Warrior
                noble2.warrior_collection[i]->change_strength(strength_loss);
            }
            for (size_t ind = 0; ind < warrior_collection.size(); ind++) { //changes each losing Warrior's strength to 0
                warrior_collection[ind]->change_strength_defeat();
            }
        }
        
        else if (army_strength_nob1 == army_strength_nob2) { //if each Noble's army has equal strength
            cout << "Mutual Annihalation: " << name << " and " << noble2.name << " die at each other's hands" << endl;
            for (size_t i = 0; i < warrior_collection.size(); i++) {
                warrior_collection[i]->change_strength_defeat(); //changes each Warrior's strength to 0
            }
            
            for (size_t ind = 0; ind < noble2.warrior_collection.size(); ind++) { //changes each Warrior's strength to 0
                noble2.warrior_collection[ind]->change_strength_defeat();
            }
        }
    }
    
private:
    string name;
    vector<Warrior*> warrior_collection;
};



int main() {
    //create nobles
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    
    //create Warriors
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    
    //Nobles hire Warriors to their army
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    
    //displays each Nobles army
    jim.display();
    lance.display();
    art.display();
    linus.display();
    billie.display();
    
    art.fire(cheetah); //fires Tarzan from King Athur's army
    art.display();
    
    //sends two Nobles and their armies to battle
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
    
    jim.display();
    lance.display();
    art.display();
    linus.display();
    billie.display();
}
