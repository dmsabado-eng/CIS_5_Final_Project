#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace std;

const int MAX_PLAYERS = 5;

struct BasketballPlayer {
    string name;
    int jerseyNumber;
    string position;
    int gamesPlayed;
    int totalPoints;
    int totalRebounds;
    int totalAssists;
};

void printMenu();
void displayPlayer(const BasketballPlayer& player);
void displayAllPlayers(const BasketballPlayer players[], int size);
int findPlayerByJersey(const BasketballPlayer players[], int size, int jerseyNumber);
double calculateAverage(int totalStat, int gamesPlayed);
void displayTeamAverages(const BasketballPlayer players[], int size);
BasketballPlayer* findTopScorer(BasketballPlayer players[], int size);
void updatePlayerStats(BasketballPlayer& player);
void displayPerformanceRating(const BasketballPlayer& player);
void clearInput();

int main() {
    BasketballPlayer players[MAX_PLAYERS] = {
        {"Jordan Lee", 3, "Point Guard", 10, 185, 42, 76},
        {"Marcus Brown", 11, "Shooting Guard", 10, 210, 38, 44},
        {"Ethan Davis", 21, "Small Forward", 10, 168, 71, 35},
        {"Noah Wilson", 34, "Power Forward", 10, 142, 93, 24},
        {"Lucas Martinez", 50, "Center", 10, 126, 108, 18}
    };

    int choice;

    do {
        printMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Invalid input. Please enter a number from 1 to 7.\n\n";
            continue;
        }

        if (choice == 1) {
            displayAllPlayers(players, MAX_PLAYERS);
        }
        else if (choice == 2) {
            int jerseyNumber;
            cout << "Enter the player's jersey number: ";
            cin >> jerseyNumber;

            if (cin.fail()) {
                clearInput();
                cout << "Invalid jersey number.\n\n";
                continue;
            }

            int index = findPlayerByJersey(players, MAX_PLAYERS, jerseyNumber);

            if (index != -1) {
                displayPlayer(players[index]);
                displayPerformanceRating(players[index]);
            }
            else {
                cout << "No player was found with jersey #" << jerseyNumber << ".\n\n";
            }
        }
        else if (choice == 3) {
            displayTeamAverages(players, MAX_PLAYERS);
        }
        else if (choice == 4) {
            BasketballPlayer* topScorer = findTopScorer(players, MAX_PLAYERS);

            if (topScorer != nullptr) {
                cout << "\n===== TOP SCORER =====\n";
                displayPlayer(*topScorer);
            }
        }
        else if (choice == 5) {
            int jerseyNumber;
            cout << "Enter the jersey number of the player to update: ";
            cin >> jerseyNumber;

            if (cin.fail()) {
                clearInput();
                cout << "Invalid jersey number.\n\n";
                continue;
            }

            int index = findPlayerByJersey(players, MAX_PLAYERS, jerseyNumber);

            if (index != -1) {
                updatePlayerStats(players[index]);
            }
            else {
                cout << "No player was found with jersey #" << jerseyNumber << ".\n\n";
            }
        }
        else if (choice == 6) {
            int jerseyNumber;
            cout << "Enter the player's jersey number: ";
            cin >> jerseyNumber;

            if (cin.fail()) {
                clearInput();
                cout << "Invalid jersey number.\n\n";
                continue;
            }

            int index = findPlayerByJersey(players, MAX_PLAYERS, jerseyNumber);

            if (index != -1) {
                displayPerformanceRating(players[index]);
            }
            else {
                cout << "No player was found with jersey #" << jerseyNumber << ".\n\n";
            }
        }
        else if (choice == 7) {
            cout << "Thank you for using the Basketball Player Statistics Tracker!\n";
        }
        else {
            cout << "Invalid choice. Please select an option from 1 to 7.\n\n";
        }

    } while (choice != 7);

    return 0;
}

void printMenu() {
    cout << "========== BASKETBALL PLAYER STATISTICS TRACKER ==========\n";
    cout << "1. Display all players\n";
    cout << "2. Search for a player by jersey number\n";
    cout << "3. Display team averages\n";
    cout << "4. Display the top scorer\n";
    cout << "5. Add stats from a new game\n";
    cout << "6. Display a player's performance rating\n";
    cout << "7. Exit\n";
    cout << "==========================================================\n";
}

void displayPlayer(const BasketballPlayer& player) {
    double pointsPerGame = calculateAverage(player.totalPoints, player.gamesPlayed);
    double reboundsPerGame = calculateAverage(player.totalRebounds, player.gamesPlayed);
    double assistsPerGame = calculateAverage(player.totalAssists, player.gamesPlayed);

    cout << fixed << setprecision(1);
    cout << "\nName: " << player.name << '\n';
    cout << "Jersey Number: #" << player.jerseyNumber << '\n';
    cout << "Position: " << player.position << '\n';
    cout << "Games Played: " << player.gamesPlayed << '\n';
    cout << "Points Per Game: " << pointsPerGame << '\n';
    cout << "Rebounds Per Game: " << reboundsPerGame << '\n';
    cout << "Assists Per Game: " << assistsPerGame << "\n\n";
}

void displayAllPlayers(const BasketballPlayer players[], int size) {
    cout << "\n================ TEAM ROSTER ================\n";
    cout << left << setw(20) << "Name"
         << setw(10) << "Jersey"
         << setw(18) << "Position"
         << right << setw(8) << "PPG"
         << setw(8) << "RPG"
         << setw(8) << "APG" << '\n';
    cout << string(72, '-') << '\n';

    for (int i = 0; i < size; i++) {
        cout << left << setw(20) << players[i].name
             << setw(10) << players[i].jerseyNumber
             << setw(18) << players[i].position
             << right << fixed << setprecision(1)
             << setw(8) << calculateAverage(players[i].totalPoints, players[i].gamesPlayed)
             << setw(8) << calculateAverage(players[i].totalRebounds, players[i].gamesPlayed)
             << setw(8) << calculateAverage(players[i].totalAssists, players[i].gamesPlayed)
             << '\n';
    }

    cout << '\n';
}

int findPlayerByJersey(const BasketballPlayer players[], int size, int jerseyNumber) {
    for (int i = 0; i < size; i++) {
        if (players[i].jerseyNumber == jerseyNumber) {
            return i;
        }
    }

    return -1;
}

double calculateAverage(int totalStat, int gamesPlayed) {
    if (gamesPlayed == 0) {
        return 0.0;
    }

    return static_cast<double>(totalStat) / gamesPlayed;
}

void displayTeamAverages(const BasketballPlayer players[], int size) {
    int totalGames = 0;
    int totalPoints = 0;
    int totalRebounds = 0;
    int totalAssists = 0;

    for (int i = 0; i < size; i++) {
        totalGames += players[i].gamesPlayed;
        totalPoints += players[i].totalPoints;
        totalRebounds += players[i].totalRebounds;
        totalAssists += players[i].totalAssists;
    }

    cout << fixed << setprecision(1);
    cout << "\n===== TEAM AVERAGES PER PLAYER-GAME =====\n";
    cout << "Average Points: " << calculateAverage(totalPoints, totalGames) << '\n';
    cout << "Average Rebounds: " << calculateAverage(totalRebounds, totalGames) << '\n';
    cout << "Average Assists: " << calculateAverage(totalAssists, totalGames) << "\n\n";
}

BasketballPlayer* findTopScorer(BasketballPlayer players[], int size) {
    if (size <= 0) {
        return nullptr;
    }

    BasketballPlayer* topPlayer = &players[0];

    for (int i = 1; i < size; i++) {
        double currentAverage = calculateAverage(players[i].totalPoints, players[i].gamesPlayed);
        double topAverage = calculateAverage(topPlayer->totalPoints, topPlayer->gamesPlayed);

        if (currentAverage > topAverage) {
            topPlayer = &players[i];
        }
    }

    return topPlayer;
}

void updatePlayerStats(BasketballPlayer& player) {
    int points;
    int rebounds;
    int assists;

    cout << "Enter points scored in the new game: ";
    cin >> points;
    cout << "Enter rebounds in the new game: ";
    cin >> rebounds;
    cout << "Enter assists in the new game: ";
    cin >> assists;

    if (cin.fail()) {
        clearInput();
        cout << "Invalid input. The player's statistics were not updated.\n\n";
        return;
    }

    if (points < 0 || rebounds < 0 || assists < 0) {
        cout << "Statistics cannot be negative. No changes were made.\n\n";
    }
    else {
        player.gamesPlayed++;
        player.totalPoints += points;
        player.totalRebounds += rebounds;
        player.totalAssists += assists;

        cout << player.name << "'s statistics were updated successfully.\n";
        displayPlayer(player);
    }
}

void displayPerformanceRating(const BasketballPlayer& player) {
    double ppg = calculateAverage(player.totalPoints, player.gamesPlayed);
    double rpg = calculateAverage(player.totalRebounds, player.gamesPlayed);
    double apg = calculateAverage(player.totalAssists, player.gamesPlayed);
    double rating = ppg + rpg + apg;

    cout << fixed << setprecision(1);
    cout << "Performance score for " << player.name << ": " << rating << '\n';

    if (rating >= 30.0) {
        cout << "Rating: Superstar performance\n\n";
    }
    else if (rating >= 22.0) {
        cout << "Rating: Strong performance\n\n";
    }
    else if (rating >= 15.0) {
        cout << "Rating: Solid performance\n\n";
    }
    else {
        cout << "Rating: Needs improvement\n\n";
    }
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
