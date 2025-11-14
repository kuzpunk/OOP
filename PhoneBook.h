#pragma once
#include "Contact.h"
#include <vector>
#include <string>

class PhoneBook {

private:
    std::vector<Contact> contacts;
    std::string filename;

public:
    PhoneBook(std::string file);
    void load();
    void save() const;

    void addContact(const Contact& c);
    bool removeByIndex(int index);
    void editContact(int index, const Contact& newContact);

    std::vector<Contact> search(const std::string& query) const;
    void sortByField(const std::string& field);

    void listContacts() const;
    int getCount() const {return contacts.size(); }

};