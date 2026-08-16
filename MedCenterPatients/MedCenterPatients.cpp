#include <iostream>;
#include <fstream>
#include <string>  
#include <cstdlib>  
#include <vector> 
#include <ctime>
#include <sstream>
using namespace std;

struct FullName {
    string surname;
    string name;
    string patronymic;

    FullName& setSurname(string surname) {
        this->surname = surname;     
        return *this;
    }

    FullName& setName(string name) {
        this->name = name;
        return *this;
    }

    FullName& setPatronymic(string patronymic) {
        this->patronymic = patronymic;
        return *this;
    }

    string getFullName() {
        return this->surname + " " + this->name + " " + this->patronymic;
    }
};

struct Date {
    int day;
    int month;
    int year;

    Date& setDay(int day) {
        this->day = day;
        return *this;
    }

    Date& setMonth(int month) {
        this->month = month;
        return *this;
    }

    Date& setYear(int year) {
        this->year = year;
        return *this;
    }

    string getDate() {
        return to_string(this->day) + "." + to_string(this->month) + "." + to_string(this->year);
    }
};

enum Gender {
    MALE,
    FEMALE
};

struct Patient {

    FullName fullName;
    Gender gender;
    Date date;
    string city;
    string phone;
    string diagnosis;

    Patient& setFullName(FullName fullName) {
        this->fullName = fullName;
        return *this;
    }

    Patient& setGender(string stringGender) {
        if (stringGender == "МУЖЧИНА") {
            this->gender = MALE;
        }
        else {
            this->gender = FEMALE;
        }
        return *this;
    }

    Patient& setDate(Date date) {
        this->date = date;
        return *this;
    }

    Patient& setCity(string city) {
        this->city = city;
        return *this;
    }

    Patient& setPhone(string phone) {
        this->phone = phone;
        return *this;
    }

    Patient& setDiagnosis(string diagnosis) {
        this->diagnosis = diagnosis;
        return *this;
    }



    string getStringGender(){
        if (this->gender == MALE) {
            return "МУЖЧИНА";
        }
        else {
            return "ЖЕНЩИНА";
        }
    }

    int ageCalculator() {
        int age;

        time_t timeInSeconds = time(nullptr);
        tm timeInDate;  
        localtime_s(&timeInDate, &timeInSeconds);

        Date today;
        today.day = timeInDate.tm_mday;
        today.month = timeInDate.tm_mon + 1;
        today.year = timeInDate.tm_year + 1900;

        if (this->date.year == today.year) {
            age = 0;
        }
        else {
            age = today.year - this->date.year - 1;
        }

        if (today.month >= this->date.month && today.day >= this->date.day) {
            age = age + 1;
        }

        return age;
    }

    string getPatient() {
        return "  ФИО: " + this->fullName.getFullName() + 
            "   Пол: " + this->getStringGender() + 
            "   Дата рождения: " + this->date.getDate() + 
            "   Город: " + this->city + 
            "   Телефон: " + this->phone + 
            "   Диагноз: " + this->diagnosis + "\n ";
    }
};

vector<Patient> patients;

void parsingDataFile(){
    ifstream file("patients.txt");
    patients.clear();

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        
        stringstream workLine(line);
        string part;
        vector<string> parts;
        while (getline(workLine, part, '\t')) {
            parts.push_back(part);
        }
        string nameClassPart = parts[0];
        string genderPart = parts[1];
        string dateClassPart = parts[2];
        string cityPart = parts[3];
        string phonePart = parts[4];
        string diagnosisPart = parts[5];

        Patient patient;

        FullName fullname;
        stringstream nameLine(nameClassPart);
        string namePart; vector<string> nameParts;
        while (getline(nameLine, namePart, ' ')) {
            nameParts.push_back(namePart);
        }
        fullname.setSurname(nameParts[0]).setName(nameParts[1]).setPatronymic(nameParts[2]);

        Date date;
        stringstream dateLine(dateClassPart);
        string datePart; vector<string> dateParts;
        while (getline(dateLine, datePart, '.')) {
            dateParts.push_back(datePart);
        }
        date.setDay(stoi(dateParts[0])).setMonth(stoi(dateParts[1])).setYear(stoi(dateParts[2]));

        patient.setFullName(fullname).setGender(genderPart).setDate(date).setCity(cityPart).setPhone(phonePart).setDiagnosis(diagnosisPart);

        patients.push_back(patient);
    }
    file.close();
}


bool isNumber(string line) {
    if (line.empty()) return false;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] >= '0' && line[i] <= '9') {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}

void showAllPatients() {
    cout << "\n СПИСОК ПАЦИЕНТОВ \n";
    for (size_t i = 0; i < patients.size(); i++) {
        cout << patients[i].getPatient();
    }
}

void addPatient() {
    Patient patient;

    cout << "\n ДОБАВЛЕНИЕ ПАЦИЕНТА \n";

    string genderPart;
    string cityPart;
    string phonePart;
    string diagnosisPart;

    FullName fullname;
    string name, surname, patronymic;
    cout << "Фамилия: "; cin >> surname;
    cout << "Имя: "; cin >> name;
    cout << "Отчество: "; cin >> patronymic;
    fullname.setSurname(surname).setName(name).setPatronymic(patronymic);

    char gender = 'а';
    while (gender != 'м' && gender != 'ж') {
        cout << "Пол (м/ж): "; cin >> gender;
    }
    if (gender == 'м') { genderPart = "МУЖЧИНА"; }
    else { genderPart = "ЖЕНЩИНА"; }

    Date date;
    int day = 0, month = 0, year = 0;
    string data = ""; 
    while (true) {
        cout << "День рождения: "; cin >> data;
        if (!isNumber(data)) { continue; }
        day = stoi(data);
        if (day >= 1 && day <= 31) {
            break;
        }
    }
    while (true) {
        cout << "Месяц рождения: "; cin >> data;
        if (!isNumber(data)) { continue; }
        month = stoi(data);
        if (month >= 1 && month <= 12) {
            break;
        }
    }
    while (true){
        cout << "Год рождения: "; cin >> data;
        if (!isNumber(data)) { continue; }
        year = stoi(data);
        if (year >= 1900 && year <= 2026) {
            break;
        }
    }
    date.setDay(day).setMonth(month).setYear(year);

    cout << "Город: "; cin >> cityPart;

    while (true) {
    cout << "Телефон: "; cin >> phonePart;
    if (!isNumber(phonePart)) { continue; }
        break;
    }

    cout << "Диагноз: "; cin >> diagnosisPart;

    patient.setFullName(fullname).setGender(genderPart).setDate(date).setCity(cityPart).setPhone(phonePart).setDiagnosis(diagnosisPart);
    patients.push_back(patient);

    ofstream file("patients.txt", ios::app);
           file << patients.back().fullName.getFullName() << "\t"
                << patients.back().getStringGender() << "\t"
                << patients.back().date.getDate() << "\t"
                << patients.back().city << "\t"
                << patients.back().phone << "\t"
                << patients.back().diagnosis << endl;
        file.close();
}

void showPatientsByAgeAndDiagnosis() {

    cout << "\n ВЫБОРКА ПАЦИЕНТОВ ПО УСЛОВИЮ\n";

    string age; string diagnosis; 
    bool havePatiets = false;
    
    while (true) {
    cout << "Пациенты старше "; cin >> age;
    if (!isNumber(age)) { continue; }
    break;
    }
    cout << "у которых диагноз "; cin >> diagnosis;
    
    for (int i = 0; i < patients.size(); i++) {

        if (patients[i].ageCalculator() > stoi(age) && patients[i].diagnosis == diagnosis) {
            cout << patients[i].getPatient();
            havePatiets = true;
        }
    }
    if (!havePatiets) { cout << "По данному условию никого не найдено.\n"; }

}

void showOutOfTownPatients() {
    cout << "\n СПИСОК ИНОГОРОДНИХ ПАЦИЕНТОВ \n";

    bool havePatients = false;
    for (size_t i = 0; i < patients.size(); i++) {
        if (patients[i].city != "Минск") {
            cout << patients[i].getPatient();
            havePatients = true;
        }
    }
    if (!havePatients) { cout << "Иногородние пациенты не найдены.\n"; }
}

int mainMenu() {
    string text_choice;
    int choice = 0;
    cout << "\nВЫБЕРИТЕ КОМАНДУ\n";
    cout << "1. Все пациенты\n";
    cout << "2. Добавить пациента\n";
    cout << "3. Иногородние пациенты\n";
    cout << "4. Список пациентов старше X лет с диагнозом Y\n";
    cout << "Выберите действие: ";
    cin >> text_choice;
    if (!text_choice.empty() && isNumber(text_choice)) {  
        choice = stoi(text_choice);  
    }
    return choice;
}
void menuHandler() {
    int choice = 0;
    while (true) {
        choice = mainMenu();

        switch (choice) {
        case 1:
            showAllPatients();
            break;
        case 2:
            addPatient();
            break;
        case 3:
            showOutOfTownPatients();
            break;
        case 4:
            showPatientsByAgeAndDiagnosis();
            break;
        default:
            cout << "Введите число от 1 до 4.\n";
            continue;
        }
    }
}

int main() {
    parsingDataFile();

    menuHandler();

    return 0;
}