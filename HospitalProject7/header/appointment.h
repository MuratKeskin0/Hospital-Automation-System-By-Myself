#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <time.h> 

typedef enum {
    Scheduled,
    Completed,
    Cancelled,
    Pending 
} AppointmentStatus;

typedef struct {
    int id;
    int doctorId;
    int patientId;
    time_t dateTime;
    AppointmentStatus status;
} Appointment;

void scheduleAppointment(Appointment appointment);
void updateAppointment(Appointment appointment);
void cancelAppointment(int id);
Appointment getAppointment(int id);
#endif
