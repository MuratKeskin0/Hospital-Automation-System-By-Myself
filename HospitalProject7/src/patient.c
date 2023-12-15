#pragma once
#include "..//header/patient.h"
#include "..//header/database.h"
void addPatient(Patient patient) {
    patient.id = (int)time(NULL);
    savePatient(patient); 
}


Patient getPatient(int id) {
    return loadPatient(id); 
}

