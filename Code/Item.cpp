#include "Item.hpp"
#include "Player.hpp"
#include <iostream>

Item::Item(std::string name_, std::string description_, int weight_)
    : name(name_), description(description_), weight(weight_) {}

std::string Item::getName() const { return name; }
std::string Item::getDescription() const { return description; }
void Item::inspect() const {
  std::cout << "物品: " << name << "\n描述: " << description
            << "\n重量: " << weight << std::endl;
}

void Weapon::use(Player *player) {
  std::cout << "你装备了" << getName() << "。" << std::endl;
  player->equip(this);
}

void Consumable::use(Player *player) {
  std::cout << "你使用了" << getName() << "。" << std::endl;
  player->heal(20); // 简单的固定回血，未来可以做成属性
}

void Key::use(Player *player) {
  (void)player;
  std::cout << "这是一个" << getName()
            << "。你需要找到它能打开的门，直接走过去试试。" << std::endl;
}
