#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <time.h>
#include <windows.h>
#include <conio.h>

using namespace std;

int gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return 0;
}

void Time() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    gotoxy(50, 0);
    cout << "Current date and time : " << asctime(ltm) << "\033[32m";
}

struct Transactions {
    float amount;
    string description;
};

class PocketMoney {
private:
    vector<Transactions> transaction;

public:
    float budget, expense, saving;
    PocketMoney() {
        budget = 0.0;
        expense = 0.0;
        saving = 0.0;
    }

    void initialize();
    void spend_money();
    void save_money();
    void display_details();
    void show_transac();
};

void PocketMoney::initialize() {
    system("cls");
    Time();
    gotoxy(20, 2);
    cout << "Enter your budget for the month : ";
    cin >> budget;
}

void PocketMoney::spend_money() {
    system("cls");
    Time();
    float amount;
    gotoxy(23, 4);
    cout << "Enter amount spent: ";
    cin >> amount;
    if (amount <= budget - expense) {
        gotoxy(23, 6);
        cout << "Expense Recorded." << endl;
        Transactions t;
        string description;
        gotoxy(23, 8);
        cout << "Enter a brief description for this expense : ";
        cin.ignore();
        getline(cin, description);
        t.amount = amount;
        t.description = description;
        expense += amount;
        transaction.push_back(t);
    } else {
        gotoxy(23, 6);
        cout << "\033[1;31mInsufficient budget to record this expense.\033[1;32m";
        gotoxy(23, 8);
        cout << "Press any key to continue...";
        _getch();
    }
}

void PocketMoney::save_money() {
    system("cls");
    Time();
    float amount;
    gotoxy(23, 5);
    cout << "Enter amount to save: ";
    cin >> amount;

    if (amount > (budget - expense)) {
        gotoxy(23, 7);
        cout << "\033[1;31mInsufficient funds to save.\033[1;32m";
        gotoxy(23, 9);
        cout << "Saving money exceeds available budget.\033[1;32m";
    } else {
        Transactions t;
        string description;
        gotoxy(13, 7);
        cout << "Enter a brief description for this saving : ";
        cin.ignore();
        getline(cin, description);
        t.amount = amount;
        t.description = description;
        saving += amount;
        transaction.push_back(t);

        gotoxy(23, 10);
        cout << "Save Successfully!";
        gotoxy(23, 12);
        cout << "Remaining Budget: " << budget - (expense + saving) << " DH";
    }
    gotoxy(23, 14);
    cout << "Press any key to continue...";
    _getch();
}

void PocketMoney::display_details() {
    system("cls");
    Time();
    gotoxy(25, 2);
    cout << "\033[1;34mPocket Details : \033[32m" << endl;
    cout << fixed << setprecision(1);
    gotoxy(20, 4);
    cout << "---------------------------\n";
    gotoxy(22, 6);
    cout << "Budget: " << budget << endl;
    gotoxy(22, 8);
    cout << "Expense: " << expense << endl;
    gotoxy(22, 10);
    cout << "Saving: " << saving << endl;
    gotoxy(20, 12);
    cout << "---------------------------\n";
    gotoxy(25, 16);
    cout << "Press any key to continue...";
    getch();
}

void PocketMoney::show_transac() {
    system("cls");
    Time();
    gotoxy(33, 2);
    cout << "\033[1;34mTransactions History : \033[32m\n";
    if (transaction.empty()) {
        gotoxy(23, 4);
        cout << "No transactions recorded yet.\n";
    } else {
        for (const auto& t : transaction) {
            gotoxy(18, 4);
            cout << "---------------------------------------------------------" << endl;
            gotoxy(22, 6);
            cout << "Description: " << t.description << " | Amount: " << t.amount << " DH" << endl;
        }
    }
    gotoxy(28, 9);
    cout << "Press any key to continue...";
    getch();
}

int main() {
    system("cls");
    system("color A");
    int choice;
    PocketMoney pm;
    pm.initialize();
    do {
        system("cls");
        Time();
        gotoxy(25, 2);
        cout << "---------------------------------" << endl;
        gotoxy(30, 4);
        cout << "\033[1;34mPocket Money Management \033[0m\033[32m\n";
        gotoxy(27, 6);
        cout << "1. Spend Money." << endl;
        gotoxy(27, 8);
        cout << "2. Save Money." << endl;
        gotoxy(27, 10);
        cout << "3. Display Details." << endl;
        gotoxy(27, 12);
        cout << "4. Show Transactions." << endl;
        gotoxy(27, 14);
        cout << "5. Exit." << endl;
        gotoxy(25, 16);
        cout << "---------------------------------" << endl;
        gotoxy(28, 18);
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                pm.spend_money();
                break;
            case 2:
                pm.save_money();
                break;
            case 3:
                pm.display_details();
                break;
            case 4:
                pm.show_transac();
                break;
            case 5:
                gotoxy(30, 21);
                cout << "\033[32mExiting Program...\033[1;32m\n\n";
                exit(0);
                break;
            default:
                gotoxy(30, 20);
                cout << "\033[1;31mInvalid choice.\033[1;32m";
                gotoxy(26, 22);
                system("pause");
                break;
        }
    } while (choice != 5);
}
