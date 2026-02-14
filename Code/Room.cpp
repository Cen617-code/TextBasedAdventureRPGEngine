#include "Room.hpp"
#include <iostream>

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

void Room::printInfo() const {
  std::cout << "=== " << name << " ===" << std::endl;
  std::cout << describe << std::endl;
  // 尺寸信息可选，如果觉得太技术化可以注释掉
  // std::cout << "尺寸: " << length << " x " << width << std::endl;
  printExits();
  std::cout << "------------------------" << std::endl;
}
