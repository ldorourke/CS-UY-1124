/*
 Warrior.h
 Lucas O'Rourke
 lor215
 
 The header for the Warrior class
 */

#ifndef WARRIOR_H
#define WARRIOR_H
#include <string>

namespace WarriorCraft {
    
    class Noble; //forward declaration
    
    class Warrior {
    public:
        Warrior(const std::string& name, int strength) : name(name), strength(strength), is_alive(true), noble(nullptr) {} //constructor
        
        //prototype methods
        std::string get_name() const;
        int get_strength() const;
        void change_strength(double ratio);
        void runaway();
        void change_noble(Noble* nob);
    private:
        std::string name;
        int strength;
        bool is_alive;
        Noble* noble;
    };
    
}

#endif
