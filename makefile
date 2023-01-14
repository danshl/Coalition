all: clean bin/cRace

bin/cRace: bin/main.o bin/Agent.o bin/Graph.o bin/Parser.o bin/Party.o bin/Simulation.o bin/PartyPolicy.o bin/AgentPolicy.o
	g++ -o bin/cRace bin/main.o bin/Agent.o bin/Graph.o bin/Parser.o bin/Party.o bin/Simulation.o bin/PartyPolicy.o bin/AgentPolicy.o

bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

bin/Agent.o: src/Agent.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Agent.o src/Agent.cpp

bin/Graph.o: src/Graph.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Graph.o src/Graph.cpp

bin/Parser.o: src/Parser.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Parser.o src/Parser.cpp

bin/Party.o: src/Party.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Party.o src/Party.cpp

bin/Simulation.o: src/Simulation.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Simulation.o src/Simulation.cpp

bin/PartyPolicy.o: src/PartyPolicy.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/PartyPolicy.o src/PartyPolicy.cpp

bin/AgentPolicy.o: src/AgentPolicy.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/AgentPolicy.o src/AgentPolicy.cpp 
clean:
	rm -f bin/*
