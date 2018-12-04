// Alice Jiang
// March 22, 2017
// Exercise #2, Question 4
/* This program uses recursive function to check if it is possible to purchase a certain amount of McNuggets when only
   combinations of 6, 9, and 20 packs of McNuggets are available. */

//buyable(int n) that returns true if n is buyable.
//e.g. buyable(15) is true, buyable(11) is false.
#include <iostream>

using namespace std;

bool buyable (int n)    // recursive function that returns true if the # of McNuggets is buyable; available pack size are 6, 9, 20 nuggets
{
    if (n == 0)         // no remainder left all nuggets packed (buyable)
        return true;
    else if (n < 6)     // remainder less than 6 (smallest pack size) (not buyable)
        return false;
    if (n%6 == 0 || n%9 == 0 || n%20 == 0)  // divisible by the pack size (buyable)
        return true;
    // More complicated scenarios
    if (n%3 == 0)   // when McNugget size is divisible by 3 - it is also divisible by 6 and 9
    {
        if (n >= 6)               // pack from the smallest size up (6, 9, then 20)
            return buyable (n-6); // amount of McNuggets still needed reduced
        else if (n >= 9)
            return buyable (n-9);
        else if (n >= 20)
            return buyable (n-20);
    }
    else            // not divisible by 3 - not completely divisible by 6 and 9
    {
        if (n >= 20)                // pack from bigger size down (20, 9, then 6)
            return buyable (n-20);
        else if (n >= 9)
            return buyable (n-9);
        else if (n >= 6)
            return buyable (n-6);
    }
}

int main()
{
    int m;          // variable for # of McNuggets wanted
    cout << "Amount of McNuggets wanted: ";
    cin >> m;
    if (m <= 0)
        cout << "Needs to be a positive amount!" << endl;
    else
    {
        if (buyable(m))     // can be made using packs of 6, 9, and 20
            cout << "Buyable!" << endl;
        else
            cout << "Sorry, this amount is not buyable" << endl;
    }
    return 0;
}
