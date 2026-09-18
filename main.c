#include <stdio.h>
#include <string.h>

// Basic Patient Details
void registerPatient()
{
    char name[50];
    int age, urgency;

    while (getchar() != '\n');

    printf("\n=== PATIENT REGISTRATION ===\n");

    printf("Enter Patient Name: ");
    scanf(" %s", name);

    printf("Enter Age: ");
    scanf("%d", &age);

    printf("Select Urgency Level (1 = Normal, 2 = Urgent, 3 = Critical): ");
    scanf("%d", &urgency);

    printf("\nPatient %s (%d yrs) registered with Urgency Level %d.\n", name, age, urgency);
}

//Display bed status
char specialtyNames[4][30] = {"General Practice (OPD)", "Paediatrics", "Cardiology", "Neurology"};
float baseFees[4] = {1500.00, 2500.00, 4500.00, 5000.00};

char wardNames[4][20] = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU"};
float wardRates[4] = {3000.00, 6000.00, 12000.00, 25000.00};
int wardCapacities[4] = {20, 10, 10, 5};

int bedOccupancy[4][20] = {0};

void displayBedStatus()
{
    int i, j;
    printf("\n=== BED OCCUPANCY STATUS ===\n");

    for (i = 0; i < 4; i++)
    {
        printf("\n%s (Capacity: %d)\n", wardNames[i], wardCapacities[i]);
        printf("Beds: ");

        for (j = 0; j < wardCapacities[i]; j++)
        {
            if (bedOccupancy[i][j] == 0)
            {
                printf("[0] ");
            }
            else
            {
                printf("[1] ");
            }
        }
        printf("\n");
    }
}
void displayMenu()
{
    printf("\n===== SMART HOSPITAL SYSTEM =====\n");
    printf("1. Register Patient\n");
    printf("2. Display Patients\n");
    printf("3. Bed Status\n");
    printf("4. Priority Queue\n");
    printf("5. Reports\n");
    printf("6. Exit\n");
}

int main()
{
    int choice;

    do
    {
        displayMenu();   // function call BEFORE switch

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                registerPatient();
                break;

            case 2:
                printf("Display Patients\n");
                break;

            case 3:
                displayBedStatus();
                break;

            case 4:
                printf("Priority Queue\n");
                break;

            case 5:
                printf("Reports\n");
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 6);

    return 0;
}
