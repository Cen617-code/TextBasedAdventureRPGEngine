#include "Player.hpp"
#include <iostream>
#include <algorithm>

Player::Player(std::string name_, std::shared_ptr<Room> startingRoom)
    : name(name_), currentRoom(startingRoom) {}

void Player::move(std::string direction) {
  auto nextRoom = currentRoom->getExit(direction);
  if (nextRoom) {
    currentRoom = nextRoom;
    std::cout << "你向" << direction << "移动。\n" << std::endl;
    // 移动后自动查看环境，这是一种经典设计
    look();
  } else {
    std::cout << "无法前往那个方向。" << std::endl;
  }
}

void Player::pickItem(std::string itemName) {
  auto poppedItem = currentRoom->popItem(itemName);
  if (poppedItem.has_value()) {
    inventory.push_back(*poppedItem);
    std::cout << "你捡起了 " << itemName << "。" << std::endl;
  } else {
    std::cout << "这里没有 " << itemName << "。" << std::endl;
  }
}

void Player::dropItem(std::string itemName) {
   for (auto it = inventory.begin(); it != inventory.end(); ++it) {
    if (it->getName() == itemName) {
      Item found = *it;
      inventory.erase(it); // 从背包移除
      currentRoom->addItem(found);
      std::cout << "你丢下了" << itemName << std::endl;
      return;
    }
   }
    std::cout << "背包里没有这个东西" << std::endl;
}

void Player::showInventory() const {
  if (inventory.empty()) {
    std::cout << "背包是空的。" << std::endl;
    return;
  }

  std::cout << "=== 背包 (" << inventory.size() << ") ===" << std::endl;
  for (const auto &item : inventory) {
    std::cout << "- " << item.getName() << ": " << item.getDescription()
              << std::endl;
  }
  std::cout << "==================" << std::endl;
}

std::shared_ptr<Room> Player::getCurrentRoom() const { return currentRoom; }

void Player::look() const { currentRoom->printInfo(); }
