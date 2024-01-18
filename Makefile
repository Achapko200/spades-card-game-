COMPILER=g++
OPTIONS=-std=c++17 -pedantic -Wall -Werror -g
COMPILE=$(COMPILER) $(OPTIONS)

card=../Card.cpp
pack=../Pack.cpp
player=../Player.cpp
team=../Team.cpp
test_framework=catch_amalgamated.cpp

test: test_card test_pack test_player

test_valgrind: test_card.exe test_pack.exe
	valgrind ./test_card.exe
	valgrind ./test_pack.exe
	valgrind ./test_player.exe

test_card: test_card.exe
	./test_card.exe

test_pack: test_pack.exe
	./test_pack.exe

test_player: test_player.exe
	./test_player.exe

# TODO include test_team in total tests later
test_team: test_team.exe
	./test_team.exe

#test_card.exe: test_card.cpp $(card) $(test_framework)
#	$(COMPILE) -o $@ $^

#test_pack.exe: test_pack.cpp $(card) $(pack) $(test_framework)
#	$(COMPILE) -o $@ $^

#test_player.exe: test_player.cpp $(card) $(player) $(test_framework)
#	$(COMPILE) -o $@ $^

#test_team.exe: test_team.cpp $(card) $(player) $(team) $(test_framework)
#	$(COMPILE) -o $@ $^

# Object files
Card.o: $(card)
	$(COMPILE) -c $^

Pack.o: $(pack)
	$(COMPILE) -c $^

Player.o: $(player)
	$(COMPILE) -c $^

Team.o: $(team)
	$(COMPILE) -c $^

catch_amalgamated.o: catch_amalgamated.cpp
	$(COMPILE) -c $^

test_card.o: test_card.cpp
	$(COMPILE) -c $^

test_pack.o: test_pack.cpp
	$(COMPILE) -c $^

test_player.o: test_player.cpp
	$(COMPILE) -c $^

test_team.o: test_team.cpp
	$(COMPILE) -c $^

# Executables
test_card.exe: Card.o catch_amalgamated.o test_card.o
	$(COMPILE) -o $@ $^

test_pack.exe: Card.o Pack.o catch_amalgamated.o test_pack.o 
	$(COMPILE) -o $@ $^

test_player.exe: Card.o Player.o catch_amalgamated.o test_player.o
	$(COMPILE) -o $@ $^

test_team.exe: Card.o Player.o Team.o catch_amalgamated.o test_team.o 
	$(COMPILE) -o $@ $^



.PHONY: clean

clean:
	rm -rvf *.out *.exe *.dSYM *.stackdump *.o