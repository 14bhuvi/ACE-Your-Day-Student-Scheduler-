#include<iostream>
#include<conio.h>
#include<fstream>
#include<string>
#include <vector>
#include<ctime>
#include<cstdio>
#include <iomanip>
#include<sstream>
using namespace std;

// Base class to store personal information
class Info {
protected:
    string name, id, course, year;
    int rollno, age;

public:
    void getdata() {
        cout << "\nEnter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter your ID: ";
        getline(cin, id);
        cout << "Enter your course: ";
        getline(cin, course);
        cout << "Enter your year: ";
        getline(cin, year);
        cout << "Enter your roll number: ";
        cin >> rollno;
    }

    void showdata() const {
        cout << "\nName: " << name << "\nAge: " << age << "\nID: " << id
             << "\nCourse: " << course << "\nYear: " << year
             << "\nRoll Number: " << rollno << endl;
    }
};

// Derived class to handle student-specific operations
class Student : public Info {
public:
    bool isDuplicateID(const string& new_id) {
        ifstream in("student.txt");
        string file_id, file_name, file_course, file_year;
        int file_rollno, file_age;

        while (in >> file_id >> file_name >> file_age >> file_course >> file_year >> file_rollno) {
            if (file_id == new_id) {
                return true;
            }
        }
        return false;
    }

    void get() {
        getdata();
        if (isDuplicateID(id)) {
            cout << "\nError: Duplicate ID detected. This record will not be saved.\n";
        } else {
            ofstream out("student.txt", ios::app);
            if (out.is_open()) {
                out << id << " " << name << " " << age << " " << course << " " << year << " " << rollno << endl;
                cout << "\nData saved successfully!\n";
            } else {
                cout << "\nError opening file for writing.\n";
            }
            out.close();
        }
    }

    void show() {
        ifstream in("student.txt");
        string file_id, file_name, file_course, file_year;
        int file_rollno, file_age;

        if (in.is_open()) {
            cout << "\nReading data from file:\n";
            while (in >> file_id >> file_name >> file_age >> file_course >> file_year >> file_rollno) {
                cout << "\nID: " << file_id << "\nName: " << file_name << "\nAge: " << file_age
                     << "\nCourse: " << file_course << "\nYear: " << file_year
                     << "\nRoll Number: " << file_rollno << "\n";
            }
            in.close();
        } else {
            cout << "\nError opening file for reading.\n";
        }
    }

    void update() {
    ifstream in("student.txt");
    ofstream out("temp.txt");
    string file_id, file_name, file_course, file_year;
    int file_rollno, file_age;
    string update_id;
    bool found = false;

    // Ask user for the ID of the record to update
    cout << "\nEnter the ID of the student to update: ";
    cin.ignore();
    getline(cin, update_id);

    // Check if both files are open
    if (in.is_open() && out.is_open()) {
        while (in >> file_id >> file_name >> file_age >> file_course >> file_year >> file_rollno) {
            if (file_id == update_id) {
                found = true;
                cout << "\nRecord found. What do you want to update?\n";
                cout << "1. Name\n2. Age\n3. Course\n4. Year\n5. Roll Number\nEnter your choice: ";
                int choice;
                cin >> choice;
                cin.ignore();

                // Update the specific field based on user choice
                switch (choice) {
                case 1:
                    cout << "Enter new name: ";
                    getline(cin, file_name);
                    break;
                case 2:
                    cout << "Enter new age: ";
                    cin >> file_age;
                    cin.ignore();
                    break;
                case 3:
                    cout << "Enter new course: ";
                    getline(cin, file_course);
                    break;
                case 4:
                    cout << "Enter new year: ";
                    getline(cin, file_year);
                    break;
                case 5:
                    cout << "Enter new roll number: ";
                    cin >> file_rollno;
                    cin.ignore();
                    break;
                default:
                    cout << "Invalid choice. No changes made.\n";
                    break;
                }
                cout << "\nRecord updated successfully.\n";
            }
            // Write updated or unmodified record to the temporary file
            out << file_id << " " << file_name << " " << file_age << " "
                << file_course << " " << file_year << " " << file_rollno << endl;
        }
        in.close();
        out.close();

        // Replace original file with updated temporary file
        if (found) {
            remove("student.txt");
            rename("temp.txt", "student.txt");
        } else {
            cout << "\nID not found. No updates made.\n";
            remove("temp.txt");
        }
    } else {
        cout << "\nError opening file.\n";
    }
}

};
class Schedule {
protected:
    string date; // Date in dd-mm-yyyy format
    string day;  // Day of the week (e.g., Monday, Tuesday)

public:
    virtual void addSchedule() = 0; // Pure virtual function
    virtual void viewSchedule() = 0; // View schedule based on date and day
};

// Derived class for Class Schedules
class ClassSchedule : public Schedule {
public:
    // Modified addSchedule to include time slots
void addSchedule() {
    ofstream out("class_schedule.txt", ios::app); // Open file in append mode
    if (!out.is_open()) {
        cout << "\nError: Could not open the class schedule file.\n";
        return;
    }

    cout << "\nEnter the date (dd-mm-yy): ";
    cin.ignore();
    getline(cin, date);

    // Validate the date format
    if (date.size() != 8 || date[2] != '-' || date[5] != '-') {
        cout << "Invalid date format! Please enter the date in dd-mm-yy format.\n";
        return;
    }

    cout << "Enter the day (e.g., Monday, Tuesday): ";
    getline(cin, day);

    char more = 'y';
    while (more == 'y' || more == 'Y') {
        string startTime, endTime, task;
        cout << "Enter the start time (e.g., 09:00): ";
        getline(cin, startTime);

        cout << "Enter the end time (e.g., 10:00): ";
        getline(cin, endTime);

        cout << "Enter the activity for " << startTime << " to " << endTime << ": ";
        getline(cin, task);

        // Write date, day, time block, and activity details to the file
        out << date << " | " << day << " | " << startTime << " to " << endTime << " | " << task << endl;

        cout << "Do you want to add another time slot? (y/n): ";
        cin >> more;
        cin.ignore(); // Clear the input buffer
    }

    cout << "\nClass schedule added successfully for " << day << ", " << date << "!\n";
    out.close();
}


// Modified viewSchedule to display time-based schedules
void viewSchedule() {
    ifstream in("class_schedule.txt");
    if (!in.is_open()) {
        cout << "\nError: Could not open the class schedule file.\n";
        return;
    }

    string inputDate, inputDay;
    cout << "Enter the date (YYYY-MM-DD): ";
    cin >> inputDate;

    cout << "Enter the day (e.g., Monday, Tuesday): ";
    cin >> ws; // Clear the input buffer before getting a line
    getline(cin, inputDay);

    string line;
    bool found = false;

    cout << "\nClass schedule for " << inputDay << ", " << inputDate << ":\n";

    while (getline(in, line)) {
        if (line.find(inputDate + " | " + inputDay + " |") == 0) { // Match date and day
            cout << line.substr(inputDate.length() + inputDay.length() + 5) << endl; // Print the schedule
            found = true;
        }
    }

    if (!found) {
        cout << "No class schedule found for " << inputDay << ", " << inputDate << ".\n";
    }

    in.close();
}



};

// Derived class for Self-Study Schedules
class SelfStudySchedule : public Schedule {
public:
    void addSchedule() {
    ofstream out("self_study_schedule.txt", ios::app); // Open file in append mode
    if (!out.is_open()) {
        cout << "\nError: Could not open the self study schedule file.\n";
        return;
    }

    cout << "\nEnter the date (dd-mm-yy): ";
    cin.ignore();
    getline(cin, date);

    // Validate the date format
    if (date.size() != 8 || date[2] != '-' || date[5] != '-') {
        cout << "Invalid date format! Please enter the date in dd-mm-yy format.\n";
        return;
    }

    cout << "Enter the day (e.g., Monday, Tuesday): ";
    getline(cin, day);

    char more = 'y';
    while (more == 'y' || more == 'Y') {
        string startTime, endTime, task;
        cout << "Enter the start time (e.g., 09:00): ";
        getline(cin, startTime);

        cout << "Enter the end time (e.g., 10:00): ";
        getline(cin, endTime);

        cout << "Enter the activity for " << startTime << " to " << endTime << ": ";
        getline(cin, task);

        // Write date, day, time block, and activity details to the file
        out << date << " | " << day << " | " << startTime << " to " << endTime << " | " << task << endl;

        cout << "Do you want to add another time slot? (y/n): ";
        cin >> more;
        cin.ignore(); // Clear the input buffer
    }

    cout << "\nself study schedule added successfully for " << day << ", " << date << "!\n";
    out.close();
}


    void viewSchedule() {
    ifstream in("self_study_schedule.txt");
    if (!in.is_open()) {
        cout << "\nError: Could not open the self-study schedule file.\n";
        return;
    }

    string inputDate, inputDay;
    cout << "Enter the date (YYYY-MM-DD): ";
    cin >> inputDate;

    cout << "Enter the day (e.g., Monday, Tuesday): ";
    cin >> ws; // Clear the input buffer before getting a full line
    getline(cin, inputDay);

    string line;
    bool found = false;

    cout << "\nSelf-study schedule for " << inputDay << ", " << inputDate << ":\n";

    while (getline(in, line)) {
        if (line.find(inputDate + " | " + inputDay + " |") == 0) { // Match date and day
            cout << line.substr(inputDate.length() + inputDay.length() + 5) << endl; // Print the schedule
            found = true;
        }
    }

    if (!found) {
        cout << "No self-study schedule found for " << inputDay << ", " << inputDate << ".\n";
    }

    in.close();
}

};


class Activity {
protected:
    string date;      // Date in dd-mm-yy format
    string details;   // Activity details
    bool isCompleted; // Completion status

public:
    virtual void addActivity() = 0;  // Pure virtual function to add an activity
    virtual void viewActivity(const string& date) = 0; // Pure virtual function to view activities
    virtual void markCompleted(const string& taskDetails) = 0; // Pure virtual function to mark tasks as completed
};
class FiveFoldActivity : public Activity {
public:
    void addActivity() {
        ofstream out("five_fold_activities.txt", ios::app); // Open the file for appending
        if (!out.is_open()) {
            cout << "\nError: Could not open the five-fold activity file.\n";
            return;
        }

        cout << "\nEnter the date for the activity (dd-mm-yy): ";
        cin.ignore();
        getline(cin, date);

        char more = 'y';
        while (more == 'y' || more == 'Y') {
            string startTime, endTime, activityDetails;

            cout << "Enter the start time (e.g., 09:00): ";
            getline(cin, startTime);

            cout << "Enter the end time (e.g., 10:00): ";
            getline(cin, endTime);

            cout << "Enter details of the activity: ";
            getline(cin, activityDetails);

            // Write the full activity schedule to the file
            out << date << " | " << startTime << " to " << endTime << " | " << activityDetails << endl;

            cout << "Do you want to add another activity for this date? (y/n): ";
            cin >> more;
            cin.ignore(); // Clear the input buffer
        }

        cout << "\nAll activities added successfully for " << date << "!\n";
        out.close();
    }

    void viewActivity(const string& date) {
        ifstream in("five_fold_activities.txt");
        if (!in.is_open()) {
            cout << "\nError: Could not open the five-fold activity file.\n";
            return;
        }

        string line;
        bool found = false;

        cout << "\nFive-fold activities for " << date << ":\n";

        while (getline(in, line)) {
            if (line.find(date) == 0) { // Match the date
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No activities found for " << date << ".\n";
        }

        in.close();
    }

    void markCompleted(const string& taskDetails)  {
        cout << "Completion tracking is not required for five-fold activities.\n";
    }
};
class Assignment : public Activity {
public:
    void addActivity() {
    ofstream out("assignment_list.txt", ios::app); // Append to file
    if (!out.is_open()) {
        cout << "\nError: Could not open the assignment file.\n";
        return;
    }

    cout << "\nEnter the assignment due date (dd-mm-yy): ";
    cin.ignore();
    getline(cin, date);

    char more = 'y';
    while (more == 'y' || more == 'Y') {
        string startTime, endTime, assignmentDetails;

        cout << "Enter the start time (e.g., 09:00): ";
        getline(cin, startTime);

        cout << "Enter the end time (e.g., 10:00): ";
        getline(cin, endTime);

        cout << "Enter assignment details: ";
        getline(cin, assignmentDetails);

        // Write to file
        out << date << " | " << startTime << " to " << endTime << " | " << assignmentDetails << " | Not Completed" << endl;

        cout << "Do you want to add another assignment for this date? (y/n): ";
        cin >> more;
        cin.ignore();
    }

    cout << "\nAll assignments added successfully for " << date << "!\n";
    out.close();
}
    void viewActivity(const string& date)  {
        ifstream in("assignment_list.txt");
        if (!in.is_open()) {
            cout << "\nError: Could not open the assignment file.\n";
            return;
        }

        string line;
        bool found = false;

        cout << "\nAssignments for " << date << ":\n";

        while (getline(in, line)) {
            if (line.find(date) == 0) { // Match date
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No assignments found for " << date << ".\n";
        }

        in.close();
    }

    void markCompleted(const string& taskDetails) {
        ifstream in("assignment_list.txt");
        ofstream out("temp.txt");

        if (!in.is_open() || !out.is_open()) {
            cout << "\nError: Could not access the assignment file.\n";
            return;
        }

        string line;
        bool found = false;

        while (getline(in, line)) {
            if (line.find(taskDetails) != string::npos) { // Match task details
                found = true;
                out << line.substr(0, line.find("| Not Completed")) << "| Completed" << endl;
            } else {
                out << line << endl;
            }
        }

        in.close();
        out.close();

        remove("assignment_list.txt");
        rename("temp.txt", "assignment_list.txt");

        if (found) {
            cout << "\nAssignment marked as completed.\n";
        } else {
            cout << "\nAssignment not found.\n";
        }
    }
};
class Hackathon : public Activity {
public:
    void addActivity()  {
    ofstream out("hackathon_list.txt", ios::app); // Append to file
    if (!out.is_open()) {
        cout << "\nError: Could not open the hackathon file.\n";
        return;
    }

    cout << "\nEnter the hackathon due date (dd-mm-yy): ";
    cin.ignore();
    getline(cin, date);

    char more = 'y';
    while (more == 'y' || more == 'Y') {
        string startTime, endTime, hackathonDetails;

        cout << "Enter the start time (e.g., 09:00): ";
        getline(cin, startTime);

        cout << "Enter the end time (e.g., 10:00): ";
        getline(cin, endTime);

        cout << "Enter hackathon details: ";
        getline(cin, hackathonDetails);

        // Write to file
        out << date << " | " << startTime << " to " << endTime << " | " << hackathonDetails << " | Not Completed" << endl;

        cout << "Do you want to add another hackathon for this date? (y/n): ";
        cin >> more;
        cin.ignore();
    }

    cout << "\nAll hackathons added successfully for " << date << "!\n";
    out.close();
}
    void viewActivity(const string& date)  {
        ifstream in("hackathon_list.txt");
        if (!in.is_open()) {
            cout << "\nError: Could not open the hackathon file.\n";
            return;
        }

        string line;
        bool found = false;

        cout << "\nHackathons for " << date << ":\n";

        while (getline(in, line)) {
            if (line.find(date) == 0) { // Match date
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No hackathons found for " << date << ".\n";
        }

        in.close();
    }

    void markCompleted(const string& taskDetails) {
        ifstream in("hackathon_list.txt");
        ofstream out("temp.txt");

        if (!in.is_open() || !out.is_open()) {
            cout << "\nError: Could not access the hackathon file.\n";
            return;
        }

        string line;
        bool found = false;

        while (getline(in, line)) {
            if (line.find(taskDetails) != string::npos) { // Match task details
                found = true;
                out << line.substr(0, line.find("| Not Completed")) << "| Completed" << endl;
            } else {
                out << line << endl;
            }
        }

        in.close();
        out.close();

        remove("hackathon_list.txt");
        rename("temp.txt", "hackathon_list.txt");

        if (found) {
            cout << "\nHackathon task marked as completed.\n";
        } else {
            cout << "\nHackathon task not found.\n";
        }
    }
};
class Game {
protected:
    string name;
public:
    Game(string n) : name(n) {} //Constructor to initialize
    virtual void play() = 0; // Pure virtual function
    string getName() { return name; }
};

// Physical Game class
class PhysicalGame : public Game {
public:
    PhysicalGame(string n) : Game(n) {} //constructor
    void play() override {
        cout << "Playing a physical game: " << name << endl;
    }
};

// PC Game class
class PCGame : public Game {
public:
    PCGame(string n) : Game(n) {} //constructor
    virtual void play() override {
        cout << "Playing a PC game: " << name << endl;
    }
};

// Rock-Paper-Scissors Class
class RockPaperScissors : public PCGame {
public:
    RockPaperScissors() : PCGame("Rock-Paper-Scissors") {} //constructor

    void play() override {
        int userScore = 0, computerScore = 0;//default
        //for round 1 to 3 do
        for (int round = 1; round <= 3; round++) {
            cout << "\n===== Round-" << round << " =====\n";

            char player = getUserChoice(); //for user choice rock,paper,scissor
            cout << "Your Choice: ";
            showChoice(player);

            char computer = getComputerChoice(); //for computer choice rock,paper,scissor(randomly)
            cout << "Computer's Choice: ";
            showChoice(computer);

            int result = chooseWinner(player, computer);
            if (result == 1) userScore++;
            else if (result == -1) computerScore++;

            cout << "Score: You [" << userScore << "] - Computer [" << computerScore << "]\n";
        }

        // Determine final winner
        cout << "\n===== Final Result =====\n";
        if (userScore > computerScore) cout << "?? You win the game!\n";
        else if (userScore < computerScore) cout << "?? Computer wins the game!\n";
        else cout << "?? It's a tie!\n";
    }

private:
    char getUserChoice() {
        char player;
        do {
            cout << "------------------------------\n";
            cout << "| Rock-Paper-Scissors GAME!  |\n";
            cout << "------------------------------\n";
            cout << "| Choose one of the following: |\n";
            cout << "------------------------------\n";
            cout << "'r' for Rock\n";
            cout << "'p' for Paper\n";
            cout << "'s' for Scissors\n";
            cout<<"\nHere:";
            cin >> player;
        } while (player != 'r' && player != 'p' && player != 's');

        return player;
    }

    char getComputerChoice() {
        int num = rand() % 3; //ctime use for using rand() function
        switch (num) {
            case 0: return 'r';
            case 1: return 'p';
            case 2: return 's';
        }
        return 'r';
    }

    void showChoice(char choice) {
        switch (choice) {
            case 'r': cout << "Rock\n"; break;
            case 'p': cout << "Paper\n"; break;
            case 's': cout << "Scissors\n"; break;
        }
    }

    int chooseWinner(char player, char computer) {
        if (player == computer) {
            cout << "It's a tie!\n";
            return 0;
        }
        else if ((player == 'r' && computer == 's') ||
                 (player == 'p' && computer == 'r') ||
                 (player == 's' && computer == 'p')) {
            cout << "You win this round!\n";
            return 1;
        }
        else {
            cout << "You lose this round!\n";
            return -1;
        }
    }
};

// Tic-Tac-Toe Game Class
class TicTacToe : public PCGame {
public:
    TicTacToe() : PCGame("Tic Tac Toe") {}

    void play() override {
        cout << "Starting Tic Tac Toe game...\n";
        startGame();
    }

private:
    int currentplayer;
    char currentmarker;
    char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};  //dynamic array is used here hence we have used vector library

    void drawboard() {
        cout << "----------------------\n";
        cout << "| Tic-Tac-Toe GAME!  |\n";
        cout << "----------------------\n";
        cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
        cout << "---|---|---\n";
        cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
        cout << "---|---|---\n";
        cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n";
    }

    bool placemarker(int slot) {
        int row = (slot - 1) / 3;
        int col = (slot - 1) % 3;
        if (board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = currentmarker;
            return true;
        }
        return false;
    }

    int winner() {
        for (int i = 0; i < 3; i++)
            if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
                return currentplayer;
        for (int i = 0; i < 3; i++)
            if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
                return currentplayer;
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return currentplayer;
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return currentplayer;
        return 0;
    }

    void swap() {
        currentmarker = (currentmarker == 'X') ? 'O' : 'X';
        currentplayer = (currentplayer == 1) ? 2 : 1;
    }

    void startGame() {
        cout << "Player 1 choose your marker [X or O]: ";
        char markerP1;
        cin >> markerP1;

        while (markerP1 != 'X' && markerP1 != 'O') {
            cout << "Invalid choice. Choose X or O: ";
            cin >> markerP1;
        }

        currentplayer = 1;
        currentmarker = markerP1;
        char markerP2 = (markerP1 == 'X') ? 'O' : 'X';

        drawboard();
        int playerwon = 0;
        //for 1 to 9 do due to 9 slots
        for (int i = 0; i < 9; i++) {
            cout << "It's Player " << currentplayer << "'s turn. Enter your slot: ";
            int slot;
            cin >> slot;

            if (slot < 1 || slot > 9) {
                cout << "Invalid slot! Try again.\n";
                i--;
                continue;
            }

            if (!placemarker(slot)) {
                cout << "Slot occupied! Try again.\n";
                i--;
                continue;
            }

            drawboard();
            playerwon = winner();

            if (playerwon) {
                cout << "Player " << playerwon << " wins!\n";
                break;
            }

            swap();
        }

        if (playerwon == 0) cout << "It's a tie!\n";
    }
};

// Hangman Class
class Hangman : public PCGame {
public:
    Hangman() : PCGame("Hangman") {}
    void play() override {
/*dynamic*/vector<string> words = {"apple", "banana", "orange", "grape", "mango", "papaya", "kiwi", "watermelon"};
        string word = words[rand() % words.size()];
        vector<bool> guessed(word.length(), false);
        int attempts = 6;
        char guess;
        cout << "\n--------------------------------------\n";
        cout << "\n|Welcome to Hangman! (Fruits Chapter)|\n";
        cout << "\n--------------------------------------\n";
        while (attempts > 0) {
            displayWord(word, guessed);
            cout << "Attempts left: " << attempts << "\nGuess a letter: ";
            cin >> guess;
            bool correct = false;
            for (size_t i = 0; i < word.length(); i++) {
                if (word[i] == guess) { guessed[i] = true; correct = true; }
            }
            if (!correct) { attempts--; cout << "Wrong guess!\n"; }
            if (isWordGuessed(guessed)) {
                cout << "Congratulations! You guessed the word: " << word << "\n";
                return;
            }
        }
        cout << "Game Over! The word was: " << word << "\n";
    }

private:
    void displayWord(const string& word, const vector<bool>& guessed) {
        for (size_t i = 0; i < word.length(); i++) {
            cout << (guessed[i] ? word[i] : '_') << " ";
        }
        cout << endl;
    }

    bool isWordGuessed(const vector<bool>& guessed) {
        for (bool g : guessed) { if (!g) return false; }
        return true;
    }
};
class Food {
public:
    virtual void displayMeal() = 0;
    virtual bool isHealthy() = 0;
};

class HostelFood : public Food {
private:
    string meals[7] = {
        "\nSunday:\nBreakfast=Paratha, Milk/Tea\nLunch=Dal, Roti, Curd, Loki, Rice\nSnacks=Burger, Tea\nDinner=Gatte ki sabji, Roti",
        "\nMonday:\nBreakfast=Bread,Jam, Butter,Milk/Tea\nLunch=Cabbage Aloo, Roti, Dal, Curd, Rice\nSnacks=Poha Namkeen, Tea\nDinner=Fried Aloo, Roti",
        "\nTuesday:\nBreakfast=Poha, Milk/Tea\nLunch=Dam Aloo, Puri, Kheer,Rice\nSnacks=Murmure\nDinner=Tehri, Gravy Aloo, Roti",
        "\nWednesday:\nBreakfast=Sandwich, Milk/Tea\nLunch=Cauliflower Aloo, Roti, Curd,Rice\nSnacks=Banana, Biscuit, Tea\nDinner=Brinjal Aloo, Roti",
        "\nThursday:\nBreakfast=Paratha Sabji, Milk/Tea\nLunch=Kadhi, Roti, Mirch Tipori, Rice\nSnacks=Murmure, Biscuit\nDinner=Palak Paneer, Roti",
        "\nFriday:\nBreakfast=Chilla, Milk/Tea\nLunch=Cauliflower Aloo, Roti, Curd,Rice\nSnacks=Chole Kulche, Tea\nDinner=Rajma, Soya chunks,Roti, Rice",
        "\nSaturday:\nBreakfast=Poha, Milk/Tea\nLunch=Paneer Aloo, Roti, Curd,Rice\nSnacks=Bhel Puri, Tea\nDinner=Kaddu, Roti"
    };
   
public:
    void displayMeal() override {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int dayOfWeek = ltm->tm_wday;
        cout << "\nToday's hostel meal:\n" << meals[dayOfWeek] << endl;
    }

    bool isHealthy() override {
        return true;
    }
};

class OutsideFood : public Food {
private:
    string foodItem;
    bool healthy;

public:
    OutsideFood(string foodItem, bool healthy) : foodItem(foodItem), healthy(healthy) {}

    void displayMeal() override {
        cout << "\nYou have chosen: " << foodItem << endl;
    }

    bool isHealthy() override {
        return healthy;
    }
};

void compareFood(Food* hostelFood, OutsideFood* outsideFood) {
    cout << "\nComparison:\n";
   
    if (outsideFood->isHealthy()) {
        cout << "\nThe outside food is healthy.\n";
    } else {
        cout << "\nThe outside food might not be as healthy as hostel food.\n";
    }

    if (hostelFood->isHealthy()) {
        cout << "\nHealthy Food Should be eaten!\n";
    }
    else {
        cout << "\nI prefer Hostel food.\n";
    }
}

void foodViewMenu() {
    int choice;
    string foodChoice;
    bool isOutsideFoodHealthy;
   
    while (true) {
        cout << "\nWelcome to Food View!\n";
        cout << "1. Eat from Hostel\n";
        cout << "2. Eat from Outside\n";
        cout << "3. Return to Main Menu\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            HostelFood hostelFood;
            hostelFood.displayMeal();
            cout << "\nHostel food is usually healthy.\n";
        } else if (choice == 2) {
            cout << "\nWhat would you like to eat from outside? ";
            cin.ignore();
            getline(cin, foodChoice);
           
            cout << "\nIs this food healthy? (1 for Yes, 0 for No): ";
            cin >> isOutsideFoodHealthy;
           
            OutsideFood outsideFood(foodChoice, isOutsideFoodHealthy);
            outsideFood.displayMeal();
           
            compareFood(new HostelFood(), &outsideFood);
        } else if (choice == 3) {
            return; // Return to main menu
        } else {
            cout << "Invalid choice! Please select 1, 2, or 3.\n";
        }
    }
}
class Attendance {
private:
    static const int MAX_RECORDS = 100; // Maximum number of attendance records
    static const int MAX_SUBJECTS = 10; // Maximum number of subjects

    string dates[MAX_RECORDS];      // Stores dates (YYYY-MM-DD)
    string days[MAX_RECORDS];       // Stores days (Monday, Tuesday, etc.)
    string subjects[MAX_RECORDS][MAX_SUBJECTS]; // Subjects for each date
    bool attendance[MAX_RECORDS][MAX_SUBJECTS]; // Attendance for each subject (1 = Present, 0 = Absent)
    int subjectCounts[MAX_RECORDS]; // Tracks the number of subjects per date
    int recordCount;                // Tracks the number of records (dates)

    string fileName; // File name for storing attendance data

public:
    // Constructor
    Attendance(string file = "attendance_data.txt") {
        fileName = file;
        recordCount = 0;
        loadFromFile();
    }

    // Add attendance for a specific date
    void addAttendance() {
        if (recordCount >= MAX_RECORDS) {
            cout << "Error: Maximum attendance records reached.\n";
            return;
        }

        string date, day;
        cout << "Enter the date (YYYY-MM-DD): ";
        cin >> date;

        cout << "Enter the day (e.g., Monday, Tuesday): ";
        cin >> ws; // Clear input buffer
        getline(cin, day);

        dates[recordCount] = date;
        days[recordCount] = day;
        subjectCounts[recordCount] = 0;

        char addMoreSubjects = 'y';
        while ((addMoreSubjects == 'y' || addMoreSubjects == 'Y') && subjectCounts[recordCount] < MAX_SUBJECTS) {
            string subject;
            char wasPresent;

            cout << "Enter the subject name: ";
            getline(cin, subject);

            cout << "Were you present in " << subject << "? (P/A): ";
            cin >> wasPresent;
            cin.ignore(); // Clear input buffer

            subjects[recordCount][subjectCounts[recordCount]] = subject;
            attendance[recordCount][subjectCounts[recordCount]] = (wasPresent == 'P' || wasPresent == 'p');
            subjectCounts[recordCount]++;

            cout << "Do you want to add another subject? (Y/N): ";
            cin >> addMoreSubjects;
            cin.ignore(); // Clear input buffer
        }

        recordCount++;
        cout << "Attendance recorded successfully for " << date << " (" << day << ").\n";
        saveToFile();
    }

    // View attendance record for a specific date
    void viewAttendanceRecord() {
        string date, day;
        cout << "Enter the date (YYYY-MM-DD): ";
        cin >> date;

        cout << "Enter the day (e.g., Monday, Tuesday): ";
        cin >> ws; // Clear input buffer
        getline(cin, day);

        int index = findRecord(date, day);
        if (index == -1) {
            cout << "No attendance record found for " << day << ", " << date << ".\n";
            return;
        }

        cout << "\nAttendance record for " << day << ", " << date << ":\n";
        for (int i = 0; i < subjectCounts[index]; i++) {
            cout << "Subject: " << subjects[index][i] << " - " << (attendance[index][i] ? "Present" : "Absent") << "\n";
        }
    }

    // Calculate attendance percentage for all subjects
    void calculateAttendancePercentage() {
        int totalClasses[MAX_SUBJECTS] = {0};
        int attendedClasses[MAX_SUBJECTS] = {0};
        string uniqueSubjects[MAX_SUBJECTS];
        int uniqueSubjectCount = 0;

        for (int i = 0; i < recordCount; i++) {
            for (int j = 0; j < subjectCounts[i]; j++) {
                // Check if the subject already exists in uniqueSubjects
                int subjectIndex = findSubject(uniqueSubjects, uniqueSubjectCount, subjects[i][j]);

                if (subjectIndex == -1) { // New subject
                    uniqueSubjects[uniqueSubjectCount] = subjects[i][j];
                    subjectIndex = uniqueSubjectCount;
                    uniqueSubjectCount++;
                }

                totalClasses[subjectIndex]++;
                if (attendance[i][j]) {
                    attendedClasses[subjectIndex]++;
                }
            }
        }

        // Display attendance percentages and remarks
        cout << "\n--- Attendance Report ---\n";
        for (int i = 0; i < uniqueSubjectCount; i++) {
            float percentage = (float(attendedClasses[i]) / totalClasses[i]) * 100;
            cout << "Subject: " << uniqueSubjects[i] << "\n";
            cout << "Attendance Percentage: " << fixed << setprecision(2) << percentage << "%\n";

            // Provide remarks
            if (percentage >= 90) {
                cout << "Remark: Good! Your attendance is on mark.\n";
            } else if (percentage >= 70) {
                cout << "Remark: Don't worry, but keep it up!\n";
            } else {
                cout << "Remark: You should attend classes regularly.\n";
            }
            cout << "---------------------------\n";
        }
    }

    // Save attendance data to a file
    void saveToFile() {
        ofstream outFile(fileName.c_str());
        if (!outFile.is_open()) {
            cout << "Error: Could not open file for saving.\n";
            return;
        }

        outFile << recordCount << "\n";
        for (int i = 0; i < recordCount; i++) {
            outFile << dates[i] << " " << days[i] << "\n";
            outFile << subjectCounts[i] << "\n";

            for (int j = 0; j < subjectCounts[i]; j++) {
                outFile << subjects[i][j] << " " << attendance[i][j] << "\n";
            }
        }

        outFile.close();
        cout << "Attendance data saved successfully to " << fileName << ".\n";
    }

    // Load attendance data from a file
    void loadFromFile() {
        ifstream inFile(fileName.c_str());
        if (!inFile.is_open()) {
            cout << "No previous attendance data found. Starting fresh.\n";
            return;
        }

        inFile >> recordCount;
        inFile.ignore();

        for (int i = 0; i < recordCount; i++) {
            getline(inFile, dates[i], ' ');
            getline(inFile, days[i]);
            inFile >> subjectCounts[i];
            inFile.ignore();

            for (int j = 0; j < subjectCounts[i]; j++) {
                getline(inFile, subjects[i][j], ' ');
                inFile >> attendance[i][j];
                inFile.ignore();
            }
        }

        inFile.close();
        
    }

private:
    // Find record by date and day
    int findRecord(const string& date, const string& day) {
        for (int i = 0; i < recordCount; i++) {
            if (dates[i] == date && days[i] == day) {
                return i;
            }
        }
        return -1; // Not found
    }

    // Find subject in unique subjects array
    int findSubject(const string uniqueSubjects[], int count, const string& subject) {
        for (int i = 0; i < count; i++) {
            if (uniqueSubjects[i] == subject) {
                return i;
            }
        }
        return -1; // Not found
    }
};
class ExamTimetable {
private:
    string fileName;

public:
    ExamTimetable(string file = "exam_timetable.txt") {
        fileName = file;
    }

    // Function to add an exam timetable
    void addExamSchedule() {
        ofstream outFile(fileName.c_str(), ios::app); // Open file in append mode
        if (!outFile.is_open()) {
            cout << "\nError: Could not open the exam timetable file for writing.\n";
            return;
        }

        string examName;
        cout << "\nEnter Exam Name: ";
        cin.ignore(); // Clear the input buffer
        getline(cin, examName);

        char addMoreSubjects = 'y';
        outFile << "Exam Name: " << examName << "\n";

        while (addMoreSubjects == 'y' || addMoreSubjects == 'Y') {
            string subject, date, timeDuration;

            cout << "Enter Subject Name: ";
            getline(cin, subject);

            cout << "Enter Date (YYYY-MM-DD): ";
            getline(cin, date);

            cout << "Enter Time Duration (e.g., 9:00 AM - 12:00 PM): ";
            getline(cin, timeDuration);

            // Save the entry to the file in the required format
            outFile << date << " | " << subject << " | " << timeDuration << "\n";

            cout << "Do you want to add another subject? (Y/N): ";
            cin >> addMoreSubjects;
            cin.ignore(); // Clear the input buffer
        }

        outFile << "--------------------------------------\n"; // Separator for each exam
        cout << "Exam timetable saved successfully.\n";
        outFile.close();
    }

    // Function to view the exam timetable
    void viewExamSchedule() {
        ifstream inFile(fileName.c_str()); // Open file in read mode
        if (!inFile.is_open()) {
            cout << "\nError: Could not open the exam timetable file for reading.\n";
            return;
        }

        string line;
        cout << "\n--- Exam Timetable ---\n";
        while (getline(inFile, line)) {
            // Display exam name as a heading
            if (line.find("Exam Name:") == 0) {
                cout << "\n" << line << "\n";
                cout << "--------------------------------------\n";
                cout << left << setw(15) << "Date"
                     << setw(30) << "Subject"
                     << setw(20) << "Time Duration" << "\n";
                cout << "--------------------------------------\n";
            } 
            // Display timetable entries
            else if (line.find("----") == string::npos) { 
                // Parse the line manually without using substr
                stringstream ss(line);
                string date, subject, timeDuration;
                getline(ss, date, '|');
                getline(ss, subject, '|');
                getline(ss, timeDuration);

                // Trim leading/trailing spaces (if necessary)
                date = trim(date);
                subject = trim(subject);
                timeDuration = trim(timeDuration);

                cout << left << setw(15) << date
                     << setw(30) << subject
                     << setw(20) << timeDuration << "\n";
            }
        }

        inFile.close();
    }

private:
    // Helper function to trim leading and trailing spaces
    string trim(const string& str) {
        size_t first = str.find_first_not_of(" ");
        size_t last = str.find_last_not_of(" ");
        return str.substr(first, (last - first + 1));
    }
};
int main() {
    cout << "\n\t\t\t\t*----------------*----------------*-------------------*";
    cout << "\n\t\t\t\t*-------------STUDENT DAY PLANNER PROGRAM-------------*";
    cout << "\n\t\t\t\t*----------------HEY USER! PLAN YOUR DAY---------------*";
    cout << "\n\t\t\t\t*----------------*----------------*-------------------*";
      srand(time(0));
    vector<PhysicalGame> physicalGames = {PhysicalGame("Badminton"), PhysicalGame("Football"), PhysicalGame("Cricket"),
        PhysicalGame("Volleyball"), PhysicalGame("Basketball"), PhysicalGame("Pakdam Pakdai"),
        PhysicalGame("Hide & Seek"), PhysicalGame("Hockey"), PhysicalGame("Gully Danda"),
        PhysicalGame("Hand Ball")};
vector<PCGame*> pcGames = {new TicTacToe(), new RockPaperScissors(), new Hangman()};
    int op; // Main menu option
    Student s; // Student object
    ClassSchedule classSchedule; // Class Schedule object
    SelfStudySchedule selfStudySchedule; // Self Study Schedule object
    FiveFoldActivity fiveFoldActivity;
    Assignment assignment;
    Hackathon hackathon;
    int choice;
    string foodChoice;
    bool isOutsideFoodHealthy;
    Attendance attendance;
    do {
        cout << "\n1. ENTER YOUR PERSONAL INFO\n2. TO DO LIST\n3. FOOD VIEW\n4. CLASS ATTENDENCE\n5. PLAY GAMES\nCHOOSE YOUR OPTION: ";
        cin >> op;

        switch (op) {
        case 1: {
            int ch;
            do {
                cout << "\n1. WRITE YOUR INFO\n2. READ YOUR INFO\n3. UPDATE YOUR INFO\n4. BACK TO MAIN MENU";
                cout << "\nENTER YOUR CHOICE: ";
                cin >> ch;
                switch (ch) {
                case 1:
                    s.get();
                    break;
                case 2:
                    s.show();
                    break;
                case 3:
                    s.update();
                    break;
                case 4:
                    cout << "Returning to main menu...\n";
                    break;
                default:
                    cout << "\nInvalid choice. Please try again.\n";
                }
            } while (ch != 4); // Stay in submenu until user selects "4. Back"
            break;
        }

    case 2: {
    int todoOption;
    do {
        cout << "\n1. CREATE TO-DO LIST AND READ TO-DO LIST\n2. BACK TO MAIN MENU";
        cout << "\nENTER YOUR CHOICE: ";
        cin >> todoOption;

        switch (todoOption) {
        case 1: {
            int taskType;
            do {
                cout << "\n1. STUDY SCHEDULE\n2. OTHER ACTIVITIES\n3. BACK";
                cout << "\nENTER YOUR CHOICE: ";
                cin >> taskType;

                switch (taskType) {
                case 1: { // Study Schedule
                    int studyOption;
                    do {
                        cout << "\n1. CLASS STUDY SCHEDULE\n2. SELF-STUDY SCHEDULE\n3.EXAM SCHEDULE\n4.BACK TO PREVIOUS MENU";
                        cout << "\nENTER YOUR CHOICE: ";
                        cin >> studyOption;

                        switch (studyOption) {
                        case 1: {
                            int classOption;
                            do {
                                cout << "\n1. ADD CLASS SCHEDULE\n2. VIEW TODAY'S CLASS SCHEDULE\n3. BACK";
                                cout << "\nENTER YOUR CHOICE: ";
                                cin >> classOption;

                                switch (classOption) {
                                case 1:
                                    classSchedule.addSchedule();
                                    break;
                                case 2:
                                    classSchedule.viewSchedule();
                                    break;
                                case 3:
                                    cout << "Returning to study schedule menu...\n";
                                    break;
                                default:
                                    cout << "Invalid choice! Try again.\n";
                                }
                            } while (classOption != 3); // Back to "Study Schedule" menu
                            break;
                        }

                        case 2: {
                            int selfStudyOption;
                            do {
                                cout << "\n1. ADD SELF-STUDY SCHEDULE\n2. VIEW TODAY'S SELF-STUDY SCHEDULE\n3. BACK";
                                cout << "\nENTER YOUR CHOICE: ";
                                cin >> selfStudyOption;

                                switch (selfStudyOption) {
                                case 1:
                                    selfStudySchedule.addSchedule();
                                    break;
                                case 2:
                                    selfStudySchedule.viewSchedule();
                                    break;
                                case 3:
                                    cout << "Returning to study schedule menu...\n";
                                    break;
                                default:
                                    cout << "Invalid choice! Try again.\n";
                                }
                            } while (selfStudyOption != 3); // Back to "Study Schedule" menu
                            break;
                        }
                       case 3: { // Exam Timetable Menu
    ExamTimetable examTimetable;
    int examOption;
    do {
        cout << "\n--- EXAM TIMETABLE MENU ---";
        cout << "\n1. ADD EXAM TIMETABLE";
        cout << "\n2. VIEW EXAM TIMETABLE";
        cout << "\n3. BACK TO MAIN MENU";
        cout << "\nENTER YOUR CHOICE: ";
        cin >> examOption;

        switch (examOption) {
        case 1:
            examTimetable.addExamSchedule();
            break;
        case 2:
            examTimetable.viewExamSchedule();
            break;
        case 3:
            cout << "Returning to main menu...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (examOption != 3);
    break;
}
                        case 4:
                            cout << "Returning to task type menu...\n";
                            break;

                        default:
                            cout << "Invalid choice! Try again.\n";
                        }
                    } while (studyOption != 4); // Back to "Task Type" menu
                    break;
                }

                case 2: { // Other Activities
                    int mainOption; // Main menu option
                    do {
                        cout << "\n================= MAIN MENU =================";
                        cout << "\n1. MANAGE FIVE-FOLD ACTIVITIES";
                        cout << "\n2. MANAGE ASSIGNMENTS";
                        cout << "\n3. MANAGE HACKATHONS";
                        cout << "\n4. EXIT";
                        cout << "\n============================================";
                        cout << "\nEnter your choice: ";
                        cin >> mainOption;

                        switch (mainOption) {
                        case 1: { // Manage Five-Fold Activities
                            int fiveFoldOption;
                            do {
                                cout << "\n======== FIVE-FOLD ACTIVITIES MENU =========";
                                cout << "\n1. ADD FIVE-FOLD ACTIVITY";
                                cout << "\n2. VIEW FIVE-FOLD ACTIVITIES";
                                cout << "\n3. BACK TO MAIN MENU";
                                cout << "\n============================================";
                                cout << "\nEnter your choice: ";
                                cin >> fiveFoldOption;

                                switch (fiveFoldOption) {
                                case 1:
                                    fiveFoldActivity.addActivity();
                                    break;
                                case 2: {
                                    string date;
                                    cout << "Enter the date to view activities (dd-mm-yy): ";
                                    cin.ignore();
                                    getline(cin, date);
                                    fiveFoldActivity.viewActivity(date);
                                    break;
                                }
                                case 3:
                                    cout << "Returning to Main Menu...\n";
                                    break;
                                default:
                                    cout << "Invalid choice! Please try again.\n";
                                }
                            } while (fiveFoldOption != 3);
                            break;
                        }

                        case 2: { // Manage Assignments
                            int assignmentOption;
                            do {
                                cout << "\n============= ASSIGNMENTS MENU =============";
                                cout << "\n1. ADD ASSIGNMENT";
                                cout << "\n2. VIEW ASSIGNMENTS";
                                cout << "\n3. MARK ASSIGNMENT AS COMPLETED";
                                cout << "\n4. BACK TO MAIN MENU";
                                cout << "\n============================================";
                                cout << "\nEnter your choice: ";
                                cin >> assignmentOption;

                                switch (assignmentOption) {
                                case 1:
                                    assignment.addActivity();
                                    break;
                                case 2: {
                                    string date;
                                    cout << "Enter the date to view assignments (dd-mm-yy): ";
                                    cin.ignore();
                                    getline(cin, date);
                                    assignment.viewActivity(date);
                                    break;
                                }
                                case 3: {
                                    string details;
                                    cout << "Enter the assignment details to mark as completed: ";
                                    cin.ignore();
                                    getline(cin, details);
                                    assignment.markCompleted(details);
                                    break;
                                }
                                case 4:
                                    cout << "Returning to Main Menu...\n";
                                    break;
                                default:
                                    cout << "Invalid choice! Try again.\n";
                                }
                            } while (assignmentOption != 4);
                            break;
                        }

                        case 3: { // Manage Hackathons
                            int hackathonOption;
                            do {
                                cout << "\n=============== HACKATHONS MENU ============";
                                cout << "\n1. ADD HACKATHON";
                                cout << "\n2. VIEW HACKATHONS";
                                cout << "\n3. MARK HACKATHON AS COMPLETED";
                                cout << "\n4. BACK TO MAIN MENU";
                                cout << "\n============================================";
                                cout << "\nEnter your choice: ";
                                cin >> hackathonOption;

                                switch (hackathonOption) {
                                case 1:
                                    hackathon.addActivity();
                                    break;
                                case 2: {
                                    string date;
                                    cout << "Enter the date to view hackathons (dd-mm-yy): ";
                                    cin.ignore();
                                    getline(cin, date);
                                    hackathon.viewActivity(date);
                                    break;
                                }
                                case 3: {
                                    string details;
                                    cout << "Enter the hackathon details to mark as completed: ";
                                    cin.ignore();
                                    getline(cin, details);
                                    hackathon.markCompleted(details);
                                    break;
                                }
                                case 4:
                                    cout << "Returning to Main Menu...\n";
                                    break;
                                default:
                                    cout << "Invalid choice! Try again.\n";
                                }
                            } while (hackathonOption != 4);
                            break;
                        }

                        case 4:
                            cout << "Returning to Main Menu...\n";
                            break;

                        default:
                            cout << "Invalid choice! Please try again.\n";
                        }
                    } while (mainOption != 4);
                    break;
                }

                case 3:
                    cout << "Returning to main menu...\n";
                    break;

                default:
                    cout << "Invalid choice! Try again.\n";
                }
            } while (taskType != 3);
            break;
        }
        case 2: cout << "Returning to main menu...\n";
                    break;
        default:
               cout << "Invalid choice! Try again.\n";    
    }
}while(todoOption!=2);
}
   case 3:{
   	  foodViewMenu();
	break;
   }
   case 4:
   	{
    char continueChoice;
    do {
        int choice;
        cout << "\n========== ATTENDANCE SYSTEM ==========";
        cout << "\n1. Add Attendance";
        cout << "\n2. View Attendance Record";
        cout << "\n3. Calculate Attendance Percentage";
        cout << "\n4. Exit";
        cout << "\n=======================================";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            attendance.addAttendance();
            break;
        case 2:
            attendance.viewAttendanceRecord();
            break;
        case 3:
            attendance.calculateAttendancePercentage();
            break;
        case 4:
            cout << "Exiting... Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
            break;
        }

        cout << "\nDo you want to continue? (Y/N): ";
        cin >> continueChoice;

    } while (continueChoice == 'Y' || continueChoice == 'y');
    break;
}
    case 5:while (true) {
        int choice;
        cout << "\nSelect game type:\n1. Physical Games\n2. PC Games\n3. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 3) {
            cout << "\nGood to have you on board\nLet's meet next time!\n";
            break;
        }
        if (choice == 1) {
            cout << "Available Physical Games:\n";
            for (size_t i = 0; i < physicalGames.size(); ++i)
                cout << i + 1 << ". " << physicalGames[i].getName() << endl;
            cout << "\nThese are some common games you can choose your own also!!\nPhysical games are good for body,\nthey make you Fit & Healthy.\n";
        }
        else if (choice == 2) {
            cout << "\nAvailable PC Games:\n";
            for (size_t i = 0; i < pcGames.size(); ++i)
                cout << i + 1 << ". " << pcGames[i]->getName() << endl;
            int gameChoice;
            cout << "Select a game to play: ";
            cin >> gameChoice;
            if (gameChoice > 0 && gameChoice <= pcGames.size())
                pcGames[gameChoice - 1]->play();
            else
                cout << "Invalid choice!\n";
        }
        for (auto game : pcGames) delete game; // Clean up dynamically allocated memory
    return 0;
    }

    

}
}while(op>=1 && op<=5);
}
