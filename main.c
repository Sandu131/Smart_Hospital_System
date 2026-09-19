#include <stdio.h>
#include <string.h>

char specialtyNames[4][30] = {"OPD", "Paediatrics", "Cardiology", "Neurology"};
float baseFees[4] = {1500.00, 2500.00, 4500.00, 5000.00};

char wardNames[4][20] = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU"};
float wardRates[4] = {3000.00, 6000.00, 12000.00, 25000.00};
int wardCapacities[4] = {20, 10, 10, 5};

int bedOccupancy[4][20] = {0};

int patient_id[100];
char patient_name[100][50];
int patient_age[100];
int patient_urgency[100];
float patient_fee[100];

int patientCount = 0;

//Register Patient Function
void registerPatient()
{
    int specChoice;
    float baseFee, surcharge = 0.0;

    while (getchar() != '\n'); // Clear buffer

    printf("\n=== PATIENT REGISTRATION ===\n");

    patient_id[patientCount] = patientCount + 1;

    printf("Enter Name: ");
    scanf("%s", patient_name[patientCount]);

    printf("Enter Age: ");
    scanf("%d", &patient_age[patientCount]);

    printf("Urgency Level (1-Normal, 2-Urgent, 3-Critical): ");
    scanf("%d", &patient_urgency[patientCount]);

    printf("Select Specialty (1-OPD, 2-Paediatrics, 3-Cardiology, 4-Neurology): ");
    scanf("%d", &specChoice);

    while (specChoice < 1 || specChoice > 4)
    {
        printf("Invalid choice! Enter (1-4): ");
        scanf("%d", &specChoice);
    }

    baseFee = baseFees[specChoice - 1];

    if (patient_urgency[patientCount] == 2) surcharge = baseFee * 0.20;
    if (patient_urgency[patientCount] == 3) surcharge = baseFee * 0.50;

    patient_fee[patientCount] = baseFee + surcharge;

    printf("\n--- REGISTRATION SUMMARY ---\n");
    printf("Patient ID : %d\n", patient_id[patientCount]);
    printf("Name       : %s (%d yrs)\n", patient_name[patientCount], patient_age[patientCount]);
    printf("Specialty  : %s\n", specialtyNames[specChoice - 1]);
    printf("Base Fee   : LKR %.2f\n", baseFee);
    printf("Surcharge  : LKR %.2f\n", surcharge);
    printf("Total Fee  : LKR %.2f\n", patient_fee[patientCount]);
    printf("----------------------------\n");

    patientCount++;
}

//Display Registered Patients Function
void displayPatients()
{
    int i;

    if (patientCount == 0)
    {
        printf("\nNo patients registered yet!\n");
        return;
    }

    printf("\n=== REGISTERED PATIENTS ===\n");

    for (i = 0; i < patientCount; i++)
    {
        printf("\nPatient ID : %d\n", patient_id[i]);
        printf("Name       : %s\n", patient_name[i]);
        printf("Age        : %d\n", patient_age[i]);
        printf("Urgency    : %d\n", patient_urgency[i]);
        printf("Total Fee  : LKR %.2f\n", patient_fee[i]);
        printf("---------------------------\n");
    }
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

//Assign Patient to Ward
void assignWard()
{
    int pId, wardChoice, bedNum;

    printf("\n=== ASSIGN WARD ===\n");

    printf("Enter Patient ID: ");
    scanf("%d", &pId);

    printf("Select Ward (1-General, 2-Paediatric, 3-Surgical, 4-ICU): ");
    scanf("%d", &wardChoice);

    printf("Enter Bed Number: ");
    scanf("%d", &bedNum);

    bedOccupancy[wardChoice - 1][bedNum - 1] = 1;

    printf("\nPatient %s assigned to %s, Bed #%d successfully!\n",
           patient_name[pId - 1], wardNames[wardChoice - 1], bedNum);
}

void displayMenu()
{
    printf("\n===== SMART HOSPITAL SYSTEM =====\n");
    printf("1. Register Patient\n");
    printf("2. Display Patients\n");
    printf("3. Bed Status\n");
    printf("4. Assign Ward\n");
    printf("5. Priority Queue\n");
    printf("6. Reports\n");
    printf("7. Exit\n");
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
                displayPatients();
                break;

            case 3:
                displayBedStatus();
                break;

            case 4:
                assignWard();
                break;

            case 5:
                printf("Priority Queue\n");
                break;

            case 6:
                printf("Reports\n");
                break;

            case 7:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 6);

    return 0;
}
