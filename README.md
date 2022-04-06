# Trails and Towers
Trails and Towers (or Trails) is a mathematical game for two players. The player's objective is to take as many *towers* as possible by making *trails* on a square field with certain rules.

## About
This is a cross-platform C++ implementation of that mathematical game based on [GLFW library](https://github.com/glfw/glfw). Now it is available for Windows and Linux (requires additional libraries). See download options on [game's website](http://trails.sogamestudios.com/download).

## Controls
Use arrow or WASD keys to choose move direction, or click on the target cell with mouse (click on a general move direction will also work). Game will show possible cells to move to as a green ones.

## Rules
Classic version of Trails and Towers has three towers on diagonal distance of one *cell* and 11x11 *field*. As being said, player's objective is to *take* as many towers as possible. Therefore, first player which takes more than a half of towers, wins. Player loses if none *move* can be done in player's turn.

Each player have colored *base* in opposite corners of the field. Usually, base color is blue for player one and red for player two and blue base is located in upper left corner when red base is located in bottom right corner. Towers are placed from field center at specified distance and on the diagonal which connects *free* cells in corners of the field. Cell where the tower is placed does not count as free.

From the bases players making moves (player one goes first) in one of possible directions: up, down, left or right. If cell in chosen direction is free, player can *occupy* it. Cell which is already occupied by current player or by opponent cannot be occupied again.

By moving at the same direction as last turn player will accumulate *boost*, which means that every turn player will move further by one cell. When player changes moving direction, boost is gone. With boost player can *jump over* occupied cells, if *target* cell is free or there is a tower. When player jumps over, every free cell between *origin* cell and target cell becomes occupied.

If player has boost and target cell is "over" the bound, player occupies every free cell in chosen direction up to bound, but only if cell next to the bound is free too. Lastly, player can take (occupy) tower only with boost and only when tower cell is target.