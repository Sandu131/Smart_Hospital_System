#include <stdio.h>
#include <string.h>

char specialtyNames[4][30] = {"General Practice (OPD)", "Paediatrics", "Cardiology", "Neurology"};
float baseFees[4] = {1500.00, 2500.00, 4500.00, 5000.00};

char wardNames[4][20] = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU"};
float wardRates[4] = {3000.00, 6000.00, 12000.00, 25000.00};
int wardCapacities[4] = {20, 10, 10, 5};

int bedOccupancy[4][20] = {0};

typedef struct {
    int id;
    char name[50];
    int age;
    int urgency;
    float totalFee;
} Patient;

Patient patients[100];
int patientCount = 0;

// Basic Patient Details with speciality selection
void registerPatient()
{
    char name[50];
    int age, urgency, specChoice;
    float baseFee, surcharge = 0.0;

    while (getchar() != '\n'); // Clear buffer

    printf("\n=== PATIENT REGISTRATION ===\n");
    printf("Enter Name: ");
    scanf("%[^\n]", name);

    printf("Enter Age: ");
    scanf("%d", &age);

    printf("Urgency Level (1-Normal, 2-Urgent, 3-Critical): ");
    scanf("%d", &urgency);

    printf("Select Specialty (1-OPD, 2-Paediatrics, 3-Cardiology, 4-Neurology): ");
    scanf("%d", &specChoice);

    while (specChoice < 1 || specChoice > 4) {
        printf("Invalid choice! Enter (1-4): ");
        scanf("%d", &specChoice);
    }

    baseFee = baseFees[specChoice - 1];

    if (urgency == 2) surcharge = baseFee * 0.20;
    if (urgency == 3) surcharge = baseFee * 0.50;

    patients[patientCount].id = patientCount + 1;
    patients[patientCount].age = age;
    patients[patientCount].urgency = urgency;
    patients[patientCount].totalFee = baseFee + surcharge;


    int i = 0;
    while (name[i] != '\0')
    {
        patients[patientCount].name[i] = name[i];
        i++;
    }
    patients[patientCount].name[i] = '\0';

    // Summary
    printf("\n--- REGISTRATION SUMMARY ---\n");
    printf("Patient ID : %d\n", patients[patientCount].id);
    printf("Name       : %s (%d yrs)\n", name, age);
    printf("Specialty  : %s\n", specialtyNames[specChoice - 1]);
    printf("Base Fee   : LKR %.2f\n", baseFee);
    printf("Surcharge  : LKR %.2f\n", surcharge);
    printf("Total Fee  : LKR %.2f\n", patients[patientCount].totalFee);
    printf("----------------------------\n");

    patientCount++;
}

//Display bed status
void displayBedStatus()
{
    int i, j;
    printf("\n=== BED STATUS ===\n");

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
