c#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Lord;

class Protector { //Protector class fights for Nobles
public:
    Protector(const string& name, int strength) : name(name), strength(strength), lord(nullptr), is_alive(true) {}
    
    Lord* check_lord() const { //checks to see if the Protector already works for a Lord
        return lord;
    }
    
    bool check_life() const { //checks to see if the Protector is alive
        return is_alive;
    }
    
    virtual void battle() const = 0; //virtual function to call the battle functions of wizards, archers, and swordsman
    
    string get_name() const { //returns the name of the Protector
        return name;
    }
    
    int get_strength() const { //returns strength of the Protector
        return strength;
    }
    
    void change_strength(double amt) { //changes the strength of the Protector
        strength = strength - (strength*amt);
    }
    
    void change_lord(Lord* lor) { //changes the Lord pointer from nullptr to the address of the Lord hiring the Protector
        lord = lor;
    }
    
private:
    string name;
    int strength;
    Lord* lord;
    bool is_alive;
};


class Wizard : public Protector { //Wizard public of the Protector
public:
    Wizard(const string& name, int strength) : Protector(name, strength) {} //calls the Protector Constructor
    
    void battle() const { //battle function for the Wizard class
        cout << "POOF!" << endl;
    }
    
private:
};



class Noble { //Noble class is base for Lord and PersonWithStrength
public:
    Noble(const string& name) : name(name), is_alive(true) {}
    
    string get_name() const { //returns name of Noble
        return name;
    }
    
    
    void battle(Noble& noble2) { //sends two Nobles to battle
        cout << name << " battles " << noble2.get_name() << endl;
        
        int strength = get_strength();
        int strength_2 = noble2.get_strength();
        
        if (is_alive == false && noble2.get_is_alive() == false) {
            cout << "Oh, NO! They're both dead! YUCK!" << endl;
        }
        
        else if (is_alive == false) {
            cout << "He's dead, " << noble2.get_name() << endl;
        }
        
        else if (noble2.get_is_alive() == false) {
            cout << "He's dead, " << name << endl;
        }
        
        else if (strength > strength_2) {
            
            if (check_class() == "Lord") {
                ind_battle();
            }
            
            if(noble2.check_class() == "Lord") {
                noble2.ind_battle();
            }
            
            cout << name << " defeats " << noble2.get_name() << endl;
            
            change_strength(strength_2);
            noble2.change_strength(strength_2);
            
            noble2.change_is_alive(false);
        }
        
        else if (strength_2 > strength) {
            
            if (check_class() == "Lord") {
                ind_battle();
            }
            
            if (noble2.check_class() == "Lord") {
                noble2.ind_battle();
            }
            
            cout << noble2.get_name() << " defeats " << name << endl;
            
            change_strength(strength);
            noble2.change_strength(strength);
            
            is_alive = false;
        }
        
        else if (strength == strength_2) {
            
            cout << "Mutual Annihlation: " << name << " and " << noble2.get_name() << " die at each other's hands" << endl;
            
            change_strength(strength);
            noble2.change_strength(strength);
            
            is_alive = false;
            noble2.change_is_alive(false);
        }

    }
    
    //virtual function calls class of either type of Noble
    virtual string check_class() const = 0;
    virtual int get_strength() const = 0;
    virtual void change_strength(int amt) = 0;
    
    bool get_is_alive() const { //checks to see if Noble is alive
        return is_alive;
    }
    
    void change_is_alive(bool var) { //changes the boolean variable is_alive
        is_alive = var;
    }
    
    virtual void ind_battle() {} //uses battle function that the Lord class contains
    
    bool check_life() const { //checks to see if the Noble is still alive
        return is_alive;
    }
    
private:
    string name;
    bool is_alive;
    };


class Lord : public Noble { //public class of the Noble
public:
    Lord(const string& name) : Noble(name) {}
    
    void hires(Protector& war) { //hires a Protector to the vector army
        if (war.check_life() == true && Noble::check_life() == true) { //checks to see if the Noble and Protector are both alive
            if (war.check_lord() == nullptr) { //checks if the Protector has a Lord yet
                army.push_back(&war);
            }
        }
        
        war.change_lord(this); //sets the Protector's Lord to the address of the Noble who hired him
    }
    
    int get_strength() const { //returns the strength of the army
        int tot_strength = 0;
        
        if (army.size() == 0) {
            return 0;
        }
        
        for (size_t i = 0; i < army.size(); i++) { //iterates through each warrior and calls get_strength() method
            tot_strength += army[i]->get_strength();
        }
        
        return tot_strength;
    }
    
    
    void ind_battle() { //calls the battle function of each individual Protector
        for (size_t i = 0; i < army.size(); i++) {
            army[i]->battle();
        }
    }
    
    
    void change_strength(int amt) { //changes the strength of the Protectors in the army
        if (army.size() > 0) {
            double ratio = amt / get_strength();
            for(size_t i = 0; i < army.size(); i++) { //changes each Protector's strength based on the ratio
                army[i]->change_strength(ratio);
            }
        }
    }
        
    
    string check_class() const { //returns string Lord to identify the class in the Noble class
        return "Lord";
    }
    
private:
    vector<Protector*> army;
};




class PersonWithStrengthToFight : public Noble { //public class from the Noble
public:
    PersonWithStrengthToFight(const string& name, int strength) : Noble(name), strength(strength)  {}
    
    string check_class() const { //return string Person to identify the type of Noble he is
        return "Person";
    }
    
    int get_strength() const { //returns the Person's strength
        return strength;
    }
    
    void change_strength(int amt) { //subtracts the amount of strength lost
        strength -= amt;
    }
    
private:
    int strength;
};


class Archer : public Protector { //a type of Protector
public:
    Archer(const string& name, int strength) : Protector(name, strength) {} //calls Protector constructor
    
    void battle() const { //Archers say Twang when they battle
        cout << "TWANG! " << Protector::get_name() << " says: Take that in the name of my lord, " << check_lord()->get_name() << endl;
    }
private:
};


class Swordsman : public Protector { //type of Protector
public:
    Swordsman(const string& name, int strength) : Protector(name, strength) {} //calls Protector constructor
    
    void battle() const { //Swordsman say clang when they battle
        cout << "CLANG! " << Protector::get_name() << " says: Take that in the name of my lord, " << check_lord()->get_name() << endl;
    }
private:
};


int main() {
    
    //creates Protectors and Nobles and sends them to battle
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}