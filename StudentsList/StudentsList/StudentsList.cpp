#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>

using namespace std;

class Grades {
private:
    string name_of_subject;
    string date_of_exam;
    string teachers_name;
    int score;

public:
    Grades(string nos, string doe, string tn, int sc) {
        name_of_subject = nos;
        date_of_exam = doe;
        teachers_name = tn;
        score = sc;
    }

    void get_grades(bool info) {
        cout << name_of_subject << endl;
        cout << "Оценка: " << score << endl;
        if (info) get_exam_info();
    }

    void get_exam_info() {
        cout << "Дата проведения экзамена: " << date_of_exam << endl;
        cout << "Преподаватель: " << teachers_name << endl;
        cout << endl;
    }

    int get_score() {
        return score;
    }
};

class Students {
private:
    string students_name;
    string date_of_birth;
    vector<Grades> exams;

public:
    Students(string sn, string dob, string nos[4], string doe[4], string tn[4], int sc[4]) {
        students_name = sn;
        date_of_birth = dob;
        for (int i = 0; i < 4; i++) {
            exams.push_back(Grades(nos[i], doe[i], tn[i], sc[i]));
        }
    }

    void get_student(bool info) {
        cout << endl << students_name << " (" << date_of_birth << ")" << endl;
        cout << endl << "Оценки:" << endl;
        for (int i = 0; i < exams.size(); i++) {
            exams[i].get_grades(info);
        }
    }

    double check_progress() {
        double progress = 0;
        for (int i = 0; i < exams.size(); i++) progress += exams[i].get_score();
        return progress * 1.0 / exams.size();
    }

    bool is_student(string name) {
        if (students_name == name) return true;
        return false;
    }

    void get_name() {
        cout << students_name << endl;
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    bool fl = true;
    string buff;
    string name, birth, subject[4], date_exam[4], name_teacher[4];
    int scores[4], count = 0, j = 0;
    vector<Students> students_list;

    ifstream fin("StudentsDB.txt");
    while (!fin.eof()) {
        getline(fin, buff);
        string temp = "";

        for (int i = 0; i < buff.size(); i++) {
            if (buff[i] != ';') {
                temp += buff[i];
            }
            else {
                count++;
                if (fl) {
                    if (count == 1) name = temp;
                    else birth = temp;
                }
                else {
                    if (count == 1) subject[j] = temp;
                    else if (count == 2) date_exam[j] = temp;
                    else if (count == 3) name_teacher[j] = temp;
                    else {
                        scores[j] = stoi(temp);
                        count = 0;
                        j++;
                    }
                }
                temp = "";
            }
        }
        if(!fl) students_list.push_back(Students(name, birth, subject, date_exam, name_teacher, scores));
        if (fl) fl = false; else fl = true;
        count = 0;
        j = 0;
    }
    fin.close();

    char option = '4';
    while (option != '0') {
        cout << endl;
        cout << "1: Вывести список студентов" << endl;
        cout << "2: Вывести успеваемость конкретного студента" << endl;
        cout << "3: Вывести студента с лучшей успеваемостью" << endl;
        cout << "0: Выйти из программы" << endl;
        cout << "Выберите опцию: ";
        cin >> option;
        cin.ignore();
        cout << endl;

        if (option == '1') {
            for (int i = 0; i < students_list.size(); i++) {
                students_list[i].get_name();
            }
        }
        else if (option == '2') {
            cout << "Введите фамилию и имя студента: ";
            getline(cin, name);
            cout << endl;
            fl = true;

            for (int i = 0; i < students_list.size(); i++) {
                if (students_list[i].is_student(name)) {
                    students_list[i].get_student(true);
                    fl = false;
                }
            }

            if (fl) cout << "Нет такого студента!" << endl;
        }
        else if (option == '3') {
            double max = students_list[0].check_progress();
            vector<int> best;
            best.push_back(0);

            for (int i = 1; i < students_list.size(); i++) {
                if (students_list[i].check_progress() > max) {
                    max = students_list[i].check_progress();
                    best.clear();
                    best.push_back(i);
                }
                else if (students_list[i].check_progress() == max) {
                    best.push_back(i);
                }
            }

            for (int i = 0; i < best.size(); i++) {
                students_list[best[i]].get_student(false);
                cout << "Средняя оценка: " << students_list[best[i]].check_progress() << endl;
            }
        }
        else if (option != '0') {
            cout << endl << "Некорректный ввод!"; 
        }
    }
}