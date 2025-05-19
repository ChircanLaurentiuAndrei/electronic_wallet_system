#include "Wallet.h"

void Wallet::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if(!file) {
        std::ofstream out(filename);
        std::cout<<"Error: Could not open file: " << filename << ".\n";
        return;
    }
    
    std::string line;
    std::getline(file, line);
    while(std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cardName, cardNumber, name, expirationDate, moneyAmount_str, viewCount_str;
        std::getline(ss, cardName, ',');
        std::getline(ss, cardNumber, ',');
        std::getline(ss, name, ',');
        std::getline(ss, expirationDate, ',');
        std::getline(ss, moneyAmount_str, ',');
        std::getline(ss, viewCount_str, ',');
        if(!cardName.empty() && !cardNumber.empty() && !name.empty() && !expirationDate.empty() && !moneyAmount_str.empty() && !viewCount_str.empty()) {
            double moneyAmount = std::stod(moneyAmount_str);
            int viewCount = std::stoi(viewCount_str);
            Card newCard(cardName, cardNumber, name, expirationDate, moneyAmount, viewCount);
            cards.push_back(newCard);
        }
    }
    file.close();
}

void Wallet::saveToFile(const std::string& filename) const{
    std::ofstream file(filename);
    if(!file) {
        std::cout<<"Error: Could not open file: " << filename << ".\n";
        return;
    }
    file << "cardName,cardNumber,name,expirationDate,moneyAmount,viewCount\n";
    for(const auto& card : cards) {
        file << card.getCard() << ","
             << card.getNumber() << ","
             << card.getName() << ","
             << card.getDate() << ","
             << card.getBalance() << ","
             << card.getView() << "\n";
    }
    file.close();
}

void Wallet::addCard(const Card& newCard) {
    for (const auto& card : cards) {
        if (card.getNumber() == newCard.getNumber()) {
            std::cerr << "Error: Card with number " << newCard.getNumber() << " already exists.\n";
            return;
        }
    }
    cards.push_back(newCard);
}

void Wallet::removeCard(const std::string& number) {
    cards.erase(std::remove_if(cards.begin(), cards.end(), [&number](const Card& c) {
        return c.getNumber() == number;
    }), cards.end());
}

Card* Wallet::findCard(const std::string& number) {
    for (auto& card : cards) {
        if (card.getNumber() == number) {
            return &card;
        }
    }
    return nullptr;
}


void Wallet::listCards() const {
    for(const auto& card : cards) {
        card.displayCard();
    }
}

void Wallet::viewCard(const std::string& number) {
    for(auto& card : cards) {
        if(card.getNumber() == number) {
            card.incrementViewCount();
            card.displayCard();
        }
        std::sort(cards.begin(), cards.end(), [](const Card& a, const Card& b) {
                return a.getView() > b.getView();
        });
        return;
    }
    std::cout << "Error: Card not found!\n";
}