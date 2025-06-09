
TARGET = eit
SRCS = main.cpp workspace.cpp
all:
	g++ $(SRCS) -o $(TARGET)

# Clean rule: delete the built program
clean:
	rm -f $(TARGET)