#include "Room.hpp"
#include <iostream>
#include <memory>

int main() {
  auto livingRoom = std::make_shared<Room>("客厅", "位于中心", 100, 100);
  auto ARoom = std::make_shared<Room>("房间 A", "位于客厅北边", 100, 50);

  livingRoom->setExit("north", ARoom);
  // 反向连接
  ARoom->setExit("south", livingRoom);

  std::cout << "=== " << livingRoom->getName() << " ===" << std::endl;
  std::cout << livingRoom->getDescribe() << std::endl;
  std::cout << "尺寸" << livingRoom->getSize().first << " * "
            << livingRoom->getSize().second << std::endl;

  // 测试新增加的 printExits 功能
  livingRoom->printExits();

  auto northRoom = livingRoom->getExit("north");
  if (northRoom) {
    std::cout << "北边出口指向" << northRoom->getName() << std::endl;
  }

  auto southRoom = ARoom->getExit("south");
  if (southRoom) {
    std::cout << "南边出口指向" << southRoom->getName() << std::endl;
  }
  return 0;
}