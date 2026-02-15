#ifndef ROOM_HPP
#define ROOM_HPP

#include "Item.hpp"
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

class Room {
private:
  std::string name;
  std::string describe;
  int width;
  int length;
  // 存储出口的映射：方向 -> 房间指针
  std::map<std::string, std::shared_ptr<Room>> exits;
  // 存储房间物品
  std::vector<Item> items;

public:
  // 构造函数
  Room(std::string name_, std::string describe_, int length_, int width_);

  // 添加物品
  void addItem(const Item &item);

  // 移除并返回物品（如果存在）
  std::optional<Item> popItem(std::string itemName);

  // 设置出口
  void setExit(std::string direction, std::shared_ptr<Room> nextRoom);

  // 获取出口
  std::shared_ptr<Room> getExit(std::string direction);

  // Getters
  std::string getName() const;
  std::string getDescribe() const;
  std::pair<int, int> getSize() const;

  // 打印所有可用出口
  void printExits() const;

  // 打印房间完整信息（名称、描述、尺寸、出口）
  void printInfo() const;

  void lookItem() const;
};

#endif // ROOM_HPP
