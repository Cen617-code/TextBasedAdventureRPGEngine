#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Item.hpp"
#include "Room.hpp"
#include <memory>
#include <string>
#include <vector>

class Weapon;
class Map; // Forward declaration

class Player {
private:
  std::string name;
  std::shared_ptr<Room> currentRoom;
  std::vector<std::shared_ptr<Item>> inventory;
  int hp;
  int maxHp;
  int strength;

public:
  Player(std::string name_, std::shared_ptr<Room> startingRoom);

  // 移动
  void move(std::string direction);

  // 物品交互
  void pickItem(std::string itemName);
  void dropItem(std::string itemName);
  void useItem(std::string itemName);
  void showInventory() const;

  // 获取当前房间（如果外部还需要直接操作房间）
  std::shared_ptr<Room> getCurrentRoom() const;

  // 查看周围（调用房间的 look 方法）
  void look() const;

  // 状态管理
  void heal(int amount);
  void takeDamage(int amount);
  int getHp() const { return hp; }
  int getStrength() const { return strength; }

  // 战斗
  void attack(std::string targetName);
  void equip(Weapon *weapon);

  // 存档
  bool saveToFile(std::string filename);
  bool loadFromFile(std::string filename, Map &map);

private:
  Weapon *equippedWeapon; // 当前装备的武器（不拥有所有权）
};

#endif // PLAYER_HPP
