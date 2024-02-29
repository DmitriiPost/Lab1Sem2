#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int STUDENTS_AMOUNT = 10;

struct Profile
{
    string fullName;
    char sex;
    int group;
    int id;
    int grades[8];
};

int countStudents()
{
    ifstream database("C:\\Users\\mitya\\source\\repos\\Lab1Sem2\\students.txt");
    if (!database.is_open())
    {
        return 0;
    }
    else
    {
        int count = 0;
        string data;
        while (!database.eof())
        {
            getline(database, data);
            count++;
        }
        database.close();
        int n;
        n = count / 5;
        return n;
    }
}

void readFromFile(Profile student[])
{
    ifstream database("C:\\Users\\mitya\\source\\repos\\Lab1Sem2\\students.txt");
    if (!database.is_open())
    {
        cout << "Ошибка открытия!\n";
    }

    else
    {
        string s;
        for (int i = 0; i < STUDENTS_AMOUNT; i++)
        {
            getline(database, student[i].fullName);
            database >> student[i].sex >> student[i].group >> student[i].id;
            for (int j = 0; j < 8; j++)
            {
                database >> student[i].grades[j];
            }
            getline(database, s, '\n');
        }
        database.close();
    }
}

void shellSort(int arr[], Profile studs[], short n)
{
    int i, j, d;
    d = n / 2;
    while (d > 0)
    {
        for (i = 0; i < n - d; i++)
        {
            j = i;
            while ((j >= 0) && (arr[j] > arr[j + d]))
            {
                swap(arr[j], arr[j + d]);
                swap(studs[j], studs[j + d]);
                j--;
            }
        }
        d /= 2;
    }
}

void createNewRecord()
{
    Profile student;
    cout << "Введите ФИО(на английском): ";
    getline(cin, student.fullName);
    cout << '\n' << "Введите пол (M/W): ";
    cin >> student.sex;
    cout << '\n' << "Введите номер группы: ";
    cin >> student.group;
    cout << "\nВведите порядковый номер студента в группе: ";
    cin >> student.id;
    cout << "\nВведите 8 оценок: ";
    for (int i = 0; i < 8; i++)
    {
        cin >> student.grades[i];
    }

    bool isDismissed = false;
    for (int i = 0; i < 8; i++)
    {
        if (student.grades[i] == 2)
        {
            isDismissed = true;
        }
    }
    if (!isDismissed)
    {
        ofstream database;
        database.open("C:\\Users\\mitya\\source\\repos\\Lab1Sem2\\students.txt", ios::app);
        if (!database.is_open())
        {
            cout << "Ошибка сохранения!\n";
        }
        else
        {
            database << student.fullName << '\n' << student.sex << '\n' << student.group << '\n' << student.id << '\n';
            for (int i = 0; i < 8; i++)
            {
                database << student.grades[i] << " ";
            }
            database << '\n';
            database.close();
            cout << "Профиль сохранен\n";
        }
    }
    else
    {
        cout << "У этого студента есть неуд, он должен быть отчислен, информация не сохранена" << '\n';
    }
}

void editData()
{
    int count = countStudents();
    int recNum;
    cout << "Введите номер записи, которую хотите изменить: ";
    cin >> recNum;

    if ((recNum >= 0) && (recNum < count))
    {
        ifstream database("C:\\Users\\mitya\\source\\repos\\Lab1Sem2\\students.txt");
        if (!database.is_open())
        {
            cout << "Ошибка чтения\n";
        }

        else
        {
            Profile* student = new Profile[count];
            string s;
            for (int i = 0; i < count; i++)
            {
                getline(database, student[i].fullName);
                database >> student[i].sex >> student[i].group >> student[i].id;
                for (int j = 0; j < 8; j++)
                {
                    database >> student[i].grades[j];
                }
                getline(database, s, '\n');
            }

            cout << "Запись, которую Вы выбрали:\n";
            cout << student[recNum].fullName << "\n";
            cout << student[recNum].sex << '\n';
            cout << student[recNum].group << '\n';
            cout << student[recNum].id << '\n';
            for (int i = 0; i < 8; i++)
            {
                cout << student[recNum].grades[i] << " ";
            }
            cout << '\n';

            short choise;
            cout << "Что хотите изменить:\n1. ФИО\n2. Пол\n3. Номер группы\n4. Номер в списке группы\n5. Оценки\n";
            cin >> choise;
            switch (choise)
            {
            case (1):
                cout << "Введите новое ФИО (на английском): ";
                getline(cin, student[recNum].fullName);
                break;
            case (2):
                cout << "Введите новый пол(M/W): ";
                cin >> student[recNum].sex;
                break;
            case (3):
                cout << "Введите новый номер группы: ";
                cin >> student[recNum].group;
                break;
            case (4):
                cout << "Введите новый номер в списке группы: ";
                cin >> student[recNum].id;
                break;
            case (5):
                cout << "Введите новые оценки: ";
                for (int i = 0; i < 8; i++)
                {
                    cin >> student[recNum].grades[i];
                }
                break;
            default:
                break;
            }
            database.close();

            ofstream database;
            database.open("C:\\Users\\mitya\\source\\repos\\Lab1Sem2\\students.txt");
            if (!database.is_open())
            {
                cout << "Ошибка сохранения!\n";
            }

            else
            {
                for (int i = 0; i < count; i++)
                {
                    database << student[i].fullName << '\n' << student[i].sex << '\n' << student[i].group << '\n' << student[i].id << '\n';
                    for (int j = 0; j < 8; j++)
                    {
                        database << student[i].grades[j] << " ";
                    }
                    database << '\n';
                }
                database.close();
            }
        }
    }
    else
    {
        cout << "Записи с таким номером нет\n";
    }
}

void showData()
{
    ifstream database("C:\\Users\\mitya\\source\\repos\\Lab1Sem2\\students.txt");
    if (!database.is_open())
    {
        cout << "Ошибка чтения\n";
    }
    else
    {
        string data;
        while (!database.eof())
        {
            getline(database, data);
            cout << data << '\n';
        }
    }
    database.close();
}

void showGroup()
{
    Profile* student = new Profile[STUDENTS_AMOUNT];
    int grNum;
    cout << "Введите номер группы: ";
    cin >> grNum;
    readFromFile(student);

    bool hasMembers = false;
    for (int i = 0; i < STUDENTS_AMOUNT; i++)
    {
        if (student[i].group == grNum)
        {
            cout << student[i].id << ". " << student[i].fullName << '\n';
            cout << student[i].sex << '\n';
            cout << "Оценки: ";
            for (int j = 0; j < 8; j++)
            {
                cout << student[i].grades[j] << " ";
            }
            cout << '\n' << '\n';
            hasMembers = true;
        }
    }
    if (!hasMembers)
    {
        cout << "Ни одной записи не найдено" << '\n';
    }
    
}

void showTop()
{
    Profile* student = new Profile[STUDENTS_AMOUNT];
    readFromFile(student);
    int sumOfGrades[STUDENTS_AMOUNT];
    for (int i = 0; i < STUDENTS_AMOUNT; i++)
    {
        sumOfGrades[i] = 0;
    }
    for (int i = 0; i < STUDENTS_AMOUNT; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            sumOfGrades[i] += student[i].grades[j];
        }
    }

    shellSort(sumOfGrades, student, STUDENTS_AMOUNT);
    int count = countStudents();
    cout << "Топ 5 лучших студентов за прошедшую сессию:\n";
    for (int i = count - 1; i >= count - 5; i--)
    {
        cout << student[i].fullName << " " << student[i].group << " гр. " << float(sumOfGrades[i]) / 8 << '\n';
    }
    cout << '\n';
}

void countMale()
{
    int count = countStudents();
    Profile* student = new Profile[STUDENTS_AMOUNT];
    ifstream database("C:\\Users\\mitya\\source\\repos\\Lab1Sem2\\students.txt");
    readFromFile(student);
    int maleAmount = 0;
    for (int i = 0; i < count; i++)
    {
        if (student[i].sex = 'M')
        {
            maleAmount++;
        }
    }
    cout << "M: " << maleAmount << " W: " << count - maleAmount << '\n';
}

void showRichStudents()
{
    int count = countStudents();
    Profile* student = new Profile[STUDENTS_AMOUNT];
    readFromFile(student);
    bool hasThree = false;
    bool hasFour = false;

    cout << "Студенты, которые не получают стипендию:\n";
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (student[i].grades[j] == 3)
            {
                hasThree = true;
            }
        }
        if (hasThree)
        {
            cout << student[i].fullName << '\n' << student[i].sex << '\n' << student[i].group << '\n' << student[i].id << '\n';
            hasThree = false;
        }
    }

    cout << "Студенты, которые учатся на хорошо и отлично:\n";
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (student[i].grades[j] == 3)
            {
                hasThree = true;
            }
            if (student[i].grades[j] == 4)
            {
                hasFour = true;
            }
        }
        if ((!hasThree) && (hasFour))
        {
            cout << student[i].fullName << '\n' << student[i].sex << '\n' << student[i].group << '\n' << student[i].id << '\n';
        }
        hasThree = false;
        hasFour = false;
    }

    cout << "Студенты, которые учатся только на отлично:\n";
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (student[i].grades[j] == 3)
            {
                hasThree = true;
            }
            if (student[i].grades[j] == 4)
            {
                hasFour = true;
            }
        }
        if ((!hasThree) && (!hasFour))
        {
            cout << student[i].fullName << '\n' << student[i].sex << '\n' << student[i].group << '\n' << student[i].id << '\n';
        }
        hasThree = false;
        hasFour = false;
    }
}

void showStudentsWithNumK()
{
    int k;
    Profile* student = new Profile[STUDENTS_AMOUNT];
    readFromFile(student);
    cout << "Введите номер студента в группе: ";
    cin >> k;
    for (int i = 0; i < STUDENTS_AMOUNT; i++)
    {
        if (student[i].id == k)
        {
            cout << student[i].fullName << '\n' << student[i].sex << '\n' << student[i].group << '\n' << student[i].id << '\n';
            for (int j = 0; j < 8; j++)
            {
                cout << student[i].grades[j] << " ";
            }
            cout << '\n';
        }
    }
}

int main()
{
    setlocale(0, "");
    short menu;
    while (true)
    {
        cout << "1. Создание новой записи\n2. Редактирование записи\n3. Вывод всех данных\n4. Вывод информации о студентах группы N\n5. Вывод топа студентов\n6. Вывод количества студентов мужского и женского пола\n7. Вывод данных о стипендии студентов\n8. Вывод данных о студентах, имеющих номер в списке группы - k\n0. Выход\n9. ИДЗ\n10. Очистить консоль\n";
        cin >> menu;
        switch (menu)
        {
        case (1):
            createNewRecord();
            break;
        case (2):
            editData();
            break;
        case (3):
            showData();
            break;
        case (4):
            showGroup();
            break;
        case (5):
            showTop();
            break;
        case (6):
            countMale();
            break;
        case (7):
            showRichStudents();
            break;
        case (8):
            showStudentsWithNumK();
            break;
        case (0):
            exit(0);
        case (10):
            system("cls");
            break;
        default:
            break;
        }
    }
}
