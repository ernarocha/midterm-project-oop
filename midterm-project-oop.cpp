#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>
using namespace std;

class Inventory { 

protected:
    int itemCount = 0;

public:
    virtual void addItem() = 0;
    virtual void updateItem() = 0;
    virtual void removeItem() = 0;
    virtual void displayItemsByCategory() = 0;
    virtual void displayAllItems() = 0;
    virtual void searchItem() = 0;
    virtual void sortItem() = 0;
    virtual void displayLowStockItems() = 0;

    string toUpperCase(const string &str)
    {
        string upperStr = str;
        for (char &c : upperStr)
        {
            c = toupper(c);
        }
        return upperStr;
    }
};

class Item { 
private:
    string id;
    string name;
    string category;
    int quantity;
    double price;

public:
    Item() : id(""), name(""), category(""), quantity(0), price(0.0) {} 

    Item(string id, string name, string category, int quantity, double price)           
        : id(id), name(name), category(category), quantity(quantity), price(price) {}

    string getID() { 
        return id;
    }

    string getName() {
        return name;
    }

    string getCategory() {
        return category;
    }

    int getQuantity() {
        return quantity;
    }

    double getPrice() {
        return price;
    }

    double setNewPrice(double newPrice) {
        double price = getPrice();
        price = newPrice;
        return newPrice;
    }

    double setNewQuantity(double newQuantity) {
        double quantity = getQuantity();
        quantity = newQuantity;
        return newQuantity;
    }
};

class InventorySystem : public Inventory { 

private:
    Item items[100]; 
    int itemCount;   
    string validCategories[3] = {"CLOTHING", "ELECTRONICS", "ENTERTAINMENT"};

public:
    InventorySystem() : itemCount(0) {}
    
    void addItem() override {
        cout << string(76, '-') << endl;
        cout << "\t\t\t\tAdd Item" << endl;
        cout << string(76, '-') << endl
             << endl;

        string category;
        bool categoryFound = false;

        do {
            cout << "Input the category of the item (Clothing, Electronics, Entertainment): ";
            getline(cin, category);

            category = toUpperCase(category);

            if (category != "CLOTHING" && category != "ELECTRONICS" && category != "ENTERTAINMENT") {
                cout << endl << "Clothing, Electronics, and Entertainment are the only categories accepted!" << endl
                     << endl;
            }

        } while (category != "CLOTHING" && category != "ELECTRONICS" && category != "ENTERTAINMENT");

        for (int i = 0; i < 3; i++) {        
            if (category == validCategories[i]) {
                categoryFound = true;

                if (itemCount < 100) {
                    string id, name;
                    int quantity;
                    double price;
                    bool validID = false;

                    cout << endl << "Item Details" << endl;

                    do {
                        validID = true;
                        cout << endl << "Input Item ID (alphanumeric, no spaces): ";
                        cin.clear();
                        cin.sync();

                        getline(cin, id);

                        id = toUpperCase(id);

                        if (id.length() <= 0) {
                            cout << endl << "Empty inputs are not allowed!" << endl;
                            validID = false;
                        }

                        for (int i = 0; i < id.length(); i++) {
                            if (id[i] == ' ') {
                                cout << endl << "Invalid ID! No spaces allowed." << endl;
                                validID = false;
                                break;
                            }
                            else if (!isalnum(id[i])) {
                                cout << endl << "Invalid ID! Only alphanumeric characters are allowed." << endl;
                                validID = false;
                                break;
                            }
                        }

                        if (validID) {
                            for (int i = 0; i < itemCount; i++) {
                                if (items[i].getID() == id) {
                                    cout << endl << "This ID already exists! Please enter a unique ID." << endl;
                                    validID = false;
                                    break;
                                }
                            }
                        }

                    } while (!validID);

                    bool validInput = false;

                    do {
                        cout << endl << "Input Item Name: ";
                        getline(cin, name);

                        if (name.length() <= 0) {
                            cout << endl << "Empty inputs are not allowed!" << endl;
                            validInput = false;
                        }
                        else {
                            validInput = true;
                        }
                    } while (!validInput);

                    do {
                        string quantityInput;
                        validInput = true;

                        cout << endl << "Input Item Quantity: ";
                        getline(cin, quantityInput);

                        if (quantityInput.length() <= 0) {
                            cout << endl << "Empty inputs are not allowed!" << endl;
                            validInput = false;
                        }

                        for (char c : quantityInput) {
                            if (c == ' ') {
                                cout << endl << "Invalid input! No spaces allowed." << endl;
                                validInput = false;
                                break;
                            }
                            else if (!isdigit(c)) {
                                cout << endl <<"Invalid input! Enter numbers greater than zero only." << endl;
                                validInput = false;
                                break;
                            }
                        }

                        if (validInput) {
                            quantity = stoi(quantityInput);
                            if (quantity <= 0) {
                                cout << endl << "Invalid input! Quantity must be greater than zero." << endl;
                                validInput = false;
                            }
                        }

                    } while (!validInput);

                    string priceInput;

                    do {
                        validInput = true;
                        bool decimalPointFound = false;

                        cout << endl << "Input Item Price: ";
                        getline(cin, priceInput);

                        if (priceInput.length() <= 0) {
                            cout << endl << "Empty inputs are not allowed!" << endl;
                            validInput = false;
                        }

                        for (char c : priceInput) {
                            if (c == ' ') {
                                cout << "Invalid input! No spaces allowed." << endl;
                                validInput = false;
                                break;
                            }
                            else if (c == '.') {
                                if (decimalPointFound) {
                                    validInput = false;
                                    break;
                                }
                                decimalPointFound = true;
                            }
                            else if (!isdigit(c)) {
                                cout << "Invalid input! Enter numbers greater than zero." << endl;
                                validInput = false;
                                break;
                            }
                        }

                        if (validInput) {
                            price = stod(priceInput);
                            if (price <= 0) {
                                cout << "Invalid input! Price must be greater than zero." << endl;
                                validInput = false;
                            }
                        }

                    } while (!validInput);

                    items[itemCount] = Item(id, name, category, quantity, price);
                    itemCount++;

                    cout << endl << string(76, '-') << endl
                         << "\t\t\t   Item added successfully!" << endl
                         << string(76, '-') << endl;

                    cout << endl << "Returning to Main Menu.." << endl;
                    system("pause");
                    system("cls");
                }
                else {
                    cout << endl << "Inventory is full, cannot add more items!" << endl;
                }
                break;
            }
        }

        if (!categoryFound) {
            cout << "Category " << category << " does not exist!" << endl;
        }
    }

void updateItem() override {
    cout << string(76, '-') << endl;
    cout << "\t\t\t\tUpdate Item" << endl;
    cout << string(76, '-') << endl;

    string inputID;

    if (itemCount == 0) {
        cout << endl << "There are no items in the inventory!" << endl;
        cout << string(76, '-') << endl;
        cout << endl << "Returning to Main Menu..." << endl;
        system("pause");
        system("cls");
        return;
    }

    cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(16) << "Price" << left << setw(20) << "Category" << endl;
    cout << string(76, '-') << endl;

    for (int i = 0; i < itemCount; i++) {
        cout << fixed << setprecision(2) << left << setw(10) << items[i].getID() << left << setw(25) << items[i].getName() << left << setw(12) << items[i].getQuantity() << "P" << left << setw(15) << items[i].getPrice() << left << setw(20) << items[i].getCategory() << endl;
    }

    bool validID = false;

    while (!validID) {
        cout << string(76, '-') << endl;

        cout << "Input the ID of the item you wish to update: ";
        getline(cin, inputID);

        inputID = toUpperCase(inputID);

        if (inputID.length() == 0) {
            cout << "Empty inputs are not allowed." << endl;
            continue;
        }

        bool hasSpace = false;
        for (char c : inputID) {
            if (c == ' ') {
                hasSpace = true;
                break;
            }
        }

        if (hasSpace) {
            cout << "Invalid input! No spaces allowed." << endl;
            continue;
        }

        bool itemFound = false;

        for (int i = 0; i < itemCount; i++) {
            if (inputID == items[i].getID()) {
                itemFound = true;
                validID = true;

                string userChoice;
                cout << endl << "Do you want to update the quantity or the price? (input Q or P): ";
                getline(cin, userChoice);
                userChoice = toUpperCase(userChoice);

                while (userChoice != "Q" && userChoice != "P") {
                    cout << "Enter 'Q' for Quantity or 'P' for Price only!" << endl << endl;
                    cout << "Do you want to update the quantity or the price? (input Q or P): ";
                    getline(cin, userChoice);
                    userChoice = toUpperCase(userChoice);
                }

                if (userChoice == "Q") {
                    int oldQuantity = items[i].getQuantity();
                    string quantityInput;
                    int newQuantity;
                    bool validQuantity = false;

                    while (!validQuantity) {
                        cout << endl << "Input new value for Quantity: ";
                        getline(cin, quantityInput);

                        bool isNumeric = true;
                        hasSpace = false;
                        for (char c : quantityInput) {
                            if (!isdigit(c)) {
                                isNumeric = false;
                            }
                            if (c == ' ') {
                                hasSpace = true;
                            }
                        }

                        if (hasSpace) {
                            cout << "Invalid input! No spaces allowed." << endl;
                        } else if (isNumeric && quantityInput.length() > 0) {
                            newQuantity = stoi(quantityInput);
                            if (newQuantity > 0) {
                                if (newQuantity == items[i].getQuantity()) {
                                    cout << "Invalid input! Quantity cannot be the same as the current value." << endl;
                                } else {
                                    validQuantity = true;
                                }
                            } else {
                                cout << "Invalid input! Quantity must be greater than zero." << endl;
                            }
                        } else {
                            cout << "Invalid input! Please enter a positive integer." << endl;
                        }
                    }

                    items[i] = Item(items[i].getID(), items[i].getName(), items[i].getCategory(), newQuantity, items[i].getPrice());
                    cout << endl << "Quantity of Item " << items[i].getName() << " is updated from " << oldQuantity << " to " << newQuantity << endl << endl;
                } else {
                    double newPrice;
                    double oldPrice = items[i].getPrice();
                    string priceInput;
                    bool validPrice = false;

                    while (!validPrice) {
                        cout << endl << "Input new value for Price: ";
                        getline(cin, priceInput);

                        bool validPriceInput = true;
                        bool decimalPointFound = false;

                        for (char c : priceInput) {
                            if (c == '.') {
                                if (decimalPointFound) {
                                    validPriceInput = false;
                                    break;
                                }
                                decimalPointFound = true;
                            } else if (!isdigit(c)) {
                                validPriceInput = false;
                                break;
                            }
                        }

                        if (validPriceInput && priceInput.length() > 0) {
                            newPrice = stod(priceInput);
                            if (newPrice > 0) {
                                if (newPrice == oldPrice) {
                                    cout << "Invalid input! Price cannot be the same as the current value." << endl;
                                } else {
                                    validPrice = true;
                                }
                            } else {
                                cout << "Invalid input! Price must be greater than zero." << endl;
                            }
                        } else {
                            cout << "Invalid input! Please enter a valid number." << endl;
                        }
                    }

                    items[i] = Item(items[i].getID(), items[i].getName(), items[i].getCategory(), items[i].getQuantity(), newPrice);
                    cout << fixed << setprecision(2) << endl << "Price of Item " << items[i].getName() << " is updated from P" << oldPrice << " to P" << newPrice << endl << endl;
                }

                cout << string(76, '-') << endl;
                cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(15) << "Price" << left << setw(20) << "Category" << endl;
                cout << string(76, '-') << endl;

                cout << fixed << setprecision(2) << left << setw(10) << items[i].getID() << left << setw(25) << items[i].getName() << left << setw(12) << items[i].getQuantity() << "P" << left << setw(12) << items[i].getPrice() << "   " << left << setw(20) << items[i].getCategory() << endl;
                cout << string(76, '-') << endl << endl;

                cout << "Returning to Main Menu..." << endl;
                system("pause");
                system("cls");
                return;
            }
        }

        if (!itemFound) {
            string tryAgain;
            bool validResponse = false;

            while (!validResponse) {
                cout << "Item ID not found! Do you want to try again? (Y/N): ";
                getline(cin, tryAgain);
                tryAgain = toUpperCase(tryAgain);

                if (tryAgain == "Y") {
                    validResponse = true;
                } else if (tryAgain == "N") {
                    validResponse = true;
                    cout << endl << "Returning to Main Menu.." << endl;
                    system("pause");
                    system("cls");
                    return;
                } else {
                    cout << "Only enter 'Y' or 'N'!" << endl;
                }
            }
        }
    }
}

    void removeItem() override {
        string id;

        cout << string(76, '-') << endl;
        cout << "\t\t\t\tRemove Item" << endl;
        cout << string(76, '-') << endl;

        bool itemIDFound = false;

        if (itemCount == 0) {
            cout << endl << "There are no items in the inventory!" << endl;
            cout << string(76, '-') << endl;
            cout << endl << "Returning to Main Menu..." << endl;
            system("pause");
            system("cls");
            return;
        }

        cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(16) << "Price" << left << setw(20) << "Category" << endl;
        cout << string(76, '-') << endl;

        for (int i = 0; i < itemCount; i++) {
            cout << fixed << setprecision(2) << left << setw(10) << items[i].getID() << left << setw(25) << items[i].getName() << left << setw(12) << items[i].getQuantity() << "P" << left << setw(15) << items[i].getPrice() << left << setw(20) << items[i].getCategory() << endl;
        }

        while (!itemIDFound) {
            cout << string(76, '-') << endl;
            cout << "Input the Item ID: ";
            cin >> id; 

            for (char &c : id) {
                c = toupper(c);
            }

            bool hasSpace = false;
            for (char c : id) {
                if (c == ' ') {
                    hasSpace = true;
                    break;
                }
            }

            if (hasSpace) {
                cout << "Invalid input! No spaces allowed." << endl;
                continue;
            }

            for (int i = 0; i < itemCount; i++) {
                if (id == items[i].getID()) {
                    itemIDFound = true;

                    for (int j = i; j < itemCount - 1; j++) { 
                        for (int k = 0; k < 5; k++) {
                            items[j] = items[j + 1];
                        }
                    }
                    itemCount--;

                    cout << "Item " << items[i].getName() << " has been removed from the inventory." << endl;

                    cout << endl << "Returning to Main Menu.." << endl;
                    system("pause");
                    system("cls");
                    return;
                }
            }

            cout << endl << "Item not found!" << endl;

            char tryAgain;
            cout << endl << "Do you want to try again? (Y/N): ";
            cin >> tryAgain;

            if (toupper(tryAgain) == 'Y') {
                itemIDFound = false;
            }
            else {
                cout << endl << "Returning to Main Menu..." << endl;
                system("pause");
                system("cls");
                return;
            }
        }
    }

    void displayItemsByCategory() override {
        string category;

        cout << string(76, '-') << endl;
        cout << "\t\t\t\tBy Category" << endl;
        cout << string(76, '-') << endl;

        if (itemCount == 0) {
            cout << endl << "There are no items in the inventory.\n"; 
            cout << string(76, '-') << endl;
            cout << "Returning to the Inventory Menu...\n";
            system("pause");
            system("cls");
            return;
        }

        bool validInput = false;
        bool hasSpace = false;

        cout << "Categories:\n"
             << "    Clothing\n"
             << "    Electronics\n"
             << "    Entertainment\n\n";

        do {
            hasSpace = false; 

            cout << "Category of choice:  ";
            getline(cin, category);
            category = toUpperCase(category);

            for (char c : category) { 
                if (c == ' ') {
                    hasSpace = true;
                    break;
                }
            }

            if (hasSpace) {
                cout << endl <<"Invalid input! No spaces allowed." << endl << endl;
                validInput = false;
            }

            else if (category != "CLOTHING" && category != "ELECTRONICS" && category != "ENTERTAINMENT") {
                cout << endl << "Clothing, Electronics, and Entertainment are the only categories accepted!" << endl << endl;
            }
            else {
                validInput = true; 
            }

        } while (!validInput);

        bool categoryFound = false;
        cout << fixed << setprecision(2);

        for (int i = 0; i < 3; i++) {
            if (category == validCategories[i]) {
                categoryFound = true;
                bool itemFound = false;
                system("cls");

                for (int j = 0; j < itemCount; j++) {
                    if (items[j].getCategory() == category) {
                        if (!itemFound) {
                            cout << string(76, '-') << endl
                                 << "\t\t\tDisplaying Items by Category" << endl
                                 << string(76, '-') << endl;

                            cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(12) << "Price" << left << setw(20) << "Category" << endl;
                            cout << string(76, '-') << endl;

                            itemFound = true;
                        }

                        string category = items[j].getCategory();
                        double price = items[j].getPrice();

                        cout << fixed << setprecision(2) << left << setw(10) << items[j].getID() << left << setw(25) << items[j].getName() << left << setw(12) << items[j].getQuantity() << "P" << left << setw(12) << price << left << setw(20) << category << endl;
                    }
                }
                cout << string(76, '-') << endl;

                if (!itemFound) {
                    cout << "No items found in this category!" << endl;
                    cout << string(76, '-') << endl;
                }
                break;
            }
        }

        cout << endl << "Returning to Main Menu..." << endl;
        system("pause");
        system("cls");
    }

    void displayAllItems() override {
        cout << string(76, '-') << endl;
        cout << "\t\t\t     Display All Items" << endl;
        cout << string(76, '-') << endl;

        if (itemCount == 0) {
            cout << endl << "There are no items in the inventory!" << endl;
        }
        else {
            cout << left << setw(10) << "ID" << setw(25) << "Name" << setw(12) << "Quantity" << setw(15) << "Price" << setw(20) << "Category" << endl;
            cout << string(76, '-') << endl;

            for (int i = 0; i < itemCount; i++) {
                cout << fixed << setprecision(2) << left << setw(10) << items[i].getID()  << setw(25) << items[i].getName()  << setw(12) << items[i].getQuantity() << setw(15) 
                    << fixed << setprecision(2) << items[i].getPrice() << setw(20) << items[i].getCategory() << endl;
            }
        }
        cout << string(76, '-') << endl;
        cout << endl << "Returning to the Inventory Menu...\n";
        system("pause");
        system("cls");
    }

void searchItem() override {
    string id;

    cout << string(76, '-') << endl;
    cout << "\t\t\t\tSearch Item" << endl;
    cout << string(76, '-') << endl;

    if (itemCount == 0) {
        cout << endl << "There are no items in the inventory.\n"; 
        cout << string(76, '-') << endl;
        cout << "Returning to the Inventory Menu...\n";
        system("pause");
        system("cls");
        return;
    }

    bool itemFound = false;
    bool validInput = true;

    do {
        cout << endl << "Input Item ID: ";
        getline(cin, id); 
        id = toUpperCase(id);

        bool hasSpace = false;

        for (char c : id) {
            if (c == ' ') {
                hasSpace = true;
                break;
            }
        }

        if (hasSpace) {
            cout << endl <<"Invalid input! No spaces allowed." << endl;
        }
        else {
            for (int i = 0; i < itemCount; i++) 
            {
                if (items[i].getID() == id) {
                    itemFound = true;
                    system("cls");

                    cout << string(76, '-') << endl;
                    cout << "\t\t\t\tSearch Item" << endl;
                    cout << string(76, '-') << endl;

                    cout << left << setw(10) << "ID" << setw(25) << "Name" << setw(12) << "Quantity" << setw(15) << "Price" << setw(20) << "Category" << endl;
                    cout << string(76, '-') << endl;

                    string category = items[i].getCategory();
                    double price = items[i].getPrice();
                    cout << fixed << setprecision(2) << left << setw(10) << items[i].getID() << left << setw(25) << items[i].getName() << left << setw(12) << items[i].getQuantity()
                         << "P" << left << setw(15) << price << left << setw(20) << category << endl;

                    cout << string(76, '-') << endl;
                    break;
                }
            }
        }

        if (!itemFound || hasSpace) {
            string tryAgain;
            validInput = false;

            while (!validInput) {
                cout << endl << "Item not found or invalid input! Do you want to try again? (Y/N): ";
                getline(cin, tryAgain);  
                tryAgain = toUpperCase(tryAgain);

                if (tryAgain == "N") {
                    cout << endl << "Returning to Main Menu.." << endl;
                    system("pause");
                    system("cls");
                    return;
                }
                else if (tryAgain == "Y") {
                    validInput = true;  
                }
                else {
                    cout << endl << "Only enter 'Y' or 'N'!" << endl;
                }
            }
        }

    } while (!itemFound);

    cout << endl << "Returning to the Inventory Menu...\n";
    system("pause");
    system("cls");
}


void sortItem() override {
    cout << string(76, '-') << endl;
    cout << "\t\t\t\tSort Items" << endl;
    cout << string(76, '-') << endl << endl;

    if (itemCount == 0) {
        cout << "There are no items in the inventory!" << endl;
        cout << endl << "Returning to Main Menu..." << endl;
        system("pause");
        system("cls");
        return;
    }

    string sortInput;
    while (true) {
        cout << "Do you want to sort items? (1 - Yes, 2 - No): ";
        getline(cin, sortInput);

        if (sortInput.empty()) {
            cout << endl << "Empty inputs are not allowed." << endl << endl;
        } else if (sortInput == "1") {
            break;  
        } else if (sortInput == "2") {
            cout << endl <<"Displaying items in the default order (as added):\n";
            displayAllItems();
            return;  
        } else {
            cout << endl << "Invalid input! Please enter 1 or 2." << endl << endl;
        }
    }

    char sortChoice;
    while (true) {
        cout << endl <<"Sort by quantity (Q) or price (P)? ";
        cin >> sortChoice;
        sortChoice = toupper(sortChoice);

        if (sortChoice == 'Q' || sortChoice == 'P') {
            break;  
        } else {
            cout << endl <<"Invalid input! Only enter 'Q' for Quantity and 'P' for Price." << endl;
        }
    }

    char orderChoice;
    while (true) {
        cout << endl << "Do you want to sort in ascending (A) or descending (D) order?: ";
        cin >> orderChoice;
        orderChoice = toupper(orderChoice);

        if (orderChoice == 'A' || orderChoice == 'D') {
            break;  
        } else {
            cout << endl << "Invalid input! Only enter 'A' for Ascending and 'D' for Descending." << endl;
        }
    }

    bool swapped;
    for (int i = 0; i < itemCount - 1; i++) {
        swapped = false;
        for (int j = 0; j < itemCount - i - 1; j++) {
            bool shouldSwap = false;

            if (sortChoice == 'Q') {
                shouldSwap = (orderChoice == 'A') ?
                              (items[j].getQuantity() > items[j + 1].getQuantity()) :
                              (items[j].getQuantity() < items[j + 1].getQuantity());
            } else if (sortChoice == 'P') {
                shouldSwap = (orderChoice == 'A') ?
                              (items[j].getPrice() > items[j + 1].getPrice()) :
                              (items[j].getPrice() < items[j + 1].getPrice());
            }

            if (shouldSwap) {
                Item temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;  
        }
    }

    cout << endl << "Items sorted successfully!" << endl;
    displayAllItems();
}

    void displayLowStockItems() {
        cout << string(76, '-') << endl;
        cout << "\t\t\t       Low Stock Items" << endl;
        cout << string(76, '-') << endl;

        if (itemCount == 0) {
            cout << endl << "There are no items in the inventory!" << endl;
            cout << string(76, '-') << endl;
            cout << endl << "Returning to Main Menu..." << endl;
            system("pause");
            system("cls");
            return;
        }

        bool lowStockFound = false;

        for (int i = 0; i < itemCount; i++)
        {
            if (items[i].getQuantity() <= 5) {

                if (!lowStockFound) {
                    cout << left << setw(10) << "ID" << setw(25) << "Name" << setw(12) << "Quantity" << setw(15) << "Price" << setw(20) << "Category" << endl;
                    cout << string(76, '-') << endl;
                    lowStockFound = true;
                }
                cout << left << setw(10) << items[i].getID() << setw(25) << items[i].getName() << setw(12) << items[i].getQuantity()
                     << setw(15) << fixed << setprecision(2) << items[i].getPrice() << setw(20) << items[i].getCategory() << endl;
            }
        }

        if (!lowStockFound) {
            cout << endl
                 << "No low stock items found!" << endl;
        }
        cout << string(76, '-') << endl;
        cout << endl << "Returning to the Inventory Menu...\n";
        system("pause");
        system("cls");
    }
};

int main() {

    InventorySystem inventory;
    string choice;
    int input;

    do {
        cout << string(30, '-') << endl;
        cout << "        Inventory Menu" << endl;
        cout << string(30, '-') << endl;
        cout << "1 - Add Item" << endl;
        cout << "2 - Update Item" << endl;
        cout << "3 - Remove Item" << endl;
        cout << "4 - Display Items by Category" << endl;
        cout << "5 - Display All Items" << endl;
        cout << "6 - Search Item" << endl;
        cout << "7 - Sort Items" << endl;
        cout << "8 - Display Low Stock Items" << endl;
        cout << "9 - Exit\n";
        cout << string(30, '-') << endl;
        cout << endl
             << "Enter your choice: ";
        getline(cin, choice);


        if (choice.length() == 1 && isdigit(choice[0]) && choice[0] >= '1' && choice[0] <= '9') {
            input = choice[0] - '0';
        }
        else {
            cout << endl << "Invalid input. Kindly enter numbers 1 to 9 only." << endl;
            system("pause");
            system("cls");
            continue;
        }

        system("cls");

        switch (input) {
        case 1:
            inventory.addItem();
            break;
        case 2:
            inventory.updateItem();
            break;
        case 3:
            inventory.removeItem();
            break;
        case 4:
            inventory.displayItemsByCategory();
            break;
        case 5:
            inventory.displayAllItems();
            break;
        case 6:
            inventory.searchItem();
            break;
        case 7:
            inventory.sortItem();
            break;
        case 8:
            inventory.displayLowStockItems();
            break;
        case 9:
            cout << "Thank you!\n\nExiting from the inventory system...";
            break;

        default:
            cout << "Returning to the Inventory Menu...\n";
            system("pause");
            system("cls");
        }
    } while (input != 9);

    return 0;
}