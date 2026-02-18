#ifndef MAP_HPP
#define MAP_HPP

#include "Room.hpp"
#include <memory>
#include <vector>

class Map {
private:
  std::vector<std::shared_ptr<Room>> rooms;
  std::shared_ptr<Room> startingRoom;

public:
  Map();
  void buildWorld();
  std::shared_ptr<Room> getStartingRoom() const;
  std::shared_ptr<Room> getRoom(std::string name) const;
  std::shared_ptr<Item> findAndRemoveItem(std::string itemName);
};

#endif // MAP_HPP
