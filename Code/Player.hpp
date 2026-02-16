#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Item.hpp"
#include "Room.hpp"
#include <memory>
#include <string>
#include <vector>

class Player {
private:
  std::string name;
  std::shared_ptr<Room> currentRoom;
  std::vector<Item> inventory;

public:
  Player(std::string name_, std::shared_ptr<Room> startingRoom);

  // 移动
  void move(std::string direction);

  // 物品交互
  void pickItem(std::string itemName);
  void showInventory() const;

  // 获取当前房间（如果外部还需要直接操作房间）
  std::shared_ptr<Room> getCurrentRoom() const;

  // 查看周围（调用房间的 look 方法）
  void look() const;
};

#endif // PLAYER_HPP
