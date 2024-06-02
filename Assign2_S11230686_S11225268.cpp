/*Assignment2
Student1: ZhiXian Chen S11230686
Student2: Ye yiyu      S11225268*/


#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/*---------------------Function Prototypes--------------------------*/
// Function for input validation
int readInput(int l_limit, int u_limit);

// Function for decide to withdraw from the procedure or not
void quirorStart(bool &continueRunning);

// Function to read data from file into arrays
void readfile(string filename, string ids[], string names[], double math[], double science[], double English[], double total[], int maxSize, int &count, bool &opensuccessfully);

// Function to print details of a student matching a provided ID number
void printall(string ids[], string names[], double math[], double science[], double English[], int count, const string &id);

// Function to display the list of students without total marks
void listwithouttotal(string ids[], string names[], double math[], double science[], double English[], int count);

// Function to display the list of students with total marks
void listwithtotal(string ids[], string names[], double math[], double science[], double English[], double total[], int count);

// Function to print list of students sorted by total marks using bubble sort
void sortedtotal(string ids[], string names[], double math[], double science[], double English[], double total[], int count);

// Function to write report to file
void writereport(string ids[], string names[], double math[], double science[], double English[], double total[], int count);



// Main function
int main()
{
    // Size of data arrays
    const int maxSize = 300;
    // Six options
    const int printAll = 1;
    const int matchID = 2;
    const int listWithTotal = 3;
    const int printSortedList = 4;
    const int writeReport = 5;
    const int exitProgram = 6;
    const int lowerLimit = 1;
    const int upperLimit = 6;

    //Data Arrays
    string ids[maxSize];
    string names[maxSize];
    double math[maxSize];
    double science[maxSize];
    double English[maxSize];
    double total[maxSize];

    // Index for arrays
    int count = 0;
    // Make sure user have calculate the total number
    bool totalMarkCalculation = false;
    // Flag that determine whether the program will continue going or not
    bool continueRunning;
    // Flag that shows whether the file has been read successfully
    bool opensuccessfully = false;

    //-------------------------------The main body of whole program----------------------------------------------

    // Set variables to 2 decimal point
    cout << fixed << setprecision(2) << endl;

    // Welcome Screen
    cout << "+----------------------------------------------------------------------------+\n"
         << "|             Welcome to Student Results Enquiry Processing System.          |\n"
         << "+----------------------------------------------------------------------------+\n\n";

    // Decide whether program start or not function call
    quirorStart(continueRunning);

    //Read data from certain file
    readfile("studentmarks.txt", ids, names, math, science, English, total, maxSize, count, opensuccessfully);

    while (continueRunning)
    {
        // Menu
        cout << "\nMenu:\n";
        cout << "1) Print the entire list\n";
        cout << "2) Print details of student matching a provided ID number\n";
        cout << "3) Display entire list with total\n";
        cout << "4) Print list sorted by total\n";
        cout << "5) Write report to file\n";
        cout << "6) Exit program\n";
        cout << "Enter your choice: ";

        // Validate input function call
        int choice = readInput(lowerLimit, upperLimit);

        // Warning message
        if (!opensuccessfully&&choice!=exitProgram)
        {
            cout << "Error: Unable to read file. Please make sure the file exists and is in the correct format." << endl;
            continue;
        }

        // Logic of six options
        if (choice == printAll)
        {
            listwithouttotal(ids, names, math, science, English, count);
        }
        else if (choice == matchID)
        {
            string id;
            cout << "Enter student ID: ";
            cin >> id;
            printall(ids, names, math, science, English, count, id);
        }
        else if (choice == listWithTotal)
        {
            listwithtotal(ids, names, math, science, English, total, count);
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
                listwithtotal(ids, names, math, science, English, total, count);
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
                writereport(ids, names, math, science, English, total, count);
            }
        }
        else if (choice == exitProgram)
        {
            break;
        }
    }
    cout << "\nExiting the programme.\nThank you for using." << endl;
    return 0;
}


/*-------------------------------Function bodies-----------------------------*/
// Function for input validation
int readInput(int l_limit, int u_limit)
{
    int x;
    cin >> x;
    while (cin.fail() || (x < l_limit || x > u_limit))
    {
        cin.clear();
        string dummy;
        getline(cin, dummy);
        cout << "Invalid choice. Please enter again:";
        cin >> x;
    }
    return x;
}

// Function for decision on whether to withdraw from the procedure
void quirorStart(bool &continueRunning)
{
    char decision;
    cout << "\n Enter S to start or Q to quit: ";
    cin >> decision;

    //Input validation
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
void readfile(string filename, string ids[], string names[], double math[], double science[], double English[], double total[], int maxSize, int &count, bool &opensuccessfully)
{
    ifstream file(filename.c_str());
    string headermove;

    if (!file)
    {
        cout << "File open failed, unable to read data" << endl;
        opensuccessfully = false;
    }
    else
    {
        getline(file, headermove);
        while (file >> ids[count] >> names[count] >> math[count] >> science[count] >> English[count] && count < maxSize)
        {
            count++;
        }
        opensuccessfully = true;
    }
}

// Function to print details of a student matching a provided ID number
void printall(string ids[], string names[], double math[], double science[], double English[], int count, const string &id)
{
    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (ids[i] == id)
        {
            found = true;
            cout << "\tStudent ID: "<<"\t"<< ids[i] << endl;
            cout << "\tStudent Name: " << "\t" << names[i] << endl;
            cout << "\tMath Marks: " << "\t" << math[i] << endl;
            cout << "\tScience Marks: " << "\t" << science[i] << endl;
            cout << "\tEnglish Marks: " << "\t" << English[i] << endl;
        }
    }
    if (!found)
    {
        cout << "Student with ID " << id << " not found." << endl;
    }
}

// Function to display the list of students without total marks
void listwithouttotal(string ids[], string names[], double math[], double science[], double English[], int count)
{
    cout << "ID\tName\tMath\tScience\tEnglish\n";
    for (int i = 0; i < count; i++)
    {
        cout << ids[i] << "\t" << names[i] << "\t"
             << math[i] << "\t" << science[i] << "\t"
             << English[i] << endl;
    }
}


// Function to calculate total marks and display the list of students with total marks
void listwithtotal(string ids[], string names[], double math[], double science[], double English[], double total[], int count)
{
    cout << "ID\tName\tMath\tScience\tEnglish\tTotal\n";
    for (int i = 0; i < count; i++)
    {
        total[i] = math[i] + science[i] + English[i];
        cout << ids[i] << "\t" << names[i] << "\t"
             << math[i] << "\t" << science[i] << "\t"
             << English[i] << "\t" << total[i] << endl;
    }
}

// Function to print list of students sorted by total marks using bubble sort
void sortedtotal(string ids[], string names[], double math[], double science[], double English[], double total[], int count)
{
    const int avoidMnumber = 1; // Avoid magic number.

    // Bubble sort algorithm
    for (int i = 0; i < count - avoidMnumber; i++)
    {
        for (int j = 0; j < count - i - avoidMnumber; j++)
        {
            if (total[j] > total[j + avoidMnumber])
            {
                //Sort student ID
                string tempId = ids[j];
                ids[j] = ids[j + avoidMnumber];
                ids[j + avoidMnumber] = tempId;
                //Sort student names
                string tempName = names[j];
                names[j] = names[j + avoidMnumber];
                names[j + avoidMnumber] = tempName;
                //Sort math marks
                double tempMath = math[j];
                math[j] = math[j + avoidMnumber];
                math[j + avoidMnumber] = tempMath;
                //Sort science marks
                double tempScience = science[j];
                science[j] = science[j + avoidMnumber];
                science[j + avoidMnumber] = tempScience;
                //Sort English marks
                double tempEnglish = English[j];
                English[j] = English[j + avoidMnumber];
                English[j + avoidMnumber] = tempEnglish;
                //Sort total marks
                double tempTotal = total[j];
                total[j] = total[j + avoidMnumber];
                total[j + avoidMnumber] = tempTotal;
            }
        }
    }
}

// Function to write report to file
void writereport(string ids[], string names[], double math[], double science[], double English[], double total[], int count)
{
    ofstream outfile("summary.txt");

    if (!outfile)
    {
        cout << "File open failed" << endl;
    }
    else
    {
        cout << "File open successfully" << endl;

        //Make sure print sorted data
        sortedtotal(ids, names, math, science, English, total, count);

        // Calculate total mark of each subject
        double mathtotal = 0, sciencetotal = 0, Englishtotal = 0, totalAll = 0;
        for (int i = 0; i < count; i++)
        {
            mathtotal += math[i];
            sciencetotal += science[i];
            Englishtotal += English[i];
            totalAll += total[i];
        }
        // Average mark of each subject
        double avgmath = mathtotal / count;
        double avgscience = sciencetotal / count;
        double avgEnglish = Englishtotal / count;
        double avgtotal = totalAll / count;
        // Variable for avoiding magic number
        const int startIndex = 0;
        const int avoidMnumber=1;

        // Variables of extreme value and Index
        double highestmark = total[count-avoidMnumber];
        double lowestmark = total[startIndex];
        int highestIndex = count-avoidMnumber;
        int lowestIndex = startIndex;


        outfile << "ID\tName\tMath\tScience\tEnglish\tTotal\n";
        for (int i = 0; i < count; ++i)
        {
            outfile << ids[i] << "\t" << names[i] << "\t" << math[i] << "\t" << science[i] << "\t" << English[i] << "\t" << total[i] << endl;
        }
        outfile << "\nClass Averages:\n";
        outfile << "Math: " << avgmath << ", Science: " << avgscience << ", English: " << avgEnglish << ", Total: " << avgtotal << endl;
        outfile << "\nHighest Total Marks: " << highestmark << " (ID: " << ids[highestIndex] << ", Name: " << names[highestIndex] << ")\n";
        outfile << "Lowest Total Marks: " << lowestmark << " (ID: " << ids[lowestIndex] << ", Name: " << names[lowestIndex] << ")\n";

        outfile.close();
        cout << "Report has been written to summary.txt\n";
    }
}
