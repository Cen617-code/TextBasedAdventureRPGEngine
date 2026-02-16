CXX = clang++
CXXFLAGS = -std=c++26 -Wall -Wextra -g
SRC_DIR = Code
# 获取 Code 目录下的所有 .cpp 文件
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# 将 .cpp 替换为 .o
OBJS = $(SRCS:.cpp=.o)
TARGET = rpg_engine

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 编译源文件生成目标文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理构建文件
clean:
	rm -f $(OBJS) $(TARGET)
	rm -f $(SRC_DIR)/*.o

.PHONY: all clean
