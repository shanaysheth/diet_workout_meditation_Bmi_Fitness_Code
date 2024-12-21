#include <iostream>        // For input/output operations
#include <fstream>         // For file handling (read/write operations)
#include <unordered_map>   // For storing user data with fast access by username
#include <string>          // For using the `std::string` type
#include <sstream>         // For parsing strings (e.g., height "5'8\"")
#include <vector>          // For dynamic arrays (used in the leaderboard)
#include <iomanip>         // For output formatting (aligning leaderboard columns)
#include <cmath>           // For mathematical calculations (e.g., BMI calculation)
#include <algorithm>       // For sorting the leaderboard

using namespace std;

struct User {
    string password;
    string sex;
    int age;
    string height;
    double currentWeight;
    double targetWeight;
    string medicalConditions;
    int streak = 0;
    string goal; // User's goal (Weight Loss, Toning, Weight Gain)
};

unordered_map<string, User> users; //Stores user data where the username (string) is the key, and the User struct is the value. Advantage, fast lookups using unordered_map.

// Save user data to a file
void saveUserData() {
    ofstream file("users_data.txt"); //Opens the file for writing.
    if (!file) {
        cerr << "Error saving user data!\n"; //console error. Used to display error messages.
        return;
    }
    for (const auto &entry : users) { //Iterates through each key-value pair in the users map.
        const string &username = entry.first; //entry.first: Accesses the key (username) in the map.
        const User &user = entry.second; //entry.second: Accesses the value (User struct) in the map.
        file << username << "\n"
             << user.password << "\n"
             << user.sex << "\n"
             << user.age << "\n"
             << user.height << "\n"
             << user.currentWeight << "\n"
             << user.targetWeight << "\n"
             << user.medicalConditions << "\n"
             << user.streak << "\n"
             << user.goal << "\n";
    }
    file.close();
}

// Load user data from a file
void loadUserData() {
    ifstream file("users_data.txt"); //Opens the file for reading.
    if (!file) {
        cout << "No existing user data found. Starting fresh!\n";
        return;
    }
    string username, password, sex, height, medicalConditions, goal;
    int age, streak;
    double currentWeight, targetWeight;

    while (getline(file, username)) {
        getline(file, password);
        getline(file, sex);
        file >> age;
        file.ignore();
        getline(file, height);
        file >> currentWeight >> targetWeight;
        file.ignore();
        getline(file, medicalConditions);
        file >> streak;
        file.ignore();
        getline(file, goal);
        User user = {password, sex, age, height, currentWeight, targetWeight, medicalConditions, streak, goal};
        users[username] = user;
    }
    file.close();
}

// Function to calculate BMI
double calculateBMI(double weight, const string &height) {
    int feet, inches;
    char quote;
    stringstream ss(height); //enables to treat a string as a stream, enabling formatted extraction (>>) just like you would with cin.
    ss >> feet >> quote >> inches; // Parse height in feet and inches
    double heightInMeters = (feet * 0.3048) + (inches * 0.0254);
    return weight / pow(heightInMeters, 2);
}

// Display content from a file
void displayContentFromFile(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open " << filename << "\n"; // console error, standard error output stream and is typically used to output error messages
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << "\n";
    }
    file.close();
}

// Workout Menu
void workoutMenu(const string &goal) {
    int intensity;
    cout << "Choose Workout Intensity:\n1. High\n2. Moderate\n3. Low\n";
    cin >> intensity;

    string intensityStr;
    if (intensity == 1) intensityStr = "high";
    else if (intensity == 2) intensityStr = "moderate";
    else intensityStr = "low";

    string filename = "workouts_" + intensityStr + "_" + goal + ".txt";
    displayContentFromFile(filename);
}

// Diet Menu
void dietMenu(const string &goal) {
    int calorieType;
    cout << "Choose Calorie Type:\n1. High Calorie\n2. Balanced\n3. Low Calorie\n";
    cin >> calorieType;

    string calorieStr;
    if (calorieType == 1) calorieStr = "high_calorie";
    else if (calorieType == 2) calorieStr = "balanced";
    else calorieStr = "low_calorie";

    string filename = "diets_" + calorieStr + "_" + goal + ".txt";
    displayContentFromFile(filename);
}

// Meditation Menu
void meditationMenu() {
    cout << "Meditation Types and Benefits:\n";
    cout << "1. Mindfulness Meditation: Managing anxiety, beginners.\n";
    cout << "2. Transcendental Meditation (TM): Structured practice, deep relaxation.\n";
    cout << "3. Loving-Kindness Meditation: Building empathy and positivity.\n";
    cout << "4. Body Scan Meditation: Managing tension, relaxation.\n";
    cout << "5. Breath Awareness Meditation: Reducing anxiety, improving focus.\n";

    int choice;
    cout << "Choose a meditation type (1-5): ";
    cin >> choice;

    string filename;
    switch (choice) {
        case 1: filename = "mindfulness_meditation.txt"; break;
        case 2: filename = "transcendental_meditation.txt"; break;
        case 3: filename = "loving_kindness_meditation.txt"; break;
        case 4: filename = "body_scan_meditation.txt"; break;
        case 5: filename = "breath_awareness_meditation.txt"; break;
        default: cout << "Invalid choice.\n"; return;
    }
    displayContentFromFile(filename);
}

// Check-ins
void checkIn(const string &username) {
    char workoutDone, dietDone;

    cout << "Did you complete your workout today? (Y/N): ";
    cin >> workoutDone;
    cout << "Did you complete your diet plan today? (Y/N): ";
    cin >> dietDone;

    if (toupper(workoutDone) == 'Y' && toupper(dietDone) == 'Y') {
        users[username].streak++;
        cout << "Great job! Your current streak is now: " << users[username].streak << "\n";
    } else {
        users[username].streak = 0;
        cout << "Oops! Streak broken. Your streak is reset to 0.\n";
    }

    saveUserData(); // Save updated streaks
}

// View/Edit Reports
void reportsMenu(const string &username) {
    User &user = users[username];
    cout << "\n--- User Report ---\n";
    cout << "Username: " << username << "\n";
    cout << "Sex: " << user.sex << "\n";
    cout << "Age: " << user.age << "\n";
    cout << "Height: " << user.height << "\n";
    cout << "Current Weight: " << user.currentWeight << " kg\n";
    cout << "Target Weight: " << user.targetWeight << " kg\n";
    cout << "Medical Conditions: " << user.medicalConditions << "\n";
    cout << "Current Goal: " << user.goal << "\n";

    cout << "\nDo you want to update any information? (Y/N): ";
    char updateChoice;
    cin >> updateChoice;

    if (toupper(updateChoice) == 'Y') {
        cout << "\n--- Update Options ---\n";
        cout << "1. Update Age\n2. Update Height\n3. Update Current Weight\n4. Update Target Weight\n5. Update Medical Conditions\n6. Update Goal\n";
        int updateOption;
        cin >> updateOption;

        switch (updateOption) {
            case 1:
                cout << "Enter new age: ";
                cin >> user.age;
                break;
            case 2:
                cout << "Enter new height (e.g., 5'8\"): ";
                cin.ignore();
                getline(cin, user.height);
                break;
            case 3:
                cout << "Enter new current weight (kg): ";
                cin >> user.currentWeight;
                break;
            case 4:
                cout << "Enter new target weight (kg): ";
                cin >> user.targetWeight;
                break;
            case 5:
                cout << "Enter new medical conditions (or type 'None'): ";
                cin.ignore();
                getline(cin, user.medicalConditions);
                break;
            case 6:
                cout << "Choose new goal:\n1. Weight Loss\n2. Toning\n3. Weight Gain\n";
                int goalChoice;
                cin >> goalChoice;
                if (goalChoice == 1) user.goal = "weight_loss";
                else if (goalChoice == 2) user.goal = "toning";
                else user.goal = "weight_gain";
                break;
            default:
                cout << "Invalid choice.\n";
                return;
        }
        saveUserData();
        cout << "Information updated successfully!\n";
    }
}

// Leaderboard
void displayLeaderboard() {
    vector<pair<string, int>> leaderboard;
    // Collect all users and their streaks into a vector
    for (const auto &entry : users) { //Iterates through the users map, where each entry is a key-value pair
        leaderboard.emplace_back(entry.first, entry.second.streak);  //entry.first: The username (key). entry.second: The User struct (value).
    }//.emplace_back is a member function of std::vector that constructs an element directly at the end of the vector without creating a temporary object.

    // Sort in descending order based on streak
    sort(leaderboard.begin(), leaderboard.end(),
         [](const pair<string, int> &a, const pair<string, int> &b) {
             return a.second > b.second; // Ensure descending order
         });

    // Display the leaderboard
    cout << "\n--- Leaderboard ---\n";
    cout << setw(15) << left << "Username" << "Streak\n";
    cout << "----------------------------\n";
    for (const auto &entry : leaderboard) {
        cout << setw(15) << left << entry.first << entry.second << "\n";
    }
}

// Post-login Menu
void postLoginMenu(const string &username) {
    int choice;
    double bmi = calculateBMI(users[username].currentWeight, users[username].height);
    cout << "\nYour BMI is: " << bmi << "\n";

    do {
        cout << "\n--- Choose an Option ---\n";
        cout << "1. Workout\n";
        cout << "2. Diet\n";
        cout << "3. Meditation\n";
        cout << "4. Check-ins\n";
        cout << "5. Leaderboard\n";
        cout << "6. Reports\n";
        cout << "7. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                workoutMenu(users[username].goal);
                break;
            case 2:
                dietMenu(users[username].goal);
                break;
            case 3:
                meditationMenu();
                break;
            case 4:
                checkIn(username);
                break;
            case 5:
                displayLeaderboard();
                break;
            case 6:
                reportsMenu(username);
                break;
            case 7:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);
}

// Register User
void registerUser() {
    string username;
    User user;

    cout << "Enter a username: ";
    cin >> username;
    if (users.find(username) != users.end()) {
        cout << "Username already exists! Try again.\n";
        return;
    }

    cout << "Enter a password: ";
    cin >> user.password;
    cout << "Enter biological sex (M/F): ";
    cin >> user.sex;
    cout << "Enter age: ";
    cin >> user.age;
    cout << "Enter height (e.g., 5'8\"): ";
    cin.ignore();
    getline(cin, user.height);
    cout << "Enter current weight (kg): ";
    cin >> user.currentWeight;
    cout << "Enter target weight (kg): ";
    cin >> user.targetWeight;
    cout << "Enter any medical conditions (or type 'None'): ";
    cin.ignore();
    getline(cin, user.medicalConditions);

    cout << "Choose your goal:\n1. Weight Loss\n2. Toning\n3. Weight Gain\n";
    int goalChoice;
    cin >> goalChoice;
    if (goalChoice == 1) user.goal = "weight_loss";
    else if (goalChoice == 2) user.goal = "toning";
    else user.goal = "weight_gain";

    users[username] = user;
    saveUserData();
    cout << "Registration successful!\n";
}

// Login User
bool loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (users.find(username) != users.end() && users[username].password == password) {
        cout << "Login successful!\n";
        postLoginMenu(username);
        return true;
    } else {
        cout << "Invalid credentials. Try again.\n";
        return false;
    }
}

// Main Menu
int main() {
    loadUserData();
    int choice;

    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}