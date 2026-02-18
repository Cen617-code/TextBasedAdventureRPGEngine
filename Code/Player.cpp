#include "Player.hpp"
#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Player::Player(std::string name_, std::shared_ptr<Room> startingRoom)
    : name(name_), currentRoom(startingRoom), hp(100), maxHp(100), strength(10),
      equippedWeapon(nullptr) {}

void Player::move(std::string direction) {
  // 1. 检查出口是否存在
  auto nextRoom = currentRoom->getExit(direction);
  if (!nextRoom) {
    std::cout << "无法前往那个方向。" << std::endl;
    return;
  }

  // 2. 检查是否上锁
  if (currentRoom->isLocked(direction)) {
    std::string keyName = currentRoom->getKeyName(direction);
    bool hasKey = false;
    for (const auto &item : inventory) {
      if (item->getName() == keyName) {
        hasKey = true;
        break;
      }
    }

    if (hasKey) {
      std::cout << "你用 " << keyName << " 打开了门锁！" << std::endl;
      currentRoom->unlock(direction);
    } else {
      std::cout << "门锁住了。你需要 " << keyName << " 才能通过。" << std::endl;
      return;
    }
  }

  // 3. 移动
  currentRoom = nextRoom;
  std::cout << "你向" << direction << "移动。\n" << std::endl;
  // 移动后自动查看环境
  look();
}

void Player::pickItem(std::string itemName) {
  auto poppedItem = currentRoom->popItem(itemName);
  if (poppedItem) {
    inventory.push_back(poppedItem);
    std::cout << "你捡起了 " << itemName << "。" << std::endl;
  } else {
    std::cout << "这里没有 " << itemName << "。" << std::endl;
  }
}

void Player::dropItem(std::string itemName) {
  for (auto it = inventory.begin(); it != inventory.end(); ++it) {
    if ((*it)->getName() == itemName) {
      auto found = *it;
      inventory.erase(it); // 从背包移除
      currentRoom->addItem(found);
      std::cout << "你丢下了" << itemName << std::endl;
      return;
    }
  }
  std::cout << "背包里没有这个东西" << std::endl;
}

void Player::showInventory() const {
  if (inventory.empty()) {
    std::cout << "背包是空的。" << std::endl;
    return;
  }

  std::cout << "=== 背包 (" << inventory.size() << ") ===" << std::endl;
  for (const auto &item : inventory) {
    std::cout << "- " << item->getName() << ": " << item->getDescription()
              << std::endl;
  }
  std::cout << "==================" << std::endl;
}

std::shared_ptr<Room> Player::getCurrentRoom() const { return currentRoom; }

void Player::look() const { currentRoom->printInfo(); }

void Player::heal(int amount) {
  hp += amount;
  if (hp > maxHp) {
    hp = maxHp;
  }
  std::cout << "你恢复了 " << amount << " 点生命值。"
            << " (当前HP: " << hp << "/" << maxHp << ")" << std::endl;
}

void Player::takeDamage(int amount) {
  hp -= amount;
  if (hp < 0)
    hp = 0;
  std::cout << "你受到了 " << amount << " 点伤害！"
            << " (当前HP: " << hp << "/" << maxHp << ")" << std::endl;
  if (hp == 0) {
    std::cout << "💔 你倒下了... 游戏结束。" << std::endl;
    exit(0); // 简单粗暴的游戏结束
  }
}

void Player::attack(std::string targetName) {
  auto monster = currentRoom->getMonster();
  if (!monster || monster->getName() != targetName) {
    std::cout << "这里没有 " << targetName << "。" << std::endl;
    return;
  }

  // 1. 玩家攻击
  int damage = strength;
  if (equippedWeapon) {
    damage += equippedWeapon->getDamage();
  }

  std::cout << "你攻击了 " << monster->getName() << "！" << std::endl;
  monster->takeDamage(damage);

  // 2. 检查怪物状态
  if (monster->isDead()) {
    std::cout << "🏆 " << monster->getName() << " 被击败了！" << std::endl;
    currentRoom->removeMonster();
  } else {
    // 3. 怪物反击
    int monsterDamage = monster->attack();
    std::cout << "😡 " << monster->getName() << " 反击了！" << std::endl;
    takeDamage(monsterDamage);
  }
}

void Player::useItem(std::string itemName) {
  for (auto it = inventory.begin(); it != inventory.end(); ++it) {
    if ((*it)->getName() == itemName) {
      (*it)->use(this);
      // 如果是消耗品，用完后应该移除？
      // 这里需要判断物品类型，或者让 use 返回一个 bool 表示是否消耗
      // 或者 Item 有一个 bool consumedOnUse() 方法
      // 为了简单起见，我们先假设所有 Consumable 都会被消耗，Weapon 不会。
      // 但是目前 use 返回 void。

      // 让我们先简单处理：Consumable 用完就扔。
      // 我们可以使用 dynamic_pointer_cast 来检查类型
      if (std::dynamic_pointer_cast<Consumable>(*it)) {
        inventory.erase(it);
      }
      return;
    }
  }
  std::cout << "你没有这个物品。" << std::endl;
}

void Player::equip(Weapon *weapon) {
  equippedWeapon = weapon;
  std::cout << "你装备了 " << weapon->getName() << " (攻击力 +"
            << weapon->getDamage() << ")" << std::endl;
}

bool Player::saveToFile(std::string filename) {
  std::ofstream outFile(filename);
  if (!outFile.is_open()) {
    std::cerr << "无法打开文件进行保存: " << filename << std::endl;
    return false;
  }

  // 1. 保存位置
  if (currentRoom) {
    outFile << "ROOM " << currentRoom->getName() << std::endl;
  }

  // 2. 保存属性
  outFile << "HP " << hp << std::endl;
  outFile << "STRENGTH " << strength << std::endl;

  // 3. 保存背包
  for (const auto &item : inventory) {
    outFile << "ITEM " << item->getName() << std::endl;
  }

  // 4. 保存装备
  if (equippedWeapon) {
    outFile << "EQUIPPED " << equippedWeapon->getName() << std::endl;
  }

  outFile.close();
  std::cout << "游戏已保存到 " << filename << std::endl;
  return true;
}

bool Player::loadFromFile(std::string filename, Map &map) {
  std::ifstream inFile(filename);
  if (!inFile.is_open()) {
    std::cerr << "无法打开文件进行读取: " << filename << std::endl;
    return false;
  }

  // 重置状态
  inventory.clear();
  equippedWeapon = nullptr;

  std::string line;
  while (std::getline(inFile, line)) {
    std::stringstream ss(line);
    std::string type;
    ss >> type;

    if (type == "ROOM") {
      std::string roomName;
      // 读取剩余部分作为房间名（可能包含空格）
      std::getline(ss, roomName);
      // 去除开头空格
      if (!roomName.empty() && roomName[0] == ' ') {
        roomName = roomName.substr(1);
      }
      auto room = map.getRoom(roomName);
      if (room) {
        currentRoom = room;
      } else {
        std::cerr << "警告: 找不到房间 " << roomName << std::endl;
      }
    } else if (type == "HP") {
      ss >> hp;
    } else if (type == "STRENGTH") {
      ss >> strength;
    } else if (type == "ITEM") {
      std::string itemName;
      std::getline(ss, itemName);
      if (!itemName.empty() && itemName[0] == ' ') {
        itemName = itemName.substr(1);
      }
      auto item = map.findAndRemoveItem(itemName);
      if (item) {
        inventory.push_back(item);
      } else {
        std::cerr << "警告: 找不到物品 " << itemName
                  << " (可能已被移除或名字错误)" << std::endl;
        // 如果找不到，作为容错，我们也许应该创建一个新的？
        // 但目前架构不支持按名字创建 Item。
        // 所以我们依赖 Map重置后的状态。
      }
    } else if (type == "EQUIPPED") {
      std::string weaponName;
      std::getline(ss, weaponName);
      if (!weaponName.empty() && weaponName[0] == ' ') {
        weaponName = weaponName.substr(1);
      }

      // 在背包里找这个武器
      for (const auto &item : inventory) {
        if (item->getName() == weaponName) {
          equippedWeapon = dynamic_cast<Weapon *>(item.get());
          break;
        }
      }
    }
  }

  inFile.close();
  std::cout << "游戏已从 " << filename << " 加载。" << std::endl;
  return true;
}
