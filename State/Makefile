CPP_FLAGS= \
	-g \
	-Wall \
	-pthread

LD_FLAGS= \
	-g

LD_LIBS= \
	-lpthread

CPP_FILES= \
	main.cpp

OBJ_FILES= \
	main.o

main: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o main $(OBJ_FILES) $(LD_LIBS) && chmod +x ./main

$(OBJ_FILES): $(CPP_FILES)
	g++ $(CPP_FLAGS) -c $(CPP_FILES)

clean:
	rm -rf main
	rm -rf $(OBJ_FILES)

