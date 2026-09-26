#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    int age;
    string course;

    void input() {
        cout << "Enter Roll Number: ";
        cin >> rollNo;

        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cin.ignore();
        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() {
        cout << "Roll Number : " << rollNo << endl;
        cout << "Name        : " << name << endl;
        cout << "Age         : " << age << endl;
        cout << "Course      : " << course << endl;
        cout << "-----------------------------" << endl;
    }
};

void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app);

    s.input();

    file << s.rollNo << endl;
    file << s.name << endl;
    file << s.age << endl;
    file << s.course << endl;

    file.close();

    cout << "\nStudent added successfully!\n";
}

void displayStudents() {
    Student s;
    ifstream file("students.txt");

    if (!file) {
        cout << "\nNo student records found.\n";
        return;
    }

    cout << "\n===== STUDENT RECORDS =====\n";

    while (file >> s.rollNo) {
        file.ignore();
        getline(file, s.name);
        file >> s.age;
        file.ignore();
        getline(file, s.course);

        s.display();
    }

    file.close();
}

void searchStudent() {
    Student s;
    int roll;
    bool found = false;

    cout << "Enter Roll Number to search: ";
    cin >> roll;

    ifstream file("students.txt");

    while (file >> s.rollNo) {
        file.ignore();
        getline(file, s.name);
        file >> s.age;
        file.ignore();
        getline(file, s.course);

        if (s.rollNo == roll) {
            cout << "\nStudent Found!\n";
            s.display();
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nStudent not found.\n";
}

void updateStudent() {
    Student s;
    int roll;
    bool found = false;

    cout << "Enter Roll Number to update: ";
    cin >> roll;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    while (file >> s.rollNo) {
        file.ignore();
        getline(file, s.name);
        file >> s.age;
        file.ignore();
        getline(file, s.course);

        if (s.rollNo == roll) {
            cout << "\nEnter new details:\n";
            s.input();
            found = true;
        }

        temp << s.rollNo << endl;
        temp << s.name << endl;
        temp << s.age << endl;
        temp << s.course << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent updated successfully!\n";
    else
        cout << "\nStudent not found.\n";
}

void deleteStudent() {
    Student s;
    int roll;
    bool found = false;

    cout << "Enter Roll Number to delete: ";
    cin >> roll;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    while (file >> s.rollNo) {
        file.ignore();
        getline(file, s.name);
        file >> s.age;
        file.ignore();
        getline(file, s.course);

        if (s.rollNo == roll) {
            found = true;
            continue;
        }

        temp << s.rollNo << endl;
        temp << s.name << endl;
        temp << s.age << endl;
        temp << s.course << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "\nStudent deleted successfully!\n";
    else
        cout << "\nStudent not found.\n";
}

int main() {
    int choice;

    do {
        cout << "\n================================\n";
        cout << "     STUDENT MANAGEMENT SYSTEM\n";
        cout << "================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            cout << "\nThank you!\n";
            break;

        default:
            cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
