// Alice Jiang
// March 22, 2017
// Exercise #2, Question 2
// This program uses recursive function to print the nth term of the Fibonacci sequence

#include <iostream>

using namespace std;

int fibonacci (int n)
{
    if (n == 1)         // base cases
        return 1;
    else if (n == 2)
        return 1;
    else
        return fibonacci(n-1) + fibonacci(n-2);  // f(n) = f(n-1) + f(n-2)
}

int main()
{
    int f;      // input for nth term
    cout << "Input the term # of the Fibonacci sequence: ";
    cin >> f;
    cout << "The number is: " << fibonacci (f);

    return 0;
}
