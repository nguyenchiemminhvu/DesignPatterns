CPP_FLAGS= \
	-g \
	-Wall

LD_FLAGS= \
	-g

CPP_FILES= \
	main.cpp

OBJ_FILES= \
	main.o

main: $(OBJ_FILES)
	g++ $(LD_FLAGS) -o main $(OBJ_FILES) && chmod +x ./main

$(OBJ_FILES): $(CPP_FILES)
	g++ $(CPP_FLAGS) -c $(CPP_FILES)

clean:
	rm -rf main
	rm -rf $(OBJ_FILES)

