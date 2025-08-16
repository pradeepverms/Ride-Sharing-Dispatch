#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <map>

struct Transaction {
    std::string type;      // "income" or "expense"
    float amount;
    std::string category;
    std::string date;      // Format: YYYY-MM
};

std::vector<Transaction> transactions;

void showMenu() {
    std::cout << "\n--- Personal Finance Tracker ---\n";
    std::cout << "1. Add Transaction\n";
    std::cout << "2. View Transactions\n";
    std::cout << "3. Filter: Expenses > 100\n";
    std::cout << "4. Save to File\n";
    std::cout << "5. Load from File\n";
    std::cout << "6. Show Monthly ASCII Bar Chart\n";
    std::cout << "7. Exit\n";
}

void addTransaction(std::vector<Transaction>& transactions) {
    Transaction t;
    std::cout << "Enter type (income/expense): ";
    std::cin >> t.type;
    std::cout << "Enter amount: ";
    std::cin >> t.amount;
    std::cin.ignore();
    std::cout << "Enter category: ";
    getline(std::cin, t.category);
    std::cout << "Enter date (YYYY-MM): ";
    getline(std::cin, t.date);
    transactions.push_back(t);
    std::cout << "Transaction added successfully!\n";
}

void viewTransactions(const std::vector<Transaction>& transactions) {
    if (transactions.empty()) {
        std::cout << "No transactions to display.\n";
        return;
    }
    std::cout << "\n--- Transactions ---\n";
    std::cout << std::left << std::setw(10) << "Type"
              << std::setw(10) << "Amount"
              << std::setw(15) << "Category"
              << std::setw(10) << "Date" << "\n";
    std::cout << "------------------------------------------\n";

    // Sort by amount descending before displaying
    std::vector<Transaction> sorted = transactions;
    std::sort(sorted.begin(), sorted.end(), [](const Transaction& a, const Transaction& b) {
        return a.amount > b.amount;
    });

    for (auto& t : sorted) {
        std::cout << std::setw(10) << t.type
                  << std::setw(10) << t.amount
                  << std::setw(15) << t.category
                  << std::setw(10) << t.date << "\n";
    }
}

void filterExpenses(const std::vector<Transaction>& transactions) {
    bool found = false;
    std::cout << "\nExpenses > 100:\n";
    for (const auto& t : transactions) {
        if (t.type == "expense" && t.amount > 100) {
            std::cout << std::left << std::setw(15) << t.category
                      << t.amount << " on " << t.date << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "No expenses greater than 100 found.\n";
}

void saveToFile(const std::vector<Transaction>& transactions, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error opening file for saving.\n";
        return;
    }
    for (const auto& t : transactions) {
        out << t.type << ','
            << t.amount << ','
            << t.category << ','
            << t.date << '\n';
    }
    out.close();
    std::cout << "Data saved to " << filename << "\n";
}

void loadFromFile(std::vector<Transaction>& transactions, const std::string& filename) {
    transactions.clear();
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Error opening file for loading.\n";
        return;
    }
    std::string line;
    while (getline(in, line)) {
        Transaction t;
        size_t pos = 0;

        pos = line.find(',');
        if (pos == std::string::npos) continue;
        t.type = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        if (pos == std::string::npos) continue;
        try {
            t.amount = std::stof(line.substr(0, pos));
        } catch (...) {
            continue;
        }
        line.erase(0, pos + 1);

        pos = line.find(',');
        if (pos == std::string::npos) continue;
        t.category = line.substr(0, pos);
        line.erase(0, pos + 1);

        t.date = line;
        transactions.push_back(t);
    }
    in.close();
    std::cout << "Data loaded from " << filename << "\n";
}

void showMonthlyBarChart(const std::vector<Transaction>& transactions) {
    if (transactions.empty()) {
        std::cout << "No data available.\n";
        return;
    }

    std::map<std::string, float> monthTotals;
    for (const auto& t : transactions) {
        if (t.type == "expense")
            monthTotals[t.date] += t.amount;
    }

    std::cout << "\nMonthly Spending Bar Chart:\n";
    for (const auto& pair : monthTotals) {
        std::cout << pair.first << " | ";
        int stars = static_cast<int>(pair.second / 10);
        for (int i = 0; i < stars; ++i)
            std::cout << '*';
        std::cout << " (" << pair.second << ")\n";
    }
}

int main() {
    int choice;
    std::string filename = "data.txt";
    do {
        showMenu();
        std::cout << "Choose: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                addTransaction(transactions);
                break;
            case 2:
                viewTransactions(transactions);
                break;
            case 3:
                filterExpenses(transactions);
                break;
            case 4:
                saveToFile(transactions, filename);
                break;
            case 5:
                loadFromFile(transactions, filename);
                break;
            case 6:
                showMonthlyBarChart(transactions);
                break;
            case 7:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid option! Please choose 1-7.\n";
        }
    } while (choice != 7);
    return 0;
}