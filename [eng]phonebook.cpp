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

    cout << "Name: ";
    getline(cin, Name);

    while (true)
    {
        if (NameIsUnique(Name)) break;
        else
        {
            system("cls");

            cout << "Phone book\n" << endl;
            cout << Line << endl;
            cout << "A contact with the same name already exists!" << endl;
            cout << "Enter a different name: ";
            getline(cin, Name);
        }
    }

    return Name;
}

void AddNewAbonent()
{
    system("cls");

    cout << "Phone book\n" << endl;
    cout << "Adding a new contact\n" << endl;

    string Name,
        HomePhone,
        JobPhone,
        MobilePhone,
        AdditionalInformation;

    Name = SetUniqueName("Adding a new contact\n");

    system("cls");

    cout << "Phone book\n" << endl;
    cout << "Adding a new contact\n" << endl;

    cout << "Name: " << Name << endl;

    cout << "Home phone: ";
    getline(cin, HomePhone);

    cout << "Job phone: ";
    getline(cin, JobPhone);

    cout << "Mobile phone: ";
    getline(cin, MobilePhone);

    cout << "Additional information: ";
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

    cout << "Phone book\n" << endl;

    cout << Line << endl;

    cout << "1) Name: " << PhoneBook[AbonentNumber].GetName() << endl;
    cout << "2) Home phone: " << PhoneBook[AbonentNumber].GetHomePhone() << endl;
    cout << "3) Job phone: " << PhoneBook[AbonentNumber].GetJobPhone() << endl;
    cout << "4) Mobile phone: " << PhoneBook[AbonentNumber].GetMobilePhone() << endl;
    cout << "5) Additional information: " << PhoneBook[AbonentNumber].GetAdditionalInformation() << endl;
    cout << endl;
}

void Window_0()
{
    int temp = 0;

    while (temp < 1 || temp > 2)
    {
        system("cls");

        cout << "Phone book\n" << endl;
        cout << "Actions:" << endl;
        cout << "1) Add contact" << endl;
        cout << "2) Exit" << endl;
        cout << "Enter action number: ";

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

        cout << "Phone book\n" << endl;

        cout << "Contact list:" << endl;

        for (int i = 0; i < PhoneBook.size(); i++)
        {
            cout << i + 1 << ") " << PhoneBook[i].GetName() << endl;
        }

        cout << endl;

        cout << "Actions:" << endl;
        cout << "1) Add contact" << endl;
        cout << "2) Show contact information" << endl;
        cout << "3) Exit" << endl;
        cout << "Enter action number: ";

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

            cout << "Phone book\n" << endl;

            cout << "Contact list:" << endl;

            for (int i = 0; i < PhoneBook.size(); i++)
            {
                cout << i + 1 << ") " << PhoneBook[i].GetName() << endl;
            }

            cout << endl;

            cout << "Enter the contact number whose information you want to show: ";
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
        AbonentInformationOutput(AbonentNumber, "Contact " + PhoneBook[AbonentNumber].GetName() + "\n");

        cout << "Actions:" << endl;
        cout << "1) Change contact" << endl;
        cout << "2) Delete contact" << endl;
        cout << "3) Back" << endl;
        cout << "Enter action number: ";

        cin >> temp;
    }

    if (temp == 1)
    {
        int ttemp = 0;

        while (ttemp < 1 || ttemp > 5)
        {
            AbonentInformationOutput(AbonentNumber, "Changing contact " + PhoneBook[AbonentNumber].GetName() + "\n");

            cout << "Enter the number of the feature you want to change : ";
            cin >> ttemp;

            ENTER_ABSORPTION
        }

        AbonentInformationOutput(AbonentNumber, "Changing contact " + PhoneBook[AbonentNumber].GetName() + "\n");
        cout << "Enter the number of the feature you want to change : " << ttemp << endl;

        if (ttemp == 1)
        {
            string FileName = PhoneBook[AbonentNumber].GetName() + ".txt";
            remove(FileName.c_str());

            string Name = SetUniqueName("Changing contact " + PhoneBook[AbonentNumber].GetName() + "\n");

            PhoneBook[AbonentNumber].SetName(Name);
        }
        else if (ttemp == 2)
        {
            string HomePhone;

            cout << "Home phone: ";
            getline(cin, HomePhone);

            PhoneBook[AbonentNumber].SetHomePhone(HomePhone);
        }
        else if (ttemp == 3)
        {
            string JobPhone;

            cout << "Job phone: ";
            getline(cin, JobPhone);

            PhoneBook[AbonentNumber].SetJobPhone(JobPhone);
        }
        else if (ttemp == 4)
        {
            string MobilePhone;

            cout << "Mobile phone: ";
            getline(cin, MobilePhone);

            PhoneBook[AbonentNumber].SetMobilePhone(MobilePhone);
        }
        else
        {
            string AdditionalInformation;

            cout << "Additional information: ";
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
