#include <stdio.h>
#include <string.h>

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
                printf("Register Patient\n");
                break;

            case 2:
                printf("Display Patients\n");
                break;

            case 3:
                printf("Bed Status\n");
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
