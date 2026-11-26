#include "student_data.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int readNumber(const string& prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minValue && value <= maxValue)
            return value;
        if (cin.eof()) return -1;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter an integer from " << minValue << " to " << maxValue << ".\n";
    }
}

string specialtyName(Specialty specialty) {
    switch (specialty) {
    case Specialty::ComputerScience: return "Computer Science";
    case Specialty::Informatics: return "Informatics";
    case Specialty::MathEconomics: return "Math & Economics";
    case Specialty::PhysicsInformatics: return "Physics & Info";
    case Specialty::LaborEducation: return "Labor Education";
    }
    return "Unknown";
}

Student inputStudent() {
    Student s{};
    cout << "Surname (no spaces): ";
    cin >> s.surname;
    s.course = readNumber("Course (1..6): ", 1, 6);
    cout << "Specialty: 1-CS 2-Informatics 3-MathEconomics\n"
        << "           4-PhysicsInfo 5-LaborEducation\n";
    int specialty = readNumber("Choice: ", 1, 5);
    s.specialty = static_cast<Specialty>(specialty);
    s.physics = readNumber("Physics (2..5): ", 2, 5);
    s.mathematics = readNumber("Mathematics (2..5): ", 2, 5);
    s.informatics = readNumber("Informatics (2..5): ", 2, 5);
    return s;
}

void printStudents(const Student* students, int n, const int* order) {
    cout << "\nSTUDENTS (Level A)\n";
    cout << left << setw(5) << "No" << setw(16) << "Surname"
        << setw(8) << "Course" << setw(22) << "Specialty"
        << setw(8) << "Physics" << setw(8) << "Math" << "Info\n";
    for (int i = 0; i < n; ++i) {
        const Student& s = students[order ? order[i] : i];
        cout << left << setw(5) << i + 1 << setw(16) << s.surname
            << setw(8) << s.course << setw(22) << specialtyName(s.specialty)
            << setw(8) << s.physics << setw(8) << s.mathematics
            << s.informatics << '\n';
    }
}

int average100(const Student& s) {
    int sum = s.physics + s.mathematics + s.informatics;
    return (sum * 100 + 1) / 3; // Average rounded to 2 decimal places.
}
