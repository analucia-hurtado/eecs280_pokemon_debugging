#include <iostream>
#include <cassert>

#include "Pokemon.hpp"


// EFFECTS: Prints a PokemonType, for example "Fire", to the stream
std::ostream & operator<<(std::ostream &os, PokemonType type) {
  if (type == FIRE) { os << "Fire"; }
  else if (type == WATER) { os << "Water"; }
  else if (type == GRASS) { os << "Grass"; }
  else if (type == ELECTRIC) { os << "Electric"; }
  else { assert(false); }
  return os;
}

// REQUIRES: If any input is read, it must be a valid PokemonType
// EFFECTS: Reads a PokemonType from a stream, for example "Fire" -> FIRE
std::istream & operator>>(std::istream &is, PokemonType &type) {
  std::string type_in;
  if (is >> type_in) {
    if (type_in == "Fire") { type = FIRE; }
    else if (type_in == "Water") { type = WATER; }
    else if (type_in == "Grass") { type = GRASS; }
    else if (type_in == "Electric") { type = ELECTRIC; }
    else { assert(false); }
  }
  return is;
}




// EFFECTS: Default constructs a level 1 Pikachu
Pokemon::Pokemon()
 : name("Pikachu"), level(1), type(ELECTRIC) { }

// EFFECTS: Creates a Pokemon with the given name and type
Pokemon::Pokemon(const std::string &name, int level, PokemonType type)
 : name(name), level(level), type(type) { }

// EFFECTS: Returns this pokemon's name
const std::string & Pokemon::get_name() const {
  return name;
}

// EFFECTS: Returns this pokemon's type
PokemonType Pokemon::get_type() const {
  return type;
}

// EFFECTS: Returns this pokemon's level
int Pokemon::get_level() const {
  return level;
}

bool Pokemon::is_effective_against(PokemonType other_type) const {
  return (type == FIRE && other_type == GRASS) ||
         (type == WATER && other_type == FIRE) ||
         (type == GRASS && other_type == WATER) ||
         (type == ELECTRIC && other_type == WATER);
}

// Returns true if the given Pokemon have the same
// name and other properties.
bool operator==(const Pokemon &a, const Pokemon &b) {
  return a.get_name() == b.get_name() &&
         a.get_type() == b.get_type() &&
         a.get_level() == b.get_level();
}
bool operator!=(const Pokemon &a, const Pokemon &b) {
  return !(a == b);
}


// EFFECTS: Prints a Pokemon to stream, including its name,
//          level, and type. For example "Squirtle 10 water".
std::ostream & operator<<(std::ostream &os, const Pokemon &pokemon) {
  os << pokemon.get_name() << " " << pokemon.get_level() << " " << pokemon.get_type();
  return os;
}

// EFFECTS Reads a Pokemon from a stream in the format:
//           "Squirtle 10 water"
std::istream & operator>>(std::istream &is, Pokemon &pokemon) {
  is >> pokemon.name >> pokemon.level >> pokemon.type;
  return is;
}

// EFFECTS: Returns true if a defeats b in a battle:
//          - If the difference in pokemon level is > 10,
//            the pokemon with the higher level wins no matter what.
//          - Otherwise, if one pokemon is effective against the other
//            based on types, it wins.
//          - Otherwise, the pokemon with the highest level wins (in
//            case of a tie, pokemon a wins).
bool Pokemon_battle(const Pokemon &a, const Pokemon &b) {
  if (a.get_level() - b.get_level() > 10) {
    return true;
  }
  else if (b.get_level() - a.get_level() > 10) {
    return false;
  }
  else if (a.is_effective_against(b.get_type())) {
    return true;
  }
  else if (b.is_effective_against(a.get_type())) {
    return false;
  }
  else {
    return a.get_level() >= b.get_level();
  }
}