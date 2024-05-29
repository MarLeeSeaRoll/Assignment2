#include <iostream>
#include <fstream>

using namespace std;

const int CAP = 300;
string id[CAP];
string name[CAP];
double mathMarks[CAP];
double scienceMarks[CAP];
double englishMarks[CAP];
double totalMarks[CAP]

// Function to read data from the input file and store it in a vector of Student objects
vector<Student> readDataFromFile(const string& filename) {
	ifstream file(filename.c_str());
    vector<Student> students;
    string line;

    while (getline(file, line)) {
        Student student;
        istringstream iss(line);

        // Parse each field from the line
        string field;
        while (getline(iss, field, ' ')) {
            if (field.substr(0, 3) == "ID#") {
                student.id = field.substr(3);
            } else if (field.substr(0, 5) == "Name:") {
                student.name = field.substr(5);
            } else if (field.substr(0, 5) == "Math:") {
                student.mathMarks = stod(field.substr(5));
            } else if (field.substr(0, 8) == "Science:") {
                student.scienceMarks = stod(field.substr(8));
            } else if (field.substr(0, 8) == "English:") {
                student.englishMarks = stod(field.substr(8));
            }
        }

        // Calculate total marks
        student.totalMarks = student.mathMarks + student.scienceMarks + student.englishMarks;

        students.push_back(student);
    }

    return students;
}

// Function to print details of a student matching a provided ID number
void printStudentDetails(const vector<Student>& students, const string& id) {
    bool found = false;
    for (const auto& student : students) {
        if (student.id == id) {
            found = true;
            cout << "Student ID: " << student.id << endl;
            cout << "Student Name: " << student.name << endl;
            cout << "Math Marks: " << student.mathMarks << endl;
            cout << "Science Marks: " << student.scienceMarks << endl;
            cout << "English Marks: " << student.englishMarks << endl;
            cout << "Total Marks: " << student.totalMarks << endl;
            break;
        }
    }
    if (!found) {
        cout << "Student with ID " << id << " not found." << endl;
    }
}

// Function to calculate total marks and display entire list with total
void displayListWithTotal(const vector<Student>& students) {
    for (const auto& student : students) {
        cout << "Student ID: " << student.id << endl;
        cout << "Student Name: " << student.name << endl;
        cout << "Math Marks: " << student.mathMarks << endl;
        cout << "Science Marks: " << student.scienceMarks << endl;
        cout << "English Marks: " << student.englishMarks << endl;
        cout << "Total Marks: " << student.totalMarks << endl;
        cout << endl;
    }
}

// Comparator function for sorting students by total marks
bool sortByTotalMarks(const Student& a, const Student& b) {
    return a.totalMarks < b.totalMarks;
}

// Function to print list of students sorted by total marks
void printSortedByTotal(const vector<Student>& students) {
    vector<Student> sortedStudents = students;
    sort(sortedStudents.begin(), sortedStudents.end(), sortByTotalMarks);

    for (const auto& student : sortedStudents) {
        cout << "Student ID: " << student.id << ", Total Marks: " << student.totalMarks << endl;
    }
}

// Function to write report to file
void writeReportToFile(const vector<Student>& students) {
    ofstream outfile("summary.txt");
    for (const auto& student : students) {
        outfile << "Student ID: " << student.id << endl;
        outfile << "Student Name: " << student.name << endl;
        outfile << "Math Marks: " << student.mathMarks << endl;
        outfile << "Science Marks: " << student.scienceMarks << endl;
        outfile << "English Marks: " << student.englishMarks << endl;
        outfile << "Total Marks: " << student.totalMarks << endl;
        outfile << endl;
    }
    outfile.close();
}

int main() {
    vector<Student> students = readDataFromFile("studentmarks.txt");
    char choice;

    do {
        cout << "Menu:\n";
        cout << "1) Print the entire list\n";
        cout << "2) Print details of student matching a provided ID number\n";
        cout << "3) Calculate total and display entire List with total\n";
        cout << "4) Print list sorted by total\n";
        cout << "5) Write report to file\n";
        cout << "6) Exit program\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case '1':
                displayListWithTotal(students);
                break;
            case '2':
                {
                    string id;
                    cout << "Enter student ID: ";
                    cin >> id;
                    printStudentDetails(students, id);
                }
                break;
            case '3':
                displayListWithTotal(students);
                break;
            case '4':
                cout << "Please invoke option 3 first to calculate the Total Marks before storing or displaying them." << endl;
                break;
            case '5':
                writeReportToFile(students);
                cout << "Report has been written to summary.txt\n";
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