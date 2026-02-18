#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>

class Monster {
private:
  std::string name;
  std::string description;
  int hp;
  int maxHp;
  int strength;

public:
  Monster(std::string name_, std::string description_, int hp_, int strength_);

  bool isDead() const;
  void takeDamage(int amount);
  int attack() const;
  void printStatus() const;

  std::string getName() const;
  std::string getDescription() const;
};

#endif // MONSTER_HPP
