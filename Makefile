
TARGET = eit
SRCS = $(wildcard *.cpp) -lgcrypt -lz
all:
	g++ $(SRCS) -o $(TARGET)

# Clean rule: delete the built program
clean:
	rm -rf .git
	make