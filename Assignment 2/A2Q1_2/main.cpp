// Alice Jiang
// March 22, 2017
// Exercise #2, Question 3
// This program uses recursive boolean method to test if a string(word) is a palindrome

#include <iostream>

using namespace std;

// This function works by comparing first and last letter of each string, moving inward towards center
/* e.g. for word "racecar", first check r and r
   then check "aceca"
   then "cec" */

bool palindrome (string s)  // recursive boolean method that returns true if the string s is a palindrome
{
    int n = 0;              // no outer pair letters removed, checks the whole string passed as parameter
    if (s.length() == 1)    // only one letter
        return false;
    else if (s.at(0) == s.at (s.length()-1)) // tests first letter and last letter - same
    {
        n++;    // shortens string by one pair, remove the outermost letters
        if (s.length()-n*2 == 1)      // if only the middle letter of this odd-number-letter word hasn't been checked
        {
            return true;
        }
        else if (s.length()-n*2 == 0) // if the two centermost letters of this even-number-letter word are checked
        {
            return true;
        }
        else
        {
            return palindrome (s.substr(n, s.length()-n*2));    // decrease size of the string by taking out the outer two letters and check again
        }
    }
    else
        return false;
}

int main()
{
    string input;      // variable for the inputed word to be tested
    cout << "Enter a word: ";
    cin >> input;

    if (input.length() == 1)
        cout << "Not a palindrome, just a one letter word" << endl;
    else if (palindrome (input))
        cout << "True! A palindrome!" << endl;  // the word is a palindrome
    else
        cout << "False!" << endl;   // the word is not a palindrome

    return 0;
}
