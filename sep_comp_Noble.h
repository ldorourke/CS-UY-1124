/*
 Noble.h
 Lucas O'Rourke
 lor215
 
 The header for the Noble class
 */


#ifndef SEP_COMP_NOBLE_H
#define SEP_COMP_NOBLE_H

#include <string>
#include <vector>
#include <iostream>

namespace WarriorCraft {
    
    class Warrior; //forward declaration
    
    class Noble {
        friend std::ostream& operator<<(std::ostream& os, const Noble& nob); //output operator overload
    public:
        Noble(const std::string& name) : name(name), is_alive(true) {} //constructor
        
        //protype methods
        void hire(Warrior& war);
        void fire(Warrior& war);
        void battle(Noble& nob2);
        std::string get_name() const;
        int get_strength() const;
        bool check_alive() const;
        void change_strength(double amt);
        void change_bool();
        void remove(const std::string& name);
    private:
        std::string name;
        bool is_alive;
        std::vector<Warrior*> army;
    };
}

#endif
