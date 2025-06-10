
TARGET = eit
SRCS = main.cpp workspace.cpp -lgcrypt
all:
	g++ $(SRCS) -o $(TARGET)

# Clean rule: delete the built program
clean:
	rm -f $(TARGET)