#ifndef PATIENT_H
#define PATIENT_H
#include <time.h> 
typedef struct {
    int id;
    char firstName[100];
    char lastName[100];
    char username[100];
    char password[100];
    int age;
    char gender[10]; 
} Patient;

void addPatient(Patient patient);
void deletePatient(int id);
Patient getPatient(int id);
void updatePatient(Patient patient);

#endif

