#include "PhoneBook.h"
#include "Validator.h"
#include <iostream>

int main() {
    PhoneBook book("contacts.txt");
    book.load();

    int choice;

    do {
        std::cout << "\n===== MENU =====\n";
        std::cout << "1. Add contact\n";
        std::cout << "2. Show all\n";
        std::cout << "3. Delete contact\n";
        std::cout << "4. Edit contact\n";
        std::cout << "5. Search\n";
        std::cout << "6. Sort\n";
        std::cout << "7. Save and exit\n";
        std::cout << "Choice: ";

        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {

        // ------------------ ADD ------------------
        case 1: {
            std::string fn, ln, mn, addr, birth, mail, work, home, mob;
            int count = 3;

            do {
                std::cout << "Enter first name: "; getline(std::cin, fn);
                fn = Validator::trim(fn);
            } while (!Validator::validateName(fn));

            do {
                std::cout << "Enter last name: "; getline(std::cin, ln);
                ln = Validator::trim(ln);
            } while (!Validator::validateName(ln));

            do {
                std::cout << "Enter middle name (or empty): "; getline(std::cin, mn);
                mn = Validator::trim(mn);
                if (mn.empty()) break;
            } while (!Validator::validateName(mn));

            std::cout << "Enter address: "; getline(std::cin, addr);

            do {
                std::cout << "Enter birth date YYYY-MM-DD (or empty): "; getline(std::cin, birth);
                if (birth.empty()) break;
            } while (!Validator::validateDate(birth));

            do {
                std::cout << "Enter email: "; getline(std::cin, mail);
            } while (!Validator::validateEmail(mail));

            do {
                std::cout << "Please enter at least one phone number\n";
                if (count == 0) count = 3;

                do {
                    std::cout << "Work phone (or empty): "; getline(std::cin, work);
                    if (work.empty()) { work=""; count--; break; }
                } while (!Validator::validatePhone(work));

                do {
                    std::cout << "Home phone (or empty): "; getline(std::cin, home);
                    if (home.empty()) { home=""; count--; break; }
                } while (!Validator::validatePhone(home));

                do {
                    std::cout << "Mobile phone (or empty): "; getline(std::cin, mob);
                    if (mob.empty()) { mob=""; count--; break; }
                } while (!Validator::validatePhone(mob));

            } while (count == 0);

            Contact c(fn, ln, mn, addr, birth, mail, work, home, mob);
            book.addContact(c);

            std::cout << "Contact added!\n";
            break;
        }

        // ------------------ SHOW ALL ------------------
        case 2:
            book.listContacts();
            break;

        // ------------------ DELETE ------------------
        case 3: {
            int index;
            std::cout << "Enter index to delete: ";
            std::cin >> index;
            std::cin.ignore();

            if (book.removeByIndex(index - 1))
                std::cout << "Deleted.\n";
            else
                std::cout << "Invalid index.\n";

            break;
        }

        // ------------------ EDIT ------------------
        case 4: {
            int index;
            std::cout << "Enter index to edit: ";
            std::cin >> index;
            std::cin.ignore();

            if (index < 1 || index > (int)book.getCount()) {
                std::cout << "Invalid index.\n";
                break;
            }

            std::cout << "Enter new data:\n";

            // повторно используем твой ввод из case 1
            std::string fn, ln, mn, addr, birth, mail, work, home, mob;
            int count = 3;

            do {
                std::cout << "Enter first name: "; getline(std::cin, fn);
                fn = Validator::trim(fn);
            } while (!Validator::validateName(fn));

            do {
                std::cout << "Enter last name: "; getline(std::cin, ln);
                ln = Validator::trim(ln);
            } while (!Validator::validateName(ln));

            do {
                std::cout << "Enter middle name (or empty): "; getline(std::cin, mn);
                mn = Validator::trim(mn);
                if (mn.empty()) break;
            } while (!Validator::validateName(mn));

            std::cout << "Enter address (or empty): "; getline(std::cin, addr);

            do {
                std::cout << "Enter birth date YYYY-MM-DD (or empty): "; getline(std::cin, birth);
                if (birth.empty()) break;
            } while (!Validator::validateDate(birth));

            do {
                std::cout << "Enter email: "; getline(std::cin, mail);
            } while (!Validator::validateEmail(mail));

            do {
                std::cout << "Please enter at least one phone number\n";
                if (count == 0) count = 3;

                do {
                    std::cout << "Work phone (or empty): "; getline(std::cin, work);
                    if (work.empty()) { work=""; count--; break; }
                } while (!Validator::validatePhone(work));

                do {
                    std::cout << "Home phone (or empty): "; getline(std::cin, home);
                    if (home.empty()) { home=""; count--; break; }
                } while (!Validator::validatePhone(home));

                do {
                    std::cout << "Mobile phone (or empty): "; getline(std::cin, mob);
                    if (mob.empty()) { mob=""; count--; break; }
                } while (!Validator::validatePhone(mob));

            } while (count == 0);

            book.editContact(index - 1, Contact(fn, ln, mn, addr, birth, mail, work, home, mob));
            std::cout << "Updated.\n";
            break;
        }

        // ------------------ SEARCH ------------------
        case 5: {
            std::string q;
            std::cout << "Enter search query: ";
            getline(std::cin, q);

            auto results = book.search(q);
            if (results.empty()) std::cout << "No matches.\n";
            else {
                std::cout << "Found:\n";
                for (auto& c : results) c.print();
            }
            break;
        }

        // ------------------ SORT ------------------
        case 6: {
            std::string field;
            std::cout << "Sort by field: \n"
            << "firstName / lastName / middleName / address /\n"
            << "birthDate / email / phoneWork / phoneHome / phoneMobile\n"
            << "Enter field: ";

            getline(std::cin, field);

            book.sortByField(field);
            std::cout << "Sorted.\n";
            break;
        }

        // ------------------ EXIT ------------------
        case 7:
            book.save();
            std::cout << "Saved. Bye!\n";
            break;

        default:
            std::cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}
