/*
 * Author: Farshad Islam
 * Friday, November 15th, 2024
 *
 * This is the InternalLogic file for my algorithm. It contains -- what else -- the internal logic
 *
 */

// Bunch of imports that definitely all play a significant role why would you even ask if they're all necessary
#include <iostream>
#include <string>
#include <random>
#include <array>
#include "raylib.h"
#include <vector>
#include <algorithm>
#include <limits.h>
#include <utility>
#include <set>

class InternalLogic
{
private:
    std::array<std::array<int, 10>, 10> randInts; // The random 2D array that main.cpp pulls from
    std::set<std::pair<int, int>> lowestCoords;   // The coordinates for the least cost path that main.cpp pulls from

public:
    /**
     * Generates a 10 x 10 grid of random numbers from 0-99 inclusive
     *
     * @return randInts
     */
    std::array<std::array<int, 10>, 10> getRandomNumbers()
    {
        std::random_device rd;                                                  // Sets up non-deterministic device
        std::mt19937 rng(rd());                                                 // Initializes random number generator
        std::uniform_int_distribution<std::mt19937::result_type> dist99(0, 99); // Sets distribution in range of [0, 99]

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                randInts[i][j] = dist99(rng); // Every value in the 2D array randInts is determined randomly
            }
        }

        return randInts; // Used exactly once. Probably should've made all these functions void.
    }

    /**
     * Will create a 2D array starting at a predetermined location within the program window, given the number of rows,
     * columns, and area of each cell that will fall within the grid
     *
     * @param numRows, numColumns, cellArea
     * @return N/A
     */
    void drawMainGrid(int numRows, int numColumns, int cellArea)
    {
        for (int i = 0; i < numRows; i++)
        {
            for (int j = 0; j < numColumns; j++)
            {
                int x = 50 + j * cellArea; // Coordinates for each cell taking margins into account
                int y = 50 + i * cellArea;

                std::string stringNum = std::to_string(randInts[i][j]); // Have to adjust for raylib's const char* requirements
                const char *cstringNum = stringNum.c_str();             // This is the value @ randomNums[i][j]

                int numX = x + (cellArea - MeasureText(cstringNum, 20)) / 2; // MeasureText() gives pixel width after being given font size, which helps give exact point where number should appear
                int numY = y + (cellArea - 20) / 2;                          // Same story but for y-coordinate of randomly generated number

                if (lowestCoords.find(std::make_pair(i, j)) != lowestCoords.end()) // If the current coordinate under inspection falls within the lowestCoords set()
                {
                    DrawRectangle(x, y, cellArea, cellArea, Color{255, 255, 150, 255}); // Will highlight cells in least cost path
                }
                else
                {
                    DrawRectangle(x, y, cellArea, cellArea, WHITE); // Each cell is made white by default
                }
                DrawRectangleLines(x, y, cellArea, cellArea, BLACK); // x and y tell program to start drawing at shape's top right corner
                DrawText(cstringNum, numX, numY, 20, BLACK);         // Each number should appear exactly in the center of the cell it resides in
            }
        }
    }

    /**
     * Creates buttons wherever specified, since Rectangle objects can have exact positioning
     *
     * @param rec, text, color
     * @return N/A
     */
    void drawButton(Rectangle rec, const char *text, Color color)
    {
        int tWidth = MeasureText(text, 20); // Writes text in default font, at size 20, in order to get its total width
        int tHeight = 20;                   // How tall the text is

        DrawRectangleRec(rec, color);                                                                    // Draws the rectangle filled in
        DrawRectangleLinesEx(rec, 1, BLACK);                                                             // Draws the outline in black, with a thickness of 1
        DrawText(text, rec.x + (rec.width - tWidth) / 2, rec.y + (rec.height - tHeight) / 2, 20, BLACK); // Yada yada yada... all the math that it takes to be able to accurately center text within the rectangle
    }

    /**
     * Uses the bottom-up approach to find the least cost path in a 2D array. Whole reason I wrote this was to learn how exactly doing things this way is so much better than standard recursion.
     *
     * @returns lowestCoords
     */
    std::set<std::pair<int, int>> solveGridFunction()
    {
        std::vector<std::vector<int>> sumMatrix(10, std::vector<int>(10, 0)); // This is a matrix containing all the sums of cells starting at the top all the way to the bottom. These sums will be calculated progressively, from top to bottom, and each cell will contain the lowest possible sum possible for it to be reached by.

        std::vector<std::vector<int>> optimalCols(10, std::vector<int>(10, -7000)); // This matrix holds all the column indices in which the least valued cell is located. They also occur within a grid, so that when referenced, each "optimal column" is placed according to where they are found in a 1D array.

        for (int b = 0; b < 10; b++)
        {
            sumMatrix[0][b] = randInts[0][b]; // Fills in base case (uppermost row will always match what is in randInts)
        }

        for (int i = 1; i < 10; i++) // Starts at i = 1 because sumMatrix[0] has already been defined
        {
            for (int j = 0; j < 10; j++)
            {
                int middle = sumMatrix[i - 1][j];                            // Tracks cell directly above sumMatrix[i][j]
                int leftSide = (j > 0) ? sumMatrix[i - 1][j - 1] : INT_MAX;  // Tracks cell @ sumMatrix[i][j]'s upper left
                int rightSide = (j < 9) ? sumMatrix[i - 1][j + 1] : INT_MAX; // Tracks cell @ sumMatrix[i][j]'s upper right

                /* INT_MAX's only real use is to prevent that cell from possibly being confused with the actual least cost value*/

                sumMatrix[i][j] = randInts[i][j] + std::min({middle, leftSide, rightSide}); // This computes the sum value that actually gets placed within sumMatrix[i][j], by determining the least value captured within the (at most) three cells that can potentially lead down to the cell of inspection.

                if (sumMatrix[i][j] == randInts[i][j] + middle) // Determines if middle provides least cost
                {
                    optimalCols[i][j] = j; // Sets the optimal column to the index directly beneath middle, so that when referenced later on, the developing least cost path will lead to the correct cell location.
                }
                else if (sumMatrix[i][j] == randInts[i][j] + leftSide) // Same idea with leftSide and rightSide
                {
                    optimalCols[i][j] = j - 1;
                }
                else if (sumMatrix[i][j] == randInts[i][j] + rightSide)
                {
                    optimalCols[i][j] = j + 1;
                }
            }
        }

        int indexBackPath = std::min_element(sumMatrix[9].begin(), sumMatrix[9].end()) - sumMatrix[9].begin(); // Finds least cost cell at the very bottom of the entire sumMatrix grid. This is where we begin backtracking from.
        int colIndex = indexBackPath;                                                                          // Just like this index says right here.

        for (int row = 9; row >= 0; row--) // "Started from the bottom now we here" (here meaning the least cost cells above as the sequence identifies all optimal coordinates in descending order)
        {
            lowestCoords.insert({row, colIndex});  // Inserts the coordinate of a least cost path cell into the set keeping track of all of them
            colIndex = optimalCols[row][colIndex]; // Sets colIndex to the next most optimal column index so that all the way up until the final iteration of the for-loop, the lowest coordinates are what get added to the lowestCoords set
        }

        return lowestCoords; // Self explanatory, but should probably be written to be a void function. Oh well...
    }

    /**
     * Just regenerates the grid while also getting rid of the previous grid's least cost path highlight. That was surprisingly
     * annoying to figure out how to get rid of, by the way. The world shan't know how long it took to make this work the way it
     * was supposed to from the very beginning.
     *
     * @returns lowestCoords
     */
    void regenerateGrid()
    {
        randInts = getRandomNumbers(); // Resets the 2D array housing all of the randomly generated numbers
        lowestCoords.clear();          // Makes the set clear so that the new least cost path is only discoverable by pressing the button meant to find exactly that
    }
};
