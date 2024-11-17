/*
 * Author: Farshad Islam
 * Friday, November 15th, 2024
 *
 * This is the main file for my least cost finding algorithm.
 *
 * If anything looks at all unprofessional, it's because it is. I was only able to scrape
 * this together by teaching myself both Raylib and one of the fundamentals of Dynamic
 * Programming through ChatGPT. Over the course of a week. In pajama shorts.
 *
 * The following code IS NOT AI-GENERATED... but it's far from sophisticated enough that
 * an AI couldn't just spit back out roughly the same thing. This program was a learning
 * experience above all else.
 *
 * This is on my GitHub, so because it's freely available, it's freely usable. If Elon Musk
 * wants to use my crappy program for something, by all means, he has the right. So do you.
 *
 */

#include "raylib.h"          // Good library. I suck at using it, but in more capable hands, it's pretty effective (see CAT & ONION)
#include "InternalLogic.cpp" // This is my pathetic attempt at OOP... Any internship scouts can contact me at fmislam.3105@gmail.com

int main(void) // Main LOOP, actually, but I'm not nearly code-savvy enough for it to matter...
{
    const int screenWidth = 1000; // Those with an HTML/CSS background will despise the fact that the window abnd its contents are based off pixel measurements instead of relative/absolute positioning
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Showcasing Dynamic Programming - Finding the least cost path using the bottom-up approach"); // Elaborated upon in the README.md file (Could never put my finger on why so many repos have that... always the most confusing ones to comprehend too...)

    const int gridRows = 10; // Technically variable dimensions for the randomized grid, but I wouldn't try it. It would likely break everything.
    const int gridColumns = 10;
    const int cellSize = 50; // Each cell is 50 x 50 pixels in area

    SetTargetFPS(60); // Guess what this does. Take a wild guess. You'd be astonished.

    InternalLogic intLo;      // Bringing in the InternalLogic class (they're good friends, although main is hesitant about InternalLogic's suggestions to take their relationship to "the next natural step" because she really isn't interested in a relationship for the time being)
    intLo.getRandomNumbers(); // This initializes the array with all the randomly generated numbers

    int rightWidth = screenWidth - (50 + gridColumns * cellSize);         // How much space between right margin and grid
    float buttonX = 50 + gridColumns * cellSize + (rightWidth - 200) / 2; // Where to put left-corner of button relative to horiztontal spacing

    Rectangle regenerate = {buttonX, 100, 200, 75}; // Button that specifies position THEN dimensions in parameters, also changes all values within the grid

    Rectangle solve = {buttonX, 400, 200, 75}; // Button that reveals the least cost path in a soft yellow, highlighting each cell from top to bottom

    while (!WindowShouldClose())
    {
        Vector2 current_mPos = GetMousePosition(); // Tracking your every movement 👁👁

        BeginDrawing();
        ClearBackground(MAROON); // "Why maroon?" I like it, leave me be.

        intLo.drawMainGrid(gridRows, gridColumns, cellSize); // Calls a function to draw the grid where all the magic happens

        intLo.drawButton(regenerate, "Regenerate Grid", WHITE); // Draws a button to pull off some randomly generated shenanigans (hee hee hee)

        intLo.drawButton(solve, "Solve Grid", WHITE); // Draws a button that when pressed, will reveal the least cost path from the top to the bottom of the grid, highlighting the cells along that path in a soft-yellow hue. Also has a 0.5% chance of deleting System32.

        // "It doesn't actually, right!?" You'll find out if you check out InternalLogic.cpp, but only after reading all of this file first.

        if (CheckCollisionPointRec(current_mPos, regenerate)) // You: "Ooo-la-la, event handling upon mouse interaction? My, oh my...""
        {
            intLo.drawButton(regenerate, "Regenerate Grid", LIGHTGRAY); // "It even rrecolors in response to hovering over the button! Is this some form of skullduggery?"

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // "WHAT HAPPENS IF I PRESS LEFT-CLICK WITH MY MOUSE!?!? I MUST KNOW!!!"
            {
                intLo.drawButton(regenerate, "Regenerate Grid", DARKGRAY);
                intLo.regenerateGrid(); // This will change every value in the grid to some other randomly generated value from 0-99 inclusive. Or the same number, but the chances of that are 1/100. Fun fact: The probability that randomly regenerating the grid yields the exact same grid as before is roughly (1/100)^100, which is essentially so close to zero that we may as well say it's as likely as Cynthia returning my phone calls.
            }
        }

        if (CheckCollisionPointRec(current_mPos, solve)) // Same old, same old. Let's just get a move on.
        {
            intLo.drawButton(solve, "Solve Grid", LIGHTGRAY); // But what's this? Looks like this button does something different! Woooooow...

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                intLo.drawButton(solve, "Solve Grid", DARKGRAY);
                intLo.solveGridFunction();                           // This actually identifies all the cells that are along the least cost path
                intLo.drawMainGrid(gridRows, gridColumns, cellSize); // With that info, each of the cells are highlighted with a soft yellow
            }
        }

        EndDrawing(); // This is all being processed and displayed at 60FPS, which is a real bummer for the little painter guy living inside your computer screen that has to draw all the assets to the display
    }

    CloseWindow(); // This is the only way to close the program. The window also doesn't resize. Bummer, huh?

    return 0; // Returns number of people who enjoyed that god-awful remake of The Crow
}
