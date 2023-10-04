#include "unit_test_framework.hpp"
#include "Trainer.hpp"

#include <iostream>
#include <sstream>

using namespace std;

TEST(trainer_name) {

  istringstream input("Ash Pikachu 70 Electric Charizard 75 Fire Blastoise 73 Water Venusaur 72 Grass Jolteon 68 Electric");
  Trainer * trainer = Trainer_factory(input);
  ASSERT_EQUAL(trainer->get_name(), "Ash");
  delete trainer;
}

TEST(trainer_output_operator) {

  istringstream input("Ash Pikachu 70 Electric Charizard 75 Fire Blastoise 73 Water Venusaur 72 Grass Jolteon 68 Electric");
  Trainer * trainer = Trainer_factory(input);
  ostringstream out;
  out << *trainer;
  ASSERT_EQUAL(out.str(), "Ash");
  delete trainer;
}

TEST(trainer_default_ctor) {

  Trainer * trainer = Trainer_factory("Misty");
  ASSERT_EQUAL(trainer->get_name(), "Misty");
  ASSERT_EQUAL(trainer->choose_pokemon(), Pokemon("Pikachu", 1, ELECTRIC));
  ASSERT_EQUAL(trainer->choose_pokemon(), Pokemon("Charmander", 1, FIRE));
  ASSERT_EQUAL(trainer->choose_pokemon(), Pokemon("Squirtle", 1, WATER));
  ASSERT_EQUAL(trainer->choose_pokemon(), Pokemon("Bulbasaur", 1, GRASS));
  ASSERT_EQUAL(trainer->choose_pokemon(), Pokemon("Cyndaquil", 1, FIRE));
  delete trainer;
}

TEST(trainer_choose_pokemon_basic) {

  istringstream input("Ash Pikachu 70 Electric Charizard 75 Fire Blastoise 73 Water Venusaur 72 Grass Jolteon 68 Electric");
  Trainer * trainer = Trainer_factory(input);
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Pikachu");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Charizard");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Blastoise");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Venusaur");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Jolteon");
  delete trainer;
}

TEST(trainer_choose_and_reset) {

  istringstream input("Ash Pikachu 70 Electric Charizard 75 Fire Blastoise 73 Water Venusaur 72 Grass Jolteon 68 Electric");
  Trainer * trainer = Trainer_factory(input);
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Pikachu");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Charizard");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Blastoise");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Venusaur");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Jolteon");
  trainer->reset();
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Pikachu");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Charizard");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Blastoise");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Venusaur");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Jolteon");
  trainer->reset();
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Pikachu");
  trainer->reset();
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Pikachu");
  delete trainer;
}

TEST(trainer_choose_pokemon_1) {

  istringstream input("Ash Pikachu 70 Electric Charizard 75 Fire Blastoise 73 Water Venusaur 72 Grass Jolteon 68 Electric");
  Trainer * trainer = Trainer_factory(input);

  // Blastoise would be chosen first instead, to face off against the 
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Pikachu");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Charizard");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Blastoise");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Venusaur");
  ASSERT_EQUAL(trainer->choose_pokemon().get_name(), "Jolteon");
  delete trainer;
}

TEST(trainer_choose_pokemon_2) {

  istringstream input("Ash Charmander 1 Fire Charmander 1 Fire Charmander 1 Fire Charmander 1 Fire Squirtle 1 Water");
  Trainer * trainer = Trainer_factory(input);

  // The water pokemon should be chosen to face against a fire type
  ASSERT_EQUAL(trainer->choose_pokemon(FIRE).get_name(), "Squirtle");
  delete trainer;
}

TEST(trainer_choose_pokemon_3) {

  istringstream input("Ash Charmander 1 Fire Squirtle 100 Water Charmander 1 Fire Charmander 1 Fire Squirtle 1 Water");
  Trainer * trainer = Trainer_factory(input);

  // The first squirtle with level 100 should be chosen to face a fire pokemon
  ASSERT_EQUAL(trainer->choose_pokemon(FIRE).get_level(), 100);
  delete trainer;
}

TEST(trainer_choose_pokemon_4) {

  istringstream input("Ash Pikachu 1 Electric Charmander 1 Fire Charmander 1 Fire Charmander 1 Fire Charmander 1 Fire");
  Trainer * trainer = Trainer_factory(input);

  // There are no water pokemon, so the first one (Pikachu), should be chosen
  ASSERT_EQUAL(trainer->choose_pokemon(FIRE).get_name(), "Pikachu");
  delete trainer;
}

// Add more tests here

TEST_MAIN()