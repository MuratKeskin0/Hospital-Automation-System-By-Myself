#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/database.h"
#include "../src/database.c"
#include "../header/doctor.h"
#include "../src/doctor.c"
#include "../header/patient.h"
#include "../src/patient.c"
#include "../header/appointment.h"
#include "../src/appointment.c"

int doctorDashboard(int doctorId);
int patientDashboard(int patientId);
int adminDashboard(int adminId);
int registerUser();

int loginUser();
int displayHospital();

int main()
{
    displayHospital();
    return 0;
}

int displayHospital()
{
    int choice;
    printf("--------------Welcome to the Hospital Management System------------\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        loginUser();
        break;
    case 2:
        registerUser();
        break;
    case 3:
        printf("Exiting the system.\n");
        exit(0);
    default:
        printf("Invalid choice. Please try again.\n");
        displayHospital(); // Recursive call to show the menu again
    }
    return 0;
}

int doctorDashboard(int doctorId)
{
    int choice;
    printf("----------------------------------------------------\n");
    printf("----------Welcome to the Doctor Dashboard------------\n");
    printf("1. Manage Appointments\n");
    printf("2. View My Information\n");
    printf("3. Delete My account\n");
    printf("4. Logout\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        int choiceDoctor;
        printf("----------------------------------------------------\n");
        printf("----------------- Manage Appointments-------------\n");
        printf("1. View My Appointments\n");
        printf("2. Modify My Appointment \n");
        printf("Enter your choice: ");
        scanf("%d", &choiceDoctor);
        switch (choiceDoctor)
        {
        case 1:
            viewDoctorAppointments(doctorId);
            doctorDashboard(doctorId);
            break;
        case 2:
            modifyDoctorAppointment(doctorId);
            doctorDashboard(doctorId);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            doctorDashboard(doctorId);
        }
        break;
    case 2:
        viewDoctorInformation(doctorId);
        doctorDashboard(doctorId);
        break;
    case 3:
        deleteDoctor(doctorId);
        displayHospital();
        break;
    case 4:
        printf("Logging out...\n");
        displayHospital();
        return 0;
    default:
        printf("Invalid choice. Please try again.\n");
    }
    return 0;
}

int patientDashboard(int patientId)
{
    int choice;
    printf("----------------------------------------------------\n");
    printf("-----------Welcome to the Patient Dashboard----------\n");
    printf("%s", getPatient(patientId).username);
    printf("\n1. View My Appointments\n");
    printf("2. Book a New Appointment\n");
    printf("3. View My Information\n");
    printf("4. Delete My Account\n");
    printf("5. Logout\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        viewDoctorAppointmentsPatient(patientId);
        patientDashboard(patientId);
        break;
    case 2:
        bookNewAppointmentForPatient(patientId);
        patientDashboard(patientId);
        break;
    case 3:
        viewPatientInformation(patientId);
        patientDashboard(patientId);
        break;
    case 4:
        deletePatient(patientId);
        displayHospital();
    case 5:
        printf("Logging out...\n");
        return 0;
    default:
        printf("Invalid choice. Please try again.\n");
    }
    return 0;
}

int adminDashboard(int adminId)
{
    int choice;
    printf("---------------------------------------------------------------------\n");
    printf("---------------Welcome to the Admin Dashboard-------------");
    printf("\n1. Change Appointment Status\n");
    printf("2. Delete Appointment\n");
    printf("3. Add Doctor\n");
    printf("4. Delete Doctor\n");
    printf("5. Update Doctor Information\n");
    printf("6. Add Patient\n");
    printf("7. Delete Patient\n");
    printf("8. Update Patient Information\n");
    printf("9. All Patients Information\n");
    printf("10. All Doctors Information\n");
    printf("11. All Appointments Information\n");
    printf("12. Logout\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        adminChangeAppointmentStatus();
        adminDashboard(adminId);
        break;
    case 2:
        adminDeleteAppointment();
        adminDashboard(adminId);
        break;
    case 3:
        adminAddDoctor();
        adminDashboard(adminId);
        break;
    case 4:
        adminDeleteDoctor();
        adminDashboard(adminId);
        break;
    case 5:
        adminUpdateDoctor();
        adminDashboard(adminId);
        break;
    case 6:
        adminAddPatient();
        adminDashboard(adminId);
        break;
    case 7:
        adminDeletePatient();
        adminDashboard(adminId);
        break;
    case 8:
        adminUpdatePatient();
        adminDashboard(adminId);
        break;
    case 9:
        displayAllPatients();
        adminDashboard(adminId);
        break;
    case 10:
        displayAllDoctors();
        adminDashboard(adminId);
        break;
    case 11:
        displayAllAppointments();
        adminDashboard(adminId);
        break;
    case 12:
        printf("Logging out...\n");
        return 0;
    default:
        printf("Invalid choice. Please try again.\n");
        adminDashboard(adminId);
    }
    return 0;
}

int registerUser()
{
    // Temporary user details
    int id;
    char firstName[100], lastName[100], username[50], password[50], role[10];
    int age;
    char gender[10];

    // Collecting user details
    printf("Enter your First Name: ");
    scanf("%s", firstName);
    printf("Enter your Last Name: ");
    scanf("%s", lastName);
    printf("Enter your Username: ");
    scanf("%s", username);
    if (checkUsernameExists(username))
    {
        printf("Username already exists. Please choose a different username.\n");
        return 0;
    }
    printf("Enter your Password: ");
    scanf("%s", password);
    printf("Are you a doctor or a patient? (doctor/patient): ");
    scanf("%s", role);

    if (strcmp(role, "doctor") == 0)
    {
        // Creating a Doctor struct and saving it
        Doctor newDoctor = {id, "", "", "", ""};
        strcpy(newDoctor.firstName, firstName);
        strcpy(newDoctor.lastName, lastName);
        strcpy(newDoctor.username, username);
        strcpy(newDoctor.password, password);
        addDoctor(newDoctor);
    }
    else if (strcmp(role, "patient") == 0)
    {
        // Additional details for patients
        printf("Enter your Age: ");
        scanf("%d", &age);
        printf("Enter your Gender: ");
        scanf("%s", gender);

        // Creating a Patient struct and saving it
        Patient newPatient = {id, "", "", "", "", 0, ""};
        strcpy(newPatient.firstName, firstName);
        strcpy(newPatient.lastName, lastName);
        strcpy(newPatient.username, username);
        strcpy(newPatient.password, password);
        newPatient.age = age;
        strcpy(newPatient.gender, gender);
        addPatient(newPatient);
    }
    else
    {
        printf("Invalid role. Registration failed.\n");
        return 0;
    }

    printf("Registration successful!\n");
    displayHospital();
    return 0;
}

int loginUser()
{
    char username[50], password[50];
    int roleChoice, id;
    printf("Identify your role:\n");
    printf("1. Doctor\n");
    printf("2. Patient\n");
    printf("3. Admin\n");
    printf("4. Back Main\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &roleChoice);

    FILE *file;
    int found = 0;

    switch (roleChoice)
    {
    case 1: // Doctor
        file = fopen(DOCTORS_FILE, "r");
        break;
    case 2: // Patient
        file = fopen(PATIENTS_FILE, "r");
        break;
    case 3: // Admin
        file = fopen(ADMIN_FILE, "r");
        break;
    case 4: // Main
        displayHospital();
        break;
    default:
        printf("Invalid role.\n");

        return 0;
    }

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    printf("Enter your Username: ");
    scanf("%s", username);
    printf("Enter your Password: ");
    scanf("%s", password);

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char fileUsername[50], filePassword[50];
        sscanf(line, "%d,%49[^,],%49[^,]", &id, fileUsername, filePassword);
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0)
        {
            found = 1;
            break;
        }
    }
    fclose(file);

    if (found)
    {
        switch (roleChoice)
        {
        case 1: // Doctor
            doctorDashboard(id);
            break;
        case 2: // Patient
            patientDashboard(id);
            break;
        case 3: // Admin
            adminDashboard(id);
            break;
        }
    }
    else
    {
        printf("Login failed. Invalid username or password.\n");
        loginUser();
    }
    return 0;
}
