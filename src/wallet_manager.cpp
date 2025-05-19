#include "Wallet.h"
#include "TransactionLogger.h"
#include <iostream>
#include <cstring>


void print_help() {
    std::cout << "Usage: wallet_manager <command> [args...]\n"
              << "Commands:\n"
              << "  add_card <card_name> <number> <owner_name> <exp_date>      Add a new card\n"
              << "  view_card <number>                                         View a card (increments view count)\n"
              << "  list_cards                                                 List all cards\n"
              << "  load_money <number> <amount>                               Load money to a card\n"
              << "  save                                                       Save wallet to file\n"
              << "  --help                                                     Show this help message\n";
}

int main(int argc, char* argv[]) {
    Wallet wallet;
    wallet.loadFromFile("..\\cards.csv");

    if (argc < 2) {
        std::cerr << "Unknown command. Use --help to see available commands.\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "add_card") {
        if (argc < 5) {
            std::cerr << "Usage: add_card <card_name> <number> <owner_name> <exp_date> \n";
            return 1;
        }
        std::string cardName = argv[2];
        std::string number = argv[3];
        std::string owner = argv[4];
        std::string exp = argv[5];

        Card newCard(cardName, number, owner, exp);
        wallet.addCard(newCard);
        wallet.saveToFile("..\\cards.csv");

    } else if (command == "view_card") {
        if (argc != 3) {
            std::cerr << "Usage: view_card <number>\n";
            return 1;
        }
        wallet.viewCard(argv[2]);
        wallet.saveToFile("..\\cards.csv");

    } else if (command == "list_cards") {
        wallet.listCards();

    } else if (command == "load_money") {
        if (argc != 4) {
            std::cerr << "Usage: load_money <number> <amount>\n";
            return 1;
        }
        std::string number = argv[2];
        double amount = std::stod(argv[3]);
        if (Card* c = wallet.findCard(number)) {
            c->addMoney(amount);
            TransactionLogger::log(number, "LOAD", amount);
            wallet.saveToFile("..\\cards.csv");
        } else {
            std::cerr << "Card not found.\n";
        }

    } else if (command == "save") {
        wallet.saveToFile("..\\cards.csv");

    } else if (command == "--help") {
        print_help();

    } else {
        std::cerr << "Unknown command. Use --help to see available commands.\n";
        return 1;
    }

    return 0;
}