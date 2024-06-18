#!/bin/bash
 echo Linking Headers....
 g++ -c AVLTree.cpp AVLTree.h Enemy.cpp Enemy.h Game.cpp Game.h Maze.cpp Maze.h Menu.cpp Menu.h Player.cpp Player.h Treasure.cpp Treasure.h Utils.cpp Utils.h
 echo Compiling...
 g++ main.cpp AVLTree.o Enemy.o Game.o Maze.o Menu.o Player.o Treasure.o Utils.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o game
 echo Starting Game
./game