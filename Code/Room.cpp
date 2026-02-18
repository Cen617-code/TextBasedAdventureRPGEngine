#include "Room.hpp"
#include "Item.hpp"
#include <iostream>
#include <memory>

Room::Room(std::string name_, std::string describe_, int length_, int width_) {
  this->name = name_;
  this->describe = describe_;
  this->length = length_;
  this->width = width_;
  this->monster = nullptr;
}

void Room::setExit(std::string direction, std::shared_ptr<Room> nextRoom,
                   bool locked, std::string keyName) {
  exits[direction] = {nextRoom, locked, keyName};
}

std::shared_ptr<Room> Room::getExit(std::string direction) {
  if (exits.count(direction)) {
    return exits[direction].room;
  }
  return nullptr;
}

bool Room::isLocked(std::string direction) const {
  if (exits.count(direction)) {
    return exits.at(direction).locked;
  }
  return false;
}

void Room::unlock(std::string direction) {
  if (exits.count(direction)) {
    exits[direction].locked = false;
  }
}

std::string Room::getKeyName(std::string direction) const {
  if (exits.count(direction)) {
    return exits.at(direction).keyName;
  }
  return "";
}

std::string Room::getName() const { return name; }

std::string Room::getDescribe() const { return describe; }

std::pair<int, int> Room::getSize() const { return {length, width}; }

void Room::printExits() const {
  std::cout << "可用出口: ";
  for (const auto &pair : exits) {
    std::cout << "[" << pair.first << "] ";
  }
  std::cout << std::endl;
}

void Room::addItem(std::shared_ptr<Item> item) { items.push_back(item); }

std::shared_ptr<Item> Room::popItem(std::string itemName) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    if ((*it)->getName() == itemName) {
      auto found = *it;
      items.erase(it); // 从房间移除
      return found;    // 返回物品
    }
  }
  return nullptr; // 没找到
}

void Room::removeMonster() { monster = nullptr; }

void Room::setMonster(std::shared_ptr<Monster> m) { monster = m; }

std::shared_ptr<Monster> Room::getMonster() const { return monster; }

void Room::lookItem() const {
  if (monster) {
    std::cout << "⚠️  警告！这里有一只 " << monster->getName() << "！"
              << std::endl;
    monster->printStatus();
    std::cout << std::endl;
  }

  if (!items.empty()) {
    std::cout << "你看到了: ";
    for (const auto &item : items) {
      std::cout << item->getName() << " ";
    }
    std::cout << std::endl;
  } else {
    std::cout << "这里空荡荡的，什么也没有。" << std::endl;
  }
}

void Room::printInfo() const {
  std::cout << "=== " << name << " ===" << std::endl;
  std::cout << describe << std::endl;
  // 尺寸信息可选，如果觉得太技术化可以注释掉
  // std::cout << "尺寸: " << length << " x " << width << std::endl;
  lookItem();
  printExits();
  std::cout << "------------------------" << std::endl;
}
