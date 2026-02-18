#include "Map.hpp"
#include "Item.hpp"

Map::Map() {
  // 可以在构造函数中初始化，或者留给 buildWorld
}

void Map::buildWorld() {
  // 1. 创建房间
  auto livingRoom = std::make_shared<Room>("客厅", "位于中心", 100, 100);
  auto ARoom = std::make_shared<Room>("房间 A", "位于客厅北边", 100, 50);
  auto treasureRoom = std::make_shared<Room>("宝藏室", "堆满了金币！", 50, 50);

  // 将房间加入列表管理
  rooms.push_back(livingRoom);
  rooms.push_back(ARoom);
  rooms.push_back(treasureRoom);

  // 2. 初始化物品
  ARoom->addItem(std::make_shared<Weapon>("rusty sword", "一把生锈的剑", 5));
  ARoom->addItem(std::make_shared<Key>("iron key", "一把古老的铁钥匙"));
  livingRoom->addItem(std::make_shared<Consumable>("book", "一本书"));
  livingRoom->addItem(std::make_shared<Consumable>("computer", "一台电脑"));

  // 3. 建立连接
  livingRoom->setExit("north", ARoom);
  ARoom->setExit("south", livingRoom);

  // 锁住的门：客厅 -> 东 -> 宝藏室
  livingRoom->setExit("east", treasureRoom, true, "iron key");
  treasureRoom->setExit("west",
                        livingRoom); // 从里面出来通常不需要钥匙，或者保持解锁

  // 4. 放置怪物
  treasureRoom->setMonster(
      std::make_shared<Monster>("Goblin", "一只贪婪的哥布林", 30, 5));

  // 5. 设置起始房间
  startingRoom = livingRoom;
}

std::shared_ptr<Room> Map::getStartingRoom() const { return startingRoom; }

std::shared_ptr<Room> Map::getRoom(std::string name) const {
  for (const auto &room : rooms) {
    if (room->getName() == name) {
      return room;
    }
  }
  return nullptr;
}

std::shared_ptr<Item> Map::findAndRemoveItem(std::string itemName) {
  for (std::shared_ptr<Room> &room : rooms) {
    if (std::shared_ptr<Item> item = room->popItem(itemName)) {
      return item;
    }
  }
  return nullptr;
}
