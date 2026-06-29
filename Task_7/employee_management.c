#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_LEN 100
#define DEPT_LEN 50
#define DESIG_LEN 50

typedef struct {
    int id;
    char name[NAME_LEN];
    char department[DEPT_LEN];
    char designation[DESIG_LEN];
    double salary;
} Employee;

Employee *employees = NULL;
int employeeCount = 0;

//====================== Utility Functions ======================//

void clearInputBuffer() {
    while (getchar() != '\n');
}

void readString(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);

    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

bool employeeExists(int id) {
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id)
            return true;
    }
    return false;
}

//====================== Add Employee ======================//

void addEmployee() {
    Employee emp;

    printf("\n===== Add Employee =====\n");

    printf("Employee ID: ");
    scanf("%d", &emp.id);
    clearInputBuffer();

    if (employeeExists(emp.id)) {
        printf("Employee with ID %d already exists!\n", emp.id);
        return;
    }

    readString("Name: ", emp.name, NAME_LEN);
    readString("Department: ", emp.department, DEPT_LEN);
    readString("Designation: ", emp.designation, DESIG_LEN);

    printf("Salary: ");
    scanf("%lf", &emp.salary);
    clearInputBuffer();

    Employee *temp = realloc(employees, (employeeCount + 1) * sizeof(Employee));

    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    employees = temp;
    employees[employeeCount++] = emp;

    printf("\nEmployee added successfully!\n");
}

//====================== View Employees ======================//

void viewEmployees() {

    printf("\n===== Employee List =====\n");

    if (employeeCount == 0) {
        printf("No employees found.\n");
        return;
    }

    printf("%-6s %-25s %-20s %-20s %-10s\n",
           "ID", "Name", "Department", "Designation", "Salary");

    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < employeeCount; i++) {
        printf("%-6d %-25s %-20s %-20s %.2lf\n",
               employees[i].id,
               employees[i].name,
               employees[i].department,
               employees[i].designation,
               employees[i].salary);
    }
}

//====================== Search Employee ======================//

int searchEmployee(int id) {
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id)
            return i;
    }

    return -1;
}

void searchEmployeeMenu() {
    int id;

    printf("\n===== Search Employee =====\n");
    printf("Enter Employee ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    int index = searchEmployee(id);

    if (index == -1) {
        printf("Employee not found!\n");
        return;
    }

    Employee emp = employees[index];

    printf("\nEmployee Found\n");
    printf("-------------------------------\n");
    printf("ID          : %d\n", emp.id);
    printf("Name        : %s\n", emp.name);
    printf("Department  : %s\n", emp.department);
    printf("Designation : %s\n", emp.designation);
    printf("Salary      : %.2lf\n", emp.salary);
}


//====================== Update Employee ======================//

void updateEmployee() {

    int id;

    printf("\n===== Update Employee =====\n");
    printf("Enter Employee ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    int index = searchEmployee(id);

    if (index == -1) {
        printf("Employee not found!\n");
        return;
    }

    printf("\nEnter New Details\n");

    readString("Name: ", employees[index].name, NAME_LEN);
    readString("Department: ", employees[index].department, DEPT_LEN);
    readString("Designation: ", employees[index].designation, DESIG_LEN);

    printf("Salary: ");
    scanf("%lf", &employees[index].salary);
    clearInputBuffer();

    printf("\nEmployee updated successfully!\n");
}


//====================== Delete Employee ======================//

void deleteEmployee() {

    int id;

    printf("\n===== Delete Employee =====\n");
    printf("Enter Employee ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    int index = searchEmployee(id);

    if (index == -1) {
        printf("Employee not found!\n");
        return;
    }

    for (int i = index; i < employeeCount - 1; i++) {
        employees[i] = employees[i + 1];
    }

    employeeCount--;

    if (employeeCount == 0) {
        free(employees);
        employees = NULL;
    } else {
        Employee *temp = realloc(employees, employeeCount * sizeof(Employee));

        if (temp != NULL)
            employees = temp;
    }

    printf("Employee deleted successfully!\n");
}

//====================== Salary Statistics ======================//

void salaryStatistics() {

    printf("\n===== Salary Statistics =====\n");

    if (employeeCount == 0) {
        printf("No employee records available.\n");
        return;
    }

    double highest = employees[0].salary;
    double lowest = employees[0].salary;
    double sum = 0;

    int highestIndex = 0;
    int lowestIndex = 0;

    for (int i = 0; i < employeeCount; i++) {

        if (employees[i].salary > highest) {
            highest = employees[i].salary;
            highestIndex = i;
        }

        if (employees[i].salary < lowest) {
            lowest = employees[i].salary;
            lowestIndex = i;
        }

        sum += employees[i].salary;
    }

    printf("Total Employees : %d\n", employeeCount);

    printf("Highest Salary  : %.2lf (%s)\n",
           highest,
           employees[highestIndex].name);

    printf("Lowest Salary   : %.2lf (%s)\n",
           lowest,
           employees[lowestIndex].name);

    printf("Average Salary  : %.2lf\n",
           sum / employeeCount);
}


//====================== Export to CSV ======================//

void exportToCSV() {

    FILE *fp = fopen("employees.csv", "w");

    if (fp == NULL) {
        printf("Unable to create CSV file.\n");
        return;
    }

    fprintf(fp, "ID,Name,Department,Designation,Salary\n");

    for (int i = 0; i < employeeCount; i++) {

        fprintf(fp,
                "%d,%s,%s,%s,%.2lf\n",
                employees[i].id,
                employees[i].name,
                employees[i].department,
                employees[i].designation,
                employees[i].salary);
    }

    fclose(fp);

    printf("\nEmployee data exported to employees.csv successfully!\n");
}


//====================== Main ======================//

int main() {

    int choice;

    while (1) {

        printf("\n");
        printf("=====================================\n");
        printf("   Employee Management System\n");
        printf("=====================================\n");
        printf("1. Add Employee\n");
        printf("2. View Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Delete Employee\n");
        printf("6. Salary Statistics\n");
        printf("7. Export to CSV\n");
        printf("8. Exit\n");
        printf("=====================================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {

            case 1:
                addEmployee();
                break;

            case 2:
                viewEmployees();
                break;

            case 3:
                searchEmployeeMenu();
                break;

            case 4:
                updateEmployee();
                break;

            case 5:
                deleteEmployee();
                break;

            case 6:
                salaryStatistics();
                break;

            case 7:
                exportToCSV();
                break;

            case 8:
                free(employees);
                printf("\nThank you for using Employee Management System!\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}