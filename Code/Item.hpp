#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <string>

class Player;

class Item {
private:
  std::string name;
  std::string description;
  int weight;

public:
  Item(std::string name_, std::string description_, int weight_ = 1);

  virtual ~Item() = default;

  std::string getName() const;
  std::string getDescription() const;
  void inspect() const;

  virtual void use(Player *player) = 0;
};

class Weapon : public Item {
private:
  int damage;

public:
  Weapon(std::string name_, std::string describe_, int damage_)
      : Item(name_, describe_), damage(damage_) {}

  void use(Player *player) override;
  int getDamage() const { return damage; }
};

class Consumable : public Item {
public:
  Consumable(std::string name_, std::string description_)
      : Item(name_, description_) {}
  void use(Player *player) override;
};

class Key : public Item {
public:
  Key(std::string name_, std::string description_)
      : Item(name_, description_) {}
  void use(Player *player) override;
};

#endif
