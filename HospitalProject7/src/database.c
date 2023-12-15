#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..//header/appointment.h"
#include "..//header/database.h"
#include "..//header/doctor.h"
#include "..//src/appointment.c"

const char *DOCTORS_FILE = "doctors.txt";
const char *PATIENTS_FILE = "patients.txt";
const char *APPOINTMENTS_FILE = "appointments.txt";
const char *ADMIN_FILE = "admin.txt";

FILE *openFileForRead(const char *filePath)
{
    FILE *file = fopen(filePath, "r");
    if (!file)
    {
        perror("Error opening file");
        return NULL;
    }
    return file;
}

FILE *openFileForWrite(const char *filePath)
{
    FILE *file = fopen(filePath, "a");
    if (!file)
    {
        perror("Error opening file");
        return NULL;
    }
    return file;
}

void closeFile(FILE *file)
{
    if (file)
    {
        fclose(file);
    }
}

void saveDoctor(Doctor doctor)
{
    FILE *file = openFileForWrite(DOCTORS_FILE);
    if (file)
    {
        fprintf(file, "%d,%s,%s,%s,%s\n", doctor.id, doctor.firstName, doctor.lastName, doctor.username, doctor.password);
        closeFile(file);
    }
}

Doctor loadDoctor(int id)
{
    FILE *file = openFileForRead(DOCTORS_FILE);
    Doctor doctor;
    int found = 0;

    if (file)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%99[^,],%99[^,],%99[^,],%99[^,]", &doctor.id, doctor.firstName, doctor.lastName, doctor.username, doctor.password);
            if (doctor.id == id)
            {
                found = 1;
                break;
            }
        }
        closeFile(file);
    }

    if (!found)
    {
        printf("Not found");
    }

    return doctor;
}

void updateDoctor(Doctor updatedDoctor)
{
    FILE *file = openFileForRead(DOCTORS_FILE);
    FILE *tempFile = openFileForWrite("temp.txt");
    Doctor doctor;
    int found = 0;

    if (file && tempFile)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%99[^,],%99[^,],%99[^,],%99[^,]", &doctor.id, doctor.firstName, doctor.lastName, doctor.username, doctor.password);
            if (doctor.id == updatedDoctor.id)
            {
                fprintf(tempFile, "%d,%s,%s,%s,%s\n", updatedDoctor.id, updatedDoctor.firstName, updatedDoctor.lastName, updatedDoctor.username, updatedDoctor.password);
                found = 1;
            }
            else
            {
                fputs(line, tempFile);
            }
        }
        closeFile(file);
        closeFile(tempFile);

        remove(DOCTORS_FILE);
        rename("temp.txt", DOCTORS_FILE);
    }

    if (!found)
    {
        printf("Not found");
    }
}

void deleteDoctor(int id)
{
    // Delete the doctor
    FILE *file = openFileForRead(DOCTORS_FILE);
    FILE *tempFile = openFileForWrite("temp_doctors.txt");
    Doctor doctor;
    int foundDoctor = 0;

    if (file && tempFile)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%99[^,],%99[^,],%99[^,],%99[^,]", &doctor.id, doctor.firstName, doctor.lastName, doctor.username, doctor.password);
            if (doctor.id != id)
            {
                fputs(line, tempFile);
            }
            else
            {
                foundDoctor = 1;
            }
        }
        closeFile(file);
        closeFile(tempFile);

        remove(DOCTORS_FILE);
        rename("temp_doctors.txt", DOCTORS_FILE);
    }

    if (!foundDoctor)
    {
        printf("Not found");
    }
    // Delete appointments associated with the doctor
    file = openFileForRead(APPOINTMENTS_FILE);
    tempFile = openFileForWrite("temp_appointments.txt");
    Appointment appointment;
    int foundAppointment = 0;

    if (file && tempFile)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%d,%d,%ld,%d", &appointment.id, &appointment.doctorId, &appointment.patientId, &appointment.dateTime, (int *)&appointment.status);
            if (appointment.doctorId != id)
            {
                fputs(line, tempFile);
            }
            else
            {
                foundAppointment = 1;
            }
        }
        closeFile(file);
        closeFile(tempFile);

        remove(APPOINTMENTS_FILE);
        rename("temp_appointments.txt", APPOINTMENTS_FILE);
    }

    if (!foundAppointment)
    {
        printf("Not found");
    }
}

void savePatient(Patient patient)
{
    FILE *file = openFileForWrite(PATIENTS_FILE);
    if (file)
    {
        fprintf(file, "%d,%s,%s,%s,%s,%d,%s\n", patient.id, patient.firstName, patient.lastName, patient.username, patient.password, patient.age, patient.gender);
        closeFile(file);
    }
}

Patient loadPatient(int id)
{
    FILE *file = openFileForRead(PATIENTS_FILE);
    Patient patient;
    int found = 0;

    if (file)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%d,%9s", &patient.id, patient.firstName, patient.lastName, patient.username, patient.password, &patient.age, patient.gender);
            if (patient.id == id)
            {
                found = 1;
                break;
            }
        }
        closeFile(file);
    }

    if (!found)
    {
        printf("Not found");
    }

    return patient;
}

void updatePatient(Patient updatedPatient)
{
    FILE *file = openFileForRead(PATIENTS_FILE);
    FILE *tempFile = openFileForWrite("temp_patients.txt");
    Patient patient;
    int found = 0;

    if (file && tempFile)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%d,%9s", &patient.id, patient.firstName, patient.lastName, patient.username, patient.password, &patient.age, patient.gender);
            if (patient.id == updatedPatient.id)
            {
                fprintf(tempFile, "%d,%s,%s,%s,%s,%d,%s\n", updatedPatient.id, updatedPatient.firstName, updatedPatient.lastName, updatedPatient.username, updatedPatient.password, updatedPatient.age, updatedPatient.gender);
                found = 1;
            }
            else
            {
                fputs(line, tempFile);
            }
        }
        closeFile(file);
        closeFile(tempFile);

        // Replace old file with new file
        remove(PATIENTS_FILE);
        rename("temp_patients.txt", PATIENTS_FILE);
    }

    if (!found)
    {
        printf("Not found");
    }
}

void deletePatient(int id)
{
    // Delete the patient
    FILE *file = openFileForRead(PATIENTS_FILE);
    FILE *tempFile = openFileForWrite("temp_patients.txt");
    Patient patient;
    int foundPatient = 0;

    if (file && tempFile)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%d,%9s", &patient.id, patient.firstName, patient.lastName, patient.username, patient.password, &patient.age, patient.gender);
            if (patient.id != id)
            {
                fputs(line, tempFile);
            }
            else
            {
                foundPatient = 1;
            }
        }
        closeFile(file);
        closeFile(tempFile);

        remove(PATIENTS_FILE);
        rename("temp_patients.txt", PATIENTS_FILE);
    }

    if (!foundPatient)
    {
        printf("Not found");
    }

    // Delete appointments associated with the patient
    file = openFileForRead(APPOINTMENTS_FILE);
    tempFile = openFileForWrite("temp_appointments.txt");
    Appointment appointment;
    int foundAppointment = 0;

    if (file && tempFile)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%d,%d,%ld,%d", &appointment.id, &appointment.doctorId, &appointment.patientId, &appointment.dateTime, (int *)&appointment.status);
            if (appointment.patientId != id)
            {
                fputs(line, tempFile);
            }
            else
            {
                foundAppointment = 1;
            }
        }
        closeFile(file);
        closeFile(tempFile);

        // Replace old file with new file
        remove(APPOINTMENTS_FILE);
        rename("temp_appointments.txt", APPOINTMENTS_FILE);
    }

    if (!foundAppointment)
    {
        printf("Not found");
    }
}

Appointment loadAppointment(int id)
{
    FILE *file = openFileForRead(APPOINTMENTS_FILE);
    Appointment appointment;
    int found = 0;

    if (file)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%d,%d,%ld,%d", &appointment.id, &appointment.doctorId, &appointment.patientId, &appointment.dateTime, (int *)&appointment.status);
            if (appointment.id == id)
            {
                found = 1;
                break;
            }
        }
        closeFile(file);
    }

    if (!found)
    {
        printf("Not found");
    }

    return appointment;
}

void saveAppointment(Appointment appointment)
{
    FILE *file = openFileForWrite(APPOINTMENTS_FILE);
    if (file)
    {
        fprintf(file, "%d,%d,%d,%ld,%d\n", appointment.id, appointment.doctorId, appointment.patientId, appointment.dateTime, appointment.status);
        closeFile(file);
    }
}

void updateAppointment(Appointment updatedAppointment)
{
    FILE *file = openFileForRead(APPOINTMENTS_FILE);
    FILE *tempFile = openFileForWrite("temp_appointments.txt");
    Appointment appointment;
    int found = 0;

    if (file && tempFile)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%d,%d,%ld,%d", &appointment.id, &appointment.doctorId, &appointment.patientId, &appointment.dateTime, (int *)&appointment.status);
            if (appointment.id == updatedAppointment.id)
            {
                fprintf(tempFile, "%d,%d,%d,%ld,%d\n", updatedAppointment.id, updatedAppointment.doctorId, updatedAppointment.patientId, updatedAppointment.dateTime, updatedAppointment.status);
                found = 1;
            }
            else
            {
                fputs(line, tempFile);
            }
        }
        closeFile(file);
        closeFile(tempFile);

        remove(APPOINTMENTS_FILE);
        rename("temp_appointments.txt", APPOINTMENTS_FILE);
    }

    if (!found)
    {
        printf("Not found");
    }
}

void deleteAppointment(int id)
{
    FILE *file = openFileForRead(APPOINTMENTS_FILE);
    FILE *tempFile = openFileForWrite("temp_appointments.txt");
    Appointment appointment;
    int found = 0;

    if (file && tempFile)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%d,%d,%ld,%d", &appointment.id, &appointment.doctorId, &appointment.patientId, &appointment.dateTime, (int *)&appointment.status);
            if (appointment.id != id)
            {
                fputs(line, tempFile);
            }
            else
            {
                found = 1;
            }
        }
        closeFile(file);
        closeFile(tempFile);

        remove(APPOINTMENTS_FILE);
        rename("temp_appointments.txt", APPOINTMENTS_FILE);
    }

    if (!found)
    {
        printf("Not found");
    }
}

void viewDoctorAppointments(int doctorId)
{
    FILE *file = openFileForRead(APPOINTMENTS_FILE);
    Appointment appointment;
    int found = 0;
    char formattedTime[30];

    if (file)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%d,%d,%ld,%d", &appointment.id, &appointment.doctorId, &appointment.patientId, &appointment.dateTime, (int *)&appointment.status);
            if (appointment.doctorId == doctorId)
            {
                found = 1;
                convertEpochToHumanReadable(appointment.dateTime, formattedTime, sizeof(formattedTime));
                printf("Appointment ID: %d, Patient ID: %d, Date/Time: %ld, Status: %d\n",
                       appointment.id, appointment.patientId, appointment.dateTime, appointment.status);
            }
        }
        closeFile(file);
    }

    if (!found)
    {
        printf("No appointments found.\n");
    }
}

void modifyDoctorAppointment(int doctorId)
{
    viewDoctorAppointments(doctorId); // First, list all appointments

    int appointmentIdToModify;
    printf("Enter the ID of the appointment to modify: ");
    scanf("%d", &appointmentIdToModify);

    Appointment appointment = loadAppointment(appointmentIdToModify);

    if (appointment.doctorId != doctorId)
    {
        printf("Invalid appointment ID or you do not have permission to modify this appointment.\n");
        return;
    }

    // Provide modification options here
    int modificationChoice;
    printf("Select what to modify:\n");
    printf("1. Date/Time\n");
    printf("2. Status\n");
    printf("Enter your choice: ");
    scanf("%d", &modificationChoice);

    switch (modificationChoice)
    {
    case 1:
        // Modify Date/Time
        printf("Enter new Date/Time (as long integer): ");
        scanf("%ld", &appointment.dateTime);
        break;
    case 2:
        // Modify Status
        printf("Select new Status:\n");
        printf("1. Scheduled\n");
        printf("2. Completed\n");
        printf("3. Cancelled\n");
        printf("4. NoShow\n");
        printf("Enter your choice: ");
        int statusChoice;
        scanf("%d", &statusChoice);
        switch (statusChoice)
        {
        case 1:
            appointment.status = Scheduled;
            break;
        case 2:
            appointment.status = Completed;
            break;
        case 3:
            appointment.status = Cancelled;
            break;
        case 4:
            appointment.status = Pending;
            break;
        default:
            printf("Invalid status choice.\n");
            return;
        }
        break;
    default:
        printf("Invalid choice.\n");
        return;
    }

    updateAppointment(appointment);
    printf("Appointment updated successfully.\n");
}

void viewDoctorInformation(int doctorId)
{
    Doctor doctor = loadDoctor(doctorId);

    if (doctor.id != 0)
    { // Assuming an ID of 0 means the doctor was not found
        printf("Doctor ID: %d\n", doctor.id);
        printf("Name: %s %s\n", doctor.firstName, doctor.lastName);
        printf("Username: %s\n", doctor.username);
        printf("Password: %s\n", doctor.password);
    }
    else
    {
        printf("Doctor information not found.\n");
    }
}

void viewPatientInformation(int patientId)
{
    Patient patient = loadPatient(patientId);

    if (patient.id != 0)
    { // Assuming an ID of 0 means the doctor was not found
        printf("Doctor ID: %d\n", patient.id);
        printf("Name: %s %s\n", patient.firstName, patient.lastName);
        printf("Username: %s\n", patient.username);
        printf("Gender: %s\n", patient.gender);
        printf("Age: %d\n", patient.age);
        printf("Password: %s\n", patient.password);
    }
    else
    {
        printf("Patient information not found.\n");
    }
}

void viewDoctorAppointmentsPatient(int patientId)
{
    FILE *file = openFileForRead(APPOINTMENTS_FILE);
    Appointment appointment;
    int found = 0;

    if (file)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%d,%d,%ld,%d", &appointment.id, &appointment.doctorId, &appointment.patientId, &appointment.dateTime, (int *)&appointment.status);
            if (appointment.patientId == patientId)
            {
                found = 1;
                printf("Appointment ID: %d, Patient ID: %d, Date/Time: %ld, Status: %d\n",
                       appointment.id, appointment.patientId, appointment.dateTime, appointment.status);
            }
        }
        closeFile(file);
    }

    if (!found)
    {
        printf("No appointments found.\n");
    }
}

void adminAddDoctor()
{
    Doctor newDoctor;
    printf("Enter First Name: ");
    scanf("%s", newDoctor.firstName);
    printf("Enter Last Name: ");
    scanf("%s", newDoctor.lastName);
    printf("Enter Username: ");
    scanf("%s", newDoctor.username);
    printf("Enter Password: ");
    scanf("%s", newDoctor.password);

    addDoctor(newDoctor);
    printf("Doctor added successfully.\n");
}

void adminAddPatient()
{
    Patient newPatient;

    printf("Enter First Name: ");
    scanf("%s", newPatient.firstName);
    printf("Enter Last Name: ");
    scanf("%s", newPatient.lastName);
    printf("Enter Username: ");
    scanf("%s", newPatient.username);
    printf("Enter Password: ");
    scanf("%s", newPatient.password);
    printf("Enter Age: ");
    scanf("%d", &newPatient.age);
    printf("Enter Gender: ");
    scanf("%s", newPatient.gender);

    addPatient(newPatient);
    printf("Patient added successfully.\n");
}

void displayAllAppointments()
{
    FILE *file = openFileForRead(APPOINTMENTS_FILE);
    Appointment appointment;

    if (file)
    {
        printf("All Appointments:\n");
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%d,%d,%ld,%d", &appointment.id, &appointment.doctorId, &appointment.patientId, &appointment.dateTime, &appointment.status);
            printf("ID: %d, Doctor ID: %d, Patient ID: %d, DateTime: %ld, Status: %d\n",
                   appointment.id, appointment.doctorId, appointment.patientId, appointment.dateTime, appointment.status);
        }
        closeFile(file);
    }
    else
    {
        printf("No appointments found or error opening file.\n");
    }
}

void displayAllDoctors()
{
    FILE *file = openFileForRead(DOCTORS_FILE);
    Doctor doctor;

    if (file)
    {
        printf("All Doctors:\n");
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%99[^,],%99[^,],%99[^,],%99[^,]", &doctor.id, doctor.firstName, doctor.lastName, doctor.username, doctor.password);
            printf("ID: %d, Name: %s %s, Username: %s\n", doctor.id, doctor.firstName, doctor.lastName, doctor.username);
        }
        closeFile(file);
    }
    else
    {
        printf("No doctors found or error opening file.\n");
    }
}

void displayAllPatients()
{
    FILE *file = openFileForRead(PATIENTS_FILE);
    Patient patient;

    if (file)
    {
        printf("All Patients:\n");
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%99[^,],%99[^,],%99[^,],%99[^,],%d,%9s", &patient.id, patient.firstName, patient.lastName, patient.username, patient.password, &patient.age, patient.gender);
            printf("ID: %d, Name: %s %s, Username: %s, Age: %d, Gender: %s\n",
                   patient.id, patient.firstName, patient.lastName, patient.username, patient.age, patient.gender);
        }
        closeFile(file);
    }
    else
    {
        printf("No patients found or error opening file.\n");
    }
}

void adminDeleteAppointment()
{

    displayAllAppointments();

    int appointmentId;
    printf("Enter the ID of the appointment to delete: ");
    scanf("%d", &appointmentId);

    deleteAppointment(appointmentId);
    printf("Appointment deleted successfully.\n");
}

void adminDeleteDoctor()
{
    displayAllDoctors();
    int doctorId;
    printf("Enter the ID of the doctor to delete: ");
    scanf("%d", &doctorId);

    deleteDoctor(doctorId);
    printf("Doctor deleted successfully.\n");
}

void adminDeletePatient()
{
    displayAllPatients();
    int patientId;
    printf("Enter the ID of the patient to delete: ");
    scanf("%d", &patientId);

    deletePatient(patientId);
    printf("Patient deleted successfully.\n");
}

void adminUpdatePatient()
{
    // First, display all patients
    displayAllPatients();

    int patientIdToUpdate;
    printf("Enter the ID of the patient to update: ");
    scanf("%d", &patientIdToUpdate);

    // Load the patient's current information
    Patient existingPatient = loadPatient(patientIdToUpdate);

    if (existingPatient.id == 0)
    {
        printf("Patient not found.\n");
        return;
    }

    // Display current information
    printf("Current Information:\n");
    printf("Name: %s %s, Username: %s, Age: %d, Gender: %s\n",
           existingPatient.firstName, existingPatient.lastName, existingPatient.username, existingPatient.age, existingPatient.gender);

    // Get new information
    printf("Enter new First Name: ");
    scanf("%s", existingPatient.firstName);
    printf("Enter new Last Name: ");
    scanf("%s", existingPatient.lastName);
    printf("Enter new Username: ");
    scanf("%s", existingPatient.username);
    printf("Enter new Password: ");
    scanf("%s", existingPatient.password);
    printf("Enter new Age: ");
    scanf("%d", &existingPatient.age);
    printf("Enter new Gender: ");
    scanf("%s", existingPatient.gender);

    updatePatient(existingPatient);
    printf("Patient information updated successfully.\n");
}

void adminUpdateDoctor()
{
    // Display all doctors
    displayAllDoctors();

    int doctorIdToUpdate;
    printf("Enter the ID of the doctor to update: ");
    scanf("%d", &doctorIdToUpdate);

    // Load the doctor's current information
    Doctor existingDoctor = loadDoctor(doctorIdToUpdate);

    if (existingDoctor.id == 0)
    {
        printf("Doctor not found.\n");
        return;
    }

    // Display current information
    printf("Current Information:\n");
    printf("Name: %s %s, Username: %s\n", existingDoctor.firstName, existingDoctor.lastName, existingDoctor.username);

    // Get new information
    printf("Enter new First Name: ");
    scanf("%s", existingDoctor.firstName);
    printf("Enter new Last Name: ");
    scanf("%s", existingDoctor.lastName);
    printf("Enter new Username: ");
    scanf("%s", existingDoctor.username);
    printf("Enter new Password: ");
    scanf("%s", existingDoctor.password);

    updateDoctor(existingDoctor);
    printf("Doctor information updated successfully.\n");
}

int checkUsernameExists(const char *username)
{
    FILE *file;
    char line[256];
    char existingUsername[50];

    // Check in DOCTORS_FILE
    file = fopen(DOCTORS_FILE, "r");
    if (file)
    {
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%*d,%*[^,],%*[^,],%49[^,],%*s", existingUsername);
            if (strcmp(username, existingUsername) == 0)
            {
                fclose(file);
                return 1; // Username exists in doctors file
            }
        }
        fclose(file);
    }

    // Check in PATIENTS_FILE
    file = fopen(PATIENTS_FILE, "r");
    if (file)
    {
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%*d,%*[^,],%*[^,],%*[^,],%49[^,],%*s", existingUsername);
            if (strcmp(username, existingUsername) == 0)
            {
                fclose(file);
                return 1; // Username exists in patients file
            }
        }
        fclose(file);
    }

    return 0; // Username does not exist in either file
}

void bookNewAppointmentForPatient(int patientId)
{
    Appointment newAppointment;
    newAppointment.patientId = patientId;
    displayAllDoctors();

    printf("Enter the ID of the doctor for the appointment: ");
    scanf("%d", &newAppointment.doctorId);

    // Check if the doctor exists
    Doctor doctor = loadDoctor(newAppointment.doctorId);
    if (doctor.id == 0)
    {
        printf("Doctor not found.\n");
        return;
    }

    printf("Enter the date and time for the appointment (format: YYYYMMDDHHMM): ");
    scanf("%ld", &newAppointment.dateTime);

    // Generate a unique ID for the new appointment
    newAppointment.id = (int)time(NULL);

    newAppointment.status = Pending;

    saveAppointment(newAppointment);
    printf("Appointment booked successfully. Appointment ID is %d.\n", newAppointment.id);
}

void changeAppointmentStatus(int appointmentId, AppointmentStatus newStatus)
{
    FILE *file = openFileForRead(APPOINTMENTS_FILE);
    FILE *tempFile = openFileForWrite("temp_appointments.txt");
    Appointment appointment;
    int found = 0;

    if (file && tempFile)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%d,%d,%d,%ld,%d", &appointment.id, &appointment.doctorId, &appointment.patientId, &appointment.dateTime, (int *)&appointment.status);
            if (appointment.id == appointmentId)
            {
                appointment.status = newStatus; // Update the status
                fprintf(tempFile, "%d,%d,%d,%ld,%d\n", appointment.id, appointment.doctorId, appointment.patientId, appointment.dateTime, appointment.status);
                found = 1;
            }
            else
            {
                fputs(line, tempFile);
            }
        }
        closeFile(file);
        closeFile(tempFile);

        remove(APPOINTMENTS_FILE);
        rename("temp_appointments.txt", APPOINTMENTS_FILE);
    }

    if (!found)
    {
        printf("Appointment with ID %d not found.\n", appointmentId);
    }
    else
    {
        printf("Appointment status updated successfully.\n");
    }
}

void adminChangeAppointmentStatus()
{
    displayAllAppointments();
    int appointmentId;
    printf("Enter the ID of the appointment to modify: ");
    scanf("%d", &appointmentId);

    printf("Select new Status:\n");
    printf("0. Scheduled\n");
    printf("1. Completed\n");
    printf("2. Cancelled\n");
    printf("3. No Show\n");
    printf("Enter your choice: ");
    int statusChoice;
    scanf("%d", &statusChoice);

    AppointmentStatus newStatus;
    switch (statusChoice)
    {
    case 1:
        newStatus = Scheduled;
        break;
    case 2:
        newStatus = Completed;
        break;
    case 3:
        newStatus = Cancelled;
        break;
    case 4:
        newStatus = Pending;
        break;
    default:
        printf("Invalid status choice.\n");
        return;
    }

    changeAppointmentStatus(appointmentId, newStatus);
}
