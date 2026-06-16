#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));

    int user, computer;

    cout << "Rock Paper Scissors Game!\n";
    cout << "1 - Rock\n2 - Paper\n3 - Scissors\n";

    while (true) {
        cout << "\nYour choice: ";
        cin >> user;

        computer = rand() % 3 + 1;

        cout << "Computer chose: " << computer << endl;

        if (user == computer) {
            cout << "Draw!\n";
        }
        else if (
            (user == 1 && computer == 3) ||
            (user == 2 && computer == 1) ||
            (user == 3 && computer == 2)
        ) {
            cout << "You win! 🎉\n";
        }
        else {
            cout << "You lose 😢\n";
        }
    }

    return 0;
}
