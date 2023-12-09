#include <iostream>
#include <string>

using namespace std;

class Date {
	int day;
	int month;
	int year;

public:
	Date() : day(0), month(0), year(0) {};
	Date(int d, int m, int y) : day(d), month(m), year(y) {};
};

class Person {
	string name;
	string pin;
	Date birthday;
	string* addresses;
	int addressesCount;

public:
	Person()
	{
		this->name = " ";
		this->pin = " ";
		Date d;
		this->birthday = d;
		this->addresses = nullptr;
		this->addressesCount = 0;
	}

	Person(string name, string pin, Date birthday, string* adresses, int addressesCount) :
		name(name), pin(pin), birthday(birthday), addressesCount(addressesCount) {
		this->birthday = birthday;
		this->addresses = new string[addressesCount];
		for (int i = 0; i < addressesCount; i++)
			this->addresses[i] = addresses[i];
	}

	//Constructor de copiere
	Person(const Person& p)
	{
		this->name = p.name;
		this->pin = p.pin;
		this->birthday = p.birthday;
		this->addressesCount = p.addressesCount;
		this->addresses = new string[p.addressesCount];
		for (int i = 0; i < p.addressesCount; i++)
			this->addresses[i] = p.addresses[i];
	}

	//Operator=
	Person& operator=(const Person& p)
	{
		if (this != &p)
		{
			this->name = p.name;
			this->pin = p.pin;
			this->birthday = p.birthday;
			delete[] this->addresses;
			this->addressesCount = p.addressesCount;
			this->addresses = new string[p.addressesCount];
			for (int i = 0; i < p.addressesCount; i++)
				this->addresses[i] = p.addresses[i];
		}
		return *this;
	}

	//Destructor
	~Person() {
		delete[] addresses;
	}
};

class Student : Person {
	int regNo;
	float* grades;
	int gradesCount;
	bool scholarship;
public:
	Student() : Person() {
		this->regNo = 0;
		this->grades = nullptr;
		this->gradesCount = 0;
		this->scholarship = false;
	}

	Student(string name, string pin, Date birthday, string* addresses, int addressesCount, int regNo, float* grades, int gradesCount, bool scholarship)
		: Person(name, pin, birthday, addresses, addressesCount)
	{
		this->regNo = regNo;
		this->gradesCount = gradesCount;
		this->grades = new float[gradesCount];
		for (int i = 0; i < gradesCount; i++) {
			this->grades[i] = grades[i];
		}
		this->scholarship = scholarship;
	}

	//Constructor de copiere
	Student(const Student& s) : Person(s) {
		this->regNo = s.regNo;
		this->gradesCount = s.gradesCount;
		this->scholarship = s.scholarship;
		this->grades = new float[gradesCount];
		for (int i = 0; i < gradesCount; i++) {
			this->grades[i] = s.grades[i];
		}
	}

	//Operator=
	Student& operator=(const Student& s)
	{
		if (this != &s)
		{
			this->regNo = s.regNo;
			this->gradesCount = s.gradesCount;
			this->grades = new float[gradesCount];
			for (int i = 0; i < gradesCount; i++) {
				this->grades[i] = s.grades[i];
			}
			this->scholarship = s.scholarship;
		}
		return *this;
	}

	//Destructor
	~Student() {
		delete[] grades;
	}
};

class University
{
	string name;
	string address;
	Student* students;
	int studentsCount;

public:
	University() {
		string name = "";
		string address = "";
		Student* students = nullptr;
		int studentsCount = 0;
	}

	University(string name, string address, Student* students, int studentsCount) {
		this->name = name;
		this->address = address;
		this->studentsCount = studentsCount;
		this->students = new Student[studentsCount];
		for (int i = 0; i < studentsCount; i++)
			this->students[i] = students[i];
	}

	//Constructor de copiere
	University(const University& u) {
		this->name = u.name;
		this->address = u.address;
		this->studentsCount = u.studentsCount;
		this->students = new Student[studentsCount];
		for (int i = 0; i < studentsCount; i++)
			this->students[i] = u.students[i];
	}

	//Operator=
	University& operator=(const University& u)
	{
		if (this != &u)
		{
			this->name = u.name;
			this->address = u.address;
			this->studentsCount = u.studentsCount;
			this->students = new Student[studentsCount];
			for (int i = 0; i < studentsCount; i++)
				this->students[i] = u.students[i];
		}
		return *this;
	}

	//Destructor
	~University() {
		delete[] students;
	}
};


int main()
{
	Date d1;
	Date d2(6, 12, 2023);

	Person p1;
	string* addresses = new string[3];
	addresses[0] = "...Bucuresti";
	addresses[1] = "...Arad";
	addresses[0] = "...Constanta";


	Person p2("Popescu Andrei", "50370104021", d2, addresses, 3);

	Student s1;

	float* grades = new float[5];
	grades[0] = 6;
	grades[1] = 7;
	grades[2] = 8;
	grades[3] = 9;
	grades[4] = 5;

	Student s2("Popescu Andrei", "5030104021232", d2, addresses, 3, 123, grades, 5, true);

	Student s3("Andresan Andrei", "5030104021232", d2, addresses, 3, 123, grades, 5, true);

	Student* students = new Student[3];
	students[0] = s1;
	students[1] = s2;
	students[2] = s3;
	University u("Universitate ASE", "Adresa Romana", students, 2);

	return 0;
}