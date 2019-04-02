ifdef OS
    BUILD_CMD = g++ tetris.o -o tetris -l-graphics -l-window -l-system
else
    ifeq ($(shell uname), Linux)
        BUILD_CMD = g++ tetris.o -o tetris -lsfml-graphics -lsfml-window -lsfml-system
    endif
endif

build:
	g++ -c tetris.cpp
	$(BUILD_CMD)

.PHONY: build
