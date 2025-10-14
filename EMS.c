#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

void design();
void RegisterUser();
int loginUser();
void adminMenu();
void employeeMenu();
void addEmployee();
void updateEmployee();
void deleteEmployee();
void searchEmployee();
void displayEmployees();

// Global Employee Data
struct Employee {
    int id;
    char name[50];
    char department[30];
    char jobRole[30];
    float salary;
};

struct Employee employees[MAX];
int empcount = 0;

// User Data
struct User {
    char username[50];
    char password[50];
    char role[10];
};

void design() {
    printf("\n===== Employee Management System =====\n\n");

    printf("EEEEEEE  MM       MM  PPPPPP   LL         OOOO      YY      YY  EEEEEEE  EEEEEEE\n");
    printf("EE       MM MM MM MM  PP   PP  LL       OO    OO      YY  YY    EE       EE     \n");
    printf("EEEEE    MM   MM  MM  PPPPPP   LL      OO       OO      YY      EEEEE    EEEEE  \n");
    printf("EE       MM       MM  PP       LL       OO     OO       YY      EE       EE     \n");
    printf("EEEEEEE  MM       MM  PP       LLLLLLLL   OOOO          YY      EEEEEEE  EEEEEEE\n\n");

    printf("MM       MM      AA       NN      NN      AA       GGGGGGGG  EEEEEEE  MM       MM  EEEEEEE  NN      NN  TTTTTTTT\n");
    printf("MM MM MM MM     AA AA     NN NN   NN     AA AA   GG          EE       MM MM MM MM  EE       NN NN   NN     TT   \n");
    printf("MM   MM  MM    AA   AA    NN  NN  NN    AA   AA  GG   GGGGGG EEEEE    MM   MM  MM  EEEEE    NN  NN  NN     TT   \n");
    printf("MM       MM   AAAAAAAAA   NN   NN NN   AAAAAAAAA  GG     GG  EE       MM       MM  EE       NN   NN NN     TT   \n");
    printf("MM       MM  AA       AA  NN      NN  AA       AA   GGGGGG   EEEEEEE  MM       MM  EEEEEEE  NN      NN     TT   \n");
}

void RegisterUser() {
    struct User user;

    printf("Enter a phone number or username: ");
    fgets(user.username, sizeof(user.username), stdin);
    user.username[strcspn(user.username, "\n")] = '\0';

    printf("Enter a password: ");
    fgets(user.password, sizeof(user.password), stdin);
    user.password[strcspn(user.password, "\n")] = '\0';

    printf("Enter a Role: ");
    fgets(user.role, sizeof(user.role), stdin);
    user.role[strcspn(user.role, "\n")] = '\0';

    FILE *fp = fopen("users.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s %s %s\n", user.username, user.password, user.role);
    fclose(fp);

    printf("Registration Successful! Please log in.\n");

    loginUser();
}

int loginUser() {
    printf("*** Login ***\n");
    char input[50];
    char input_password[50];
    char input_role[10];
    int found = 0;

    printf("Enter Username or Phone: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("Enter Password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = '\0';

    printf("Enter a Role: ");
    fgets(input_role, sizeof(input_role), stdin);
    input_role[strcspn(input_role, "\n")] = '\0';

    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    struct User user;
    while (fscanf(fp, "%s %s %s", user.username, user.password, user.role) != EOF) {
        if (strcmp(user.username, input) == 0 && strcmp(user.password, input_password) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found) {
        printf("Login Successful!\n");
        if (strcmp(input_role, "HR") == 0 || strcmp(input_role, "Manager") == 0) {
            adminMenu();
        } else {
            employeeMenu();
        }
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}
void adminMenu() {
    while (1) {
        int ch;
        printf("\n===== Admin Panel =====\n");
        printf("1. Add Employee\n");
        printf("2. Update Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Display Employees\n");
        printf("5. Search Employee\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        getchar(); // To consume newline after integer input

        switch (ch) {
            case 1: addEmployee(); break;
            case 2: updateEmployee(); break;
            case 3: deleteEmployee(); break;
            case 4: displayEmployees(); break;
            case 5: searchEmployee(); break;
            case 6: return; // Exit admin menu
            default: printf("Invalid choice!\n");
        }
    }
}

void addEmployee() {
    struct Employee e;

    printf("Enter a ID: ");
    scanf("%d", &e.id);
    getchar(); // To clear the newline character after scanf

    printf("Enter a Name: ");
    fgets(e.name, sizeof(e.name), stdin);
    e.name[strcspn(e.name, "\n")] = '\0'; // Remove newline character

    printf("Enter a Department: ");
    fgets(e.department, sizeof(e.department), stdin);
    e.department[strcspn(e.department, "\n")] = '\0';

    printf("Enter Job Role: ");
    fgets(e.jobRole, sizeof(e.jobRole), stdin);
    e.jobRole[strcspn(e.jobRole, "\n")] = '\0';

    printf("Enter a Salary: ");
    scanf("%f", &e.salary);
    getchar(); // To clear the newline character

    employees[empcount] = e; // Add the new employee to the array at the current index of empcount
    empcount++;              // Increment the employee count
    printf("Employee added successfully!\n");
}

void updateEmployee() {
    int Id;
    printf("Enter Employee ID to update: ");
    scanf("%d", &Id);
    getchar(); // To clear the newline character
    int found = 0;

    for (int i = 0; i < empcount; i++) {
        if (employees[i].id == Id) {
            printf("Enter a new Name: ");
            fgets(employees[i].name, sizeof(employees[i].name), stdin);
            employees[i].name[strcspn(employees[i].name, "\n")] = '\0';

            printf("Enter a new Department: ");
            fgets(employees[i].department, sizeof(employees[i].department), stdin);
            employees[i].department[strcspn(employees[i].department, "\n")] = '\0';

            printf("Enter a new Job Role: ");
            fgets(employees[i].jobRole, sizeof(employees[i].jobRole), stdin);
            employees[i].jobRole[strcspn(employees[i].jobRole, "\n")] = '\0';

            printf("Enter a new Salary: ");
            scanf("%f", &employees[i].salary);
            getchar(); // To clear the newline character
            found = 1;
            printf("Employee Updated Successfully!\n");
            break;
        }
    }

    if (found == 0) {
        printf("Employee ID not Found!\n");
    }
}

void deleteEmployee() {
    int id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);
    getchar(); // To clear the newline character
    int found = 0;

    for (int i = 0; i < empcount; i++) {
        if (employees[i].id == id) {
            // Shift elements to the left
            for (int j = i; j < empcount - 1; j++) {
                employees[j] = employees[j + 1];
            }
            empcount--; // Decrease the employee count
            found = 1;
            printf("Employee Deleted Successfully!\n");
            break;
        }
    }

    if (found == 0) {
        printf("Employee ID not Found!\n");
    }
}

void searchEmployee() {
    int id;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);
    getchar(); // To clear the newline character
    int found = 0;

    for (int i = 0; i < empcount; i++) {
        if (employees[i].id == id) {
             printf("Employee Found:\n");
             printf("Name: %s\n", employees[i].name);
             printf("Department: %s\n", employees[i].department);
             printf("Job Role: %s\n", employees[i].jobRole);
             printf("Salary: %.2f\n", employees[i].salary);
             printf("\n"); // Added an extra new line after displaying the details
             found = 1;
            break;
        }
    }

    if (found == 0) {
        printf("Employee not found\n");
    }
}

void displayEmployees() {
    printf("\nTotal Number of Employees: %d\n", empcount); // Display total number of employees
    printf("\n===== Employee List =====\n");
    for (int i = 0; i < empcount; i++) {
        printf("ID: %d, Name: %s, Department: %s, Role: %s, Salary: %.2f\n", employees[i].id, employees[i].name, employees[i].department, employees[i].jobRole, employees[i].salary);
    }
}



void employeeMenu() {
   while(1){
    int ch;
     printf("\n===== Employee Panel =====\n");
     printf("1. View Employees\n2. Logout\n");
     printf("Enter choice: ");
     scanf("%d", &ch);
     getchar(); // To clear the newline character after scanf

     switch (ch) {
            case 1: displayEmployees(); break;
            case 2: return;
            default: printf("Invalid choice!\n");
        }
   }
}


int main() {
    design();
    while (1) {
        int ch;
        printf("\n===== Employee Management System =====\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        getchar(); // To consume newline after integer input

        switch (ch) {
            case 1: RegisterUser(); break;
            case 2: loginUser(); break;
            case 3: return;
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
