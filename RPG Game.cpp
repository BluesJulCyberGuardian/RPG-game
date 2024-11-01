#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <regex>

using namespace std;

// Character class definition
class Character {
public:
  string name;
  int health;
  string weapon;

  Character(string name, int health, string weapon) {
    this->name = name;
    this->health = health;
    this->weapon = weapon;
  }
 // Attack logic
  int attack(Character& other) {
    int damage = rand() % (max_damage - min_damage + 1) + min_damage;
    other.health -= damage;
    return damage;
  }
// Heal logic
  void heal() {
    int heal = rand() % (max_heal - min_heal + 1) + min_heal;
    health += heal;
  }
 // Check if character is alive
  bool is_alive() {
    return health > 0;
  }

private:
  int min_damage = 10;
  int max_damage = 25;
  int min_heal = 1;
  int max_heal = 10;
};

int main() {
  // Read input file
  string game_location;
  vector<Character> characters;
  {
    fstream input_file("rpg-data.txt");
    if (input_file.is_open()) {
      getline(input_file, game_location);
      for (int i = 0; i < 2; i++) {
        string line;
        getline(input_file, line);

        //Split the line into name and weapon
        size_t space_pos = line.find(' ');
        if (space_pos != string::npos) {
          string name = line.substr(0, space_pos);
          string weapon = line.substr(space_pos + 1);

        // Check if the health input is a valid integer
        int health_int;
        if (!(stringstream(line.substr(space_pos + 1)) >> health_int)) { 
          health_int = 100;
        }

        characters.push_back(Character(name, health_int, weapon));
      }
    }
  }
}

// Start game
  cout << "\033[1;31mWelcome to the RPG! \033[2;39m You are in " << game_location << endl;
  cout << "\033[1;35m" << characters[0].name << " " << characters[0].weapon << " has " << characters[0].health << " health\033[0m" << endl;
  cout << "\033[1;34m" << characters[1].name << " " << characters[1].weapon << " has " << characters[1].health << " health\033[0m" << endl;

  int turn = rand() % 2;


while (true) {
  // Display current player's turn
  cout << "\033[1;32m" << characters[turn].name << "'s turn!\033[0m" << endl;

  // Get player input
  cout << "\033[1;33mWhat would you like to do? (1) Attack, (2) Heal, (3) Quit\033[0m" << endl;
  int choice;
  cin >> choice;
  
  // Handle player input
  if (choice == 1) {
    // Attack other player
    int damage = characters[turn].attack(characters[(turn + 1) % 2]);
    cout << characters[turn].name << " attacked " << characters[(turn + 1) % 2].name << " for " << damage << " damage" << endl;
    
    // Check if other player is defeated
    if (!characters[(turn + 1) % 2].is_alive()) {
      cout << characters[(turn + 1) % 2].name << " has been defeated!" << endl;
      break;
    }
  } else if (choice == 2) {
    // Heal self
    characters[turn].heal();
  } else if (choice == 3) {
  // Quit game
  cout << "Quitting game..." << endl;
  return 0;
} else {
  // Invalid input
  cout << "Invalid input. Please choose again." << endl;
}

  // Display player information
  for (int i = 0; i < 2; i++) {
    if (i == turn) {
     cout << "\033[1;34m" << characters[i].name << " has " << characters[i].health << " health.\033[0m\n" << endl;
    } else {
      cout << characters[i].name << " has " << characters[i].health << " health" << " and is using " << characters[i].weapon << endl;
    }
  }

  // Increment turn counter
  turn = (turn + 1) % 2;
}

// Write results to file
ofstream output_file("rpg-results.txt");
if (characters[0].is_alive()) {
  output_file << characters[0].name << " has won!" << endl;
} else {
  output_file << characters[1].name << " has won!" << endl;
}
for (int i = 0; i < 2; i++) {
  output_file << characters[i].name << " has " << characters[i].health << " health" << endl;
}

// Create a victory graphic
string graphic = "\n\n";
graphic += "                ___________\n";
graphic += "               '._==_==_=_.'\n";
graphic += "               .-\\:      /-.\n";
graphic += "              | (|:.     |) |\n";
graphic += "               '-|:.     |-'\n";
graphic += "                 \\::.    /\n";
graphic += "                  '::. .'\n";
graphic += "                    ) (\n";
graphic += "                  _.' '._\n";
graphic += "                 `\"\"\"\"\"\"\"`";

// Set the text color to GOld
cout << "\033[1;38;5;178m";

// Display the victory graphic
for (size_t i = 0; i < graphic.length(); i++) {
  cout << graphic[i];
  // Add a sparkle effect
    if (i % 20 == 0) {
      cout << "\033[35m**";
    }
    // Display the character
    cout << graphic[i];
    // Reset the text color to Gold
    cout << "\033[1;38;5;178m"; 
  }

// Reset the text color to Cyan
cout << "\033[1;36m";

// Display a message
cout << "\nCongratulations on your victory!" << endl;

return 0;
}
