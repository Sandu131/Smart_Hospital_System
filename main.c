#include <stdio.h>
#include <string.h>

char specialtyNames[4][30] = {"OPD", "Paediatrics", "Cardiology", "Neurology"};
float baseFees[4] = {1500.00, 2500.00, 4500.00, 5000.00};
int consultationTimes[4] = {15, 20, 30, 30};
int specialtyQueue[4] = {0, 0, 0, 0};

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
    int specChoice, isAdmitted = 0, wardChoice = 0, days = 0;
    float baseFee, surcharge = 0.0, wardCost = 0.0, grossTotal, discount = 0.0, finalPayable;
    int waitTime = 0;
    int currentQueue, timePerPatient;

    while (getchar() != '\n');

    printf("\n=== PATIENT REGISTRATION ===\n");

    patient_id[patientCount] = patientCount + 1;

    printf("Enter Name: ");
    scanf("%[^\n]", patient_name[patientCount]);

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

    currentQueue = specialtyQueue[specChoice - 1];
    timePerPatient = consultationTimes[specChoice - 1];

    waitTime = currentQueue * timePerPatient;
    specialtyQueue[specChoice - 1] = currentQueue + 1;

    if (patient_urgency[patientCount] == 2) surcharge = baseFee * 0.20;
    if (patient_urgency[patientCount] == 3) surcharge = baseFee * 0.50;

    printf("Admitted to Ward? (1=Yes, 0=No): ");
    scanf("%d", &isAdmitted);

    if (isAdmitted == 1) {
        printf("Select Ward (1-General, 2-Paediatric, 3-Surgical, 4-ICU): ");
        scanf("%d", &wardChoice);
        printf("Enter Days Admitted: ");
        scanf("%d", &days);

        wardCost = days * wardRates[wardChoice - 1];
    }

    grossTotal = baseFee + surcharge + wardCost;

    if (patient_age[patientCount] < 5 || patient_age[patientCount] > 65)
    {
        discount = grossTotal * 0.15;
    }

    finalPayable = grossTotal - discount;
    patient_fee[patientCount] = finalPayable;

    printf("\n--- REGISTRATION SUMMARY ---\n");
    printf("Patient ID  : PAT-%d\n", patient_id[patientCount] + 1000);
    printf("Name        : %s (%d yrs)\n", patient_name[patientCount], patient_age[patientCount]);
    printf("Base Fee    : LKR %.2f\n", baseFee);
    printf("Surcharge   : LKR %.2f\n", surcharge);
    printf("Ward Cost   : LKR %.2f\n", wardCost);
    printf("Gross Total : LKR %.2f\n", grossTotal);
    printf("Discount    : LKR -%.2f\n", discount);
    printf("Final Bill  : LKR %.2f\n", finalPayable);
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

    if (patientCount == 0)
    {
        printf("\nNo patients available to assign!\n");
        return;
    }

    printf("\n=== ASSIGN WARD ===\n");

    printf("Enter Patient ID (Numeric part, e.g. 1): ");
    scanf("%d", &pId);

    // Patient ID Validation
    while (pId < 1 || pId > patientCount)
    {
        printf("Invalid Patient ID! Enter again (1-%d): ", patientCount);
        scanf("%d", &pId);
    }

    printf("Select Ward (1-General, 2-Paediatric, 3-Surgical, 4-ICU): ");
    scanf("%d", &wardChoice);

    while (wardChoice < 1 || wardChoice > 4)
    {
        printf("Invalid Ward! Choice must be (1-4): ");
        scanf("%d", &wardChoice);
    }

    printf("Enter Bed Number (1-%d): ", wardCapacities[wardChoice - 1]);
    scanf("%d", &bedNum);

    while (bedNum < 1 || bedNum > wardCapacities[wardChoice - 1])
    {
        printf("Invalid Bed Number for %s! Enter (1-%d): ",
               wardNames[wardChoice - 1], wardCapacities[wardChoice - 1]);
        scanf("%d", &bedNum);
    }

    bedOccupancy[wardChoice - 1][bedNum - 1] = 1;

    printf("\nPatient %s assigned to %s, Bed #%d successfully!\n",
           patient_name[pId - 1], wardNames[wardChoice - 1], bedNum);
}

// Priority Queue
void showPriorityQueue()
{
    int i, j;

    if (patientCount == 0)
    {
        printf("\nNo patients in queue.\n");
        return;
    }

    printf("\n--- PRIORITY QUEUE (Urgent Patients First) ---\n");

    for (j = 3; j >= 1; j--) {
        for (i = 0; i < patientCount; i++) {
            if (patient_urgency[i] == j) {
                printf("Priority Level %d | ID: %d | Name: %s | Age: %d\n",
                       patient_urgency[i], patient_id[i], patient_name[i], patient_age[i]);
            }
        }
    }
    printf("----------------------------------------------\n");
}

//Generate report function
void generateReport()
{
    int i, j;
    float totalRevenue = 0.0;
    int criticalCount = 0;
    int highestIndex = 0;
    int occupiedBeds = 0;

    if (patientCount == 0) {
        printf("\nNo data available to generate reports.\n");
        return;
    }

    for (i = 0; i < patientCount; i++) {
        totalRevenue += patient_fee[i];

        if (patient_urgency[i] == 3) {
            criticalCount++;
        }

        if (patient_fee[i] > patient_fee[highestIndex]) {
            highestIndex = i;
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < wardCapacities[i]; j++)
        {
            occupiedBeds += bedOccupancy[i][j];
        }
    }

    printf("\n=== HOSPITAL SUMMARY REPORT ===\n");
    printf("Total Patients Registered : %d\n", patientCount);
    printf("Total Critical Patients   : %d\n", criticalCount);
    printf("Total Revenue Generated   : LKR %.2f\n", totalRevenue);
    printf("Highest Bill Paid By      : %s (LKR %.2f)\n", patient_name[highestIndex], patient_fee[highestIndex]);
    printf("Total Beds Occupied       : %d\n", occupiedBeds);
    printf("--------------------------------\n");
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
                showPriorityQueue();
                break;

            case 6:
                generateReport();
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
