#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <limits>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Prompt 10: Organize code into functions

// Prompt 5: Show instructions
void showInstructions() {
    cout << "==== Guess The Number ====\n";
    cout << "Try to guess the number in as few attempts as possible!\n";
    cout << "Choose a difficulty level or set your own range.\n\n";
}

// Prompt 5 + 7: Choose difficulty or custom range
int getDifficulty() {
    int maxRange;
    cout << "Select difficulty: \n1. Easy (1-50)\n2. Medium (1-100)\n3. Hard (1-200)\n4. Custom\nChoice: ";
    int choice;
    cin >> choice;

    switch (choice) {
        case 1: maxRange = 50; break;
        case 2: maxRange = 100; break;
        case 3: maxRange = 200; break;
        case 4:
            cout << "Enter your custom max number: ";
            cin >> maxRange;
            break;
        default:
            cout << "Invalid choice. Defaulting to 1-100.\n";
            maxRange = 100;
    }
    return maxRange;
}

// Prompt 1: Limit number of tries
// Prompt 3: Add warmer/colder hints
// Prompt 4: Show previous guesses
// Prompt 6: Track number of attempts
// Prompt 8: Track best score
// Prompt 9: Track time taken
bool playGame(int maxRange, int& bestScore) {
    int numberToGuess = rand() % maxRange + 1;
    int guess, attempts = 0;
    const int MAX_TRIES = 10;
    vector<int> guesses;

    auto start = high_resolution_clock::now();

    while (attempts < MAX_TRIES) {
        cout << "Enter guess (" << MAX_TRIES - attempts << " tries left): ";
        cin >> guess;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        guesses.push_back(guess);
        attempts++;

        if (guess == numberToGuess) {
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<seconds>(end - start);

            cout << "🎉 You guessed it in " << attempts << " tries and " << duration.count() << " seconds!\n";

            if (bestScore == 0 || attempts < bestScore) {
                bestScore = attempts;
                cout << "🏆 New best score!\n";
            }

            return true;
        } else if (guess < numberToGuess) {
            cout << "Too low! ";
        } else {
            cout << "Too high! ";
        }

        // Prompt 3: Warmer/Colder hints
        if (attempts > 1) {
            int diff = abs(guess - numberToGuess);
            int lastDiff = abs(guesses[attempts - 2] - numberToGuess);
            if (diff < lastDiff)
                cout << "(Getting warmer)\n";
            else
                cout << "(Getting colder)\n";
        } else {
            cout << "\n";
        }

        // Prompt 4: Show previous guesses
        cout << "Previous guesses: ";
        for (int g : guesses) cout << g << " ";
        cout << "\n";
    }

    cout << "❌ You've used all your tries! The number was: " << numberToGuess << "\n";
    return false;
}

int main() {
    srand(time(0));
    bool playAgain = true;
    int bestScore = 0;

    showInstructions();

    while (playAgain) {
        int maxRange = getDifficulty();
        playGame(maxRange, bestScore);

        // Prompt 2: Ask to play again
        cout << "\nPlay again? (1 = yes, 0 = no): ";
        cin >> playAgain;
    }

    cout << "Thanks for playing! 👋\n";
    return 0;
}
