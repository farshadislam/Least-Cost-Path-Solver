## Least Cost Path Solver

This is a small, but useful project I embarked upon in order to teach myself more about C++, raylib, and dynamic programming. The idea is simple: A 10x10 grid is generated with numbers ranging from 0-99 in each cell. What my program does is find the least cost path from the top all the way down to the bottom, without being able to make any horizontal-only moves. "Least cost path" means that by determining the sum of all the numbers in any possible path from the top to the bottom of the grid (or cost), the program uses an algorithm to systematically determine which path has the lowest possible sum of all its cells' values.

# How to run this program

1. Download the .zip file from GitHub
2. Extract contents (with .7zip or WinRAR, or the built-in function on Windows 11)
3. Compliment a loved one
4. Open "main.cpp" with an IDE
5. Hit F5 on your keyboard to build the program
6. Go back into the outermost folder
7. Run the "main" .exe file that has now been built

# How to use this program

Look at the grid. If you want to find the least cost path, hit "Solve Grid". Now the least cost path is highlighted in yellow.

Want to try again with a different grid this time? Hit "Regenerate Grid" for an all new 2D array, and repeat the process from there.
