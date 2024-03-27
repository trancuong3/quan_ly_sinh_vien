#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// Define ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

class Student
{
private:
    string name;
    int age;
    int numberofstudent; // id student
    double math;
    double english;
    double physics;
    double mediumscore;

public:
    Student() {}
    Student(int id, string n, int a, double m, double e, double p)
        : name(n), age(a), numberofstudent(id), math(m), english(e), physics(p)
    {
        mediumscore = (math + english + physics) / 3;
    }

    void setnumberofstudent(int id)
    {
        numberofstudent = id;
    }

    int getnumberofstudent()
    {
        return numberofstudent;
    }
    void setname(string n)
    {
        name=n;
    }
    string getname()
    {
        return name;
    }

    void checkpass() const
    {
        if (mediumscore > 4)
        {
            cout << GREEN << "pass" << RESET;
        }
        else
        {
            cout << RED << "not pass" << RESET;
        }
    }

    void display() const
    {
        cout << "id : " << numberofstudent << endl;
        cout << "name student: " << name << endl;
        cout << "age : " << age << endl;
        cout << "math scores : " << math << endl;
        cout << "english scores : " << english << endl;
        cout << "physics scores : " << physics << endl;
        cout << "type : ";
        checkpass();
        cout<<endl;
        cout << "-----------------------------------------" << endl;
        cout << endl;
    }
      string getLastName() const {
        string lastName = "";
        bool foundSpace = false;
        for (int i = name.length() - 1; i >= 0; i--) {
            if (name[i] == ' ') {
                foundSpace = true;
                return lastName;
            } else {
                lastName = name[i] + lastName;
            }
        }
        if (lastName == "") {
            return name;
        }
        return lastName;
    }
};

class Studentmanagement
{
private:
    vector<Student> students;

public:
      static bool compareNames(const Student& a, const Student& b) {
        if (a.getLastName() < b.getLastName()) {
            return true;
        } else {
            return false;
        }
    }
    void addstudent(Student& s)
    {
        students.push_back(s);
    }

    void displaystudent()
    {
        for (Student& s1 : students)
        {
            s1.display();
        }
    }

    void newStudent()
    {
        string name;
        int age;
        double math;
        double english;
        double physics;

        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter student age: ";
        cin >> age;

        cout << "Enter math scores: ";
        cin >> math;

        cout << "Enter english scores: ";
        cin >> english;

        cout << "Enter physics scores: ";
        cin >> physics;

        Student newstudent(students.size() + 1, name, age, math, english, physics);
        students.push_back(newstudent);
        reSortList();
    }

    void removestudent()
    {
        int numberofstudent;
        cout << "Enter student id to remove: ";
        cin >> numberofstudent;

        students.erase(students.begin() + numberofstudent - 1);
        int newid = 1;
        for (Student& studentx : students)
        {
            studentx.setnumberofstudent(newid);
            newid++;
        }
    }
 void searchname()
{
    string name;
    cout << "Enter the name of the student you want to search: ";
    cin.ignore();
    getline(cin, name);

    vector<Student> foundStudents;
    for (Student& student : students)
    {
        if (student.getname() == name)
        {
            foundStudents.push_back(student);
        }
    }

    if (foundStudents.empty())
    {
        cout << "No students found with the given name.\n";
    }
    else
    {
        for (Student& foundStudent : foundStudents)
        {
            foundStudent.display();
        }
    }
}

    void edit()
    {
        string name;
        int age;
        int id;
        double math;
        double english;
        double physics;

        cout << "Enter student id to edit: ";
        cin >> id;

        cout << "Enter new student name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter new student age: ";
        cin >> age;

        cout << "Enter new math scores: ";
        cin >> math;

        cout << "Enter new english scores: ";
        cin >> english;

        cout << "Enter new physics scores: ";
        cin >> physics;

        Student studentedit(id, name, age, math, english, physics);
        for (Student& st1 : students)
        {
            if (st1.getnumberofstudent() == id)
            {
                st1 = studentedit;
            }
        }
    }
    bool empty()
    {
        if (students.size() == 0)
            return true;
        else
            return false;
    }
     void reSortList() {
        sort(students.begin(), students.end(), compareNames);
        for (int i = 0; i < students.size(); i++) {
            students[i]. setnumberofstudent(i + 1);
        }
    }
};

int main()
{
    Studentmanagement manager;
    Student s1(1, "nguyen van A", 20, 4, 5, 6);
    manager.addstudent(s1);
    manager.reSortList();
    manager.displaystudent();

    int choose;
    do
    {
        cout << "\n=== Student Management System ===" << endl;
        cout << "1) add student" << endl;
        cout << "2) remove student" << endl;
        cout << "3) edit information student" << endl;
        cout << "4) search name student "<<endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choose;

        switch (choose)
        {
        case 1:
            manager.newStudent();
            cout << "Student added\n";
            manager.displaystudent();

            break;
        case 2:
            manager.removestudent();
            cout << "Student list after removal:\n";
            manager.displaystudent();

            break;
        case 3:
            manager.edit();
            cout << "Student after edit:\n";
            manager.displaystudent();
         ;
            break;
        case 4:
            manager.searchname();


        }
    }
    while (choose != 0);

    return 0;
}
