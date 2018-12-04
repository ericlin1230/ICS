// April 3, 2017
// Alice Jiang
// Minesweeper
/* This program determines the result of clicking on a square during a Minesweeper game.
   Input file (DATA.txt) will contain 21 lines of data. The first 16 lines will contain thrity characters each. Each character will be either an 'X',
   that represents a square with a mine or period (.) that reps a square without a mine.
   The last five lines will each contain 2 integers, r and c, that represent the row and column of the square that is clicked.
   The top left square of the minefield is assumed to be at row one and column one.
   The output to the screen will contain the results of clicking on the square.
   Each click, from the input file, is assumed to be the first click of a new game (game board won't change) */
#include <iostream>
#include <fstream>  // needed to compile file
#include <string>   // for string stream
#include <sstream>
#include <cstdlib>  // for atoi

// 16 x 30 board
using namespace std;

int mine (string x [16][30], int a, int b)    // recursive function to check how many mine surrounds a safe square or empty squares
{
    // a index position of row
    // b index position of column
    int n = 0;  // variable to store number of mines around that square
    for (int r = a-1; r <= a+1; r++)        // checks all 9 squares, 8 surrounding the middle one
    {
        for (int c = b-1; c <= b+1; c++)
        {
            if ((r >= 0 && r < 16) && (c >= 0 && c < 30) && x [r][c] == "X")    // check the surrounding 8 squares (within the boundary of the board)
            {
                n++;    // # of mines surrounding the square adds one
            }
        }
    }
    return n;
}

bool bound (int a, int b)   // checks if the square has valid coordinate (within the boundary)
{
    if (a >= 0 && a < 16 && b >= 0 || b < 30)   // within 16 x 30 board or index position (0-15) and (0-29)
        return true;    // within boundary
}

/*void print (int y [16][30])           // prints the board with number of mines surrounding labeled (9 means unchecked, 0 means no mine surrounding...)
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            cout << y [i][j] << " ";
        }
        cout << endl;
    }
}*/

//              board          row    column  stores number of mines surrounding a square (initalized to 9)
void space (string x [16][30], int a, int b, int y[16][30]) // recursive function that reveals spaces
{
    // center square is within bound and empty, unchecked, but has mine surrounding it
    if (bound (a,b) && x [a][b] == "." && y [a][b] == 9 && mine (x, a, b) != 0)
    {
        y [a][b] = mine (x, a, b);  // stores the number of mines surrounding this square, neighbouring squares not further revealed
    }
    // uses recursive - for center square that is within bound and empty, unchecked, and has no mine surrounding it
    else if (bound (a, b) && x [a][b] == "." && y [a][b] == 9 && mine (x, a, b) == 0)
    {
        y [a][b] = 0;   // this center square is marked as empty
        if (a == 0 && b == 0)       // if the center square is at the upperleft corner, only needs to check 3 neighbouring squares (expand)
        {
            if (y [a][b+1] == 9)
                space (x, a, b+1, y);
            if (y [a+1] [b] == 9)
                space (x, a+1, b, y);
            if (y [a+1] [b+1] == 9)
                space (x, a+1, b+1, y);
        }
        else if (a == 0 && b == 29) // at the upperright corner, only needs to check 3 neighbouring squares
        {
            if (y [a][b-1] == 9)
                space (x, a, b-1, y);
            if (y [a+1] [b] == 9)
                space (x, a+1, b, y);
            if (y [a+1] [b-1] == 9)
                space (x, a+1, b-1, y);
        }
        else if (a == 15 && b == 0) // at the lowerleft corner, check 3 squares
        {
            if (y [a][b+1] == 9)
                space (x, a, b+1, y);
            if (y [a-1] [b] == 9)
                space (x, a-1, b, y);
            if (y [a-1] [b+1] == 9)
                space (x, a-1, b+1, y);
        }
        else if (a == 15 && b == 29)   // at the lowerright corner, check 3 squares
        {
            if (y [a][b-1] == 9)
                space (x, a, b-1, y);
            if (y [a+1] [b] == 9)
                space (x, a+1, b, y);
            if (y [a+1] [b-1] == 9)
                space (x, a+1, b-1, y);
        }
        else if (a > 0 && a < 15 && b == 29)   // along the right most column, but not the two corners, check 5 neighbouring squares
        {
            if (y [a][b-1] == 9)
                space (x, a, b-1, y);
            if (y [a+1] [b] == 9)
                space (x, a+1, b, y);
            if (y [a+1] [b-1] == 9)
                space (x, a+1, b-1, y);
            if (y [a-1] [b] == 9)
                space (x, a-1, b, y);
            if (y [a-1] [b-1] == 9)
                space (x, a-1, b-1, y);
        }
        else if (a > 0 && a < 15 && b == 0)     // along the leftmost column, but not the two corners, 5 neighbouring
        {
            if (y [a][b+1] == 9)
                space (x, a, b+1, y);
            if (y [a+1] [b] == 9)
                space (x, a+1, b, y);
            if (y [a+1] [b+1] == 9)
                space (x, a+1, b+1, y);
            if (y [a-1] [b] == 9)
                space (x, a-1, b, y);
            if (y [a-1] [b+1] == 9)
                space (x, a-1, b+1, y);
        }
        else if (a == 0 && b > 0 && b < 29)    // along the top row but not the two corners, 5 neighbouring
        {
            if (y [a][b-1] == 9)
                space (x, a, b-1, y);
            if (y [a] [b+1] == 9)
                space (x, a, b+1, y);
            if (y [a+1] [b-1] == 9)
                space (x, a+1, b-1, y);
            if (y [a+1] [b] == 9)
                space (x, a+1, b, y);
            if (y [a+1] [b+1] == 9)
                space (x, a+1, b+1, y);
        }
        else if (a == 15 && b > 0 && b < 29)   // along the bottom row but not the two corners, 5 neighbouring
        {
            if (y [a][b-1] == 9)
                space (x, a, b-1, y);
            if (y [a] [b+1] == 9)
                space (x, a, b+1, y);
            if (y [a-1] [b-1] == 9)
                space (x, a-1, b-1, y);
            if (y [a-1] [b] == 9)
                space (x, a-1, b, y);
            if (y [a-1] [b+1] == 9)
                space (x, a-1, b+1, y);
        }
        else    // with 8 neighbouring squares
        {
            if (y [a-1][b-1] == 9)
                space (x, a-1, b-1, y);
            if (y [a-1][b] == 9)
                space (x, a-1, b, y);
            if (y [a-1][b+1] == 9)
                space (x, a-1, b+1, y);
            if (y [a][b-1] == 9)
                space (x, a, b-1, y);
            if (y [a][b+1] == 9)
                space (x, a, b+1, y);
            if (y [a+1][b-1] == 9)
                space (x, a+1, b-1, y);
            if (y [a+1][b] == 9)
                space (x, a+1, b, y);
            if (y [a+1][b+1] == 9)
                space (x, a+1, b+1, y);
        }
        //print (y);
        //cout << endl;
    }
}

int main()
{
    string arr [16] [30]; // declares string array with 16 rows and 30 columns to store the board results from the file
    int ARR [5][2]; // declares integer array with 5 rows and 2 columns to store the position of the square clicked

    // takes in the iput textfile
    ifstream InFile ("DATA.txt");  // opens the text file
    if (InFile.fail())
    {
        cout << "File: DATA.txt is not found" << endl;
    }
    else
    {
        string line;    // varaible to store each line of the file
        int row = 0;
        while (getline(InFile, line))   // reads each line of the file
        {
            string buf; // buffer string
            stringstream s(line);   // insert the line(string) into a stream
            int field = 0;
            s << line;  // put the line into the stream
            string input;   // string for the input (X or .)
            if (row < 16)   // stores the first 16 lines of file into string array
            {
                getline(s, input);  // get the whole line of the result
                for (int i = 0 ; i < input.length(); i++)   // stores each character of the line to the array
                {
                    arr [row][i] = input.at(i);   // get each character of the line
                }
            }
            else
            {
                while (getline(s, input, ' '))  // store the last five lines of square position to integer array, field separated by space
                {
                    ARR [row-16][field] = atoi(input.c_str());  // converts string into integer
                    field++;    // column index position adds one
                }
            }
            row++;  // row index position adds one
        }
        cout << "All Done" << endl;
    }

    // prints out the floorplan
    for (int r = 0; r < 16; r++)
    {

        for (int c = 0; c < 30; c++)
        {
            cout << arr [r][c];
        }
        cout << endl;
    }

    // prints out the coordinate of the squares clicked
    for (int r = 0; r < 5; r++)
    {
        for (int c = 0; c < 2; c++)
        {
            cout << ARR [r][c] << " ";
        }
        cout << endl;
    }

    // output of the clicking results
    for (int r = 0; r < 5; r++)
    {
        if (arr [ARR[r][0]-1] [ARR[r][1]-1] == "X") // the square clicked has a mine
        {
            cout << "MINE at (" << ARR[r][0] << "," << ARR[r][1] << ") - YOU LOSE" << endl;
        }
        else   // checks for surrounding of the square
        {
            if (mine (arr, ARR[r][0]-1, ARR[r][1]-1) != 0)  // the square has mines surrounding it
                cout << "NO MINE at (" << ARR[r][0] << "," << ARR[r][1] << ") - " << mine (arr,ARR[r][0]-1,ARR[r][1]-1) << " SURROUNDING IT" << endl;
            else    // checks the number of squares revealed from this empty square
            {
                int reveal = 0;    // variable for # of spaces revealed
                int space_check [16][30];   // array to store number of mines surrounding the squares to account if square has been checked, used in space function (reveal squares)
                for (int a = 0; a < 16; a++)
                {
                    for (int b = 0 ; b < 30; b++)
                    {
                        space_check[a][b] = 9;   // all initalize to be 9 as unchecked
                    }
                }
                space (arr, ARR[r][0]-1, ARR[r][1]-1, space_check);    // calls for the recursive reveal square function
                for (int i = 0; i < 16; i++)
                {
                    for (int j = 0 ; j < 30; j++)
                    {
                        if (space_check [i][j] != 9)   // if the square is checked/revealed (empty or has mine surrounding it)
                        {
                            reveal++;   // number of squares revealed increses
                        }
                    }
                }
                cout << "NO MINE at (" << ARR[r][0] << "," << ARR[r][1] << ") - " << reveal << " SQUARES REVEALED" << endl;
            }
        }
    }
    return 0;
}
