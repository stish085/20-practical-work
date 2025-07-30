// 20 задание 4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

  const std::string FILE_NAME = "C:\\practice\\atmState.bin";
const std::string LOG_FILE = "C:\\practice\\atmLog.txt";
const int MAX_BANKNOTES = 1000;
const int DENOM_COUNT = 6;
const int DENOMINATIONS[DENOM_COUNT] = { 5000, 2000, 1000, 500, 200, 100 };

std::vector<int> banknotes;

void logOperation(const std::string& message) {
    std::ofstream log(LOG_FILE, std::ios::app);
    if (log.is_open()) {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        log << "[" << 1900 + localTime->tm_year << "-"
            << 1 + localTime->tm_mon << "-"
            << localTime->tm_mday << " "
            << localTime->tm_hour << ":"
            << localTime->tm_min << ":"
            << localTime->tm_sec << "] "
            << message << "\n";
        log.close();
    }
}

void loadATM() {
    std::ifstream file(FILE_NAME, std::ios::binary);
    if (file.is_open()) {
        banknotes.clear();
        int value;
        while (file.read(reinterpret_cast<char*>(&value), sizeof(int))) {
            banknotes.push_back(value);
        }
        file.close();
        std::cout << "ATM data loaded from file.\n";
        logOperation("ATM state loaded from file.");
    }
    else {
        std::cout << "File not found. ATM is empty.\n";
        logOperation("File not found. ATM is empty.");
    }
}

void saveATM() {
    std::ofstream file(FILE_NAME, std::ios::binary | std::ios::trunc);
    for (int i = 0; i < banknotes.size(); ++i) {
        file.write(reinterpret_cast<char*>(&banknotes[i]), sizeof(int));
    }
    file.close();
    logOperation("ATM state saved.");
}

void printStatus() {
    int counts[DENOM_COUNT] = { 0 };
    int total = 0;
    for (int i = 0; i < banknotes.size(); ++i) {
        for (int j = 0; j < DENOM_COUNT; ++j) {
            if (banknotes[i] == DENOMINATIONS[j]) {
                counts[j]++;
                total += banknotes[i];
                break;
            }
        }
    }

    std::cout << "\nCurrent ATM status:\n";
    for (int i = 0; i < DENOM_COUNT; ++i) {
        std::cout << "Banknotes of " << DENOMINATIONS[i] << ": " << counts[i] << "\n";
    }
    std::cout << "Total amount: " << total << " RUB\n";
    std::cout << "Total number of banknotes: " << banknotes.size() << "\n\n";
}

void fillATM() {
    int before = banknotes.size();
    while (banknotes.size() < MAX_BANKNOTES) {
        int idx = rand() % DENOM_COUNT;
        banknotes.push_back(DENOMINATIONS[idx]);
    }
    int added = banknotes.size() - before;
    std::cout << "ATM filled with " << added << " banknotes.\n";
    logOperation("ATM filled with " + std::to_string(added) + " banknotes.");
    printStatus();
}

void withdrawMoney(int amount) {
    if (amount % 100 != 0 || amount <= 0) {
        std::cout << "Amount must be positive and a multiple of 100.\n";
        logOperation("Error: Invalid withdrawal amount: " + std::to_string(amount));
        return;
    }

    int available[DENOM_COUNT] = { 0 };
    for (int i = 0; i < banknotes.size(); ++i) {
        for (int j = 0; j < DENOM_COUNT; ++j) {
            if (banknotes[i] == DENOMINATIONS[j]) {
                available[j]++;
                break;
            }
        }
    }

    int toWithdraw[DENOM_COUNT] = { 0 };
    int remaining = amount;

    for (int i = 0; i < DENOM_COUNT; ++i) {
        int take = std::min(remaining / DENOMINATIONS[i], available[i]);
        toWithdraw[i] = take;
        remaining -= take * DENOMINATIONS[i];
    }

    if (remaining > 0) {
        std::cout << "Operation failed: not enough suitable banknotes.\n";
        logOperation("Error: Cannot withdraw " + std::to_string(amount) + " RUB (insufficient banknotes).");
        return;
    }

    
    for (int i = 0; i < DENOM_COUNT; ++i) {
        int count = toWithdraw[i];
        for (int j = 0; j < banknotes.size() && count > 0; ) {
            if (banknotes[j] == DENOMINATIONS[i]) {
                banknotes.erase(banknotes.begin() + j);
                count--;
            }
            else {
                ++j;
            }
        }
    }

    std::cout << "Withdrawn " << amount << " RUB:\n";
    for (int i = 0; i < DENOM_COUNT; ++i) {
        if (toWithdraw[i] > 0) {
            std::cout << DENOMINATIONS[i] << " x " << toWithdraw[i] << "\n";
        }
    }

    logOperation("Withdrawal: " + std::to_string(amount) + " RUB.");
    printStatus();
}

int main() {
     std::srand(static_cast<unsigned int>(std::time(nullptr)));

    loadATM();
    printStatus();

    char command;
    while (true) {
        std::cout << "Enter command (+ — fill, - — withdraw, q — quit): ";
        std::cin >> command;

        if (command == '+') {
            fillATM();
        }
        else if (command == '-') {
            int amount;
            std::cout << "Enter withdrawal amount (multiple of 100): ";
            std::cin >> amount;
            withdrawMoney(amount);
        }
        else if (command == 'q') {
            saveATM();
            logOperation("ATM session ended.");
            std::cout << "ATM state saved. Exiting...\n";
            break;
        }
        else {
            std::cout << "Unknown command.\n";
            logOperation("Error: Unknown command '" + std::string(1, command) + "'");
        }
    }

    return 0;
   

    

}
