#include "Room.hpp"
#include "Item.hpp"
#include <iostream>
#include <memory>


Room::Room(std::string name_, std::string describe_, int length_, int width_) {
  this->name = name_;
  this->describe = describe_;
  this->length = length_;
  this->width = width_;
}

void Room::setExit(std::string direction, std::shared_ptr<Room> nextRoom) {
  exits[direction] = nextRoom;
}

std::shared_ptr<Room> Room::getExit(std::string direction) {
  // map::operator[]
  // 如果key不存在会创建默认元素，这里为了安全可以改进，但暂时保持原逻辑
  if (exits.count(direction)) {
    return exits[direction];
  }
  return nullptr;
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

void Room::lookItem() const {
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
