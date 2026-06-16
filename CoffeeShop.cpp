#include <iostream>
#include <vector>
using namespace std;

struct Item {
    string name;
    double price;
};

vector<Item> menu = {
    {"Espresso", 30},
    {"Americano", 35},
    {"Cappuccino", 45},
    {"Latte", 50}
};

vector<Item> order;
double totalSales = 0;

void showMenu() {
    cout << "\n--- COFFEE MENU ---\n";
    for (int i = 0; i < menu.size(); i++) {
        cout << i + 1 << " - " << menu[i].name
             << " (" << menu[i].price << ")\n";
    }
    cout << menu.size() + 1 << " - Finish order\n";
}

void showOrder(double total) {
    cout << "\n--- YOUR ORDER ---\n";
    for (auto &item : order) {
        cout << item.name << " - " << item.price << "\n";
    }
    cout << "TOTAL: " << total << "\n";
}

void adminPanel() {
    cout << "\n--- ADMIN PANEL ---\n";
    cout << "Total sales: " << totalSales << "\n";
}

int main() {
    int choice;
    double total = 0;

    while (true) {
        showMenu();
        cout << "Choose: ";
        cin >> choice;

        if (choice >= 1 && choice <= menu.size()) {
            order.push_back(menu[choice - 1]);
            total += menu[choice - 1].price;
            cout << "Added: " << menu[choice - 1].name << "\n";
        }
        else if (choice == menu.size() + 1) {
            totalSales += total;
            showOrder(total);
            order.clear();
            total = 0;
        }
        else if (choice == 6) {
            adminPanel();
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
