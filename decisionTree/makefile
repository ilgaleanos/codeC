CC                       = g++
STD                     = -std=c++11
CFLAGS             = -Wall
INCLUDES        = -L/usr/local/include
OPTIM               = -O3 -march=native
TARGET             = main
RM                      = rm -f

$(TARGET):
	$(CC) $(STD) $(CFLAGS) $(INCLUDES) $(TARGET).cpp $(LIBS) -o $(TARGET).out $(OPTIM)

run:
	./$(TARGET).out

clean:
	$(RM) $(TARGET).out
