/*
 hw07.cpp
 Lucas O'Rourke 
 lor215
 
 The tester code for a mideval Warrior and Noble fighting game
 */


#include "sep_comp_Noble.h"
#include "sep_comp_Warrior.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using namespace WarriorCraft;

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    
    cout << jim;
    cout << lance;
    cout << art ;
    cout << linus;
    cout << billie;
    
    cheetah.runaway();
    cout << art;
    
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
}
