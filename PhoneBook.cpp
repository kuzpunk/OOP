#include "PhoneBook.h"
#include <fstream>
#include <iostream>
#include <algorithm>

PhoneBook::PhoneBook(std::string file) : filename(std::move(file)) {}

void PhoneBook::load() {
    contacts.clear();
    std::ifstream fin(filename);
    if (!fin.is_open()) return;

    std::string line;
    while (std::getline(fin, line)){
        if (!line.empty())
            contacts.push_back(Contact::fromFileString(line));
    }
    fin.close();
}

void PhoneBook::save() const {
    std::ofstream fout(filename);
    for (const auto& c : contacts)
        fout << c.toFileString() << "\n";
    fout.close();
}

void PhoneBook::addContact(const Contact& c){
    contacts.push_back(c);
}

bool PhoneBook::removeByIndex(int index){
    if (index < 0 || index >= (int)contacts.size()) return false;
    contacts.erase(contacts.begin() + index);
    return true;
}

void PhoneBook::editContact(int index, const Contact& newContact){
    if (index >= 0 && index < (int)contacts.size())
        contacts[index] = newContact;
}

std::vector<Contact> PhoneBook::search(const std::string& query) const {
    std::vector<Contact> result;

    for (const auto& c : contacts) {

        if (c.getFirstName().find(query) != std::string::npos ||
            c.getLastName().find(query) != std::string::npos ||
            c.getMiddleName().find(query) != std::string::npos ||
            c.getAddress().find(query) != std::string::npos ||
            c.getBirthDate().find(query) != std::string::npos ||
            c.getEmail().find(query) != std::string::npos ||
            c.getPhoneWork().find(query) != std::string::npos ||
            c.getPhoneHome().find(query) != std::string::npos ||
            c.getPhoneMobile().find(query) != std::string::npos)
        {
            result.push_back(c);
        }
    }

    return result;
}


void PhoneBook::sortByField(const std::string& field) {
    if (field == "firstName")
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b){ return a.getFirstName() < b.getFirstName(); });

    else if (field == "lastName")
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b){ return a.getLastName() < b.getLastName(); });

    else if (field == "middleName")
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b){ return a.getMiddleName() < b.getMiddleName(); });

    else if (field == "address")
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b){ return a.getAddress() < b.getAddress(); });

    else if (field == "birthDate")
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b){ return a.getBirthDate() < b.getBirthDate(); });

    else if (field == "email")
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b){ return a.getEmail() < b.getEmail(); });

    else if (field == "phoneWork")
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b){ return a.getPhoneWork() < b.getPhoneWork(); });

    else if (field == "phoneHome")
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b){ return a.getPhoneHome() < b.getPhoneHome(); });

    else if (field == "phoneMobile")
        std::sort(contacts.begin(), contacts.end(),
            [](const Contact& a, const Contact& b){ return a.getPhoneMobile() < b.getPhoneMobile(); });

    else {
        std::cout << "Unknown field: '" << field 
                  << "'. Available fields: firstName, lastName, middleName, address, birthDate, email, phoneWork, phoneHome, phoneMobile\n";
    }
}


void PhoneBook::listContacts() const {
    if (contacts.empty()) {
        std::cout << "Contact list is empty.\n";
        return;
    }

    for (size_t i = 0; i < contacts.size(); ++i) {
        std::cout << i + 1 << ". ";
        contacts[i].print();
    }
}
