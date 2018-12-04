// April 10, 2017
// Alice Jiang
/* This program reads a textfile containing the floor plan of a house with rooms separated by walls.
   "I" means walls and "." means room space. Each character occupies one square meter. The objective
   is to determine how many rooms will have floorings installed given a limited supply of hardwood (going
   from largest room and so on). Program outputs the number of rooms with hardwood installed and the square meters
   of floorings left over. */
/* first line of the file is the number of square meters of flooring
   second line givers r (1-25) that represents the rows in the grid
   third line gives c (1-25) that represents number of columns of the grid
   remaining r lines gives c characters of floor plan */

#include <iostream>
#include <fstream>  // needed to compile file;
#include <string>   // for string stream
#include <sstream>
#include <cstdlib>  // for atoi
#include <vector>

using namespace std;

bool bound (int a, int b, int x, int y)     // this function checks if the coordinate of the square is within boundary of the floorplan
{
    if (a >= 0 && a < x && b >= 0 && b < y)     // a is for row and b is for column
        return true;        // within bound
    else
        return false;
}

/*void print (vector <vector <int> > z)       // this function prints out the check vector (initialized to be 9 (unchecked), 1- wall, 0- empty space)
{
    for (int i = 0; i < z.size(); i++)
    {
        for (int j = 0; j < z[i].size(); j++)
        {
            cout << z [i][j] << " ";
        }
        cout << endl;
    }
}*/

// this recursive function expands until the room is revealed         check vector (9, 1, 0)
void room (vector <vector <string> > &g, int x, int y, int a, int b, vector <vector <int> > &z)   // pass reference for vectors
{ //     floorplan vector ("I" or ",")    row  column   total (max) number of row and column
    if (bound (x, y, a, b) == false)
    {
        return;     // not recursed if out of bound
    }
    else if (z [x][y] != 9)     // 9 means unchecked
    {
        return;     // not recursed if the square has been checked
    }
    else if (g [x][y] == "I")
    {
        z [x][y] = 1;           // check function marks the wall as 1
        return;                 // not recursed if the square is a wall
    }
    else        // must then be within bound, unchecked, and an empty space
    {
        z [x][y] = 0;   // now checked and the square is marked as empty room space (0)
        // calls the four neighbouring functions to recurse
        room (g, x-1, y, a, b, z);    // square right above
        room (g, x, y-1, a, b, z);    // square to the left
        room (g, x, y+1, a, b, z);    // square to the right
        room (g, x+1, y, a, b, z);    // square right below
        //print (z);
        //cout << endl;
    }
}

void Sort (vector <int> &s)  // sorts the room size array from greatest size to lowest size
{
    // finds the biggest number and moves it to the top of the vector
    for (int j = 0; j < s.size()-1; j++)
    {
        int Max = s [j];  // initialize to be the greatest number
        int pos = j;      // the position of the current maximum
        bool Move = false;  // assumes no need to swap
        for (int i = j+1; i < s.size(); i++)    // for all other elements after
        {
            if (s [i] > Max)    // if the current element is greater, swap them
            {
                Max = s [i];
                pos = i;
                Move = true;    // a swap is necessary
            }
        }
        if (Move)       // to swap and move the max to the beginning of the vector
        {
            int temp = s [j];
            s [j] = s [pos];
            s [pos] = temp;
        }
    }
}

int main()
{
    int wood = 0;   // variable to store the supply of hardwood floorings available
    int r = 0;  // variable to store the rows of the grid
    int c = 0;  // variable to store the columns of the grid
    int roomspace = 0; // variable to store the area of total empty room space
    vector <vector <string> > grid; // declares 2D vector to store the floorplan

    // stores file input
    ifstream InFile ("floorplan.txt");  // opens the text file for the floor plan
    if (InFile.fail())
    {
        cout << "File: floorplan.txt is not found" << endl;
    }
    else
    {
        string line;    // varaible to store each line of the file
        int n = 0;      // variable to keep track of lines in the file
        while (getline (InFile, line))  // reads each line of the file
        {
            n++;    // reading the nth line of the file
            if (n == 1) // first line
                wood = atoi (line.c_str()); // stores information about supply of hardwood
            else if (n == 2)
                r = atoi (line.c_str());    // stores the number of rows in the grid
            else if (n == 3)
                c = atoi (line.c_str());    // stores number of columns in the grid
            else
            {
                grid.resize (r, vector <string> (c)); // resize the vector to r row and c columns
                // for the rest of the file - the floorplan
                string buf; // buffer string
                stringstream s(line);   // insert the line(string) into a stream
                int field = 0;
                s << line;  // put the line into the stream
                string input;   // string for the input (I or .)
                getline(s, input);  // get the whole line of the result
                for (int j = 0; j < grid[n-4].size(); j++)  // stored into the index position of (n-4), since the floorplan starts on the 4th line of the file
                {
                    grid [n-4][j] = input.at(j);    // stores each character of the line into the column of that row
                }
            }
        }
        cout << "All Done" << endl;     // input file is read and data stored
        cout << wood << endl;
        cout << r << "\n" << c << endl;
        // prints out the floorplan
        for (int a = 0; a < grid.size(); a++)
        {
            for (int b = 0; b < grid[a].size(); b++)
            {
                cout << grid [a][b];
                if (grid [a][b] == ".")
                    roomspace++;        // if it is an empty room space, total available roomspace adds one
            }
            cout << endl;
        }
        //cout << roomspace << endl;

        vector <vector <int> > checked;   // declares integer vector to keep track if the square has been checked
        checked.resize (r, vector <int> (c, 9));   // initializes all to be 9 (unchecked) - same dimension as the floorplan vector (grid)

        bool vacant = false;    // variable to find if a square is a room space, initialized to be false
        int c_x = 0;    // initialize row coordinate of square to be checked in the floorplan as empty room
        int c_y = 0;    // initialize column coordinate of square to be checked in the floorplan as empty room
        bool reached_end = false;   // variable to keep track if all the empty room space of the room have been checked - all rooms are revealed
        vector <int> SIZE;      // vector to store the size of rooms revealed (incremental of one room, two rooms...)
        int n_of_room = 0;      // vector to store the number of rooms paved

        // uses recursive function to find each room size (incremented total)
        while (true)
        {
            int room_size = 0;  // clears to be zero for each new room size
            for (int i = 0; i < r; i++)         // runs through the floorplan vector (grid) to find the next empty room space that is unchecked by recursive by rows
            {
                for (int j = 0; j < c; j++)
                {
                    if (grid [i][j] == "." && checked [i][j] == 9 && vacant == false)   // the first empty roomspace and unchecked
                    {
                        c_x = i;        // stores its row index position
                        c_y = j;        // stores its column index position
                        vacant = true;  // only needs this first square marked as found
                    }
                }
            }
            vacant = false;     // marked as unfound for the next room
            room (grid, c_x, c_y, r, c, checked);   // calls recursive function to expand one room
            for (int i = 0; i < r; i++)         // finds the room size by counting its empty spaces
            {
                for (int j = 0; j < c; j++)
                {
                    if (checked [i][j] == 0)    // empty space is marked as 0
                    {
                        room_size++;    // room size adds one (this is the total amount of roomsize, could be of one room, two rooms...)
                    }
                }
            }
            SIZE.push_back(room_size);  // stores this size to the end of size vector
            if (room_size == roomspace) // all rooms are revealed when the total roomsize added equals the total roomsize of the floorplan
                break;
        }

        vector <int> final_size (SIZE.size());  // declares the vector that stores size of each individual room
        // stores the size of each individual room
        for (int i = 0; i < SIZE.size(); i++)
        {
            final_size[0] = SIZE.front();   // the size of the first room equals the first room size of the previous size array (because only one room)
            if (i > 0)  // for other rooms
                final_size[i] = SIZE[i]-SIZE[i-1];  // the size of the specific room is the different between total after this room and the previous room in the previous size array
        }
        Sort (final_size);  // sorts this size vector for each room in descending order
        bool enough = true; // variable to keep track if there is enough floorings for the next largest room
        // finds the remaining flooring supplies left
        for (int i = 0; i < final_size.size(); i++)
        {
            //cout << final_size[i] << endl;
            if (wood - final_size[i] >= 0 && enough)      // when there is enough supply to pave this room
            {
                wood = wood - final_size[i];    // available wood supply decreases
                n_of_room++;    // room paved adds one
            }
            else
            {
                enough = false; // not enough floorings for the next largest room, therefore stops because cannot skip over any room
            }
        }
        cout << "\n" << n_of_room << " rooms, " << wood << " square metre(s) left over " << endl;   // outputs the number of rooms paved and amounts of supply left over
    }
    return 0;
}
