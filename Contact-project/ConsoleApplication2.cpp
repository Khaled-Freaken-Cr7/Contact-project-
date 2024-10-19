#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

const int MAX_CONTACTS = 100000;
string contactNames[MAX_CONTACTS];
string contactPhones[MAX_CONTACTS];
int contactCount = 0;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void saveContactsToFile(const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error opening file for saving." << endl;
        return;
    }
    for (int i = 0; i < contactCount; i++) {
        outFile << contactNames[i] << "," << contactPhones[i] << endl;
    }
    outFile.close();
}

void loadContactsFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file for loading." << endl;
        return;
    }
    contactCount = 0;
    string line, name, phone;
    while (getline(inFile, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            name = line.substr(0, commaPos);
            phone = line.substr(commaPos + 1);
            if (contactCount < MAX_CONTACTS) {
                contactNames[contactCount] = name;
                contactPhones[contactCount] = phone;
                contactCount++;
            }
        }
    }
    inFile.close();
}

void addContact(const string& name, const string& phone)
{
    clearScreen();
    if (contactCount >= MAX_CONTACTS - 1) {
        cout << "Cannot add more contacts. The last index is reserved." << endl;
        return;
    }
    contactNames[contactCount] = name;
    contactPhones[contactCount] = phone;
    bool phoneFlag = false, nameFlag = false;
    for (int i = 0; i < contactCount; i++)
    {
        if (contactPhones[i] == phone)
            phoneFlag = true;
        if (contactNames[i] == name)
            nameFlag = true;
    }
    if (phoneFlag && nameFlag)
    {
        cout << "This contact number is registered, enter another number.\n";
        contactNames[contactCount].clear();
        contactPhones[contactCount].clear();
    }
    else if (phoneFlag)
    {
        cout << "This contact number is registered, enter another number.\n";
        contactNames[contactCount].clear();
        contactPhones[contactCount].clear();
    }
    else
    {
        contactCount++;
        cout << "Contact added successfully." << endl;
    }
}
void deleteContact(const string& name) {
    clearScreen();
    int matchCount = 0;
    for (int i = 0; i < contactCount; i++) {
        if (contactNames[i] == name) {
            matchCount++;
            cout << matchCount << ". Name: " << contactNames[i] << ", Phone: " << contactPhones[i] << endl;
        }
    }

    if (matchCount == 0) {
        cout << "Contact not found." << endl;
        return;
    }
    int choice;
    if (matchCount > 1) {
        cout << "Multiple contacts found with the name '" << name << "'. Please select the contact number to delete: ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > matchCount) {
            cin.clear();
            cin.ignore();
            clearScreen();
            cout << "Invalid choice. Operation cancelled." << endl;
            return;
        }
    }
    else {
        choice = 1;
    }
    matchCount = 0;
    for (int i = 0; i < contactCount; i++) {
        if (contactNames[i] == name) {
            matchCount++;
            if (matchCount == choice) {
                for (int j = i; j < contactCount - 1; j++) {
                    contactNames[j] = contactNames[j + 1];
                    contactPhones[j] = contactPhones[j + 1];
                }
                contactCount--;
                cout << "Contact deleted and changes saved successfully." << endl;
                return;
            }
        }
    }
}
void updateContact(const string& name, const string& newPhone) {
    clearScreen();
    vector<int> matchIndices;
    int matchCount = 0;

    for (int i = 0; i < contactCount; i++) {
        if (contactNames[i].find(name) != string::npos) {
            matchIndices.push_back(i);
            matchCount++;
            cout << matchCount << ". Name: " << contactNames[i] << ", Phone: " << contactPhones[i] << endl;
        }
    }
    if (matchCount == 0) {
        cout << "No contacts found with the name containing '" << name << "'." << endl;
        return;
    }
    int choice;
    if (matchCount > 1) {
        cout << "Multiple contacts found with similar names. Please select the contact number to update: ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > matchCount) {
            cin.clear();
            cin.ignore();
            cout << "Invalid choice. Operation cancelled." << endl;
            return;
        }
    }
    else
    {
        choice = 1;
    }
    int index = matchIndices[choice - 1];
    contactPhones[index] = newPhone;
    cout << "Contact updated and changes saved successfully." << endl;
}
void displayAllContacts() {
    clearScreen();
    if (contactCount == 0) {
        cout << "No contacts available." << endl;
        return;
    }
    cout << "----------------------------------------" << endl;
    cout << "| " << setw(20) << left << "Name" << "| " << setw(15) << left << "Phone" << " |" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < contactCount; i++) {
        cout << "| " << setw(20) << left << contactNames[i] << "| " << setw(15) << left << contactPhones[i] << " |" << endl;
    }
    cout << "----------------------------------------" << endl;
}
void searchContact(const string& name) {
    clearScreen();
    for (int i = 0; i < contactCount; i++) {
        if (contactNames[i] == name) {
            cout << "Name: " << contactNames[i] << ", Phone: " << contactPhones[i] << endl;
            return;
        }
    }
    cout << "Contact not found." << endl;
}
int main()
{
    int choice;
    string name, phone;
    const string filename = "contacts.txt";
    loadContactsFromFile(filename);
    clearScreen();
    while (true)
    {
        cout << "Choose the operation you want to perform:" << endl;
        cout << "1. Add a new contact" << endl;
        cout << "2. Delete a contact" << endl;
        cout << "3. Update contact details" << endl;
        cout << "4. Display all contacts" << endl;
        cout << "5. Search for a contact by name" << endl;
        cout << "6. Exit the program" << endl;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            clearScreen();
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            continue;
        }
        cin.ignore();
        switch (choice) {
        case 1:
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter phone: ";
            getline(cin, phone);
            addContact(name, phone);
            break;
        case 2:
            cout << "Enter the name you want to delete: ";
            getline(cin, name);
            deleteContact(name);
            break;
        case 3:
            cout << "Enter the name you want to update: ";
            getline(cin, name);
            cout << "Enter the new phone: ";
            getline(cin, phone);
            updateContact(name, phone);
            break;
        case 4:
            displayAllContacts();
            break;
        case 5:
            cout << "Enter the name you want to search for: ";
            getline(cin, name);
            searchContact(name);
            break;
        case 6:
            saveContactsToFile("contacts.txt");
            return 0;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
        saveContactsToFile("contacts.txt");

    }
    return 0;
}