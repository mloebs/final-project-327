# Copyright Will Holden wcholden@bu.edu

# The syntax is

# thingtobuld:  what-it-needs-or-depends-on
#    instructions on how to build it

keys: keystroke_test.cpp
	g++ keystroke_test.cpp -o keys -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

game: gameplay_fxn.cpp
	g++ gameplay_fxn.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

