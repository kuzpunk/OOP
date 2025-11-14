#include "Contact.h"
#include <sstream>

Contact::Contact(std::string fn, std::string ln, std::string mn,
            std::string addr, std::string birth, std::string mail,
            std::string work, std::string home, std::string mobile)
    : firstName(fn), lastName(ln), middleName(mn), 
    address(addr), birthDate(birth), email(mail),
    phoneWork(work), phoneHome(home), phoneMobile(mobile) {}

void Contact::print() const {
    std::cout << firstName << " " << lastName << " " << middleName
            << " | " << address << " | " << birthDate << " | " << email
            << " | " << phoneWork << " | "  << phoneHome 
              << " | " << phoneMobile << " | "  << std::endl;
}

std::string Contact::toFileString() const{
    std::ostringstream oss;
    oss << firstName << ";" << lastName << ";" << middleName << ";" 
        << address << ";" << birthDate << ";" << email << ";"
        << phoneWork << ";" << phoneHome << ";" << phoneMobile;
    return oss.str();
}

Contact Contact::fromFileString(const std::string& line){
    std::stringstream ss(line);
    std::string data[9];
    for (int i=0; i<9; ++i){
        std::getline(ss, data[i], ';');
    }
    return Contact(data[0], data[1], data[2], data[3], data[4], data[5], 
                   data[6], data[7], data[8]);
}