#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>

using namespace std;

enum Specialty {
    CS,  // Комп'ютерні науки
    INF, // Інформатика
    ME,  // Математика та економіка
    PI,  // Фізика та інформатика
    LT   // Трудове навчання
};

string strSpecialty[] = { "Комп'ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

struct Student {
    char surname[64];
    int course;
    Specialty specialty;
    unsigned short grade_physics;
    unsigned short grade_math;
    union {
        unsigned short grade_programming;   // Оцінка з програмування
        unsigned short grade_num_methods;  // Оцінка з чисельних методів
        unsigned short grade_pedagogy;     // Оцінка з педагогіки
    };
};

void CreateFile(const char* file_name);
void PrintFile(const char* file_name);
bool BinarySearch(const char* file_name, const char* surname, int course, unsigned short grade_physics);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char file_name[81];
    cout << "Введіть ім'я файлу: ";
    cin.getline(file_name, sizeof(file_name));

    int menu_option;
    do {
        cout << "\nМеню:\n";
        cout << "1. Створити файл\n";
        cout << "2. Вивести файл\n";
        cout << "3. Пошук студента\n";
        cout << "4. Вихід\n";
        cout << "Ваш вибір: ";
        cin >> menu_option;

        switch (menu_option) {
        case 1:
            CreateFile(file_name);
            break;
        case 2:
            PrintFile(file_name);
            break;
        case 3: {
            char surname[64];
            int course;
            unsigned short grade_physics;

            cout << "Введіть прізвище: ";
            cin >> surname;
            cout << "Введіть курс: ";
            cin >> course;
            cout << "Введіть оцінку з фізики: ";
            cin >> grade_physics;

            if (BinarySearch(file_name, surname, course, grade_physics))
                cout << "Студент знайдений.\n";
            else
                cout << "Студент не знайдений.\n";
            break;
        }
        case 4:
            cout << "Завершення роботи.\n";
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    } while (menu_option != 4);

    return 0;
}

void CreateFile(const char* file_name) {
    ofstream file(file_name, ios::binary);
    if (!file) {
        cerr << "Помилка створення файлу!\n";
        return;
    }

    Student student;
    char choice;
    do {
        cout << "\nВведіть дані студента:\n";
        cin.ignore();
        cout << "Прізвище: ";
        cin.getline(student.surname, sizeof(student.surname));
        cout << "Курс: ";
        cin >> student.course;

        int spec;
        cout << "Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> spec;
        student.specialty = static_cast<Specialty>(spec);

        cout << "Оцінка з фізики: ";
        cin >> student.grade_physics;
        cout << "Оцінка з математики: ";
        cin >> student.grade_math;

        switch (student.specialty) {
        case CS:
            cout << "Оцінка з програмування: ";
            cin >> student.grade_programming;
            break;
        case INF:
            cout << "Оцінка з чисельних методів: ";
            cin >> student.grade_num_methods;
            break;
        default:
            cout << "Оцінка з педагогіки: ";
            cin >> student.grade_pedagogy;
            break;
        }

        file.write(reinterpret_cast<char*>(&student), sizeof(Student));

        cout << "Додати ще одного студента? (Y/N): ";
        cin >> choice;

    } while (choice == 'Y' || choice == 'y');

    file.close();
}

    void PrintFile(const char* file_name) {
        ifstream file(file_name, ios::binary);
        if (!file) {
            cerr << "Помилка відкриття файлу!\n";
            return;
        }

        cout << "\n================================================================================================================================\n";
        cout << "| #  | Прізвище       | Курс | Спеціальність             | Фізика | Математика | Програмування | Чисельні методи | Педагогіка  |\n";
        cout << "--------------------------------------------------------------------------------------------------------------------------------\n";

        Student student;
        int index = 0;
        while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            cout << "| " << setw(2) << right << ++index << " | "
                << setw(15) << left << student.surname
                << "| " << setw(4) << student.course
                << " | " << setw(24) << left << strSpecialty[student.specialty]
                << "  | " << setw(6) << student.grade_physics
                << " | " << setw(10) << student.grade_math;

            switch (student.specialty) {
            case CS:
                cout << "   | " << setw(13) << student.grade_programming << " |";
                cout << setw(16) << "-" << "    |";
                cout << setw(11) << "-" << "    |\n";
                break;
            case INF:
                cout << "| " << setw(13) << "-" << "  |";
                cout << setw(16) << student.grade_num_methods << " |";
                cout << setw(11) << "-" << "  |\n";
                break;
            default:
                cout << "| " << setw(13) << "-" << "|";
                cout << setw(16) << "-" << "|";
                cout << setw(11) << student.grade_pedagogy << "|\n";
                break;
            }
        }

        cout << "================================================================================================================================\n";
        file.close();
    

}

bool BinarySearch(const char* file_name, const char* surname, int course, unsigned short grade_physics) {
    ifstream file(file_name, ios::binary);
    if (!file) {
        cerr << "Помилка відкриття файлу!\n";
        return false;
    }

    Student student;
    while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (strcmp(student.surname, surname) == 0 && student.course == course && student.grade_physics == grade_physics) {
            return true;
        }
    }

    return false;
}
