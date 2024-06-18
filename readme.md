Controls:
	-Arrow Keys in Menu
	-WASD in Game
	-Additionally just open help in menu to understand the game

Compiling Instructions:
	Windows:
		1. make sure you have installed mingw64 with sfml and then just run compile.bat
	Linux:
		1. make sure you have g++ and sfml installed 
			-for debian based distros ( Ubuntu etc ) :
				-sudo apt install g++ libsfml-dev
			-for arch based distros : 
				-sudo pacman -S g++ libsfml-dev
		2. and then run compile.sh
	
	For VS 2022, sfml is not configured that well and causes too many lib linkage errors so i didn't bother by putting the steps here, although the project was originally coded on visual studio with SFML VC++17 (VS22)
			
