// March. 27, 2017
// program manages a class of students and keeps track of their marks. User can select the 7 menu options.
// class of student will be a vector of student structures
// course structure is within student structure

#include <iostream>
#include <iomanip>
#include <cstdlib>  // for atoi
#include <vector>
#include <fstream> // this line is needed to compile (file)
#include <sstream> // needed for string streams


using namespace std;

struct Course   // structure for each course
{
    string course; // course name
    int mark;      // mark associated with this course
};

struct Student  // struture for each student
{
    string name;     // student name
    int ID;          // student ID
    int n_of_course; // number of courses taking
    vector <Course> lesson;   // course is a structure within this student structure
};

vector <Student> student;   // declares vector for student structure

int length (int x)  // function that finds the length or number of characters for ID, # of courses, and mark (integer type)
{
    int n_length = 0;   // variable to store the integer length
    while (true)
    {
        if (x/10 > 0)   // if the number is divisible by 10
        {
            n_length++;  // length plus one
            x = x/10;    // reduce the number by one place value
        }
        if (x < 10)      // if the number is reduced to a single digit
        {
            n_length++;  // add the last place value to the integer length
            break;
        }
    }
    return n_length;
}

int main()
{
    int n;   // variable to accept menu option number from user
    int id;  // variable to store the ID of the student to be changed or deleted
    bool search_student = false;    // initialize student is not yet found in the class
    int pos;    // variable to store position of the student on the list/vector

    // variable for chekcing valid input
    int id_id;  // stores input of ID
    int n_n;    // stores input of # of courses
    int mark_mark;  // variable to store input for mark
    while (true)
    {
        // 7 Menu Options
        cout << "1) Open a class from a file" << endl;
        cout << "2) Add a new student " << endl;
        cout << "3) Change existing student " << endl;
        cout << "4) Delete a student " << endl;
        cout << "5) Print a class list (include the class average) " << endl;
        cout << "6) Save the class to a file " << endl;
        cout << "7) Quit " << endl;

        cout << "\nSelect the above options: ";
        cin >> n;   // obtains the option user wants to use

        if (n == 7) // program ends
            break;
        else if (n == 1)    // adds a class list from a file into the existing student vector
        {
            string in_filename;  // variable to store the inputing file name
            cout << "Input filename: " << endl;
            cin >> in_filename;
            ifstream InFile(in_filename.c_str()); // convert the filename to a C string

            if (InFile.fail())  // file fails to open
            {
                cout << "File: " << in_filename << " not found" << endl;
            }
            else    // file opens
            {
                int line = 0;   // variable for number of lines in the file read, will be the same as number of students on the list
                string inputStr;    // variable to store one line of the file
                int start_s = student.size();   // varaible to store number of existing students in the vector before adding the list
                // first new student will be added to this index position
                // read the file once first
                while (getline(InFile,inputStr))
                {
                    line++;     // counts the number of lines/total numbere of new students to be added
                }
                student.resize(student.size()+line);  // resize the student vector to provide space for these new students
                line = 0;   // clears number of lines read before reading the file again
                ifstream InFile(in_filename.c_str()); // open text file again
                // read textfile for the second time
                while (getline(InFile,inputStr))
                {
                    // process a string as a stream
                    string buf; // a buffer string
                    stringstream s(inputStr); // insert the string into a stream
                    s << inputStr; // put the line into the stream
                    string input;  // variable to store each field of the string (e.g. name, ID, etc.)
                    int field = 0;  // varaible to store number of fields in one line of string
                    while (getline(s, input, ',')) // gets a string from the stream up the next comma (comma is used to separate the field)
                    {
                        field++;      // number of fields read add one
                        if (field == 1)     // first field is the name of the student
                            student[start_s + line].name = input;   // add the name into the vector
                        if (field == 2)     // second field is the ID
                        {
                            student[start_s + line].ID = atoi(input.c_str());     // convert string numbers into integer and stores ID
                        }
                        if (field == 3)     // third field is the number of courses taken
                        {
                            student[start_s + line].n_of_course = atoi(input.c_str());
                        }
                        // after # of courses taken is obtained
                        if (field > 3 && field%2 == 0)  // an even field number (e.g. 4) means the data is for course name
                        {
                            Course tempp;   // temporary variable to hold the data for each course vector
                            tempp.course = input;   // stores course name
                            student[start_s+line].lesson.push_back(tempp);  // push the course name into the course vector, leaving space for mark already
                        }
                        if (field > 3 && field%2 == 1)  // an odd field number means the data is the mark for the newly created course
                        {
                            student[start_s+line].lesson[student[start_s+line].lesson.size()-1].mark = atoi(input.c_str());
                            // space for mark is already created from push_back(tempp), add the mark into the newest course vector
                        }
                    }
                    line++; // one more student
                }
                cout << "ALL DONE"  << endl;
            }
        }
        else if (n == 2)    // adds a new student
        {
            cout << "Input name, ID, number of courses, the course name(s), and the corresponding mark: " << endl;
            // add elements into the student vector
            Student temp;       // variable to hold the student data
            cin.ignore();       // clears previous inputs
            getline (cin, temp.name);   // accepts inputs for first name and last name
            while (true)    // checks for correct ID
            {
                cin >> id_id;
                if (id_id >= 0) // ID has to be a positive number
                {
                    temp.ID = id_id;    // stores into the temporary vector
                    break;
                }
                else
                {
                    cout << "Not a valid input, try again!" << endl;
                }
            }
            while (true)    // checks for correct # of courses input
            {
                cin >> n_n;
                if (n_n > 0)    // has to be an integer above zero
                {
                    temp.n_of_course = n_n;
                    break;
                }
                else
                {
                    cout << "Not a valid input, try again!" << endl;
                }
            }
            int counter = temp.n_of_course; // varaible for the number of courses this student takes
            while (counter > 0)  // adds course and mark into the course vector for the # of courses
            {
                Course tempo;  // temporary variable to hold the data for each course
                cin >> tempo.course;
                while (true)
                {
                    cin >> mark_mark;
                    if (mark_mark >= 0 && mark_mark <= 100) // valid and stored if mark is including and between zero and 100
                    {
                        tempo.mark = mark_mark;
                        break;
                    }
                    else
                    {
                        cout << "Not a valid input, try again!" << endl;
                    }
                }
                temp.lesson.push_back (tempo);  // push the temporary course data structure onto the vector
                counter--; // repeat this process for each course the student takes
            }
            student.push_back(temp); // push the temporary student data structure onto the vector
            cout << "Student is added!" << endl;
        }
        else if (n == 3)  // change information about existing student
        {
            cout << "Enter the ID of the student you want to change information of: ";
            cin >> id;
            for (int i = 0; i < student.size(); i++)    // search through the student vector
            {
                if (student[i].ID == id)
                {
                    search_student = true;  // id found if student is in the list
                    pos = i;    // stores index position of the student
                }
            }
            if (search_student)
            {
                string change;    // variable for the information to be changed
                string NAME, COURSE;  // variable to store the new student name, course name
                int N, MARK; // variable to store the new number of courses, mark

                // for information change in course name or mark
                bool search_course = false; // the course is not yet found
                int POS;    // varaible to store the index position of the course in the course vector
                string C_check;   // existing course name

                cout << "What information would you like to change? (name, # of courses, course name, or mark) " << endl;
                cin.ignore();
                getline (cin, change);  // obtain the type of information to be changed
                if (change == "name")   // change the student name
                {
                    cout << "Input the new name: ";
                    getline (cin,NAME);
                    student[pos].name = NAME;     // update that student's name
                    cout << "Information Updated! " << endl;
                }
                else if (change == "# of courses")  // change the number of couses taken
                {
                    cout << "Input the new number: ";
                    while (true)    // check for valid input, # of courses has to be greater than zero
                    {
                        cin >> N;
                        if (N > 0)
                        {
                            student[pos].n_of_course = N;
                            cout << "Information Updated! " << endl;
                            break;
                        }
                        else
                        {
                            cout << "Not a valid input!" << endl;
                        }
                    }
                    if (student[pos].lesson.size() < N)
                    {
                        if (N-student[pos].lesson.size() == 1)
                            cout << "Please remember to add " << N-student[pos].lesson.size() << " course to match this updated number!" << endl;
                        else
                            cout << "Please remember to add " << N-student[pos].lesson.size() << " courses to match this updated number!" << endl;
                    }
                    else if (student[pos].lesson.size() > N)
                    {
                        if (student[pos].lesson.size()-N == 1)
                            cout << "Please remember to remove " << student[pos].lesson.size()-N << " course to match this updated number!" << endl;
                        else
                            cout << "Please remember to remove " << student[pos].lesson.size()-N << " courses to match this updated number!" << endl;
                    }
                }
                else if (change == "course name")
                {
                    cout << "Enter the existing course name you would like to change: ";
                    cin >> C_check;
                    for (int i = 0; i < student[pos].lesson.size(); i++)
                    {
                        if (student[pos].lesson[i].course == C_check)      // searches for that course name in the course vector
                        {
                            search_course = true;   // course name is found
                            POS = i;    // stores the index position of this course
                        }
                    }
                    if (search_course)
                    {
                        cout << "What would you like to change the course name to: ";
                        cin >> COURSE;
                        student[pos].lesson[POS].course = COURSE;   // update the new course name
                        cout << "Information Updated! " << endl;
                    }
                    else
                    {
                        cout << "Sorry, course not found!" << endl;
                    }
                }
                else if (change == "mark")  // change the mark
                {
                    cout << "What the course name this mark is associated with: ";
                    cin >> C_check;
                    for (int i = 0; i < student[pos].lesson.size(); i++)    // searches for the course the mark is associated with
                    {
                        if (C_check == student[pos].lesson[i].course)
                        {
                            POS = i;                // store the index position of the course
                            search_course = true;
                        }
                    }
                    if (search_course)
                    {
                        cout << "What would you like to change the mark for this course to: ";
                        while (true)    // checks for valid input, mark has to be including and between zero and 100
                        {
                            cin >> MARK;
                            if (MARK >= 0 && MARK <= 100)
                            {
                                student[pos].lesson[POS].mark = MARK;       // update the mark associated with that course
                                cout << "Information Updated! " << endl;
                                break;
                            }
                            else
                            {
                                cout << "Not a valid input!" << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "Sorry, course not found!" << endl;
                    }
                }
                search_student = false;     // student is not yet found -> for the next change
            }
            else
            {
                cout << "Student NOT found!" << endl;   // no matching ID found
            }
        }
        else if (n == 4)  // delete a student
        {
            cout << "Enter the ID of the student you want to delete: ";
            cin >> id;
            for (int i = 0; i < student.size(); i++)
            {
                if (student[i].ID == id)
                {
                    search_student = true;            // found if student is in the list
                    student.erase(student.begin()+i); // removes the sutdent at the ith index position
                }
            }
            if (search_student) // student is found
            {
                cout << "Student of that ID is removed!" << endl;
                search_student = false;     // reset to not found
            }
            else
            {
                cout << "Student NOT found!" << endl;
            }
        }
        else if (n == 5)    // prints the class list and the class average
        {
            int sum = 0;    // variable to store sum of marks in all courses
            int number = 0; // variable to store the number of courses
            double average; // variable for class average
            // preset the # of characters for name, ID, # of courses, course, mark
            int l_name = 4;
            int l_id = 2;
            int l_n = 12;
            int l_course = 6;
            int l_mark = 4;
            // variable to store the highest number of characters
            // used when setting table width
            for (int r = 0; r < student.size(); r++)    // goes through the student vector
            {
                if (student[r].name.length() > l_name)  // if the characters of the student name is longer than the current length for name
                {
                    l_name = student[r].name.length(); // becomes the new longest name
                }
                int a = length(student[r].ID);  // variable that stores the length or # of digits of the ID, calls the length function
                if (a > l_id)     // when this new length is longer than the stored length, it becomes the new length
                {
                    l_id = a;
                }
                int b = length(student[r].n_of_course); // variable that stores the # of digits of the # of courses
                if (b > l_n)
                {
                    l_n = b;    // becomes the new length if it is longer than the previously stored length
                }
                for (int c = 0; c < student[r].lesson.size(); c++)      // runs through the course vector associated with each student
                {
                    if (student[r].lesson[c].course.length() > l_course)
                    {
                        l_course = student[r].lesson[c].course.length();   // the # of characters in the course name
                    }
                    int d = length(student[r].lesson[c].mark);
                    if (d > l_mark)
                    {
                        l_mark = d;  // # of digits in the mark
                    }
                }
            }
            // prints out the class list
            cout << setw(5+l_name) << "Name" << setw(5+l_id) << "ID" << setw(5+l_n) << "# of Courses" << setw(5+l_course) << "Course" << setw(5+l_mark) << "Mark" << endl;
            for (int r = 0; r < student.size(); r++)
            {
                cout << setw(5+l_name) << student[r].name << setw(5+l_id) << student[r].ID << setw(5+l_n) << student[r].n_of_course << setw(5+l_course);
                for (int c = 0; c < student[r].lesson.size(); c++)
                {
                    cout << student[r].lesson[c].course << setw(5+l_mark) << student[r].lesson[c].mark;
                    cout << endl;
                    if (c != student[r].lesson.size()-1)
                    {
                        cout << setw(5+l_name+5+l_id+5+l_n+5+l_course);
                    }
                    sum = sum + student[r].lesson[c].mark;
                    number++;
                }
                cout << endl;
            }
            cout.setf(ios::fixed);  // fixed number of decimal places in output
            cout.precision(2);  // rounds average to two decimal places
            average = sum / (number*1.0);   // calculates class average
            cout << "The class average is: " << average << endl;
        }
        else if (n == 6)    // saves the class list to a file
        {
            string filename_save;   // variable for the file name to be created and saved to
            cout << "Output filename: " << endl;
            cin >> filename_save;
            ofstream OutFile (filename_save.c_str()); // convert the filename to a C string
            if (OutFile.fail())
            {
                cout << "File: " << filename_save << " not created" << endl;
            }
            else
            {
                for (int r = 0; r < student.size(); r++)    // goes through student vector
                {
                    OutFile << student[r].name << "," << student[r].ID << "," << student [r].n_of_course;   // prints out the student information to the output file
                    for (int c = 0; c < student[r].lesson.size(); c++)  // goes through course vector associated with one particular student
                    {
                        OutFile << "," << student[r].lesson[c].course << "," << student[r].lesson[c].mark;  // prints out the course info after the student info to the file
                    }
                    OutFile << endl;
                }
            }
            OutFile.close(); // close the file when done
            cout << "File Saved!" << endl;
        }
        cout << endl;
    }

    return 0;
}
