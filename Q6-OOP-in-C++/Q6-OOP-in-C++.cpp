#include <iostream>
#include <string>
using namespace std;

// Base class: Vehicle
class Vehicle {
protected:
    string brand;
    int year;

public:
    Vehicle(string brd, int yr) {
        brand = brd;
        year = yr;
    }

    // Virtual method to display details
    virtual void displayDetails() {
        cout << "Vehicle Details:" << endl;
        cout << "Brand: " << brand << endl;
        cout << "Manufacture Year: " << year << endl;
    }
};

// Derived class: Car
class Car : public Vehicle {
private:
    string model;

public:
    Car(string brd, int yr, string mdl) : Vehicle(brd, yr) {
        model = mdl;
    }

    // Overriding displayDetails
    void displayDetails() override {
        cout << "\nCar Details:" << endl;
        cout << "Brand: " << brand << endl;
        cout << "Model: " << model << endl;
        cout << "Manufacture Year: " << year << endl;
    }
};

int main() {
    // Vehicle object
    Vehicle v1("Subaru", 2016);
    v1.displayDetails();

    // Car object
    Car c1("Toyota", 2012, "Rav4");
    c1.displayDetails();

    return 0;
}
