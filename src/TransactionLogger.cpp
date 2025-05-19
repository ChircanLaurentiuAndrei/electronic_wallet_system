#include "TransactionLogger.h"

void TransactionLogger::log(const std::string& cardNumber, const std::string& type, double amount) {
    std::ofstream file("transactions.txt", std::ios::app);
    time_t now;
    time(&now);
    char* dt = ctime(&now);
    file << dt << " :" << "Card Number: " << cardNumber <<", Transaction: " << type << ", Amount: " << amount <<".\n";
}

void TransactionLogger::viewLogs() {
    std::ifstream in("transactions.txt");
    std::string line;
    while (std::getline(in, line)) {
        std::cout << line << "\n";
    }
}