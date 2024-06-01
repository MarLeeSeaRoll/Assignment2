#include <iostream>
#include <fstream>

using namespace std;

int readInput(int l_limit, int u_limit)
{
    int x;
    cin >> x;
    while (cin.fail() || (x < l_limit || x > u_limit))
    {
        cin.clear();
        string dummy;
        getline(cin, dummy);
        cout << "Invalid choice. Please enter again.\n";
        cin >> x;
    }
    return x;
}

void quirOrStart(bool &continueRunning)
{
    char decision;
    cout << "\n Enter S to start or Q to quit." << endl;
    cin >> decision;
    while (cin.fail() | (decision != 'q' && decision != 'Q' && decision != 's' && decision != 'S'))
    {
        cin.clear();
        string dummy;
        getline(cin, dummy);
        cout << "Invalid choice. Please enter again:";
        cin >> decision;
    }
    switch (decision)
    {
    case 's':
        continueRunning = true;
        break;
    case 'S':
        continueRunning = true;
        break;
    case 'q':
        continueRunning = false;
        break;
    case 'Q':
        continueRunning = false;
        break;
    }
}
// Function to read data from file into arrays
int readDataFromFile(const string &filename, string ids[], string names[], double mathMarks[], double scienceMarks[], double englishMarks[], double totalMarks[], int maxSize)
{
    int count = 0;
    string headeremove;
    ifstream infile;
    infile.open("studentmarks.txt");
    if (!infile)
    {
        cout << "File search failed" << endl;
    }
    else
    {
        cout << "File successfully opened." << endl;
    }
    getline(infile, headeremove);
    while (infile >> ids[count] >> names[count] >> mathMarks[count] >> scienceMarks[count] >> englishMarks[count] && count < maxSize)
    {
        totalMarks[count] = mathMarks[count] + scienceMarks[count] + englishMarks[count];
        count++;
    }
    infile.close();

    return count;
}

// Function to print details of a student matching a provided ID number
void printStudentDetails(string ids[], string names[], double mathMarks[], double scienceMarks[], double englishMarks[], double totalMarks[], int count, const string &id)
{
    bool found = false;
    for (int i = 0; i < count; ++i)
    {
        if (ids[i] == id)
        {
            found = true;
            cout << "Student ID: " << ids[i] << endl;
            cout << "Student Name: " << names[i] << endl;
            cout << "Math Marks: " << mathMarks[i] << endl;
            cout << "Science Marks: " << scienceMarks[i] << endl;
            cout << "English Marks: " << englishMarks[i] << endl;
            cout << "Total Marks: " << totalMarks[i] << endl;
            break;
        }
    }
    if (!found)
    {
        cout << "Student with ID " << id << " not found." << endl;
    }
}

// Function to display the list of students with total marks
void displayListWithTotal(string ids[], string names[], double mathMarks[], double scienceMarks[], double englishMarks[], double totalMarks[], int count)
{
    for (int i = 0; i < count; ++i)
    {
        cout << "Student ID: " << ids[i] << ", Name: " << names[i]
             << ", Math: " << mathMarks[i] << ", Science: " << scienceMarks[i]
             << ", English: " << englishMarks[i] << ", Total: " << totalMarks[i] << endl;
    }
}

// Function to print list of students sorted by total marks using bubble sort
void printSortedByTotal(string ids[], string names[], double mathMarks[], double scienceMarks[], double englishMarks[], double totalMarks[], int count)
{
    // Bubble sort
    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = 0; j < count - i - 1; ++j)
        {
            if (totalMarks[j] > totalMarks[j + 1])
            {
                // Manually swap elements
                string tempId = ids[j];
                ids[j] = ids[j + 1];
                ids[j + 1] = tempId;

                string tempName = names[j];
                names[j] = names[j + 1];
                names[j + 1] = tempName;

                double tempMath = mathMarks[j];
                mathMarks[j] = mathMarks[j + 1];
                mathMarks[j + 1] = tempMath;

                double tempScience = scienceMarks[j];
                scienceMarks[j] = scienceMarks[j + 1];
                scienceMarks[j + 1] = tempScience;

                double tempEnglish = englishMarks[j];
                englishMarks[j] = englishMarks[j + 1];
                englishMarks[j + 1] = tempEnglish;

                double tempTotal = totalMarks[j];
                totalMarks[j] = totalMarks[j + 1];
                totalMarks[j + 1] = tempTotal;
            }
        }
    }

    // Display sorted list
    displayListWithTotal(ids, names, mathMarks, scienceMarks, englishMarks, totalMarks, count);
}

// Function to write report to file
void writeReportToFile(string ids[], string names[], double mathMarks[], double scienceMarks[], double englishMarks[], double totalMarks[], int count)
{
    ofstream outfile("summary.txt");
    for (int i = 0; i < count; ++i)
    {
        outfile << "Student ID: " << ids[i] << ", Name: " << names[i]
                << ", Math: " << mathMarks[i] << ", Science: " << scienceMarks[i]
                << ", English: " << englishMarks[i] << ", Total: " << totalMarks[i] << endl;
    }
    outfile.close();
    cout << "Report has been written to summary.txt\n";
}

int main()
{
    const int maxSize = 300;
    const int printAll = 1;
    const int matchID = 2;
    const int listWithTotal = 3;
    const int printSortedList = 4;
    const int writeReport = 5;
    const int exitProgram = 6;
    const int lowerLimit = 1;
    const int upperLimit = 6;
    string ids[maxSize];
    string names[maxSize];
    double mathMarks[maxSize];
    double scienceMarks[maxSize];
    double englishMarks[maxSize];
    double totalMarks[maxSize];
    int count = readDataFromFile("studentmarks.txt", ids, names, mathMarks, scienceMarks, englishMarks, totalMarks, maxSize);
    bool totalMarkCalculation = false;
    bool continueRunning = true;
    // Welcome Screen
    cout << "+----------------------------------------------------------------------------+\n"
         << "|             Welcome to Student Results Enquiry Processing System.          |\n"
         << "+----------------------------------------------------------------------------+\n\n";

    quirOrStart(continueRunning);

    do
    {
        cout << "\nMenu:\n";
        cout << "1) Print the entire list\n";
        cout << "2) Print details of student matching a provided ID number\n";
        cout << "3) Display entire list with total\n";
        cout << "4) Print list sorted by total\n";
        cout << "5) Write report to file\n";
        cout << "6) Exit program\n";
        cout << "Enter your choice: ";

        int choice = readInput(lowerLimit, upperLimit);

        if (choice == printAll)
        {
            displayListWithTotal(ids, names, mathMarks, scienceMarks, englishMarks, totalMarks, count);
        }
        else if (choice == matchID)
        {
            string id;
            cout << "Enter student ID: ";
            cin >> id;
            printStudentDetails(ids, names, mathMarks, scienceMarks, englishMarks, totalMarks, count, id);
        }
        else if (choice == listWithTotal)
        {
            displayListWithTotal(ids, names, mathMarks, scienceMarks, englishMarks, totalMarks, count);
            totalMarkCalculation = true;
        }
        else if (choice == printSortedList)
        {
            if (!totalMarkCalculation)
            {
                cout << "Please select option 3 to calculate the total score first" << endl;
            }
            else
            {
                printSortedByTotal(ids, names, mathMarks, scienceMarks, englishMarks, totalMarks, count);
            }
        }
        else if (choice == writeReport)
        {
            if (!totalMarkCalculation)
            {
                cout << "Please select option 3 to calculate the total score first" << endl;
            }
            else
            {
                writeReportToFile(ids, names, mathMarks, scienceMarks, englishMarks, totalMarks, count);
            }
        }
        else if (choice == exitProgram)
        {
            break;
        }
    } while (continueRunning);

    return 0;
}
