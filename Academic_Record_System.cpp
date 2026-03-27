#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class Student {
    int rollNumber;
    char name[50];
    float gpa;

public:
    void getDetails() {
        cout << "\nEnter Roll Number: ";
        cin >> rollNumber;
        cin.ignore();
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter GPA: ";
        cin >> gpa;
    }

    void showDetails() const {
        cout << left << setw(15) << rollNumber 
             << setw(25) << name 
             << setw(10) << gpa << endl;
    }

    int getRoll() const { return rollNumber; }
};

// Function to save record to a binary file
void saveRecord() {
    Student s;
    ofstream outFile("records.dat", ios::binary | ios::app);
    s.getDetails();
    outFile.write(reinterpret_cast<char*>(&s), sizeof(Student));
    outFile.close();
    cout << "\n[Success] Record saved to disk.";
}

// Function to read all records
void displayAll() {
    Student s;
    ifstream inFile("records.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened!! Press any Key...";
        return;
    }
    cout << "\n--- Student Records ---\n";
    cout << left << setw(15) << "Roll No" << setw(25) << "Name" << setw(10) << "GPA" << endl;
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        s.showDetails();
    }
    inFile.close();
}

int main() {
    int choice;
    do {
        cout << "\n\n1. Add Record\n2. View Records\n3. Exit\nSelection: ";
        cin >> choice;
        switch (choice) {
            case 1: saveRecord(); break;
            case 2: displayAll(); break;
            case 3: cout << "Exiting..."; break;
        }
    } while (choice != 3);
    return 0;
}