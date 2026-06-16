#include <iostream>
using namespace std;

int main() {
    double balance = 1000;
    int choice;
    double amount;

    while (true) {
        cout << "\n=== ATM MENU ===\n";
        cout << "1 - Check balance\n";
        cout << "2 - Deposit\n";
        cout << "3 - Withdraw\n";
        cout << "4 - Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Balance: " << balance << endl;
        }
        else if (choice == 2) {
            cout << "Enter amount to deposit: ";
            cin >> amount;
            balance += amount;
            cout << "Added!\n";
        }
        else if (choice == 3) {
            cout << "Enter amount to withdraw: ";
            cin >> amount;

            if (amount <= balance) {
                balance -= amount;
                cout << "Withdraw successful!\n";
            } else {
                cout << "Not enough money!\n";
            }
        }
        else if (choice == 4) {
            cout << "Bye!\n";
            break;
        }
        else {
            cout << "Wrong choice\n";
        }
    }

    return 0;
}
