// Alice Jiang
// March 23, 2017
// Exercise #2, Question 6
// This program stores input of a set of points in a vector using structure, and calculate the slope for any pair of points

#include <iostream>
#include <vector>   // call to compile

using namespace std;

struct Point    // structure to store x, y coordinates
{
    int x;
    int y;
};

int main()
{
    int n;  // variable for number of points inputed
    cout << "How many points? ";
    cin >> n;
    if (n <= 1)
        cout << "Has to be at least two points" << endl;
    else
    {
        // create a vector of structures
        vector <Point> grid(n); // create a vector that will hold n (input) number of points

        for (int i = 0; i < grid.size(); i++)
        {
            cout << "Input point #" << i+1 << endl; // stores inputs for x, y coordinates of each point
            cin >> grid[i].x;
            cin >> grid[i].y;
        }

        int a, b;  // variables for the pair of point that will form the line segment
        while (true)
        {
            cout << "\nSelect two points" << endl;
            cin >> a;   // first point of the segment, point # a
            if (a == 0)
            {
                cout << "Bye!" << endl; // program ends when 0 is inputed
                break;
            }
            else if (a < 0 || a > n)    // the point # is not valid
            {
                cout << "Not a valid input!" << endl;
            }
            else
            {
                cin >> b;   // second point of the segment, point # b
                if (b == 0)
                {
                    cout << "Bye!" << endl;
                    break;
                }
                else if (a == b)    // the same point cannot form a valid line segment
                {
                    cout << "Can't be the same point!" << endl;
                }
                else if (b < 0 || b > n)
                {
                    cout << "Not a valid input!" << endl;
                }
                else
                {
                    // calculate slope of the line segment
                    // check if denominator (x2-x1) is valid (none zero)
                    if (grid[b-1].x-grid[a-1].x == 0)
                        cout << "The slope of the line segment from (" << grid[a-1].x << "," << grid[a-1].y << ") to (" << grid[b-1].x << "," << grid[b-1].y << ") is undefined " << endl;  // denominator cannot be zero
                    else if (grid[b-1].y-grid[a-1].y == 0)
                        cout << "The slope of the line segment from (" << grid[a-1].x << "," << grid[a-1].y << ") to (" << grid[b-1].x << "," << grid[b-1].y << ") is 0 " << endl;  // slope is zero when numerator is zero, given a valid denominator
                    else
                    {
                        // slope = (y2-y1)/(x2-x1)
                        cout.setf(ios::fixed);  // fixed number of decimal places in output
                        cout.precision(1);  // rounds to one decimal places
                        double slope = double(grid[b-1].y-grid[a-1].y)/double (grid[b-1].x-grid[a-1].x);
                        //                                                           (x1, y1)                                           (x2, y2)
                        cout << "The slope of the line segment from (" << grid[a-1].x << "," << grid[a-1].y << ") to (" << grid[b-1].x << "," << grid[b-1].y << ") is " << slope << endl;
                    }
                }
            }
        }
    }
    return 0;
}
