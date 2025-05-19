#include "Wallet.h"
#include "TransactionLogger.h"
#include <iostream>
#include <cstring>

void print_help() {
    std::cout << "Usage: remote_wallet <command> [args...]\n"
              << "Commands:\n"
              << "  spend <number> <amount>                                     Deduct money from a card\n"
              << "  transfer <from_number> <to_number> <amount>                 Transfer money between cards\n"
              << "  view_card <number>                                          View a card (increments view count)\n"
              << "  list                                                        List all cards\n"
              << "  --help                                                      Show this help message\n";
}

int main(int argc, char* argv[]) {
    Wallet wallet;
    wallet.loadFromFile("..\\cards.csv");

    if (argc < 2) {
        std::cerr << "Unknown command. Use --help to see available commands.\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "spend") {
        if (argc != 4) {
            std::cerr << "Usage: spend <number> <amount>\n";
            return 1;
        }
        std::string number = argv[2];
        double amount = std::stod(argv[3]);
        if (Card* c = wallet.findCard(number)) {
            if (c->removeMoney(amount)) {
                TransactionLogger::log(number, "USE", amount);
                wallet.saveToFile("..\\cards.csv");
            } else {
                std::cerr << "Insufficient balance.\n";
            }
        } else {
            std::cerr << "Card not found.\n";
        }

    } else if (command == "transfer") {
        if (argc != 5) {
            std::cerr << "Usage: transfer <from> <to> <amount>\n";
            return 1;
        }
        std::string from = argv[2];
        std::string to = argv[3];
        double amount = std::stod(argv[4]);
        if (Card* c1 = wallet.findCard(from)) {
            if (Card* c2 = wallet.findCard(to)) {
                if (c1->getBalance() >= amount) {
                    c1->transferTo(*c2, amount);
                    TransactionLogger::log(from, "TRANSFER_OUT", amount);
                    TransactionLogger::log(to, "TRANSFER_IN", amount);
                    wallet.saveToFile("..\\cards.csv");
                } else {
                    std::cerr << "Insufficient balance in source card.\n";
                }
            } else {
                std::cerr << "Target card not found.\n";
            }
        } else {
            std::cerr << "Source card not found.\n";
        }

    } else if (command == "view_card") {
        if (argc != 3) {
            std::cerr << "Usage: view_card <number>\n";
            return 1;
        }
        wallet.viewCard(argv[2]);
        wallet.saveToFile("..\\cards.csv");

    } else if (command == "list") {
        wallet.listCards();

    } else if (command == "--help") {
        print_help();

    } else {
        std::cerr << "Unknown command. Use --help to see available commands.\n";
        return 1;
    }

    return 0;
}
