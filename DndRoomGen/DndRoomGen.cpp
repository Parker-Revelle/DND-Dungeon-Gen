#include <iostream>
#include <random>
#include <vector>
#include <time.h>
#include <string>
#include <stdio.h> 
#include <stdlib.h> 
#include <fstream>

using namespace std;






//generates aspects of room
class Room {
public:
    //all aspects of the room necessary
    int roomsize;
    string special;
    string traps;
    int trapNum;
    string terrain;
    string bossRoom;
    string creatures;
    string creatureType;
    string itemRarity;
    int chestNum;

    //generates a room between 20 and 120 feet in diameter
    int roomSize() {
        return ((rand() % 25) + 1) * 5 + 20;
    }
    //Generates if the room is a special condition room
    string roomSpecial() {
        vector<string> specials{ "No Healing Room", "Double Damage Room", "One-Shot Room", "All Spells are cast at lowest level", "All spells are cast at highest possible levels", "Silent Room", "Double Fire Damage Room", "Double Ice Damage Room", "Double Thunder Damage Room",
            "Magical Darkness Room", "No Magic Room", "Double Healing Room", "Dual Cast Room", "Zero Gravity Room", "Super Weight Room", "Wild Magic Room", "Spellslot Recovery Room" };

        int value = rand() % 100;
        if (value > 65) {
            value = rand() % specials.size();
            return specials.at(value);
        }
        return "None";
    }

    //Generates if the room has traps;
    string roomTraps(){
        int value = rand() % 100;
        if (value > 50) {
            return "Yes";
        }
        return "No";
    }

    //Generates if the room has special terrain besides "Dungeon"
    string roomTerrain() {
        vector<string> terrain{ "Swamp", "Mountain", "Snowy Mountain", "Plains", "Cave", "Jungle", "Forest", "Ocean", "Icy Cave", "Desert" };
        int value = rand() % 100;
        if (value > 65) {
            value = rand() % terrain.size();
            return terrain.at(value);
        }
        return "None";
    }

    //Generates if room has creatures or not
    string Boss() {
        int value = rand() % 100;
        if (value > 90) {
            return "Yes";
        }
        return "No";
    }
    //Generates if room has creatures or not
    string roomCreatures() {
        int value = rand() % 100;
        if (value > 10) {
            return "Yes";
        }
        return "No";
    }

    //determines the monster type, up to 3 choices
    string creaturetype() {
        string output = "";
        vector<string> monsterType{ "Abberation", "Beast", "Celestial", "Construct", "Dragon", "Elemental", "Fey", "Fiend", "Demon", "Devil", "Giant", "Humanoid", "Monstrosity", "Ooze", "Plant", "Swarm of Tiny Beasts", "Undead" };
        int value = rand() % 100;
        if (value > 66) {
            value = 3;
        }
        else if (value > 33 && value < 66) {
            value = 2;
        }
        else if (value < 33) {
            value = 1;
        }
        for (int i = 0; i < value; i++) {
            string type = monsterType.at(rand() % monsterType.size());
            type += " ";
            output += type;
        }
        return output;
    }

    //determines if chest is in the room
    int chestRoom(){
        int value = rand() % 100;
        if (value >= 75){
            int value = rand() % 3 + 1;
            return value;
        }
        return 0;

    }

    //Determines rarity of chests in room
    string chestRarity() {
        int value = rand() % 100 + 1;
        if (value >= 98) {
            return "Legendary";
        }
        else if (value >= 90) {
            return "Very Rare";
        }
        else if (value >= 75) {
            return "Rare";
        }
        else if (value >= 50) {
            return "Uncommon";
        }
        else {
            return "Common";
        }
    }


    //Generates the room
    void makeRoom() {
        roomsize = roomSize();
        special = roomSpecial();
        traps = roomTraps();
        if (traps == "Yes") {
            trapNum = rand() % 3 + 1;
        }
        terrain = roomTerrain();
        bossRoom = Boss(); 
        if (bossRoom == "Yes") {
            creatures = "Yes";
            creatureType = creaturetype();
        }
        else {
            creatures = roomCreatures();
            if (creatures == "Yes") {
                creatureType = creaturetype();

            }
        }
        chestNum = chestRoom();
        if (chestNum > 0) {
            itemRarity = chestRarity();
        }
    }

    Room() {
        roomsize = 0;
        special = "N/A";
        traps = "N/A";
        trapNum = 0;
        terrain = "N/A";
        bossRoom = "N/A";
        creatures = "N/A";
        creatureType = "N/A";
        itemRarity = "N/A";
        chestNum = 0;
    }
};



int main(){
    srand(time(NULL));
    char input = 'y';
    char writeout;
    int counter = 1;
    //makes it possible to open file if needed
    ofstream runFile;
    while (tolower(input) == 'y') {
        if (counter == 1) {
            //asks if they want to make a txt file
            cout << "Would you like to document this run? Y/N >>";
            cin >> writeout;
            if (tolower(writeout) == 'y') {
                string title;
                cout << endl;
                cout << "What would you like the run to be called? >> ";
                cin >> title;
                title += ".txt";
                runFile.open(title);
                


            }
            
        }
        //makes the room every iteration
        Room x;
        x.makeRoom();
        cout << "Room " << counter << ":" << endl;
        cout << "Roomsize: " << x.roomsize << " ft" << endl;
        cout << "Special Condition: " << x.special << endl;
        cout << "Traps in the room: " << x.traps << endl;
        //if there are traps, it outputs the number of them
        if (x.traps == "Yes") {
            cout << "Number of Traps: " << x.trapNum << endl;
        }
        cout << "Terrain: " << x.terrain << endl;
        //If the room is a boss room, it doesn't print out the creatures, just the type(s).
        if (x.bossRoom == "Yes") {
            cout << "Boss Room" << endl;
            cout << "Boss Type(s): " << x.creatureType << endl;
        }
        else {
            cout << "Creatures: " << x.creatures << endl;
            cout << "Creature Type(s): " << x.creatureType << endl;
        }
        if (x.chestNum > 0) {
            cout << "Chests: " << x.chestNum << endl;
            cout << "Item Rarity: " << x.itemRarity << endl;
        }
        cout << endl;
        cout << endl;
        //If the user chose to document the run, it writes out to the file as well
        if (runFile.is_open()) {
            string notes;
            runFile << "Room " << counter << ":" << endl;
            runFile << "Roomsize: " << x.roomsize << " ft" << endl;
            runFile << "Special Condition: " << x.special << endl;
            runFile << "Traps in the room: " << x.traps << endl;
            if (x.traps == "Yes") {
                runFile << "Number of Traps: " << x.trapNum << endl;
            }
            runFile << "Terrain: " << x.terrain << endl;
            if (x.bossRoom == "Yes") {
                runFile << "Boss Room" << endl;
                runFile << "Boss Type(s): " << x.creatureType << endl;
            }
            else {
                runFile << "Creatures: " << x.creatures << endl;
                runFile << "Creature Type(s): " << x.creatureType << endl;
            }
            if (x.chestNum > 0) {
                runFile << "Chests: " << x.chestNum << endl;
                runFile << "Item Rarity: " << x.itemRarity << endl;
            }
            cout << "Notes to add for file >> " << endl;
            cin.ignore();
            getline(cin, notes);
            cout << endl;
            runFile << "Notes: " << notes;
            runFile << endl;
            runFile << endl;
        }
        
        //Asking to go again through the cycle
        cout << "Would you like to move to the next room? Y/N >>";
        cin >> input;
        counter += 1;
    }
    
   

    return 0;
}


