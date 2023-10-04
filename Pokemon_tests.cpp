#include "unit_test_framework.hpp"
#include "Pokemon.hpp"

#include <iostream>
#include <sstream>

using namespace std;

// Tests for the PokemonType Enum and operators

TEST(pokemon_type_output) {
  std::ostringstream os;
  os << FIRE;
  ASSERT_EQUAL(os.str(), "Fire");
}

TEST(pokemon_type_input) {
  std::istringstream is("Water");
  PokemonType type;
  is >> type;
  ASSERT_EQUAL(type, WATER);
}




// Tests for the Pokemon class

TEST(default_constructor) {
  Pokemon p;
  ASSERT_EQUAL(p.get_name(), "Pikachu");
  ASSERT_EQUAL(p.get_level(), 1);
  ASSERT_EQUAL(p.get_type(), ELECTRIC);
}

TEST(custom_constructor) {
  Pokemon p("Charmander", 5, FIRE);
  ASSERT_EQUAL(p.get_name(), "Charmander");
  ASSERT_EQUAL(p.get_level(), 5);
  ASSERT_EQUAL(p.get_type(), FIRE);
}

TEST(pokemon_output) {
  Pokemon p("Bulbasaur", 7, GRASS);
  std::ostringstream os;
  os << p;
  ASSERT_EQUAL(os.str(), "Bulbasaur 7 Grass");
}

TEST(pokemon_input) {
  std::istringstream is("Jolteon 25 Electric");
  Pokemon p;
  is >> p;
  ASSERT_EQUAL(p.get_name(), "Jolteon");
  ASSERT_EQUAL(p.get_level(), 25);
  ASSERT_EQUAL(p.get_type(), ELECTRIC);
}

TEST(pokemon_equality_operators) {
  Pokemon p1("Charmander", 1, FIRE);
  Pokemon p2("Charmander", 1, FIRE);
  Pokemon p3("Charmander", 2, FIRE);
  Pokemon p4("Charmander1", 1, FIRE);
  Pokemon p5("Charmander", 1, WATER);

  ASSERT_TRUE(p1 == p2);
  ASSERT_TRUE(p1 != p3);
  ASSERT_TRUE(p1 != p4);
  ASSERT_TRUE(p1 != p5);
}

TEST(is_effective) {

  Pokemon fire("Charmander", 5, FIRE);
  ASSERT_FALSE(fire.is_effective_against(FIRE));
  ASSERT_FALSE(fire.is_effective_against(WATER));
  ASSERT_TRUE(fire.is_effective_against(GRASS));
  ASSERT_FALSE(fire.is_effective_against(ELECTRIC));

  Pokemon water("Squirtle", 5, WATER);
  ASSERT_TRUE(water.is_effective_against(FIRE));
  ASSERT_FALSE(water.is_effective_against(WATER));
  ASSERT_FALSE(water.is_effective_against(ELECTRIC));
  ASSERT_FALSE(water.is_effective_against(GRASS));

  Pokemon grass("Bulbasaur", 5, GRASS);
  ASSERT_FALSE(grass.is_effective_against(FIRE));
  ASSERT_TRUE(grass.is_effective_against(WATER));
  ASSERT_FALSE(grass.is_effective_against(GRASS));
  ASSERT_FALSE(grass.is_effective_against(ELECTRIC));

  Pokemon electric("Pikachu", 5, ELECTRIC);
  ASSERT_FALSE(electric.is_effective_against(FIRE));
  ASSERT_TRUE(electric.is_effective_against(WATER));
  ASSERT_FALSE(electric.is_effective_against(GRASS));
  ASSERT_FALSE(electric.is_effective_against(ELECTRIC));
}

TEST(pokemon_battle) {
  Pokemon charmander_high("Charmander", 25, FIRE);
  Pokemon charmander_medium("Charmander", 20, FIRE);
  Pokemon charmander_low("Charmander", 10, FIRE);
  Pokemon squirtle("Squirtle", 12, WATER);
  Pokemon pikachu("Pikachu", 12, ELECTRIC);

  // Squirtle can't beat high level charmander, but can use
  // type advantage to beat medium and low level
  ASSERT_FALSE(Pokemon_battle(squirtle, charmander_high));
  ASSERT_TRUE(Pokemon_battle(squirtle, charmander_medium));
  ASSERT_TRUE(Pokemon_battle(squirtle, charmander_low));

  // No type relationship, base only on level
  ASSERT_FALSE(Pokemon_battle(pikachu, charmander_high));
  ASSERT_FALSE(Pokemon_battle(pikachu, charmander_medium));
  ASSERT_TRUE(Pokemon_battle(pikachu, charmander_low));

  // Test tie situation
  Pokemon pikachu2 = pikachu;
  Pokemon charmander12("Charmander", 12, FIRE);
  ASSERT_TRUE(Pokemon_battle(pikachu, pikachu2));
  ASSERT_TRUE(Pokemon_battle(pikachu2, pikachu));
  ASSERT_TRUE(Pokemon_battle(pikachu, charmander12));
  ASSERT_TRUE(Pokemon_battle(charmander12, pikachu));

  // Test exact boundaries
  Pokemon p1("A", 10, WATER);
  Pokemon p2("A", 20, FIRE);
  Pokemon p3("A", 21, FIRE);
  ASSERT_TRUE(Pokemon_battle(p1, p2));
  ASSERT_FALSE(Pokemon_battle(p1, p3));
}

TEST_MAIN() // No semicolon!
