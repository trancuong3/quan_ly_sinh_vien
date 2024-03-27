#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Define ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

class Student
{
private:
    string name;
    int age;
    int numberofstudent; // id student
    double math;
    double english;
    double physics;
    double mediumScore;

public:
    Student() {}
    Student(int id, string n, int a, double m, double e, double p)
        : name(n), age(a), numberofstudent(id), math(m), english(e), physics(p)
    {}

    void setNumberOfStudent(int id)
    {
        numberofstudent = id;
    }

    int getNumberOfStudent()
    {
        return numberofstudent;
    }

    void setName(string n)
    {
        name = n;
    }

    string getName()
    {
        return name;
    }

    void checkPass() const
    {
        if (mediumScore > 4)
        {
            cout << GREEN << "pass" << RESET;
        }
        else
        {
            cout << RED << "not pass" << RESET;
        }
    }

    void calculateMediumScore()
    {
        mediumScore = (math + english + physics) / 3;
    }

    void displayStudent() const
    {
        cout << "| " << setw(2) << numberofstudent << " | " << setw(12) << name << " | " << setw(3) << age << " | ";
        setColorByScore(math);
        cout << setw(10) << math << RESET << " | ";
        setColorByScore(english);
        cout << setw(13) << english << RESET << " | ";
        setColorByScore(physics);
        cout << setw(12) << physics << RESET << " | ";
        checkPass();
        cout << setw(11) << " |" << endl;
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

private:
    void setColorByScore(double score) const
    {
        if (score < 4)
        {
            cout << RED;
        }
        else if (score >= 4 && score < 7)
        {
            cout << YELLOW;
        }
        else
        {
            cout << GREEN;
        }
    }
};

class StudentManagement
{
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
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << "| ID |     Name     | Age | Math Score | English Score | Physics Score|    Type           |" << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        for (Student &s1 : students)
        {
            s1.displayStudent();
        }
        cout << "-------------------------------------------------------------------------------------------------" << endl;
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
        int numberofstudent;
        cout << "Enter student id to remove: ";
        cin >> numberofstudent;

        students.erase(students.begin() + numberofstudent - 1);
        int newid = 1;
        for (Student &studentx : students)
        {
            studentx.setNumberOfStudent(newid);
            newid++;
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
            cout << "-------------------------------------------------------------------------------------------------" << endl;
            cout << "| ID |     Name     | Age | Math Score | English Score | Physics Score |    Type    |" << endl;
            cout << "-------------------------------------------------------------------------------------------------" << endl;
            for (Student &foundStudent : foundStudents)
            {
                foundStudent.displayStudent();
            }
            cout << "-------------------------------------------------------------------------------------------------" << endl;
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
            if (st1.getNumberOfStudent() == id)
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
            students[i].setNumberOfStudent(i + 1);
        }
    }
};

int main()
{
    StudentManagement manager;
    Student s1(1, "nguyen van A", 20, 4, 5, 6);
    manager.addStudent(s1);
    manager.reSortList();
    manager.displayStudents();

    int choose;
    do
    {
        cout << "\n=== Student Management System ===" << endl;
        cout << "1) add student" << endl;
        cout << "2) remove student" << endl;
        cout << "3) edit information student" << endl;
        cout << "4) search name student " << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
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
