#ifndef DOCTOR_H
#define DOCTOR_H
#include <stdbool.h>
#include <time.h> 

typedef struct {
    int id;
    char firstName[100];
    char lastName[100];
    char username[100];
    char password[100];
    char specialization[100];
} Doctor;

void addDoctor(Doctor doctor);
void deleteDoctor(int id);
Doctor getDoctor(int id);
void updateDoctor(Doctor doctor);

#endif
