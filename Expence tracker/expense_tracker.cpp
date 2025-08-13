#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip> // for fixed and setprecision
using namespace std;

struct Expense {
    char category[50];
    float amount;
    char date[11]; // Format: DD-MM-YYYY
};

Expense expenses[100]; // max 100 expenses
int expenseCount = 0;

// Load expenses from file
void loadExpenses() {
    ifstream file("expenses.txt");
    if (!file) return;

    while (file >> expenses[expenseCount].category
                >> expenses[expenseCount].amount
                >> expenses[expenseCount].date) {
        expenseCount++;
    }
    file.close();
}

// Add expense
void addExpense() {
    if (expenseCount >= 100) {
        cout << "Expense limit reached!" << endl;
        return;
    }

    Expense e;
    cout << "Enter category: ";
    cin.ignore();
    cin.getline(e.category, 50);
    cout << "Enter amount: ";
    cin >> e.amount;
    cout << "Enter date (DD-MM-YYYY): ";
    cin >> e.date;

    expenses[expenseCount++] = e;

    ofstream file("expenses.txt", ios::app);
    file << e.category << " " << e.amount << " " << e.date << endl;
    file.close();

    cout << "Expense added successfully!" << endl;
}

// View report by full date
void viewDateReport() {
    char searchDate[11]; // DD-MM-YYYY
    cout << "Enter date (DD-MM-YYYY): ";
    cin >> searchDate;

    float total = 0;
    bool found = false;

    cout << "\n--- Expenses for " << searchDate << " ---\n";
    for (int i = 0; i < expenseCount; i++) {
        if (strcmp(expenses[i].date, searchDate) == 0) {
            cout << expenses[i].date << " | "
                 << expenses[i].category << " | Rs. "
                 << fixed << setprecision(2) << expenses[i].amount << endl;
            total += expenses[i].amount;
            found = true;
        }
    }

    if (!found) {
        cout << "No expenses found for " << searchDate << endl;
    } else {
        cout << "---------------------------\n";
        cout << "Total: Rs. " << fixed << setprecision(2) << total << endl;
    }
}

int main() {
    loadExpenses();

    cout << "=====================================\n";
    cout << "   PERSONAL EXPENSE TRACKER (C++)\n";
    cout << "=====================================\n";

    int choice;
    do {
        cout << "\n1. Add Expense\n";
        cout << "2. View Report by Date\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addExpense(); break;
            case 2: viewDateReport(); break;
            case 3: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}


