#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 50 // Current License limit: 50 employees

// Structure ---------------------------------------------
typedef struct {
    int id;
    char name[50];
    char gender[10];
    char role[30];
    float salary;
} Employee;

// Function Declarations ---------------------------------
void addEmployee(Employee *emp, int *count);
void displayEmployees(Employee *emp, int count);
void updateEmployee(Employee *emp, int count);
void deleteEmployee(Employee *emp, int *count);
void saveEmployees(Employee *emp, int count);
void loadEmployees(Employee *emp, int *count);
int menu();

// Main Function ----------------------------------------
int main() {
    Employee employees[MAX_EMPLOYEES];
    int count = 0;

    // Load any existing data from the file
    loadEmployees(employees, &count);

    while (1) {
        int userChoice = menu();
        switch (userChoice) {
            case 1:
                addEmployee(employees, &count);
                break;
            case 2:
                displayEmployees(employees, count);
                break;
            case 3:
                updateEmployee(employees, count);
                break;
            case 4:
                deleteEmployee(employees, &count);
                break;
            case 5:
                saveEmployees(employees, count);
                printf("\nSaving data and shutting down. Have a great day!\n");
                exit(0);
            default:
                printf("\nInvalid option. Please try again.\n");
        }
    }
    return 0;
}

// Main Function ---------------------------------------------
int menu() {
    int choice;
    printf("\nEMPLOYEE MANAGEMENT SYSTEM\n");
    printf("1. Add Employee\n");
    printf("2. Display Employees\n");
    printf("3. Update Employee\n");
    printf("4. Delete Employee\n");
    printf("5. Exit (Save & Quit)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar(); // clear buffer
    return choice;
}

// Create Employee --------------------------------------------
void addEmployee(Employee *emp, int *count) {
    if (*count >= MAX_EMPLOYEES) {
        printf("\nSorry, the database is full. You need to delete someone first or upgrade your license\n");
        return;
    }

    Employee *newEmp = emp + *count; // Pointer to the next empty slot

    printf("\nAdding a New Employee Record");
    printf("\nEnter Employee ID: ");
    scanf("%d", &newEmp->id);
    getchar();

    printf("Enter Employee Name: ");
    fgets(newEmp->name, sizeof(newEmp->name), stdin);
    newEmp->name[strcspn(newEmp->name, "\n")] = '\0'; // Remove newline

    printf("Enter Gender: ");
    scanf("%s", newEmp->gender);
    getchar();

    printf("Enter Role: ");
    fgets(newEmp->role, sizeof(newEmp->role), stdin);
    newEmp->role[strcspn(newEmp->role, "\n")] = '\0';

    printf("Enter Salary: ");
    scanf("%f", &newEmp->salary);
    getchar(); // Clean up

    (*count)++;
    printf("\n Employee has been added Successfully!\n");
}

// Show / Display Employees -------------------------------------------
void displayEmployees(Employee *emp, int count) {
    if (count == 0) {
        printf("\nEmployee list is currently empty.\n");
        return;
    }

    // Balance sizes: ID(5), Name(25), Gender(10), Role(20), Salary(10)
    printf("\n%-5s %-25s %-10s %-20s %-10s\n", "ID", "Name", "Gender", "Role", "Salary");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        Employee *curr = emp + i; // Accessing structure using pointer arithmetic
        printf("%-5d %-25s %-10s %-20s %-10.2f\n",
               curr->id, curr->name, curr->gender, curr->role, curr->salary);
    }
}

// Update Employee -----------------------------------------------------
void updateEmployee(Employee *emp, int count) {
    int searchId, found = 0;
    printf("\nPlease enter the ID of the employee you want to update: ");
    scanf("%d", &searchId);
    getchar();

    for (int i = 0; i < count; i++) {
        Employee *curr = emp + i; // Pointer to the current employee
        if (curr->id == searchId) {
            found = 1;
            printf("\nPlease provide the updated information below:\n");

            printf("Enter Name: ");
            fgets(curr->name, sizeof(curr->name), stdin);
            curr->name[strcspn(curr->name, "\n")] = '\0';

            printf("Enter Gender: ");
            scanf("%s", curr->gender);
            getchar();

            printf("Enter Role: ");
            fgets(curr->role, sizeof(curr->role), stdin);
            curr->role[strcspn(curr->role, "\n")] = '\0';

            printf("Enter Salary: ");
            scanf("%f", &curr->salary);
            getchar();

            printf("\nThe employee's records have been updated successfully!\n");
            break;
        }
    }
    if (!found) printf("\nSorry, couldn't find an employee with ID %d.\n", searchId);
}

// Delete Employee -----------------------------------------------------
void deleteEmployee(Employee *emp, int *count) {
    int deleteId, found = 0;
    printf("\nPlease enter the ID of the employee to remove: ");
    scanf("%d", &deleteId);
    getchar();

    for (int i = 0; i < *count; i++) {
        Employee *curr = emp + i; // Using pointer arithmetic to find employee
        if (curr->id == deleteId) {
            found = 1;
            // Shifting records to fill the gap after deletion using pointer logic
            for (int j = i; j < *count - 1; j++) {
                *(emp + j) = *(emp + j + 1); // Directly copy data using pointers
            }
            (*count)--;
            printf("\nThe employee record has been removed.\n");
            break;
        }
    }
    if (!found) printf("\nNo employee found with ID %d, so nothing was deleted.\n", deleteId);
}

// Save Employee to File --------------------------------
void saveEmployees(Employee *emp, int count) {
    FILE *fp = fopen("employee.dat", "wb");
    if (fp == NULL) {
        printf("\nOops! Could not open the file for saving.\n");
        return;
    }
    fwrite(emp, sizeof(Employee), count, fp);
    fclose(fp);
    printf("\nData successfully saved to 'employee.dat'.\n");
}

// Load Employee from File ----------------------------
void loadEmployees(Employee *emp, int *count) {
    FILE *fp = fopen("employee.dat", "rb");
    if (fp == NULL) {
        *count = 0;
        return;
    }
    *count = fread(emp, sizeof(Employee), MAX_EMPLOYEES, fp);
    fclose(fp);
}
