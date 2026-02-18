#include "Monster.hpp"
#include <iostream>

Monster::Monster(std::string name_, std::string description_, int hp_,
                 int strength_)
    : name(name_), description(description_), hp(hp_), maxHp(hp_),
      strength(strength_) {}

bool Monster::isDead() const { return hp <= 0; }

void Monster::takeDamage(int amount) {
  hp -= amount;
  if (hp < 0)
    hp = 0;
  std::cout << name << " 受到了 " << amount << " 点伤害。" << " (HP: " << hp
            << "/" << maxHp << ")" << std::endl;
}

int Monster::attack() const { return strength; }

void Monster::printStatus() const {
  std::cout << "怪物: " << name << " (" << description << ")\n"
            << "HP: " << hp << "/" << maxHp << "\n"
            << "攻击力: " << strength << std::endl;
}

std::string Monster::getName() const { return name; }

std::string Monster::getDescription() const { return description; }
