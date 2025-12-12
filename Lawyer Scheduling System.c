//Name: Md. Atiq Shahriar
//ID: 2212050042
//Course Name: CSE115L
//Section: 12

#include <stdio.h>
#include <stdlib.h>


void addCase() {
    FILE *file;
    int id;
    char lawyerName[50], clientName[50], date[20];

    file = fopen("schedule.txt", "a");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n=== Add New Case ===\n");
    printf("Enter Case ID: ");
    scanf("%d", &id);
    printf("Enter Lawyer Name (No spaces): ");
    scanf("%s", lawyerName);
    printf("Enter Client Name (No spaces): ");
    scanf("%s", clientName);
    printf("Enter Date (DD-MM-YYYY): ");
    scanf("%s", date);

    fprintf(file, "%d %s %s %s\n", id, lawyerName, clientName, date);
    fclose(file);
    printf("--> Saved successfully!\n");
}


void viewAllCases() {
    FILE *file;
    int id;
    char lawyerName[50], clientName[50], date[20];

    file = fopen("schedule.txt", "r");

    if (file == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n=== All Case List ===\n");
    printf("ID\tLawyer\t\tClient\t\tDate\n");
    printf("------------------------------------------------\n");

    while (fscanf(file, "%d %s %s %s", &id, lawyerName, clientName, date) != EOF) {
        printf("%d\t%s\t\t%s\t\t%s\n", id, lawyerName, clientName, date);
    }
    fclose(file);
}


void searchCase() {
    FILE *file;
    int searchID, id, found = 0;
    char lawyerName[50], clientName[50], date[20];

    file = fopen("schedule.txt", "r");

    if (file == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Case ID to search: ");
    scanf("%d", &searchID);

    while (fscanf(file, "%d %s %s %s", &id, lawyerName, clientName, date) != EOF) {
        if (id == searchID) {
            printf("\n--- Record Found ---\n");
            printf("ID: %d\n", id);
            printf("Lawyer: %s\n", lawyerName);
            printf("Client: %s\n", clientName);
            printf("Date: %s\n", date);
            found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("\nSorry! Case ID not found.\n");
    }
    fclose(file);
}


void deleteCase() {
    FILE *file, *tempFile;
    int deleteID, id, found = 0;
    char lawyerName[50], clientName[50], date[20];

    file = fopen("schedule.txt", "r");
    tempFile = fopen("temp.txt", "w");

    if (file == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Case ID to delete: ");
    scanf("%d", &deleteID);

    while (fscanf(file, "%d %s %s %s", &id, lawyerName, clientName, date) != EOF) {
        if (id == deleteID) {
            found = 1;
        } else {
            fprintf(tempFile, "%d %s %s %s\n", id, lawyerName, clientName, date);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found == 1) {
        remove("schedule.txt");
        rename("temp.txt", "schedule.txt");
        printf("\n--> Case deleted successfully!\n");
    } else {
        remove("temp.txt");
        printf("\nCase ID not found.\n");
    }
}


int main() {
    int choice;

    while (1) {
        printf("\n##################################\n");
        printf("   Lawyer Scheduling System V2\n");
        printf("##################################\n");
        printf("1. Add New Case\n");
        printf("2. View List\n");
        printf("3. Search Case\n");
        printf("4. Delete Case\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        if (choice == 1) addCase();
        else if (choice == 2) viewAllCases();
        else if (choice == 3) searchCase();
        else if (choice == 4) deleteCase();
        else if (choice == 5) {
            printf("Exiting program... Goodbye!\n");
            break;
        }
        else printf("Invalid input! Please try again.\n");
    }
    return 0;
}
