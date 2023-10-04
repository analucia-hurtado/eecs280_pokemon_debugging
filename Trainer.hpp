#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

#include <string>

#include "Pokemon.hpp"

using namespace std;

class Trainer {
private:
  std::string name;
  vector<Pokemon> pokemon; // all pokemon the trainer owns
  vector<Pokemon> active_roster; // current pokemon that are ready for battle
  // INVARIANT: All trainers have exactly 5 pokemon (assumption for simplicity)

public:

  // Creates a trainer with the given name and a default set of starter
  // pokemon, all at level 1, in this order:
  //   Pikachu 1 Electric
  //   Charmander 1 Fire
  //   Squirtle 1 Water
  //   Bulbasaur 1 Grass
  //   Cyndaquil 1 Fire
  Trainer(const std::string &name);

  // Creates a trainer with name and exactly 5 pokemon by reading input
  // from 'is'. Initially, all the pokemon are on the active roster.
  Trainer(std::istream &is);

  // EFFECTS: Returns the name of the trainer
  const std::string & get_name() const;

  // EFFECTS: Arbitrarily chooses a pokemon for battle by selecting the first
  //          pokemon in the trainer's active roster. That pokemon is removed
  //          from the roster and returned.
  Pokemon choose_pokemon();

  // EFFECTS: Chooses a pokemon to face a specific adversary type. Specifically,
  //          the first pokemon in the active roster that is "effective" against
  //          the given adversary is chosen and returned. If there are no such
  //          pokemon, the first pokemon in the roster is returned. The chosen
  //          pokemon is removed from the roster.
  Pokemon choose_pokemon(PokemonType adversary_type);

  // EFFECTS: Resets the trainers active roster so that it contains all
  //          of their pokemon.
  void reset();

};


// EFFECTS: Creates a trainer with the given name and the
//          default set of pokemon.
Trainer * Trainer_factory(const std::string &name);

// REQUIRES: The stream input contains valid trainer information
// EFFECTS: Creates a dynamically allocated Trainer and returns
//          a pointer to it. Don't forget to use delete to free the
//          Trainer when you're finished with it!
Trainer * Trainer_factory(std::istream &is);

// EFFECTS: Prints the name of the trainer to the given stream
std::ostream & operator<<(std::ostream &os, const Trainer &trainer);