# 学习笔记 - RPG 引擎开发（场景建模）

## 📅 日期：2026-02-13

## 🎯 今日目标
实现 `Room` 类的基本框架和出口系统，作为 RPG 引擎场景建模的第一步。

---

## 📚 核心知识点

### 1. 智能指针的使用
- **`std::shared_ptr`**：共享所有权的智能指针
- **使用场景**：多个房间可能需要指向同一个房间对象（例如房间 A 的北边是房间 B，房间 B 的南边又是房间 A）
- **创建方法**：`std::make_shared<Room>(参数...)`
- **优点**：自动内存管理，避免内存泄漏

### 2. STL 容器的应用
- **`std::map`**：键值对映射容器
- **使用场景**：存储方向字符串到房间指针的映射（`std::map<std::string, std::shared_ptr<Room>>`）
- **访问方式**：`map[key]` 或 `map.at(key)`

### 3. 类的封装
- **private 成员**：隐藏内部数据（name, describe, width, length, map）
- **public 接口**：通过 getter/setter 方法访问数据
- **构造函数**：初始化对象状态

### 4. const 成员方法
- **作用**：表示该方法不会修改对象的成员变量
- **优势**：
  - 编译器可以优化
  - 明确接口语义
  - 可以在 const 对象上调用

### 5. std::pair
- **用途**：将两个值组合成一个对象返回
- **访问成员**：`.first` 和 `.second`
- **应用**：`getSize()` 返回 `{length, width}`

---

## 🔨 实现步骤

### 步骤 1：定义 Room 类结构
```cpp
class Room {
private:
    std::string name;
    std::string describe;
    int width;
    int length;
    std::map<std::string, std::shared_ptr<Room>> map;
public:
    // ...
};
```

### 步骤 2：实现构造函数
```cpp
Room(std::string name_, std::string describe_, int length_, int width_) {
    this->name = name_;
    this->describe = describe_;
    this->length = length_;
    this->width = width_;
}
```
**要点**：使用 `this->` 区分成员变量和参数

### 步骤 3：实现 setExit 方法（今日核心任务）
```cpp
void setExit(std::string direction, std::shared_ptr<Room> nextRoom) {
    map[direction] = nextRoom;
}
```
**逻辑挑战解决**：安全地将方向字符串与目标房间智能指针关联

### 步骤 4：实现 Getter 方法
```cpp
std::string getName() const { return name; }
std::string getDescribe() const { return describe; }
std::pair<int, int> getSize() const { return {length, width}; }
std::shared_ptr<Room> getExit(std::string direction) {
    return map[direction];
}
```

### 步骤 5：编写测试代码
```cpp
int main() {
    auto livingRoom = std::make_shared<Room>("客厅", "位于中心", 100, 100);
    auto ARoom = std::make_shared<Room>("房间 A", "位于客厅北边", 100, 50);
    livingRoom->setExit("north", ARoom);

    // 输出测试
    std::cout << "=== " << livingRoom->getName() << " ===" << std::endl;
    std::cout << livingRoom->getDescribe() << std::endl;
    std::cout << "尺寸" << livingRoom->getSize().first << " * "
              << livingRoom->getSize().second << std::endl;

    // 验证出口
    auto northRoom = livingRoom->getExit("north");
    if(northRoom) {
        std::cout << "北边出口指向" << northRoom->getName() << std::endl;
    }

    return 0;
}
```

### 运行结果
```
=== 客厅 ===
位于中心
尺寸100 * 100
北边出口指向房间 A
```
✅ 验证成功：房间连接正确工作！

---

## 🎓 重要代码片段

### 智能指针创建对象
```cpp
auto room = std::make_shared<Room>("名称", "描述", length, width);
```

### 访问智能指针成员
```cpp
room->getName();        // 使用箭头运算符 ->
room->setExit(...);    // 不是点运算符 .
```

### 智能指针的布尔判断
```cpp
if (northRoom) {    // 检查智能指针是否非空
    // 指针有效
}
```

---

## 💡 经验总结

1. **类设计考虑**：成员变量应该是什么类型？（原始值 vs 智能指针）
2. **命名约定**：参数用后缀 `_` 区分成员变量和参数
3. **const 正确性**：getter 方法应该标记为 const
4. **测试驱动**：先实现简单测试输出，验证逻辑正确性

---

## 🚀 下一步计划

- [ ] 添加 `getDescription()` 的完整输出格式化
- [ ] 实现双向房间连接（房间 A 的南边回到客厅）
- [ ] 添加多个方向的出口测试（east, south, west）
- [ ] 考虑：是否需要 `removeExit` 方法？
- [ ] 考虑：是否需要 `listExits()` 方法显示所有可用出口？

---

## ✅ 今日成就

- [√] 理解智能指针的共享所有权概念
- [√] 正确使用 std::map 存储房间出口
- [√] 实现类的封装（private/public）
- [√] 编写并运行测试代码验证功能
- [√] 完成 `setExit` 核心任务

**里程碑**：RPG 引擎的第一步 - 场景建模 - 已完成基础框架！🎉

---
---

# 学习笔记 - RPG 引擎开发（交互循环与模块化）

## 📅 日期：2026-02-14

## 🎯 今日目标
实现游戏的主循环机制，让玩家可以在房间之间自由移动，并对代码进行模块化重构。

---

## 📚 核心知识点

### 1. 模块化编程 (Modular Programming)
- **头文件 (.hpp)**：放置类的声明（Declaration）。充当"接口"，告诉使用者这个类有哪些功能。
  - 包含：成员变量定义、方法原型、必要的 `#include`。
  - 防卫式声明：`#ifndef ROOM_HPP ... #endif` 防止头文件被重复包含。
- **源文件 (.cpp)**：放置类的实现（Implementation）。
  - 包含：具体函数的代码逻辑。
  - 需要 `#include "Room.hpp"`。
- **主程序 (main.cpp)**：只负责业务逻辑流程，代码变得非常整洁。
- **编译方法**：需要同时编译所有源文件：
  ```bash
  clang++ -std=c++26 Code/main.cpp Code/Room.cpp -o rpg_engine
  ```

### 2. 双向连接 (Bidirectional Linking)
- 房间之间的连接通常是双向的。
- **实现**：
  ```cpp
  livingRoom->setExit("north", ARoom);
  ARoom->setExit("south", livingRoom); // 手动建立反向连接
  ```

### 3. 游戏循环 (Game Loop)
- RPG 游戏的核心是一个无限循环：**显示信息 -> 等待输入 -> 处理指令 -> 更新状态**。
- **实现结构**：
  ```cpp
  while (true) {
      currentRoom->printInfo(); // 1. 显示
      std::cin >> command;      // 2. 输入
      if (command == "quit") break; // 3. 退出条件
      // ... 处理移动 ...      // 4. 更新状态
  }
  ```

### 4. 玩家状态追踪
- 使用一个指针指向当前所在的房间。
- `std::shared_ptr<Room> currentRoom = livingRoom;`
-移动就是更新这个指针：`currentRoom = nextRoom;`

---

## 🔨 代码架构演进

### 文件结构
- `Code/Room.hpp`: Room 类声明
- `Code/Room.cpp`: Room 类实现
- `Code/main.cpp`: 游戏入口与主循环

### Room 类新功能
- `printExits()`: 遍历 map 打印所有可用出口
- `printInfo()`: 封装了名称、描述和出口的打印逻辑

---

## 🚀 下一步计划

- [ ] **指令解析器升级**：目前只能处理单词，无法处理 "go north" 这种带空格的指令。
- [ ] **背包系统**：添加 `Item` 类，通过 `pick` 指令捡起物品。
- [ ] **地图构建器**：将硬编码的房间创建逻辑（`make_shared`...）移到一个单独的 `Map` 类或函数中。

---

## ✅ 今日成就

- [√] 成功将代码拆分为模块化结构 (.hpp/.cpp)
- [√] 实现了双向房间移动逻辑
- [√] 完成了游戏主循环 (Game Loop)
- [√] 修复了单向移动的限制，现在可以来回走动了！

**里程碑**：我们的 RPG 引擎已经“动”起来了！它不再是静态的数据，而是一个可交互的世界。🌍

---
---

# 学习笔记 - RPG 引擎开发（物品系统与高级交互）

## 📅 日期：2026-02-15

## 🎯 今日目标
实现物品系统（Item System），让玩家能够查看、捡起物品，并升级指令解析器以支持更自然的语言交互（如 `pick sword`）。

---

## 📚 核心知识点

### 1. 物品系统的架构
- **`Item` 类**：封装物品的基本属性（名称、描述）。
- **容器的使用**：
  - `Room` 类中使用 `std::vector<Item>` 存储房间内的物品。
  - `main` 函数中使用 `std::vector<Item>` 作为玩家的背包（Inventory）。

### 2. 交互逻辑：捡起物品 (Pick Up)
- **查找与移除**：
  - 在 `Room` 中查找指定名称的物品。
  - 使用 `vector::erase` 配合迭代器移除物品。
- **所有权转移**：物品对象从房间的 vector 复制/移动到玩家背包的 vector 中。

### 3. C++17 `std::optional`
- **用途**：用于处理“可能失败”的返回值（如没找到物品）。
- **用法**：
  - 返回 `std::nullopt` 表示无值。
  - 使用 `.has_value()` 检查是否有值。
  - 使用 `*` 解引用获取值。

### 4. 字符串流与解析 (`std::stringstream`)
- **功能**：将整行输入字符串视为流，方便按空格分割单词。
- **应用**：将 "pick rusty sword" 解析为 `command="pick"` 和 `argument="rusty sword"`。

---

## 🔨 实现细节回顾

### 1. 物品类定义 (Item.hpp)
简单的名称和描述封装。

### 2. 房间中的物品逻辑 (Room.cpp)
```cpp
// 移除并返回物品
std::optional<Item> Room::popItem(std::string itemName) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getName() == itemName) {
            Item found = *it;
            items.erase(it); // 关键：从容器中删除
            return found;    // 返回副本
        }
    }
    return std::nullopt;
}
```

### 3. 指令解析 (main.cpp)
```cpp
// 使用 getline 读取整行
std::getline(std::cin, commandLine);
// 自定义 splitCommand 函数处理 "pick xxx"
auto [action, target] = splitCommand(commandLine);
```

### 4. 游戏循环中的处理
- **look**: 调用 `currentRoom->lookItem()` 显示物品。
- **pick**: 调用 `popItem` 尝试获取，成功则加入 `inventory`。
- **go**: 处理 `go north` 这种动词+名词的移动指令。

---

## 🚀 下一步计划

- [ ] **背包查看**：实现 `inventory` 指令，列出背包里的物品。
- [ ] **物品使用**：实现 `use key` 之类的逻辑（需要结合锁住的门）。
- [ ] **地图构建器**：目前的地图创建还在 `main` 函数里，代码有点乱。

---

## ✅ 今日成就

- [√] 创建了 `Item` 类并集成到 `Room` 中
- [√] 实现了 `look` 指令查看房间物品
- [√] 实现了 `pick` 指令捡起物品到背包
- [√] 实现了 `go` 指令支持（如 `go north`）
- [√] 掌握了 `std::optional` 和 `stringstream` 的基本用法

**里程碑**：我们的 RPG 引擎现在支持物品交互了！这是游戏性的一大飞跃。🎒⚔️
