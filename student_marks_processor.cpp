#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Student {
    string id;
    string name;
    double mathMarks;
    double scienceMarks;
    double englishMarks;
    double totalMarks;
};


int readDataFromFile(const string& filename, Student students[], int maxSize) {
    ifstream file(filename.c_str());
    string line;
    int count = 0;

    while (getline(file, line) && count < maxSize) {
        istringstream iss(line);
        iss >> students[count].id >> students[count].name >> students[count].mathMarks >> students[count].scienceMarks >> students[count].englishMarks;
        students[count].totalMarks = students[count].mathMarks + students[count].scienceMarks + students[count].englishMarks;
        count++;
    }

    return count;
}

// Function to print details of a student matching a provided ID number
void printStudentDetails(Student students[], int count, const string& id) {
    bool found = false;
    for (int i = 0; i < count; ++i) {
        if (students[i].id == id) {
            found = true;
            cout << "Student ID: " << students[i].id << endl;
            cout << "Student Name: " << students[i].name << endl;
            cout << "Math Marks: " << students[i].mathMarks << endl;
            cout << "Science Marks: " << students[i].scienceMarks << endl;
            cout << "English Marks: " << students[i].englishMarks << endl;
            cout << "Total Marks: " << students[i].totalMarks << endl;
            break;
        }
    }
    if (!found) {
        cout << "Student with ID " << id << " not found." << endl;
    }
}

// Function to display the list of students with total marks
void displayListWithTotal(Student students[], int count) {
    for (int i = 0; i < count; ++i) {
        cout << "Student ID: " << students[i].id << ", Name: " << students[i].name
             << ", Math: " << students[i].mathMarks << ", Science: " << students[i].scienceMarks
             << ", English: " << students[i].englishMarks << ", Total: " << students[i].totalMarks << endl;
    }
}

// Function to print list of students sorted by total marks using bubble sort
void printSortedByTotal(Student students[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (students[j].totalMarks > students[j + 1].totalMarks) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    displayListWithTotal(students, count);
}

// Function to write report to file
void writeReportToFile(Student students[], int count) {
    ofstream outfile("summary.txt");
    for (int i = 0; i < count; ++i) {
        outfile << "Student ID: " << students[i].id << ", Name: " << students[i].name
                << ", Math: " << students[i].mathMarks << ", Science: " << students[i].scienceMarks
                << ", English: " << students[i].englishMarks << ", Total: " << students[i].totalMarks << endl;
    }
    outfile.close();
    cout << "Report has been written to summary.txt\n";
}

int main() {
    const int maxSize = 300;
    Student students[maxSize];
    int count = readDataFromFile("studentmarks.txt", students, maxSize);
    char choice;

    do {
        cout << "\nMenu:\n";
        cout << "1) Print the entire list\n";
        cout << "2) Print details of student matching a provided ID number\n";
        cout << "3) Display entire list with total\n";
        cout << "4) Print list sorted by total\n";
        cout << "5) Write report to file\n";
        cout << "6) Exit program\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                displayListWithTotal(students, count);
                break;
            case '2': {
                string id;
                cout << "Enter student ID: ";
                cin >> id;
                printStudentDetails(students, count, id);
                break;
            }
            case '3':
                displayListWithTotal(students, count);
                break;
            case '4':
                printSortedByTotal(students, count);
                break;
            case '5':
                writeReportToFile(students, count);
                break;
            case '6':
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please enter again.\n";
        }
    } while (choice != '6');

    return 0;
}
