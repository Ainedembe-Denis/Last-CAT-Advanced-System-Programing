#include <stdio.h>

// Structure to hold vehicle details
struct Vehicle {
    int id;
    char type[20];
    int capacity;
};

// Save vehicle details to file
void saveToFile(struct Vehicle v) {
    // 'a' append to the existing data
    FILE *fp = fopen("vehicles.bat", "a");
    if (fp != NULL) {
        fprintf(fp, "%d\t%s\t%d\n", v.id, v.type, v.capacity);
        fclose(fp);
    }
}

// Display all vehicles from file
void displayFile() {
    FILE *fp = fopen("vehicles.bat", "r");
    struct Vehicle v;

    if (fp != NULL) {
        printf("\nAvailable Vehicles:\n");
        
        while (fscanf(fp, "%d\t%[^\t]\t%d\n", &v.id, v.type, &v.capacity) == 3) {
            printf("ID: %d | Type: %s | Capacity: %d\n", v.id, v.type, v.capacity);
        }
        fclose(fp);
    }
}

int main() {
    int n;
    printf("TRANSPORT MANAGEMENT SYSTEM\n");
    printf("Enter number of vehicles to add: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        struct Vehicle v;
        printf("\nEnter details for vehicle %d:\n", i + 1);

        printf("ID: ");
        scanf("%d", &v.id);
        
        getchar(); 

        printf("Type: ");
        fgets(v.type, sizeof(v.type), stdin);
        
        for (int j = 0; v.type[j] != '\0'; j++) {
            if (v.type[j] == '\n') {
                v.type[j] = '\0';
                break;
            }
        }

        printf("Capacity: ");
        scanf("%d", &v.capacity);

        saveToFile(v);
    }

    displayFile();

    return 0;
}
