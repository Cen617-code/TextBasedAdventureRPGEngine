#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <iostream>

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

  virtual void use(Player* player) = 0;
};

class Weapon : public Item {
private:
  int damage;
public:
  Weapon(std::string name_, std::string describe_, int damage_) : Item(name_, describe_), damage(damage_) {}

  void use(Player* player) override{
    (void) player;
    std::cout << "你挥舞着" << getName() << "，造成了" << damage << "点伤害！" << std::endl;
  }
};

class Consumable : public Item {
public:
  Consumable(std::string name_, std::string description_) : Item(name_, description_) {}
  void use(Player* player) override{
    (void) player;
    std::cout << "你使用了" << getName() << "。感觉好多了！" << std::endl;
  }
};

#endif
