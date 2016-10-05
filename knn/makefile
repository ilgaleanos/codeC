CC 			= g++

CFLAGS 		= -Wall
INCLUDES 	= -L/usr/local/include
LIBS 		= -lgsl -lgslcblas -lm
OPTIM 		= -O3 -march=native

TARGET 		= main
RM     		= rm -f

$(TARGET):
	$(CC) $(CFLAGS) $(INCLUDES) $(TARGET).cpp $(LIBS) -o $(TARGET).out $(OPTIM)

run:
	./$(TARGET).out

clean:
	$(RM) $(TARGET).out
