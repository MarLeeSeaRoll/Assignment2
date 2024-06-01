#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

// Input validation for choice selection
int validate_input(int lower_limit, int upper_limit) // perimeters to keep choices between 1 - 4
{
    int input;
    cin >> input;

    while (input < lower_limit || input > upper_limit || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            string dummy;
            cin >> dummy;
            cout << "ERROR!. Invalid option was detected" << endl;
            cout << "Kindly enter a number" << endl;
        }

        else if (input < lower_limit || input > upper_limit)
        {
            cin.clear();
            cout << "ERROR!. Your choice is not in range" << endl;
            cout << "Kindly enter a number between " << lower_limit << " and " << upper_limit << endl;
        }

        cin >> input;
    }
    return input;
}

// Function to display a welcome message
void welcome_message()
{
    cout << "+-------------------------------------------------+\n";
    cout << "|   WELCOME TO THE STUDENT MARKS SORTING PROGRAM  |\n";
    cout << "+-------------------------------------------------+\n";
}

// Function to display exit message
void end_program(bool &continue_running)
{
    continue_running = false;

    cout << endl;
    cout << "+-------------------------------------+\n";
    cout << "|  Thank you for using this program!  |\n";
    cout << "+-------------------------------------+\n";
}

void program_start_quit(bool &continue_running)
{
    char user_decision;
    cout << "Enter S to start or Q to quit" << endl;
    cin >> user_decision;

    while (user_decision != 'S' && user_decision != 's' && user_decision != 'Q' && user_decision != 'q')
    {
        cin.clear();
        string dummy;
        cin >> dummy;
        cout << "ERROR!, invalid input was detected" << endl;
        cout << "Please enter either \"S\" or \"Q\" only" << endl;
        cin >> user_decision;
    }

    if (user_decision == 'S' || user_decision == 's')
    {
        continue_running = true;
    }

    else if (user_decision == 'Q' || user_decision == 'q')
    {
        continue_running = false;
    }
}

void fill_array(string file_name, int &rows, string student_id[], string student_name[], double maths_marks[], double science_marks[], double english_marks[])
{
    string remove_header;

    ifstream read_file;
    read_file.open(file_name.c_str());

    if (!read_file)
    {
        cout << "ERROR!. This file could not be found" << endl;
    }

    else
    {
        getline(read_file, remove_header);

        while (read_file >> student_id[rows] >> student_name[rows] >> maths_marks[rows] >> science_marks[rows] >> english_marks[rows])
        {
            rows++;
        }
    }
}

void print_entire_list(int rows, string student_id[], string student_name[], double maths_marks[], double science_marks[], double english_marks[])
{
    cout << "\n The Entire List of Students:" << endl;
    cout << left << setw(15) << "ID#" << setw(10);
    cout << left << setw(15) << "Name" << setw(15);
    cout << left << setw(15) << "Maths" << setw(10);
    cout << left << setw(15) << "Science" << setw(15);
    cout << left << setw(15) << "English" << setw(15) << endl;

    for (int i = 0; i < rows; i++)
    {
        cout << left << setw(15) << student_id[i] << setw(10);
        cout << left << setw(15) << student_name[i] << setw(15);
        cout << left << setw(15) << maths_marks[i] << setw(10);
        cout << left << setw(15) << science_marks[i] << setw(15);
        cout << left << setw(15) << english_marks[i] << endl;
    }
}

void print_by_id(int rows, string student_id[], string student_name[], double maths_marks[], double science_marks[], double english_marks[])
{
    string query_id;
    bool data_exists = false;

    cout << "Kindly enter the ID number that you would like to search. Example: S122243" << endl;
    cin >> query_id;
    while (cin.fail())
    {
        cin.clear();
        string dummy;
        cin >> dummy;
        cout << "ERROR!. Invalid Input Detected" << endl;
        cout << "Please enter letter \"S\" with numbers only" << endl;
        cin >> query_id;
    }

    cout << "List of student(s) matching the given ID:" << endl;
    cout << left << setw(15) << "ID#" << setw(15);
    cout << left << setw(15) << "Name#" << setw(15);
    cout << left << setw(15) << "Maths" << setw(15);
    cout << left << setw(15) << "Science" << setw(15);
    cout << left << setw(15) << "English" << setw(15) << endl;

    for (int i = 0; i < rows; i++)
    {
        if (student_id[i] == query_id)
        {
            data_exists = true;
            cout << left << setw(15) << student_id[i] << setw(15);
            cout << left << setw(15) << student_name[i] << setw(15);
            cout << left << setw(15) << maths_marks[i] << setw(15);
            cout << left << setw(15) << science_marks[i] << setw(15);
            cout << left << setw(15) << english_marks[i] << setw(15);
        }
    }

    cout << endl;

    if (!data_exists)
    {
        cout << "No students were found with the ID# " << query_id << endl;
    }
}

void print_by_total(int rows, string student_id[], string student_name[], double maths_marks[], double science_marks[], double english_marks[], double total_marks[])
{
    cout << "\n The Entire List of Students with Total:" << endl;
    cout << left << setw(15) << "ID#" << setw(10);
    cout << left << setw(15) << "Name" << setw(15);
    cout << left << setw(15) << "Maths" << setw(10);
    cout << left << setw(15) << "Science" << setw(15);
    cout << left << setw(15) << "English" << setw(15);
    cout << left << setw(15) << "Total" << setw(15) << endl;

    for (int i = 0; i < rows; i++)
    {
        total_marks[i] = maths_marks[i] + science_marks[i] + english_marks[i];
        cout << left << setw(15) << student_id[i] << setw(10);
        cout << left << setw(15) << student_name[i] << setw(15);
        cout << left << setw(15) << maths_marks[i] << setw(10);
        cout << left << setw(15) << science_marks[i] << setw(15);
        cout << left << setw(15) << english_marks[i];
        cout << left << setw(15) << total_marks[i] << endl;
    }
}

// Function to sort arrays based on total marks using Bubble Sort algorithm
void print_sorted(int rows, string student_id[], string student_name[], double maths_marks[], double science_marks[], double english_marks[], double total_marks[])
{
    for (int i = 0; i < rows - 1; ++i)
    {
        // Last i elements are already sorted
        for (int j = 0; j < rows - i - 1; ++j)
        {
            if (total_marks[j] < total_marks[j + 1])
            {
                // Sorting in descending order
                // Swap total_marks[j] and total_marks[j + 1]
                double temp_total = total_marks[j];
                total_marks[j] = total_marks[j + 1];
                total_marks[j + 1] = temp_total;

                // Swap corresponding student_id[j] and student_id[j + 1]
                string temp_id = student_id[j];
                student_id[j] = student_id[j + 1];
                student_id[j + 1] = temp_id;

                // Swap corresponding student_name[j] and student_name[j + 1]
                string temp_name = student_name[j];
                student_name[j] = student_name[j + 1];
                student_name[j + 1] = temp_name;

                // Swap corresponding maths_marks[j] and maths_marks[j + 1]
                double temp_maths = maths_marks[j];
                maths_marks[j] = maths_marks[j + 1];
                maths_marks[j + 1] = temp_maths;

                // Swap corresponding science_marks[j] and science_marks[j + 1]
                double temp_science = science_marks[j];
                science_marks[j] = science_marks[j + 1];
                science_marks[j + 1] = temp_science;

                // Swap corresponding english_marks[j] and english_marks[j + 1]
                double temp_english = english_marks[j];
                english_marks[j] = english_marks[j + 1];
                english_marks[j + 1] = temp_english;
            }
        }
    }

    for (int i = 0; i < rows; i++)
    {
        total_marks[i] = maths_marks[i] + science_marks[i] + english_marks[i];
    }

    // Print the sorted list
    cout << "\n The List of Students Sorted by Total Marks:" << endl;
    cout << left << setw(15) << "ID#" << setw(15);
    cout << left << setw(15) << "Name" << setw(15);
    cout << left << setw(15) << "Maths" << setw(15);
    cout << left << setw(15) << "Science" << setw(15);
    cout << left << setw(15) << "English" << setw(15);
    cout << left << setw(15) << "Total" << setw(15) << endl;

    for (int i = 0; i < rows; i++)
    {
        cout << left << setw(15) << student_id[i] << setw(15);
        cout << left << setw(15) << student_name[i] << setw(15);
        cout << left << setw(15) << maths_marks[i] << setw(15);
        cout << left << setw(15) << science_marks[i] << setw(15);
        cout << left << setw(15) << english_marks[i] << setw(15);
        cout << left << setw(15) << total_marks[i] << endl;
    }
}

void write_report(string file_name, int &rows, string student_id[], string student_name[], double maths_marks[], double science_marks[], double english_marks[], double total_marks[])
{
    ofstream write_file;
    write_file.open(file_name.c_str());

    if (!write_file)
    {
        cout << "ERROR!. This file could not be found" << endl;
    }
    else
    {
        write_file << left << setw(15) << "ID#" << setw(15) << "Name" << setw(15) << "Maths" << setw(15) << "Science" << setw(15) << "English" << setw(15) << "Total" << endl;

        for (int i = 0; i < rows; i++)
        {
            write_file << left << setw(15) << student_id[i] << setw(15) << student_name[i] << setw(15) << maths_marks[i] << setw(15) << science_marks[i] << setw(15) << english_marks[i] << setw(15) << total_marks[i] << endl;
        }

        cout << "Report Successfully Generated to summary.txt" << endl;
    }

    write_file.close();
}

int main()
{
    int choice;
    int rows = 0;

    // Constant declarations
    const int CAPACITY = 300;
    const int PRINT_LIST = 1;
    const int PRINT_DETAILS = 2;
    const int PRINT_TOTAL = 3;
    const int PRINT_SORTED = 4;
    const int WRITE_REPORT = 5;
    const int EXIT_PROGRAM = 6;
    const int FIRST_OPTION = 1;
    const int LAST_OPTION = 6;

    bool continue_running = true;

    // Arrays for storing different categories of data
    string student_id[CAPACITY];
    string student_name[CAPACITY];
    double maths_marks[CAPACITY];
    double science_marks[CAPACITY];
    double english_marks[CAPACITY];
    double total_marks[CAPACITY];

    welcome_message();

    program_start_quit(continue_running);

    while (continue_running)
    {
        rows = 0;
        fill_array("studentmarks.txt", rows, student_id, student_name, maths_marks, science_marks, english_marks);

        cout << endl;

        cout << "Menu:" << endl;
        cout << "1) Print the Entire List" << endl;
        cout << "2) Print Details of Student Matching a Given ID" << endl;
        cout << "3) Calculate Total and Print Entire List with Total" << endl;
        cout << "4) Print List Sorted by Total" << endl;
        cout << "5) Write Report to file" << endl;
        cout << "6) Exit program" << endl;
        cout << "Enter your choice:";
        choice = validate_input(FIRST_OPTION, LAST_OPTION);

        if (choice == PRINT_LIST)
        {
            print_entire_list(rows, student_id, student_name, maths_marks, science_marks, english_marks);
        }

        else if (choice == PRINT_DETAILS)
        {
            print_by_id(rows, student_id, student_name, maths_marks, science_marks, english_marks);
        }

        else if (choice == PRINT_TOTAL)
        {
            print_by_total(rows, student_id, student_name, maths_marks, science_marks, english_marks, total_marks);
        }

        else if (choice == PRINT_SORTED)
        {
            print_sorted(rows, student_id, student_name, maths_marks, science_marks, english_marks, total_marks);
        }

        else if (choice == WRITE_REPORT)
        {
            write_report("summary.txt", rows, student_id, student_name, maths_marks, science_marks, english_marks, total_marks);
        }

        else if (choice == EXIT_PROGRAM)
        {
            end_program(continue_running);
        }
    }

    return 0;
}