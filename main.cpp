#include <iomanip>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>

using namespace std;

class calender
{
private:
    int daycode = 0;
    string banner = "banner.txt";
    string welcome = "Art.txt";
    string developer = "Developer.txt";
    string thankyou = "thankyou.txt";
    string str;

public:
    void menu();
    void art(int, string); // int type = banner or welcome
                           // Welcome --> Sleep
                           // Banner ---> without Sleep

    void display(int, int, int, int); // year month day type
    // type == Which type of date to be display .. for eg .. particular year or particular month
    int numOfday(int);
    int month_finder(int, int);
    int dayfinder(int, int, int);
    void animation(int, string); // speed,file
};
void calender::animation(int speed, string temp)
{
    int i = 0;
    while (temp[i] != NULL)
    {
        cout << temp[i];
        i++;
        Sleep(speed);
    }
}

void calender::art(int type, string name)
{
    string filename(name);

    FILE *input_file = fopen(filename.c_str(), "r");

    unsigned char character = 0;
    while (!feof(input_file))
    {
        character = getc(input_file);
        if (type == 99)
            Sleep(2);
        else
            Sleep(0);

        cout << character << "";
    }
    cout << endl;
    fclose(input_file);
}

int calender::numOfday(int year)
{
    int temp;
    temp = (((year - 1) * 365) + ((year - 1) / 4) - ((year - 1) / 100) + ((year / 400) + 1)) % 7;
    return temp;
}

void calender::menu()
{
    int ch, type, date, month, day;
    do
    {

        system("cls");
        art(2, banner);
        str = "\n\t\t\t  <------  WELCOME TO MAIN MENU  -------> ";
        animation(2, str);
        cout << endl
             << "\t\t <---------------------------------------------------------->";

        cout << endl
             << "\t\t <-------   1  .  Calender of the year         -------------> ";
        cout << endl
             << "\t\t <-------   2  .  Search a Particular Year Calender --------> ";
        cout << endl
             << "\t\t <-------   10  . About Developer            -------------> ";
        cout << endl
             << "\t\t <-------   99 .  Exit                           -----------> ";

        cout << endl
             << "\t\t <---------------------------------------------------------->";
        cin >> ch;

        switch (ch)
        {
        case 1:
            type = 1;
            str = "\n\t\t Enter Date -----> ";
            animation(2, str);
            cin >> date;
            display(date, 1, 1, type); // date /month/day
            getch();
            break;

        case 2: // Showing a particular date of the year
        top:
            type = 2;
            str = "\n\t\t Enter Years -----> ";
            animation(2, str);
            fflush(stdin);
            cin >> date;
            str = "\t\t Enter Month -----> ";
            animation(2, str);
            cin >> month;
            if (month > 12)
            {
                str = "\n\t\t <------ Month Should not be greater than 12 -----> ";
                animation(2, str);
                goto top;
            }

            display(date, month - 1, 1, type);
            getch();

            break;
        case 10: // developer
            system("cls");
            art(99, developer);
            getch();
            break;
        case 99:

            system("cls");
            art(99, thankyou);
            // getch();
            break;

        default:
            str = "\n\t\t <---- Invalid options  -----> ";
            animation(2, str);
            break;
        }
    } while (ch != 99);
}

void calender::display(int date, int entry_month, int day, int type)
{

    string weeks[] = {" Sun ", " Mon ", " Tue ", " Wed ", " Thu ", " Fri ", " Sat "};
    int weeks_in_days[] = {1, 2, 3, 4, 5, 6, 7};
    int total_days[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
    // string month[] = {"Januray", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    int days;      // number of days store
    int last_days; // store last day for next month
    int temp = 0;  // dividing days in weeks system
    last_days = 0;

    int ch = 0; // ch for to store the switch statement variable

    last_days = numOfday(date);

    system("cls");
    if (type == 2)
    {
        for (int month = 0; month < 12; month++)
        {
            if (entry_month == month)
            {
                // banner();
                art(1, banner);
                days = month_finder(month, date);
                // weeks

                cout << endl
                     << setw(10) << "     ";
                for (int week = 0; week <= 6; week++)
                {
                    cout << setw(5) << weeks[week] << " ";
                }

                cout << endl
                     << setw(9)
                     << "  ";

                temp = 0;
                if (last_days == 7)
                    last_days = 0;

                for (int i = 1; i <= last_days; i++)
                {
                    temp++;
                    cout << setw(6) << "  ";
                }

                for (int day = 0; day < days; day++)
                {

                    if (temp == 7)
                    {
                        cout << endl
                             << setw(9)
                             << "  ";

                        temp = 0;
                    }
                    cout << setw(5) << total_days[day] << " ";

                    temp++;
                    last_days = temp;
                }
                cout << endl
                     << "     <------------------------------------------------------>";
            }
        }

        str = "\n\t 1. Next Month ";
        animation(2, str);

        str = "\n\t 2. Previous Month ";
        animation(2, str);

        str = "\n\t 3. Next Years ";
        animation(2, str);

        str = "\n\t 4. Previous Year ";
        animation(2, str);

        str = "\n\t 100. Return To Main Menu ";
        animation(2, str);
        cout << endl
             << "\t<----------------------------->";
        cin >> ch;

        switch (ch)
        {
        case 1: // next month

            if (entry_month == 11)
                display(date, 0, day, type);

            display(date, entry_month + 1, day, type);
            break;

        case 2: // previous month

            if (entry_month == 0)
                display(date, 11, day, type);

            display(date, entry_month - 1, day, type);
            break;

        case 3: // Next Year
            display(date + 1, entry_month, day, type);
            break;

        case 4: // previous month

            display(date - 1, entry_month, day, type);
            break;

        case 100:
            menu(); // main menu
            break;
        }
    }
    else if (type == 1)
    {
        system("cls");
        for (int month = 0; month < 12; month++)
        {

            // banner();
            days = month_finder(month, date);
            // weeks

            cout << endl
                 << setw(10) << "    ";
            for (int week = 0; week <= 6; week++)
            {
                cout << setw(5) << weeks[week] << " ";
            }

            cout << endl
                 << setw(9)
                 << "  ";

            temp = 0;
            if (last_days == 7)
                last_days = 0;

            for (int i = 1; i <= last_days; i++)
            {
                temp++;
                cout << setw(6) << "  ";
            }

            for (int day = 0; day < days; day++)
            {

                if (temp == 7)
                {
                    cout << endl
                         << setw(9)
                         << "  ";

                    temp = 0;
                }
                cout << setw(5) << total_days[day] << " ";

                temp++;
                last_days = temp;
            }
            cout << endl
                 << "     <------------------------------------------------------>";
        }
    }
}

int calender::month_finder(int num, int date)
{
    string month[] = {"Januray", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    // days = for total number of day in a month
    int days = 0;

    // cout << endl
    //      << "                               " << date << endl
    //      << "     <--------------------   " << month[num] << "   ------------------->";
    cout<<endl;
    str = "                               ";
    animation(2, str);
    cout << date;

    cout << endl;
    str = "     <--------------------   " + month[num] + "    ------------------->";
    animation(2, str);
    num = num + 1;

    if (num == 1)
        days = 31;
    else if (num == 2)
    {
        if (date % 400 == 0 || (date % 4 == 0 && date % 100 != 0))
            days = 29;
        else
            days = 28;
    }
    else if (num == 3)
    {
        days = 31;
    }
    else if (num == 4)
    {
        days = 30;
    }
    else if (num == 5)
    {
        days = 31;
    }
    else if (num == 6)
    {
        days = 30;
    }
    else if (num == 7)
    {
        days = 31;
    }
    else if (num == 8)
    {
        days = 31;
    }
    else if (num == 9)
    {
        days = 30;
    }
    else if (num == 10)
    {
        days = 31;
    }
    else if (num == 11)
    {
        days = 30;
    }
    else if (num == 12)
    {
        days = 31;
    }

    return days;
}

int main()
{
    system("cls");
    // system("color 2f");
    system("color a");
    string welcome = "Art.txt";
    string developer = "Developer.txt";
    calender cal;

    system("cls");

    cal.art(99, welcome);
    Sleep(1000);
    system("cls");
    cal.art(100, developer);
    getch();
    cal.menu();
}
