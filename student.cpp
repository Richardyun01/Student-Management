#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "student.h"

using namespace std;

StudentDatabase::StudentDatabase(const string& filename)
	: _filename(filename)
{
	load();
	sort(_sortOpt);
}

StudentDatabase::~StudentDatabase() {
	save();
}

void StudentDatabase::load() {
    ifstream file(_filename);
    if (file) {
        string line;
        while (getline(file, line)) {
            Student s;
            s.name       = line.substr(0, 15);
            s.ID         = line.substr(16, 10);
            s.department = line.substr(27, 25);
            s.birth      = line.substr(53, 4);
            s.tel        = line.substr(58, 12);

            s.name.erase(find_if(s.name.rbegin(), s.name.rend(), bind1st(not_equal_to<char>(), ' ')).base(), s.name.end());
            s.department.erase(find_if(s.department.rbegin(), s.department.rend(), bind1st(not_equal_to<char>(), ' ')).base(), s.department.end());

            _students.push_back(s);
        }
        file.close();
    }
}

void StudentDatabase::save() {
    ofstream file(_filename, ios::out);
    if (file.is_open()) {
        for (const Student& s : _students) s.print(file);
        file.close();
    }
}

void StudentDatabase::insert(const Student& student) {
    for (const Student& s : _students) {
        if (s.ID == student.ID) {
            cout << "Error : Already inserted" << endl;
            return;
        }
    }

    _students.push_back(student);
    cout << "Student information inserted successfully!" << endl;
}

void StudentDatabase::search(const string& str, StudentOption opt) {
    switch (opt) {
    case StudentOption::byName:
        for (const Student& s : _students) {
            if (s.name == str) s.print();
        }
        break;
    case StudentOption::byID:
        for (const Student& s : _students) {
            if (s.ID == str) s.print();
        }
        break;
    case StudentOption::byBirth:
        for (const Student& s : _students) {
            if (s.birth == str) s.print();
        }
        break;
    case StudentOption::byDepartment:
        for (const Student& s : _students) {
            if (s.department == str) s.print();
        }
        break;
    default:
        break;
    }
}

static bool compareByName(const Student& a, const Student& b) {
    return a.name < b.name;
}

static bool compareByID(const Student& a, const Student& b) {
    return a.ID < b.ID;
}

static bool compareByBirth(const Student& a, const Student& b) {
    return a.birth < b.birth;
}

static bool compareByDepartment(const Student& a, const Student& b) {
    return a.department < b.department;
}

void StudentDatabase::sort(StudentOption opt) {
	_sortOpt = opt;
    switch (opt) {
    case StudentOption::byName:
        ::sort(_students.begin(), _students.end(), compareByName);
        break;
    case StudentOption::byID:
        ::sort(_students.begin(), _students.end(), compareByID);
        break;
    case StudentOption::byBirth:
        ::sort(_students.begin(), _students.end(), compareByBirth);
        break;
    case StudentOption::byDepartment:
        ::sort(_students.begin(), _students.end(), compareByDepartment);
        break;
    default:
        break;
    }
}

void StudentDatabase::list() {
    cout << "Name            StudentID  Dept                Birth Year Tel" << endl;
    for (const Student& s : _students) s.print();
}
