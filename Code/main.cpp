#include "Item.hpp"
#include "Room.hpp"
#include <iostream>
#include <memory>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::pair<std::string, std::string> splitCommand(const std::string &input) {
  std::stringstream ss(input);
  std::string command, argument;
  ss >> command; // 读取第一个词，如 "pick"
  // 读取剩下的所有内容作为参数，如 "rusty sword"
  std::string temp;
  while (ss >> temp) {
    if (!argument.empty())
      argument += " ";
    argument += temp;
  }
  return {command, argument};
}

int main() {
  std::vector<Item> inventory; // 声明背包
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
    std::string commandLine;
    std::getline(std::cin, commandLine);
    if (commandLine.empty())
      continue;

    auto [action, target] = splitCommand(commandLine);

    if (action == "pick") {
      auto poppedItem = currentRoom->popItem(target);
      if (poppedItem.has_value()) {
        inventory.push_back(*poppedItem);
        std::cout << "你捡起了 " << target << "。" << std::endl;
      } else {
        std::cout << "这里没有 " << target << "。" << std::endl;
      }
      continue;
    }else if (action == "go") {
      auto nextRoom = currentRoom->getExit(target);
      if(nextRoom){
        currentRoom = nextRoom;
        std::cout << "你向" << target << "移动。\n" << std::endl;
      }else {
        std::cout << "无法前往那个方向" << std::endl;
      }
    }
    if (commandLine == "quit") {
      std::cout << "再见！" << std::endl;
      break;
    } else if (commandLine == "look") {
      currentRoom->lookItem();
      continue; // 跳过后续的移动检查
    }
  }

  return 0;
}