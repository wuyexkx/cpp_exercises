
CC = g++
SRCS = list.cpp
TARGET = main.exe

BUILD = build
OBJS = $(patsubst %.cpp, $(BUILD)/%.o, $(notdir $(SRCS)))

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ 

$(OBJS): $(SRCS)
# 如果没有BUILD文件夹就创建
	@if [ ! -d $(BUILD) ]; then mkdir -p $(BUILD); fi
	$(CC) -c $^ -o $@

clean:
	rm -rf $(BUILD)
	rm -rf $(OBJS) $(TARGET)
