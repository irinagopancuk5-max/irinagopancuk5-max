#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<double> expenses;
    int choice;
    double amount;

    while (true) {
        cout << "\n=== EXPENSE TRACKER ===\n";
        cout << "1 - Add expense\n";
        cout << "2 - Show expenses\n";
        cout << "3 - Total sum\n";
        cout << "4 - Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter amount: ";
            cin >> amount;
            expenses.push_back(amount);
            cout << "Added!\n";
        }
        else if (choice == 2) {
            if (expenses.empty()) {
                cout << "No expenses yet\n";
            } else {
                cout << "Expenses: ";
                for (int i = 0; i < expenses.size(); i++) {
                    cout << expenses[i] << " ";
                }
                cout << endl;
            }
        }
        else if (choice == 3) {
            double sum = 0;
            for (int i = 0; i < expenses.size(); i++) {
                sum += expenses[i];
            }
            cout << "Total: " << sum << endl;
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Wrong choice\n";
        }
    }

    return 0;
}
