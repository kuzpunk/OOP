#pragma once
#include <string>
#include <iostream>

class Contact {
private:
    std::string firstName;
    std::string lastName;
    std::string middleName;
    std::string address;
    std::string birthDate;
    std::string email;
    std::string phoneWork;
    std::string phoneHome;
    std::string phoneMobile;
public:
    Contact() = default;
    Contact(std::string fn, std::string ln, std::string mn,
            std::string addr, std::string birth, std::string mail,
            std::string work, std::string home, std::string mobile);

    void print() const;
    std::string toFileString() const;
    static Contact fromFileString(const std::string& line);

        std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getMiddleName() const { return middleName; }
    std::string getAddress() const { return address; }
    std::string getBirthDate() const { return birthDate; }
    std::string getEmail() const { return email; }
    std::string getPhoneWork() const { return phoneWork; }
    std::string getPhoneHome() const { return phoneHome; }
    std::string getPhoneMobile() const { return phoneMobile; }
};