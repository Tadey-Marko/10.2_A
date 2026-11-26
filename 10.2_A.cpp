// Умова (ЛР 10.2, рівень А, варіант 3): фізичне й індексне сортування
// за спеціальністю, середнім балом та прізвищем; бінарний пошук студента.
#include <iostream>
#include <cmath>
#include <utility>
#include "student_data.h"
using namespace std;

struct SearchKey {
    Specialty specialty;
    int average;
    string surname;
};

// Alphabetical order of Ukrainian specialty names from the methodology.
int specialtyOrder(Specialty s) {
    switch (s) {
    case Specialty::Informatics: return 1;
    case Specialty::ComputerScience: return 2;
    case Specialty::MathEconomics: return 3;
    case Specialty::LaborEducation: return 4;
    case Specialty::PhysicsInformatics: return 5;
    }
    return 6;
}

SearchKey getKey(const Student& s) {
    return { s.specialty, average100(s), s.surname };
}

int compareKeys(const SearchKey& a, const SearchKey& b) {
    int sa = specialtyOrder(a.specialty), sb = specialtyOrder(b.specialty);
    if (sa != sb) return sa < sb ? -1 : 1;
    if (a.average != b.average) return a.average < b.average ? -1 : 1;
    if (a.surname != b.surname) return a.surname < b.surname ? -1 : 1;
    return 0;
}

void sortPhysical(Student* students, int n) {
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - 1 - i; ++j)
            if (compareKeys(getKey(students[j]), getKey(students[j + 1])) > 0)
                swap(students[j], students[j + 1]);
}

void sortIndexes(const Student* students, int n, int* order) {
    for (int i = 0; i < n; ++i) order[i] = i;
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - 1 - i; ++j)
            if (compareKeys(getKey(students[order[j]]),
                getKey(students[order[j + 1]])) > 0)
                swap(order[j], order[j + 1]);
}

int binarySearch(const Student* students, const int* order, int n,
    const SearchKey& key) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        int comparison = compareKeys(getKey(students[order[middle]]), key);
        if (comparison == 0) return order[middle];
        if (comparison < 0) left = middle + 1;
        else right = middle - 1;
    }
    return -1;
}

#ifndef UNIT_TEST
int main() {
    int n = readNumber("Number of students (1..100): ", 1, 100);
    if (n < 1) return 0;

    Student* students = new Student[n];
    for (int i = 0; i < n; ++i) {
        cout << "\nStudent " << i + 1 << ":\n";
        students[i] = inputStudent();
    }

    int* order = new int[n];
    int choice;
    do {
        cout << "\n1-Show 2-Physical sort 3-Index sort 4-Binary search 0-Exit\n";
        choice = readNumber("Choice: ", 0, 4);
        if (choice == 1) printStudents(students, n);
        if (choice == 2) {
            sortPhysical(students, n);
            printStudents(students, n);
        }
        if (choice == 3) {
            sortIndexes(students, n, order);
            printStudents(students, n, order);
        }
        if (choice == 4) {
            sortIndexes(students, n, order);
            SearchKey key{};
            cout << "Surname: ";
            cin >> key.surname;
            cout << "Specialty: 1-CS 2-Informatics 3-MathEconomics\n"
                << "           4-PhysicsInfo 5-LaborEducation\n";
            int specialty = readNumber("Choice: ", 1, 5);
            key.specialty = static_cast<Specialty>(specialty);
            double avg;
            cout << "Average grade (2.00..5.00): ";
            if (!(cin >> avg) || !isfinite(avg) || avg < 2 || avg > 5) {
                cout << "Invalid average.\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }
            key.average = static_cast<int>(lround(avg * 100));
            int pos = binarySearch(students, order, n, key);
            if (pos == -1) cout << "Student not found.\n";
            else cout << "Found: " << students[pos].surname << ", "
                << specialtyName(students[pos].specialty)
                << ", average=" << average100(students[pos]) / 100.0 << '\n';
        }
    } while (choice > 0);

    delete[] order;
    delete[] students;
    return 0;
}

#endif
