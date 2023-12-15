#ifndef DATABASE_H
#define DATABASE_H

#include "doctor.h"
#include "patient.h"
#include "appointment.h"

void saveDoctor(Doctor doctor);
Doctor loadDoctor(int id);
void updateDoctor(Doctor doctor);
void deleteDoctor(int id);

void savePatient(Patient patient);
Patient loadPatient(int id);
void updatePatient(Patient patient);
void deletePatient(int id);

void saveAppointment(Appointment appointment);
Appointment loadAppointment(int id);
void updateAppointment(Appointment appointment);
void deleteAppointment(int id);

#endif
