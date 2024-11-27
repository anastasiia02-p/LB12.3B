#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <windows.h>

using namespace std;

enum Specialty {
    CS,  // ����'����� �����
    INF, // �����������
    ME,  // ���������� �� ��������
    PI,  // Գ���� �� �����������
    LT   // ������� ��������
};

string strSpecialty[] = { "����'����� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

struct Student {
    char surname[64];
    int course;
    Specialty specialty;
    unsigned short grade_physics;
    unsigned short grade_math;
    union {
        unsigned short grade_programming;   // ������ � �������������
        unsigned short grade_num_methods;  // ������ � ��������� ������
        unsigned short grade_pedagogy;     // ������ � ���������
    };
};

void CreateFile(const char* file_name);
void PrintFile(const char* file_name);
bool BinarySearch(const char* file_name, const char* surname, int course, unsigned short grade_physics);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char file_name[81];
    cout << "������ ��'� �����: ";
    cin.getline(file_name, sizeof(file_name));

    int menu_option;
    do {
        cout << "\n����:\n";
        cout << "1. �������� ����\n";
        cout << "2. ������� ����\n";
        cout << "3. ����� ��������\n";
        cout << "4. �����\n";
        cout << "��� ����: ";
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

            cout << "������ �������: ";
            cin >> surname;
            cout << "������ ����: ";
            cin >> course;
            cout << "������ ������ � ������: ";
            cin >> grade_physics;

            if (BinarySearch(file_name, surname, course, grade_physics))
                cout << "������� ���������.\n";
            else
                cout << "������� �� ���������.\n";
            break;
        }
        case 4:
            cout << "���������� ������.\n";
            break;
        default:
            cout << "������� ����. ��������� �� ���.\n";
        }
    } while (menu_option != 4);

    return 0;
}

void CreateFile(const char* file_name) {
    ofstream file(file_name, ios::binary);
    if (!file) {
        cerr << "������� ��������� �����!\n";
        return;
    }

    Student student;
    char choice;
    do {
        cout << "\n������ ��� ��������:\n";
        cin.ignore();
        cout << "�������: ";
        cin.getline(student.surname, sizeof(student.surname));
        cout << "����: ";
        cin >> student.course;

        int spec;
        cout << "������������ (0 - ����'����� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        cin >> spec;
        student.specialty = static_cast<Specialty>(spec);

        cout << "������ � ������: ";
        cin >> student.grade_physics;
        cout << "������ � ����������: ";
        cin >> student.grade_math;

        switch (student.specialty) {
        case CS:
            cout << "������ � �������������: ";
            cin >> student.grade_programming;
            break;
        case INF:
            cout << "������ � ��������� ������: ";
            cin >> student.grade_num_methods;
            break;
        default:
            cout << "������ � ���������: ";
            cin >> student.grade_pedagogy;
            break;
        }

        file.write(reinterpret_cast<char*>(&student), sizeof(Student));

        cout << "������ �� ������ ��������? (Y/N): ";
        cin >> choice;

    } while (choice == 'Y' || choice == 'y');

    file.close();
}

    void PrintFile(const char* file_name) {
        ifstream file(file_name, ios::binary);
        if (!file) {
            cerr << "������� �������� �����!\n";
            return;
        }

        cout << "\n================================================================================================================================\n";
        cout << "| #  | �������       | ���� | ������������             | Գ���� | ���������� | ������������� | ������� ������ | ���������  |\n";
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
        cerr << "������� �������� �����!\n";
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
