#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Student {
	string name;		//15
	string ID;			//10
	string department;	//25
	string birth;		//4
	string tel;			//12

	string admission() const {
		return ID.substr(0, 4);
	}

	void print(ostream& file = cout) const {
		char cstr[128];
		snprintf(cstr, 128, "%-15s %-10s %-25s %-4s %-12s", name.c_str(), ID.c_str(), department.c_str(), birth.c_str(), tel.c_str());
		file << string(cstr) << endl;
	}
};

enum StudentOption {
	byName = 1,
	byID,
	byBirth,
	byDepartment
};

class StudentDatabase {
private:
	vector<Student> _students;
	const string& _filename;
	StudentOption _sortOpt = StudentOption::byName;

public:
	StudentDatabase(const string& filename);
	~StudentDatabase();

	void load();
	void save();

	void insert(const Student& student);
	void search(const string& str, StudentOption opt);
	void sort(StudentOption opt);
	void list();
};

/*TODO 함수 뒤의 const의 역할:
    - 객체 내부 변수 변경 불가
    - const 함수만 호출 가능
*/
