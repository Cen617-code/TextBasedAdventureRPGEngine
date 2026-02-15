#include "Item.hpp"
#include "Room.hpp"
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>

int main() {
  auto livingRoom = std::make_shared<Room>("客厅", "位于中心", 100, 100);
  auto ARoom = std::make_shared<Room>("房间 A", "位于客厅北边", 100, 50);

  ARoom->addItem(Item("锈剑", "一把生锈的剑"));

  livingRoom->setExit("north", ARoom);
  // 反向连接
  ARoom->setExit("south", livingRoom);

  std::shared_ptr<Room> currentRoom = livingRoom;

  while (true) {
    // 显示当前房间信息
    currentRoom->printInfo();

    std::cout << "> ";
    std::string command;
    std::cin >> command;

    if (command == "quit") {
      std::cout << "再见！" << std::endl;
      break;
    } else if (command == "look") {
      currentRoom->lookItem();
      continue; // 跳过后续的移动检查
    }

    auto nextRoom = currentRoom->getExit(command);
    if (nextRoom) {
      currentRoom = nextRoom;
      std::cout << "你向" << command << "移动。\n" << std::endl;
    } else {
      std::cout << "那个方向没有路。\n" << std::endl;
    }
  }

  return 0;
}