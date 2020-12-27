CFLAGS+=-O2 -Wall -Wno-pointer-sign -std=gnu11 -fsanitize=address -fsanitize=undefined
CPPFLAGS+=-O2 -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor -Wstrict-null-sentinel  -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Weffc++ -std=gnu++17
.PHONY: all clear

all: main

main: main.o
	g++ $(CPPFLAGS) $^ -o $@

main.o: main.cpp
	g++ $(CPPFLAGS) -c $< -o $@

clear:
	rm -rf *.o
