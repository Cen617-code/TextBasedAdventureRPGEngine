#include "Item.hpp"
#include <iostream>

Item::Item(std::string name_, std::string description_, int weight_) {
  this->name = name_;
  this->description = description_;
  this->weight = weight_;
}

std::string Item::getName() const { return name; }

std::string Item::getDescription() const { return description; }

void Item::inspect() const {
  std::cout << "物品: " << name << "\n描述: " << description << std::endl;
}
