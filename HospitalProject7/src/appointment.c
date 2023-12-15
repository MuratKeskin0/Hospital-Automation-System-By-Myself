#pragma once
#include "..//header/appointment.h"
#include "..//header/database.h"
#include <time.h>

void scheduleAppointment(Appointment appointment)
{

    appointment.id = (int)time(NULL);
    saveAppointment(appointment);
}

void cancelAppointment(int id)
{
    Appointment appointment = getAppointment(id);
    if (appointment.id != 0)
    {
        appointment.status = Cancelled;
        updateAppointment(appointment);
    }
    else
    {
        printf("Not found");
    }
}

Appointment getAppointment(int id)
{
    return loadAppointment(id);
}

void convertEpochToHumanReadable(time_t epochTime, char *buffer, size_t bufferSize)
{
    struct tm *timeInfo;
    timeInfo = localtime(&epochTime);
    strftime(buffer, bufferSize, "%Y-%m-%d %H:%M:%S", timeInfo);
}
