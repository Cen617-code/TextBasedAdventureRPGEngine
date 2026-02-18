#ifndef ROOM_HPP
#define ROOM_HPP

#include "Item.hpp"
#include "Monster.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>

class Room {
  struct Exit {
    std::shared_ptr<Room> room;
    bool locked;
    std::string keyName;
  };

private:
  std::string name;
  std::string describe;
  int width;
  int length;
  // 存储出口的映射：方向 -> Exit 结构体
  std::map<std::string, Exit> exits;
  // 存储房间物品
  std::vector<std::shared_ptr<Item>> items;
  // 房间里的怪物（目前限一个）
  std::shared_ptr<Monster> monster;

public:
  // 构造函数
  Room(std::string name_, std::string describe_, int length_, int width_);

  // 添加物品
  void addItem(std::shared_ptr<Item> item);

  // 移除并返回物品（如果存在）
  std::shared_ptr<Item> popItem(std::string itemName);

  // 设置出口
  void setExit(std::string direction, std::shared_ptr<Room> nextRoom,
               bool locked = false, std::string keyName = "");

  // 检查锁状态
  bool isLocked(std::string direction) const;
  // 解锁
  void unlock(std::string direction);
  // 获取钥匙名
  std::string getKeyName(std::string direction) const;

  // 怪物管理
  void setMonster(std::shared_ptr<Monster> monster);
  std::shared_ptr<Monster> getMonster() const;
  void removeMonster();

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
