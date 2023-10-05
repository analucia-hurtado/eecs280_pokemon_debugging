#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <iostream>

// Represent a Pokemon's type.
enum PokemonType {
  FIRE,
  WATER,
  GRASS,
  ELECTRIC,
};

// EFFECTS: Prints a PokemonType, for example "Fire", to the stream
std::ostream & operator<<(std::ostream &os, PokemonType type);

// REQUIRES: If any input is read, it must be a valid PokemonType
// EFFECTS: Reads a PokemonType from a stream, for example "Fire" -> FIRE
std::istream & operator>>(std::istream &is, PokemonType &type);

class Pokemon {
public:

  // EFFECTS: Default constructs a level 1 Pikachu
  Pokemon();

  // EFFECTS: Creates a Pokemon with the given name, level, and type
  Pokemon(const std::string &name, int level, PokemonType type);

  // EFFECTS: Returns this pokemon's name
  const std::string & get_name() const;

  // EFFECTS: Returns this pokemon's type
  PokemonType get_type() const;

  // EFFECTS: Returns this pokemon's level
  int get_level() const;

  // EFFECTS: Returns true if this pokemon is super effective
  //          against pokemon of the given other type
  bool is_effective_against(PokemonType type) const;

private:
  std::string name;
  int level;
  PokemonType type;

  // This "friend declaration" allows the implementation of operator>>
  // to access private member variables of the Pokemon class.
  friend std::istream & operator>>(std::istream &is, Pokemon &pokemon);
};

// Returns true/false if the given Pokemon have the same
// name and other properties.
bool operator==(const Pokemon &a, const Pokemon &b);
bool operator!=(const Pokemon &a, const Pokemon &b);

//EFFECTS Prints Pokemon to stream, for example "Squirtle 10 Water"
std::ostream & operator<<(std::ostream &os, const Pokemon &pokemon);

// EFFECTS Reads a Pokemon from a stream in the format:
//           "Squirtle 10 water"
std::istream & operator>>(std::istream &is, Pokemon &pokemon);

// EFFECTS: Returns true if a defeats b in a battle:
//          - If the difference in pokemon level is > 10,
//            the pokemon with the higher level wins no matter what.
//          - Otherwise, if one pokemon is effective against the other
//            based on types, it wins.
//          - Otherwise, the pokemon with the highest level wins (in
//            case of a tie, pokemon a wins).
bool Pokemon_battle(const Pokemon &a, const Pokemon &b);

#endif // POKEMON_HPP
