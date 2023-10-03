#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#define ENTER_ABSORPTION string templine; getline(cin, templine); // без этой штуки первые гетлайны в функциях автоматически засасывают предыдущий энтер

ofstream ofile;
ifstream ifile;

void Window_0(), Window_1(), Window_2(int AbonentNumber);
void Deserealize(), Serealize();

class Abonent
{
public:

    Abonent(string Name, string HomePhone, string JobPhone, string MobilePhone, string AdditionalInformation)
    {
        this->Name = Name;
        this->HomePhone = HomePhone;
        this->JobPhone = JobPhone;
        this->MobilePhone = MobilePhone;
        this->AdditionalInformation = AdditionalInformation;
    }

    void SetName(string Name) { this->Name = Name; }
    string GetName() { return this->Name; }

    void SetHomePhone(string HomePhone) { this->HomePhone = HomePhone; }
    string GetHomePhone() { return this->HomePhone; }

    void SetJobPhone(string JobPhone) { this->JobPhone = JobPhone; }
    string GetJobPhone() { return this->JobPhone; }

    void SetMobilePhone(string MobilePhone) { this->MobilePhone = MobilePhone; }
    string GetMobilePhone() { return this->MobilePhone; }

    void SetAdditionalInformation(string AdditionalInformation) { this->AdditionalInformation = AdditionalInformation; }
    string GetAdditionalInformation() { return this->AdditionalInformation; }

private:

    string Name;
    string HomePhone;
    string JobPhone;
    string MobilePhone;
    string AdditionalInformation;

};

vector<Abonent> PhoneBook;

bool NameIsUnique(string Name)
{
    for (auto i : PhoneBook)
    {
        if (i.GetName() == Name) return false;
    }

    return true;
}

string SetUniqueName(string Line)
{
    string Name;

    cout << "Имя: ";
    getline(cin, Name);

    while (true)
    {
        if (NameIsUnique(Name)) break;
        else
        {
            system("cls");

            cout << "Телефонная книга\n" << endl;
            cout << Line << endl;
            cout << "Контакт с таким именем уже существует!" << endl;
            cout << "Введите другое имя: ";
            getline(cin, Name);
        }
    }

    return Name;
}

void AddNewAbonent()
{
    system("cls");

    cout << "Телефонная книга\n" << endl;
    cout << "Добавление нового контакта\n" << endl;

    string Name,
        HomePhone,
        JobPhone,
        MobilePhone,
        AdditionalInformation;

    Name = SetUniqueName("Добавление нового контакта\n");

    system("cls");

    cout << "Телефонная книга\n" << endl;
    cout << "Добавление нового контакта\n" << endl;

    cout << "Имя: " << Name << endl;

    cout << "Домашний телефон: ";
    getline(cin, HomePhone);

    cout << "Рабочий телефон: ";
    getline(cin, JobPhone);

    cout << "Мобильный телефон: ";
    getline(cin, MobilePhone);

    cout << "Дополнительная информация: ";
    getline(cin, AdditionalInformation);

    PhoneBook.push_back({ Name, HomePhone, JobPhone, MobilePhone, AdditionalInformation });

    Serealize();

    Window_1();
}

void Deserealize() // файл -> вектор
{
    ifile.open("FileNames.txt");

    vector<Abonent> tempPhoneBook;
    string line;

    if (ifile.is_open())
    {
        while (getline(ifile, line))
        {
            int count = 1;

            ifstream itemp;
            string templine;

            string Name,
                HomePhone,
                JobPhone,
                MobilePhone,
                AdditionalInformation;

            itemp.open(line);

            while (getline(itemp, templine))
            {
                switch (count)
                {
                case 1: Name = templine; break;
                case 2: HomePhone = templine; break;
                case 3: JobPhone = templine; break;
                case 4: MobilePhone = templine; break;
                case 5: AdditionalInformation = templine; break;
                }

                count++;
            }

            tempPhoneBook.push_back({ Name, HomePhone, JobPhone, MobilePhone, AdditionalInformation });
        }
    }

    ifile.close();

    PhoneBook = tempPhoneBook;
}

void Serealize() // вектор -> файл
{
    ofile.open("FileNames.txt");

    for (auto i : PhoneBook)
    {
        ofile << i.GetName() << ".txt\n";
    }

    ofile.close();

    for (auto i : PhoneBook)
    {
        ofile.open(i.GetName() + ".txt");

        ofile << i.GetName() << "\n" << i.GetHomePhone() << "\n" << i.GetJobPhone() << "\n" << i.GetMobilePhone() << "\n" << i.GetAdditionalInformation();

        ofile.close();
    }
}

void AbonentInformationOutput(int AbonentNumber, string Line)
{
    system("cls");

    cout << "Телефонная книга\n" << endl;

    cout << Line << endl;

    cout << "1) Имя: " << PhoneBook[AbonentNumber].GetName() << endl;
    cout << "2) Домашний телефон: " << PhoneBook[AbonentNumber].GetHomePhone() << endl;
    cout << "3) Рабочий телефон: " << PhoneBook[AbonentNumber].GetJobPhone() << endl;
    cout << "4) Мобильный телефон: " << PhoneBook[AbonentNumber].GetMobilePhone() << endl;
    cout << "5) Дополнительная информация: " << PhoneBook[AbonentNumber].GetAdditionalInformation() << endl;
    cout << endl;
}

void Window_0()
{
    int temp = 0;

    while (temp < 1 || temp > 2)
    {
        system("cls");

        cout << "Телефонная книга\n" << endl;
        cout << "Действия:" << endl;
        cout << "1) Добавить контакт" << endl;
        cout << "2) Выйти" << endl;
        cout << "Введите номер действия: ";

        cin >> temp;

        ENTER_ABSORPTION
    }

    if (temp == 1) AddNewAbonent();
    else return;
}

void Window_1()
{
    int temp = 0;

    while (temp < 1 || temp > 3)
    {
        system("cls");

        cout << "Телефонная книга\n" << endl;

        cout << "Список контактов:" << endl;

        for (int i = 0; i < PhoneBook.size(); i++)
        {
            cout << i + 1 << ") " << PhoneBook[i].GetName() << endl;
        }

        cout << endl;

        cout << "Действия:" << endl;
        cout << "1) Добавить контакт" << endl;
        cout << "2) Показать информацию о контакте" << endl;
        cout << "3) Выйти" << endl;
        cout << "Введите номер действия: ";

        cin >> temp;

        ENTER_ABSORPTION
    }

    if (temp == 1) AddNewAbonent();
    else if (temp == 2)
    {
        int ttemp = 0;

        while (ttemp < 1 || ttemp > PhoneBook.size())
        {
            system("cls");

            cout << "Телефонная книга\n" << endl;

            cout << "Список контактов:" << endl;

            for (int i = 0; i < PhoneBook.size(); i++)
            {
                cout << i + 1 << ") " << PhoneBook[i].GetName() << endl;
            }

            cout << endl;

            cout << "Введите номер контакта, информацию о котором необходимо показать: ";
            cin >> ttemp;
        }

        ttemp--;
        Window_2(ttemp);
    }
    else return;
}

void Window_2(int AbonentNumber)
{
    int temp = 0;

    while (temp < 1 || temp > 3)
    {
        AbonentInformationOutput(AbonentNumber, "Информация о контакте " + PhoneBook[AbonentNumber].GetName() + "\n");

        cout << "Действия:" << endl;
        cout << "1) Изменить контакт" << endl;
        cout << "2) Удалить контакт" << endl;
        cout << "3) Назад" << endl;
        cout << "Введите номер действия: ";

        cin >> temp;
    }

    if (temp == 1)
    {
        int ttemp = 0;

        while (ttemp < 1 || ttemp > 5)
        {
            AbonentInformationOutput(AbonentNumber, "Изменение контакта " + PhoneBook[AbonentNumber].GetName() + "\n");

            cout << "Введите номер характеристики, которую необходимо изменить: ";
            cin >> ttemp;

            ENTER_ABSORPTION
        }

        AbonentInformationOutput(AbonentNumber, "Изменение контакта " + PhoneBook[AbonentNumber].GetName() + "\n");
        cout << "Введите номер характеристики, которую необходимо изменить: " << ttemp << endl;

        if (ttemp == 1)
        {
            string FileName = PhoneBook[AbonentNumber].GetName() + ".txt";
            remove(FileName.c_str());

            string Name = SetUniqueName("Изменение контакта " + PhoneBook[AbonentNumber].GetName() + "\n");

            PhoneBook[AbonentNumber].SetName(Name);
        }
        else if (ttemp == 2)
        {
            string HomePhone;

            cout << "Домашний телефон: ";
            getline(cin, HomePhone);

            PhoneBook[AbonentNumber].SetHomePhone(HomePhone);
        }
        else if (ttemp == 3)
        {
            string JobPhone;

            cout << "Рабочий телефон: ";
            getline(cin, JobPhone);

            PhoneBook[AbonentNumber].SetJobPhone(JobPhone);
        }
        else if (ttemp == 4)
        {
            string MobilePhone;

            cout << "Мобильный телефон: ";
            getline(cin, MobilePhone);

            PhoneBook[AbonentNumber].SetMobilePhone(MobilePhone);
        }
        else
        {
            string AdditionalInformation;

            cout << "Дополнительная информация: ";
            getline(cin, AdditionalInformation);

            PhoneBook[AbonentNumber].SetAdditionalInformation(AdditionalInformation);
        }

        Serealize();

        Window_2(AbonentNumber);
    }
    else if (temp == 2)
    {
        string FileName = PhoneBook[AbonentNumber].GetName() + ".txt";
        remove(FileName.c_str());

        PhoneBook.erase(PhoneBook.begin() + AbonentNumber);

        Serealize();

        if (PhoneBook.size()) Window_1();
        else
        {
            remove("FileNames.txt");

            Window_0();
        }
    }
    else Window_1();
}

int main()
{
    setlocale(LC_ALL, "ru");

    Deserealize();

    if (PhoneBook.size()) Window_1();
    else Window_0();
}

/*
*                                                         ОКНА
*                                                        /    \
*                                                 window1      window0 (при отсутствии контактов)
*                                           (список контактов)    |   \
*                                          /                 \    |    AddNewAbonent()
*                                   window2                   выход             |
*                          (информация о контакте)         из программы       window1
*                         /                       \
*             (изменить контакт)                  window1
*             (удалить контакт)                   (назад)
*                  (назад)
*/
