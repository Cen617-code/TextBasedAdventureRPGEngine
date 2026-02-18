# Text-Based RPG Engine (C++26)

## 🎮 Game Overview
Current Version: 1.0 (Feb 2026)

This is a modern C++ text-based adventure engine built as a learning project. It features a complete game loop, OOP-based entity system, and persistent state management.

## ✨ Features

- **Dynamic World**: Interconnected rooms navigated via cardinal directions.
- **Inventory System**: 
  - `Item` class hierarchy with `Consumable` (e.g., potions) and `Weapon` (e.g., swords).
  - Flexible `pick`, `drop`, and `use` mechanics. (e.g., `pick rusty sword`)
- **Combat System**: 
  - Turn-based combat against `Monitor` entities (e.g., Goblin).
  - Damage calculation based on player stats and equipped weapons.
- **Locked Rooms**: Puzzle mechanics requiring specific keys to unlock paths.
- **Persistence**: Save (`save`) and load (`load`) game state using file serialization.
- **Modern C++**: Heavy usage of `std::shared_ptr`, polymorphism, and STL containers.

## 🛠️ Tech Stack & Architecture

- **Language**: C++26
- **Compiler**: Clang++
- **Memory Management**: Extensive use of Smart Pointers (`std::shared_ptr`) for automatic memory handling.
- **Design Patterns**:
  - **Component-based Room**: Rooms hold mapped Exits, Item vectors, and Monster pointers.
  - **Polymorphic Items**: Base `Item` class with virtual methods for specialized behaviors.
  - **Map Builder**: Encapsulated world generation logic.

## 🚀 How to Build & Run

### Prerequisites
- Clang++ compiler (supporting C++20/23/26 features)
- Make (optional, but recommended)

### Compile
Using the provided Makefile:
```bash
make
```
Or manually:
```bash
clang++ -std=c++26 -Wall -Wextra -g -o rpg_engine Code/Item.cpp Code/Map.cpp Code/Monster.cpp Code/Player.cpp Code/Room.cpp Code/main.cpp
```

### Run
```bash
./rpg_engine
```

## 📝 Commands

- **Movement**: `go north`, `go south`, etc.
- **Interaction**: 
  - `look`: Examine current room.
  - `pick <item>`: Pick up an item.
  - `drop <item>`: Drop an item.
  - `use <item>`: Use (consumable) or Equip (weapon).
  - `inventory`: Check backpack.
- **Combat**: `attack <monster>`
- **System**: `save`, `load`, `quit`

## 📂 Project Structure
```
.
├── Code/           # Source files
│   ├── Item.hpp/cpp
│   ├── Map.hpp/cpp
│   ├── Monster.hpp/cpp
│   ├── Player.hpp/cpp
│   ├── Room.hpp/cpp
│   └── main.cpp
├── Makefile        # Build script
├── Note.md         # Detailed Dev Logs (Chinese)
├── README.md       # Project Overview
└── savegame.txt    # Save file (generated)
```

## 🎓 Learning Outcomes
This project was used to master:
- Smart Pointers functionality and ownership semantics.
- OOP principles: Encapsulation, Inheritance, Polymorphism.
- File I/O for game state persistence.
- Solving circular dependencies with Forward Declarations.
- Linker and Compiler error troubleshooting.

---
*Created by [User] & Antigravity (AI Assistant) - Feb 2026*
