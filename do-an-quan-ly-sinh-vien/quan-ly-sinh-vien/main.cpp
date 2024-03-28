#include <iomanip> // For setw
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// Define ANSI color codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

class Student {
private:
    string name;
    int age;
    int studentID; // id student
    double math;
    double english;
    double physics;
    double mediumScore;

public:
    Student() {}
    Student(int id, string n, int a, double m, double e, double p)
        : name(n), age(a), studentID(id), math(m), english(e), physics(p)
    {
        mediumScore = (math + english + physics) / 3;
    }

    void setStudentID(int id)
    {
        studentID = id;
    }

    int getStudentID() const
    {
        return studentID;
    }

    void setName(string n)
    {
        name = n;
    }

    string getName() const
    {
        return name;
    }

    void checkPass() const
    {
        if (mediumScore > 4)
        {
            cout << GREEN << "PASS " << RESET;
        }
        else
        {
            cout << RED << "NOT PASS  " << RESET;
        }
    }

    void displayStudent() const
    {
        cout << "| " << setw(3) << studentID << " | " << setw(18) << name << " | " << setw(3) << age << " | "
             << setw(10) << math << " | " << setw(13) << english << " | " << setw(13) << physics << " | ";
        checkPass();
        cout << setw(10 - (mediumScore > 4 ? 3 : 8)) << " |" << endl;
    }

    string getLastName() const
    {
        string lastName = "";
        bool foundSpace = false;
        for (int i = name.length() - 1; i >= 0; i--)
        {
            if (name[i] == ' ')
            {
                foundSpace = true;
                return lastName;
            }
            else
            {
                lastName = name[i] + lastName;
            }
        }
        if (lastName == "")
        {
            return name;
        }
        return lastName;
    }
};

class StudentManagement {
private:
    vector<Student> students;

public:
    static bool compareNames(const Student &a, const Student &b)
    {
        return a.getLastName() < b.getLastName();
    }

    void addStudent(Student &s)
    {
        students.push_back(s);
    }

    void displayStudents()
    {
        cout << "---------------------------------------------------------------------------------------------------" << endl;
        // Print blank space to center "List Students"
        cout << "| " << setw(3) << "ID" << " | " << setw(18) << "Name" << " | " << setw(3) << "Age" << " | "
             << setw(10) << "Math" << " | " << setw(13) << "English" << " | " << setw(13) << "Physics" << " | "
             << setw(10) << "Type" << " |" << endl;
        cout << "---------------------------------------------------------------------------------------------------" << endl;
        for (Student &s : students)
        {
            s.displayStudent();
        }
        cout << "---------------------------------------------------------------------------------------------------" << endl;
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

        Student newStudent(students.size() + 1, name, age, math, english, physics);
        students.push_back(newStudent);
        reSortList();
    }

    void removeStudent()
    {
        int studentID;
        cout << "Enter student id to remove: ";
        cin >> studentID;

        students.erase(students.begin() + studentID - 1);
        int newID = 1;
        for (Student &student : students)
        {
            student.setStudentID(newID);
            newID++;
        }
    }

    void searchName()
    {
        string name;
        cout << "Enter the name of the student you want to search: ";
        cin.ignore();
        getline(cin, name);

        vector<Student> foundStudents;
        for (Student &student : students)
        {
            if (student.getName() == name)
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
            cout << "---------------------------------------------------------------------------------------------------" << endl;
            cout << "| " << setw(3) << "ID" << " | " << setw(15) << "Name" << " | " << setw(3) << "Age" << " | "
                 << setw(10) << "Math" << " | " << setw(13) << "English" << " | " << setw(13) << "Physics" << " | "
                 << setw(10) << "Type" << " |" << endl;
            cout << "---------------------------------------------------------------------------------------------------" << endl;
            for (Student &foundStudent : foundStudents)
            {
                foundStudent.displayStudent();
            }
            cout << "---------------------------------------------------------------------------------------------------" << endl;
        }
    }

    void editStudent()
    {
        int id;
        string name;
        int age;
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

        Student studentEdit(id, name, age, math, english, physics);
        for (Student &st1 : students)
        {
            if (st1.getStudentID() == id)
            {
                st1 = studentEdit;
            }
        }
        reSortList();
    }

    bool empty()
    {
        return students.empty();
    }

    void reSortList()
    {
        sort(students.begin(), students.end(), compareNames);
        for (int i = 0; i < students.size(); i++)
        {
            students[i].setStudentID(i + 1);
        }
    }
};

int main()
{
    StudentManagement manager;
    Student s1(1, "Nguyen Van An", 20, 4, 2, 1);
    manager.addStudent(s1);
    Student s2(2, "Nguyen Van BA", 21, 9, 9, 9);
    manager.addStudent(s2);
    manager.reSortList();
    manager.displayStudents();

    int choose;
    do
    {
        cout << "\n\n---------------------------------------------" << endl;
        cout << "|          Student Management System         |" << endl;
        cout << "|--------------------------------------------|  " << endl;
        cout << "| Options:                                   |" << endl;
        cout << "| 1. Add Student                             |" << endl;
        cout << "| 2. Remove Student                          |" << endl;
        cout << "| 3. Edit Student Information                |" << endl;
        cout << "| 4. Search Student by Name                  |" << endl;
        cout << "| 0. Exit                                    |" << endl;
        cout << "---------------------------------------------" << endl;

        cin >> choose;

        switch (choose)
        {
        case 1:
            manager.newStudent();
            cout << "Student added\n";
            manager.displayStudents();
            break;
        case 2:
            manager.removeStudent();
            cout << "Student list after removal:\n";
            manager.displayStudents();
            break;
        case 3:
            manager.editStudent();
            cout << "Student after edit:\n";
            manager.displayStudents();
            break;
        case 4:
            manager.searchName();
            break;
        }
    } while (choose != 0);

    return 0;
}
