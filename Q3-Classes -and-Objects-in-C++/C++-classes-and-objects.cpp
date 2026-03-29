#include <iostream>
#include <string>

using namespace std;

// a) Defining a class Student
class Student {
private:
    string name;
    int id;
    float marks;

public:
    // b) Implementing a Constructor
    Student(string n, int i, float m) {
        name = n;
        id = i;
        marks = m;
    }

    // Method to display details
    void displayDetails() {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Marks: " << marks << endl;
        cout << "------------------------" << endl;
    }
};

// c) Main function
int main() {
    // Creating two student objects
    Student s1("Denis Ainedembe", 101, 87.0);
    Student s2("Olivia Namusoke", 102, 94.5);

    // Display their details
    s1.displayDetails();
    s2.displayDetails();

    return 0;
}
