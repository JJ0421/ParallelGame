Credits:
This game was made by JJ Abbott and Mitch Brooks. It was written in C++ using
pthreads and SDL libraries. 

Summary of Game:
It is a two player game. The object of the game is to
collect key(s) in order to unlock a door that will advance players to the next level.
Each player has three lives. A player loses a life if they are hit by an enemy. A
player loses all lives if they fall off the map. Once all lives are lost for either
player, both players restart that level with full health.

Parallelization:
Thread 0 (main thread) - draws/updates the screen and plays background music along
			 with menu sounds
Thread 1 - controls player1 and updates all of player1's statistics/interactions
	   (such as interacting with obstacles or enemies)
Thread 2 - controls player2 and updates all of player2's statistics/interactions
	   (such as interacting with obstacles or enemies)
Thread 3 - Strictly controls enemy movement. There are two types of enemies (up
	   and down or left and right) and each enemy is given their own movement
	   speed.

