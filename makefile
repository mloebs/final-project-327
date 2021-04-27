# Copyright Will Holden wcholden@bu.edu

# The syntax is

# thingtobuld:  what-it-needs-or-depends-on
#    instructions on how to build it

keys: accuracy_keystroke.cpp
	g++ accuracy_keystroke.cpp -o keys -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

game: gameplay_fxn.cpp
	g++ gameplay_fxn.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

enter: enter.cpp
	g++ enter.cpp -o enter -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

enter_v2: enter_v2.cpp
	g++ enter_v2.cpp -o enter_v2 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio 
