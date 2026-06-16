#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));
    int secret = rand() % 10 + 1;
    int guess;

    cout << "I guessed a number from 1 to 10. Try to guess!\n";

    while (true) {
        cout << "Your guess: ";
        cin >> guess;

        if (guess == secret) {
            cout << "Correct! You win 🎉\n";
            break;
        } else if (guess < secret) {
            cout << "Too small!\n";
        } else {
            cout << "Too big!\n";
        }
    }

    return 0;
}
