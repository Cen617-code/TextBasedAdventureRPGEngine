#include <string>
#include <iostream>
#include <map>
#include <memory>

class Room{
private:
    std::string name;
    std::string describe;
    int width;
    int length;
    std::map<std::string, std::shared_ptr<Room>> map; 
public:
    Room(std::string name_, std::string describe_, int length_, int width_){
        this->name = name_;
        this->describe = describe_;
        this->length = length_;
        this->width = width_;
    }

    void setExit(std::string direction, std::shared_ptr<Room> nextRoom){
        map[direction] = nextRoom;
    }

    std::string getName() const {
        return name;
    }

    std::string getDescribe() const {
        return describe;
    }

    //字符形式
    // std::string getSize() const {
    //     return std::format("{} * {}", length, width);
    // }

    std::pair<int, int> getSize() const {
        return {length, width};
    }

    std::shared_ptr<Room> getExit(std::string direction) {
        return map[direction];
    }
};

int main(){
    auto livingRoom = std::make_shared<Room>("客厅", "位于中心", 100, 100);
    auto ARoom = std::make_shared<Room>("房间 A", "位于客厅北边", 100, 50);
    livingRoom->setExit("north", ARoom);
    std::cout << "=== " << livingRoom->getName() << " ===" << std::endl;
    std::cout << livingRoom->getDescribe() << std::endl;
    std::cout << "尺寸" << livingRoom->getSize().first << " * " 
              << livingRoom->getSize().second << std::endl;
    auto northRoom = livingRoom->getExit("north");
    if(northRoom){
        std::cout << "北边出口指向" << northRoom->getName() <<std::endl;
    }
    return 0;

}