#pragma once
#include "..//header/doctor.h"
#include "..//header/database.h"

void addDoctor(Doctor doctor) {
    doctor.id = (int)time(NULL);
     saveDoctor(doctor);
}


Doctor getDoctor(int id) {
    loadDoctor(id);
}

