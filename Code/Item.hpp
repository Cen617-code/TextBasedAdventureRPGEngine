#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {
private:
  std::string name;
  std::string description;
  int weight;

public:
  Item(std::string name_, std::string description_, int weight_ = 1);

  std::string getName() const;
  std::string getDescription() const;
  void inspect() const;
};

#endif
