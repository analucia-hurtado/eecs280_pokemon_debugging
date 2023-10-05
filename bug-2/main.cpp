#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string>

#include "Pokemon.hpp"
#include "Trainer.hpp"

using namespace std;

class League {
private:
  Trainer *player;
  vector<Trainer*> gym_leaders;
  vector<Trainer*> defeated;

public:
  League(std::istream &player_input, std::istream &gym_leaders_input)
   : player(Trainer_factory(player_input)) {
    
    int num_gym_leaders;
    string ignore;
    gym_leaders_input >> num_gym_leaders;
    gym_leaders_input >> ignore; // read in the word "leaders"

    for(int i = 0; i < num_gym_leaders; ++i) {
      gym_leaders.push_back(Trainer_factory(gym_leaders_input));
    }
  }

  bool one_battle(Trainer *gym_leader) {
    Pokemon enemy = gym_leader->choose_pokemon();
    cout << *gym_leader << " chooses " << enemy << endl;
    Pokemon p = player->choose_pokemon(enemy.get_type());
    cout << *player << " chooses " << p << endl;
    if (Pokemon_battle(p, enemy)) {
      cout << p << " defeats " << enemy << endl << endl;
      return true;
    }
    else {
      cout << enemy << " defeats " << p << endl << endl;
      return false;
    }
  }

  void one_match(Trainer *gym_leader) {

    cout << "-----" << *player << " vs. " << *gym_leader << "-----" << endl;

    int num_wins = 0;
    for(int i = 0; i < Trainer::ROSTER_SIZE; ++i) {
      if (one_battle(gym_leader)) {
        ++num_wins;
      }
    }

    assess_result(gym_leader, num_wins);

    cout << endl;
  }

  void assess_result(Trainer *gym_leader, int num_wins) {
    cout << "Result: " << *player << "=" << num_wins << ", "
         << *gym_leader << "=" << Trainer::ROSTER_SIZE - num_wins << endl;

    if (num_wins >= 3) {
      defeated.push_back(gym_leader);
    }

    if (num_wins == 0 || num_wins == Trainer::ROSTER_SIZE) {
      cout << "It's a clean sweep!" << endl;
    }
  }

  void play_all_matches() {
    for(int i = 0; i < gym_leaders.size(); ++i) {
      player->reset();
      one_match(gym_leaders[i]);
    }

    cout << *player << " won " << defeated.size() << " matches by defeating:" << endl;
    for(int i = 0; i < defeated.size(); ++i) {
      cout << *defeated[i] << endl;
    }
  }

  ~League() {
    // Clean up by deleting all Trainer objects
    delete player;
    for(size_t i = 0; i < gym_leaders.size(); ++i) {
      delete gym_leaders[i];
    }
  }
  
};

int main(int argc, char *argv[]) {

  if (argc != 3) {
    cout << "Usage: battle.exe PLAYER_FILE GYM_LEADERS_FILE" << endl;
    return 1;
  }

  std::string player_in_name = argv[1];
  std::string gym_leaders_in_name = argv[2];

  std::ifstream player_in(player_in_name);
  if ( !player_in.is_open() ) {
    cout << "Unable to open " << player_in_name << endl;
    return 1;
  }
  std::ifstream gym_in(gym_leaders_in_name);
  if ( !gym_in.is_open() ) {
    cout << "Unable to open " << gym_leaders_in_name << endl;
    return 1;
  }
  
  League battle(player_in, gym_in);
  battle.play_all_matches();
}