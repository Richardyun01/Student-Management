#include <iostream>
#include <string>
#include "student.h"

using namespace std;

#define DEFAULT_DATABASE "file1.txt"

class StudentManager {
private:
    StudentDatabase& _db;

    void insertStudent() {
        Student student;
        cout << "Name? ";
        cin.ignore();
        getline(cin, student.name);

        cout << "Student ID (10 digits)? ";
        cin >> student.ID;

        cout << "Birth Year (4 digits)? ";
        cin >> student.birth;

        cout << "Department? ";
        cin.ignore();
        getline(cin, student.department);

        cout << "Tel? ";
        cin >> student.tel;

        _db.insert(student);
    }

    void searchStudent() {
        cout << endl << "- Search" << endl;
        cout << "1. Search by name" << endl;
        cout << "2. Search by student ID (10 numbers)" << endl;
        cout << "3. Search by admission year (4 numbers)" << endl;
        cout << "4. Search by department name" << endl;
        cout << "5. List All" << endl;
        cout << "> ";

        string str;
        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Name keyword? ";
            cin.ignore();
            getline(cin, str);
            _db.search(str, StudentOption::byName);
            break;
        case 2:
            cout << "Student ID? ";
            cin >> str;
            _db.search(str, StudentOption::byID);
            break;
        case 3:
            cout << "Admission year keyword? ";
            cin >> str;
            _db.search(str, StudentOption::byBirth);
            break;
        case 4:
            cout << "Department name keyword? ";
            cin.ignore();
            getline(cin, str);
            _db.search(str, StudentOption::byDepartment);
            break;
        case 5:
            _db.list();
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }

    void sortStudent() {
        cout << endl << "- Sorting Option" << endl;
        cout << "1. Sort by Name" << endl;
        cout << "2. Sort by Student ID" << endl;
        cout << "3. Sort by Admission Year" << endl;
        cout << "4. Sort by Department name" << endl;
        cout << "> ";

        int choice;
        cin >> choice;
        _db.sort((StudentOption)choice);
    }

public:
    StudentManager(StudentDatabase &db) : _db(db) {}

    void run() {
        while (true) {
            cout << endl << "Main Menu" << endl;
            cout << "1. Insertion" << endl;
            cout << "2. Search" << endl;
            cout << "3. Sorting Option" << endl;
            cout << "4. Exit" << endl;
            cout << "> ";

            int choice;
            cin >> choice;
            switch (choice) {
            case 1:
                insertStudent();
                break;
            case 2:
                searchStudent();
                break;
            case 3:
                sortStudent();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice" << endl;
                break;
            }
        }
    }
};

int main(int argc, char* argv[]) {
    StudentDatabase db(argc == 2 ? argv[1] : DEFAULT_DATABASE);
    StudentManager app(db);
    app.run();
    return 0;
}
