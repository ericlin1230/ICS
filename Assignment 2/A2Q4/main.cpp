// Alice Jiang
// March 27, 2017
/* This program reads a text file and writes an edited version of the file. The output file will contain the same
   text but each line is restrained by a user specified maximum length. */

#include <iostream>
#include <vector>
#include <fstream>  // compile file
#include <string>   // string stream
#include <sstream>

using namespace std;

int main()
{
    vector <string> text;   // create a vector of strings to store the text from the input file
    int length; // variable to store the maximum length of characters in each line

    // read input file
    ifstream InFile ("intext.txt"); // opens textfile intext.txt
    if (InFile.fail())
    {
        cout << "File: intext.txt is not found" << endl;
    }
    else
    {
        string inputStr;    // string for each line of the file
        while (getline(InFile,inputStr))
        {
            // process each line of the file with fields separated by spaces
            string buf;  // buffer string
            stringstream s(inputStr);  // insert the string into a stream
            s << inputStr; // put the line into the stream
            string input;  // string for the input (each word)
            while (getline(s, input, ' '))  // each field is separated by space
            {
                text.push_back(input);  // add the new word to the end of the vector
            }
        }
        cout << "Input file is ready" << endl;
    }

    cout << "Maximum length: "; // obtains user specified maximum length
    cin >> length;
    int len = 0;    // varaible keeps track of number of characters in a line

    // outputs file
    ofstream OutFile ("outtext.txt");   // saves the edited version to outtext.txt
    if (OutFile.fail())
    {
        cout << "File: outtext.txt cannot be created" << endl;
    }
    else
    {
        for (int i = 0; i < text.size(); i++)   // goes through all elements of the vector (words of the text)
        {
            if (len + text[i].length() > length)    // when the addition of the current word will exceed the maximum length
            {
                OutFile << endl;   // the word will be added to the next line
                len = text[i].length() + 1;  // the characters taken of the new line is the number of letters of the current word plus one space
            }
            else
            {
                len = len + text[i].length() + 1;   // word is added to the current line (amount of characters taken includes # of letters of the word and one space)
            }
            OutFile << text[i] << " ";  // prints out the word on the line
        }
    }
    OutFile.close(); // close the file when done
    cout << "New file is saved!" << endl;
    return 0;
}
