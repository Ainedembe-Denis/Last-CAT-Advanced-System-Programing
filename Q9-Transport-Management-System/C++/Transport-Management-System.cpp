#include <iostream>
#include <fstream>   
#include <string>

using namespace std;

// Vehicle class definition
class Vehicle {
    int id;       
    string type; 
    int capacity; 

public:
    // Constructor to initialize vehicle details
    Vehicle(int i, string t, int c) : id(i), type(t), capacity(c) {}

    // Method to save vehicle details to file
    void saveToFile() {
        ofstream fout("vehicles.bat", ios::app); 
        fout << id << "\t" << type << "\t" << capacity << endl;
        fout.close();
    }

    // Static method to display all vehicles
    static void displayFile() {
        ifstream fin("vehicles.bat"); 
        int id, capacity;
        string type;
        cout << "\nAvailable Vehicles (from file):" << endl;
        
        while (fin >> id >> ws && getline(fin, type, '\t') && fin >> capacity) {
            cout << "ID: " << id << " | Type: " << type << " | Capacity: " << capacity << endl;
        }
        fin.close(); 
    }
};

int main() {
    int n;
    cout << "TRANSPORT MANAGEMENT SYSTEM" << endl;
    cout << "Enter number of vehicles to add: " ;
    cin >> n; 

    // Loop to input multiple vehicles
    for (int i = 0; i < n; i++) {
        int id, capacity;
        string type;
        cout << "\nEnter details for vehicle " << i+1 << ":\n";
        
        cout << "ID: "; cin >> id;
        cout << "Type: "; getline(cin >> ws, type);
        cout << "Capacity: "; cin >> capacity;

        // Create object and save to file
        Vehicle v(id, type, capacity);
        v.saveToFile();
    }

    // Display all vehicles from file
    Vehicle::displayFile();
    return 0;
}
