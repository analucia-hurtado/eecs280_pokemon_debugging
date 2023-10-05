
#include <algorithm>
#include <random>
#include <string>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <cassert>

#include "Trainer.hpp"

Trainer::Trainer(const std::string &name)
  : name(name),
    pokemon({
      {"Pikachu", 1, ELECTRIC},
      {"Charmander", 1, FIRE},
      {"Squirtle", 1, WATER},
      {"Bulbasaur", 1, GRASS},
      {"Cyndaquil", 1, FIRE},
    }),
    active_roster (pokemon) {
  // nothing to do here
}

Trainer::Trainer(std::istream &is) {
  is >> name;

  // Assumption: Read exactly ROSTER_SIZE pokemon
  for(int i = 0; i < ROSTER_SIZE; ++i) {
    Pokemon p;
    is >> p;
    pokemon.push_back(p);
  }

  // copy the pokemon vector to the initial active roster
  active_roster = pokemon;
}

// EFFECTS: Returns the name of the trainer
const std::string & Trainer::get_name() const {
  return name;
}

// REQUIRES: The trainer's active roster is not empty
// EFFECTS: Arbitrarily chooses a pokemon for battle by selecting the first
//          pokemon in the trainer's active roster. That pokemon is removed
//          from the roster and returned.
Pokemon Trainer::choose_pokemon() {
  assert(!active_roster.empty());
  Pokemon chosen = active_roster[0];
  active_roster.erase(active_roster.begin());
  return chosen;
}

// REQUIRES: The trainer's active roster is not empty
// EFFECTS: Chooses a pokemon to face a specific adversary type. Specifically,
//          the first pokemon in the active roster that is "effective" against
//          the given adversary is chosen and returned. If there are no such
//          pokemon, the first pokemon in the roster is returned. The chosen
//          pokemon is removed from the roster.
Pokemon Trainer::choose_pokemon(PokemonType adversary_type) {
  assert(!active_roster.empty());
  Pokemon chosen;
  for(int i = 0; i < active_roster.size(); ++i) {
    if (active_roster[i].is_effective_against(adversary_type)) {
      chosen = active_roster[i];
      active_roster.erase(active_roster.begin() + i);
      break;
    }
  }
  return chosen;
}

// EFFECTS: Resets the trainers active roster so that it contains all
//          of their pokemon.
void Trainer::reset() {
  active_roster = pokemon;
}

// EFFECTS: Creates a trainer with the given name and the
//          default set of pokemon.
Trainer * Trainer_factory(const std::string &name) {
  return new Trainer(name);
}

// REQUIRES: The stream input contains valid trainer information
// EFFECTS: Creates a dynamically allocated Trainer and returns
//          a pointer to it. Don't forget to use delete to free the
//          Trainer when you're finished with it!
Trainer * Trainer_factory(std::istream &is) {
  return new Trainer(is);
}

// EFFECTS: Prints the name of the trainer to the given stream
std::ostream & operator<<(std::ostream &os, const Trainer &trainer) {
  os << trainer.get_name();
  return os;
}