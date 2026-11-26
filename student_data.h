#pragma once
#include <string>

enum class Specialty {
    ComputerScience = 1, Informatics, MathEconomics,
    PhysicsInformatics, LaborEducation
};

// Level A: the same three subjects for every student (no union).
struct Student {
    std::string surname;
    int course;
    Specialty specialty;
    int physics;
    int mathematics;
    int informatics;
};

int readNumber(const std::string& prompt, int minValue, int maxValue);
Student inputStudent();
std::string specialtyName(Specialty specialty);
void printStudents(const Student* students, int n, const int* order = nullptr);
int average100(const Student& student);
#pragma once
