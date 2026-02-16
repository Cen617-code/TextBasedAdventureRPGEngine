#include "Item.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>

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
  // 1. 初始化房间
  auto livingRoom = std::make_shared<Room>("客厅", "位于中心", 100, 100);
  auto ARoom = std::make_shared<Room>("房间 A", "位于客厅北边", 100, 50);

  // 2. 初始化物品
  ARoom->addItem(Item("rusty sword", "一把生锈的剑"));
  livingRoom->addItem(Item("book", "一本书"));
  livingRoom->addItem(Item("computer", "一台电脑"));

  // 3. 建立连接
  livingRoom->setExit("north", ARoom);
  ARoom->setExit("south", livingRoom);

  // 4. 初始化玩家
  Player player("Hero", livingRoom);

  // 初始查看环境
  player.look();

  while (true) {
    std::cout << "\n> ";
    std::string commandLine;
    std::getline(std::cin, commandLine);
    if (commandLine.empty())
      continue;

    auto [action, target] = splitCommand(commandLine);

    if (action == "quit") {
      std::cout << "再见！" << std::endl;
      break;
    } else if (action == "look") {
      player.look();
    } else if (action == "go") {
      player.move(target);
    } else if (action == "pick") {
      player.pickItem(target);
    } else if (action == "inventory" || action == "i") {
      player.showInventory();
    } else if(action == "drop"){
      player.dropItem(target);
    }else {
      std::cout << "未知指令。" << std::endl;
    }
  }

  return 0;
}