#include <iostream>
#include <fstream>
#include <iomanip>

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

void quirorStart(bool &continueRunning)
{
    char decision;
    cout << "\n Enter S to start or Q to quit: ";
    cin >> decision;
    while (cin.fail() || (decision != 'q' && decision != 'Q' && decision != 's' && decision != 'S'))
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
    case 'S':
        continueRunning = true;
        break;
    case 'q':
    case 'Q':
        continueRunning = false;
        break;
    }
}
// Function to read data from file into arrays
int readfile(const string &filename, string ids[], string names[], double math[], double science[], double English[], double total[], int maxSize)
{
    ifstream file(filename.c_str());
    int count = 0;
    string headermove;
    getline(file, headermove);

    while (file >> ids[count] >> names[count] >> math[count] >> science[count] >> English[count] && count < maxSize)
    {
        total[count] = math[count] + science[count] + English[count];
        count++;
    }

    return count;
}

// Function to print details of a student matching a provided ID number
void printall(string ids[], string names[], double math[], double science[], double English[], double total[], int count, const string &id)
{
    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (ids[i] == id)
        {
            found = true;
            cout << "\tStudent ID: " << ids[i] << endl;
            cout << "\tStudent Name: " << names[i] << endl;
            cout << "\tMath Marks: " << math[i] << endl;
            cout << "\tScience Marks: " << science[i] << endl;
            cout << "\tEnglish Marks: " << English[i] << endl;
            cout << "\tTotal Marks: " << total[i] << endl;
            break;
        }
    }
    if (!found)
    {
        cout << "Student with ID " << id << " not found." << endl;
    }
}

// Function to display the list of students with total marks
void totalist(string ids[], string names[], double math[], double science[], double English[], double total[], int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << "Student ID: " << ids[i] << ", Name: " << names[i]
             << ", Math: " << math[i] << ", Science: " << science[i]
             << ", English: " << English[i] << ", Total: " << total[i] << endl;
    }
}

// Function to print list of students sorted by total marks using bubble sort
void sortedtotal(string ids[], string names[], double math[], double science[], double English[], double total[], int count)
{
    const int avoidMnumber = 1;
    // Bubble sort
    for (int i = 0; i < count - avoidMnumber; i++)
    {
        for (int j = 0; j < count - i - avoidMnumber; j++)
        {
            if (total[j] > total[j + avoidMnumber])
            {
                // Manually swap elements
                string tempId = ids[j];
                ids[j] = ids[j + avoidMnumber];
                ids[j + avoidMnumber] = tempId;

                string tempName = names[j];
                names[j] = names[j + avoidMnumber];
                names[j + avoidMnumber] = tempName;

                double tempMath = math[j];
                math[j] = math[j + avoidMnumber];
                math[j + avoidMnumber] = tempMath;

                double tempScience = science[j];
                science[j] = science[j + avoidMnumber];
                science[j + avoidMnumber] = tempScience;

                double tempEnglish = English[j];
                English[j] = English[j + avoidMnumber];
                English[j + avoidMnumber] = tempEnglish;

                double tempTotal = total[j];
                total[j] = total[j + avoidMnumber];
                total[j + avoidMnumber] = tempTotal;
            }
        }
    }

    // Display sorted list
    totalist(ids, names, math, science, English, total, count);
}

// Function to write report to file
void writerepo(string ids[], string names[], double math[], double science[], double English[], double total[], int count)
{
    ofstream outfile("summary.txt");

    double totalMath = 0, totalScience = 0, totalEnglish = 0, totalAll = 0;
    for (int i = 0; i < count; i++)
    {
        totalMath += math[i];
        totalScience += science[i];
        totalEnglish += English[i];
        totalAll += total[i];
    }
    double avgMath = totalMath / count;
    double avgScience = totalScience / count;
    double avgEnglish = totalEnglish / count;
    double avgTotal = totalAll / count;

    // Find highest and lowest total marks
    double highestMarks = total[0], lowestMarks = total[0];
    int highestIndex = 0, lowestIndex = 0;
    for (int i = 1; i < count; i++)
    {
        if (total[i] > highestMarks)
        {
            highestMarks = total[i];
            highestIndex = i;
        }
        if (total[i] < lowestMarks)
        {
            lowestMarks = total[i];
            lowestIndex = i;
        }
    }
    outfile << "ID\tName\tMath\tScience\tEnglish\tTotal\n";
    for (int i = 0; i < count; ++i)
    {
        outfile << ids[i] << "\t" << names[i] << "\t" << math[i] << "\t" << science[i] << "\t" << English[i] << "\t" << total[i] << endl;
    }
    outfile << "\nClass Averages:\n";
    outfile << "Math: " << avgMath << ", Science: " << avgScience << ", English: " << avgEnglish << ", Total: " << avgTotal << endl;
    outfile << "\nHighest Total Marks: " << highestMarks << " (ID: " << ids[highestIndex] << ", Name: " << names[highestIndex] << ")\n";
    outfile << "Lowest Total Marks: " << lowestMarks << " (ID: " << ids[lowestIndex] << ", Name: " << names[lowestIndex] << ")\n";

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
    double math[maxSize];
    double science[maxSize];
    double English[maxSize];
    double total[maxSize];
    int count = readfile("studentmarks.txt", ids, names, math, science, English, total, maxSize);
    bool totalMarkCalculation = false;
    bool continueRunning;
    // Welcome Screen
    cout << "+----------------------------------------------------------------------------+\n"
         << "|             Welcome to Student Results Enquiry Processing System.          |\n"
         << "+----------------------------------------------------------------------------+\n\n";

    quirorStart(continueRunning);

    while (continueRunning)
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
            totalist(ids, names, math, science, English, total, count);
        }
        else if (choice == matchID)
        {
            string id;
            cout << "Enter student ID: ";
            cin >> id;
            printall(ids, names, math, science, English, total, count, id);
        }
        else if (choice == listWithTotal)
        {
            totalist(ids, names, math, science, English, total, count);
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
                sortedtotal(ids, names, math, science, English, total, count);
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
                writerepo(ids, names, math, science, English, total, count);
            }
        }
        else if (choice == exitProgram)
        {
            break;
        }
    }
    cout << "\nThank you for using." << endl;
    return 0;
}
