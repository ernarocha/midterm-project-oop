#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

// Abstract base class
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

        string toUpperCase(const string &str) {
        string upperStr = str;
            for (char &c : upperStr) {
                c = toupper(c);
            }
            return upperStr;
        }
};

// Item class definition
class Item {
    private:
        string id;
        string name;
        string category;
        int quantity;
        double price;

    public:
        // Default constructor
        Item() : id(""), name(""), category(""), quantity(0), price(0.0) {}

        // Parameterized constructor
        Item(string id, string name, string category, int quantity, double price)
        : id(id), name(name), category(category), quantity(quantity), price(price) {}

        // Getters
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

// Derived InventorySystem class
class InventorySystem : public Inventory {
    private:
        Item items[100]; // Array to store items
        int itemCount; //Variable to hold the number of added products
        string validCategories[3] = {"CLOTHING", "ELECTRONICS", "ENTERTAINMENT"};

        //Function to search for the Product ID

    public:
        InventorySystem() : itemCount(0) {}

        void addItem() override {
        cout << string(76, '-') << endl;
        cout << "\t\t\t\tAdd Item" << endl;
        cout << string(76, '-') << endl << endl;

        string category;
        bool categoryFound = false;

            cin.clear();
            cin.sync();
        do {
            cout << "Input the category of the item (Clothing, Electronics, Entertainment): ";

            getline(cin, category);


            //di ko muna ginawang getline

            category = toUpperCase(category);

            if (category != "CLOTHING" && category != "ELECTRONICS" && category != "ENTERTAINMENT") {
                cout << endl << "Clothing, Electronics, and Entertainment are the only categories accepted!" << endl << endl;
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

                        for (char &c : id) {
                            c = toupper(c);
                        }

                        for (int i = 0; i < id.length(); i++) {
                            if (id[i] == ' ') {
                                cout << "Invalid ID! No spaces allowed." << endl;
                                validID = false;
                                break;
                            }
                            else if (!isalnum(id[i])) {
                                cout << "Invalid ID! Only alphanumeric characters are allowed." << endl;
                                validID = false;
                                break;
                            }
                        }

                        if (validID) {
                            for (int i = 0; i < itemCount; i++) {
                                if (items[i].getID() == id) {
                                    cout << "This ID already exists! Please enter a unique ID." << endl;
                                    validID = false;
                                    break;
                                }
                            }
                        } 

                    } while (!validID);

                    cout << endl << "Input Item Name: ";
                    getline(cin, name);

                    bool validInput = false;

                    do {
                        string quantityInput;
                        validInput = true;

                        cout << endl << "Input Item Quantity: ";
                        getline(cin, quantityInput);

                        for (char c : quantityInput) {
                            if (c == ' ') {
                                cout << "Invalid input! No spaces allowed." << endl;
                                validInput = false;
                                break;
                            }
                            else if (!isdigit(c)) {
                                cout << "Invalid input! Enter numbers greater than zero only." << endl;
                                validInput = false;
                                break;
                            }
                        }

                        if (validInput) {
                            quantity = stoi(quantityInput);
                            if (quantity <= 0) {
                                cout << "Invalid input! Quantity must be greater than zero." << endl;
                                validInput = false;
                            }
                        }

                    } while (!validInput);

                    do {
                        string priceInput;
                        validInput = true;
                        bool decimalPointFound = false;

                        cout << endl << "Input Item Price: ";
                        getline(cin, priceInput);

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

                    cout << endl << string(76, '-') << endl << "\t\t\t   Item added successfully!" << endl << string(76, '-') << endl;

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

    cin.clear();
    cin.sync();

    while (!validID) {
        cout << string(76, '-') << endl;

        cout << "Input the ID of the item you wish to update: ";
        getline(cin, inputID);

        inputID = toUpperCase(inputID);

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

        for (int i = 0; i < itemCount; i++) {
            if (inputID == items[i].getID()) {
                validID = true;

                string userChoice;

                cout << endl << "Do you want to update the quantity or the price? (input Q or P): ";
                getline(cin, userChoice);

                userChoice = toUpperCase(userChoice);

                double newPrice;
                double oldPrice = items[i].getPrice();
                string priceInput;
                bool validPrice = false;

                while (userChoice != "Q" && userChoice != "P") {
                    cout << "Enter 'Q' for Quantity or 'P' for Price only!" << endl;

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
                        }
                        else if (isNumeric && quantityInput.length() > 0) {
                            newQuantity = stoi(quantityInput);
                            if (newQuantity > 0) {
                                if (newQuantity == items[i].getQuantity()) {
                                    cout << "Invalid input! Quantity cannot be the same as the current value." << endl;
                                }
                                else {
                                    validQuantity = true;
                                }
                            }
                            else {
                                cout << "Invalid input! Quantity must be greater than zero." << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a positive integer." << endl;
                        }
                    }

                    oldQuantity = items[i].getQuantity();
                    items[i] = Item(items[i].getID(), items[i].getName(), items[i].getCategory(), newQuantity, items[i].getPrice());
                    cout << endl << "Quantity of Item " << items[i].getName() << " is updated from "
                        << oldQuantity << " to " << newQuantity << endl << endl;
                }
                else {
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
                            }
                            else if (!isdigit(c)) {
                                validPriceInput = false;
                                break;
                            }
                        }

                        if (validPriceInput && priceInput.length() > 0) {
                            newPrice = stod(priceInput);  // Set newPrice to the input value
                            if (newPrice > 0) {
                                if (newPrice == oldPrice) {
                                    cout << "Invalid input! Price cannot be the same as the current value." << endl;
                                }
                                else {
                                    validPrice = true;
                                }
                            }
                            else {
                                cout << "Invalid input! Price must be greater than zero." << endl;
                            }
                        }
                        else {
                            cout << "Invalid input! Please enter a valid number." << endl;
                        }
                    }

                    oldPrice = items[i].getPrice();
                    items[i] = Item(items[i].getID(), items[i].getName(), items[i].getCategory(), items[i].getQuantity(), newPrice);  // Correctly update the price
                    cout << fixed << setprecision(2) << endl << "Price of Item " << items[i].getName() << " is updated from P"
                        << oldPrice << " to P" << newPrice << endl << endl;
                }

                cout << string(76, '-') << endl;
                cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(16) << "Price" << left << setw(20) << "Category" << endl;
                cout << string(76, '-') << endl;

                cout << fixed << setprecision(2) << left << setw(10) << items[i].getID() << left << setw(25) << items[i].getName() << left << setw(12) << items[i].getQuantity() << "P" << left << setw(15) << items[i].getPrice() << "   " << left << setw(20) << items[i].getCategory() << endl;
                cout << string(76, '-') << endl << endl;

                cout << "Returning to Main Menu..." << endl;
                system("pause");
                system("cls");
                return;
            }
        }

        cout << endl << "Invalid ID!" << endl;

        char tryAgain;

        cout << "Do you want to try again? (Y/N): ";
        cin >> tryAgain;

        cin.ignore();
        tryAgain = toupper(tryAgain);

        if (tryAgain != 'Y') {
            cout << endl << "Returning to Main Menu.." << endl;
            system("pause");
            system("cls");
            return;
        }
    }
}
       
        void removeItem() override {
            string id;

            cout << string(74, '-') << endl;
            cout << "\t\t\t\tRemove Item" << endl;
            cout << string(74, '-') << endl;

            bool itemIDFound = false;

            if (itemCount == 0) {
                cout << endl <<  "There are no items in the inventory!" << endl;
                cout << endl << "Returning to Main Menu..." << endl;
                system("pause");
                system("cls");
                return;
            }

            cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(16) << "Price" << left << setw(20) << "Category" << endl;
            cout << string(74, '-') << endl;

            for (int i = 0; i < itemCount; i++) {
                cout << fixed << setprecision(2) << left << setw(10) << items[i].getID() << left << setw(25) << items[i].getName() << left << setw(12) << items[i].getQuantity() << "P" << left << setw(15) << items[i].getPrice() << left << setw(20) << items[i].getCategory() << endl;
            }

            while (!itemIDFound) {
                cout << string(74, '-') << endl;
                cout << "Input the Item ID: ";
                cin >> id; //need din ata validation

                for (char &c : id) {
                    c = toupper(c);
                }

                for (int i = 0; i < itemCount; i++) {
                    if (id == items[i].getID()) {
                        itemIDFound = true;

                     //To shift the remaining products to the left 
                        for (int j = i; j < itemCount -1; j++) {
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

                cout <<  endl << "Item not found!" << endl;

                char tryAgain;
                cout << endl <<"Do you want to try again? (Y/N): ";
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
            cout << "                           By Category" << endl;
            cout << string(76, '-') << endl;

            if (itemCount == 0) {
                cout << endl << "There are no items in the inventory.\n\n";                 //To display when there are no added products in the inventory
                cout << "Returning to the Inventory Menu...\n";
                system("pause");
                system("cls");
                return;
            }

            do {
                cout << "Categories:\n"
                     << "    Clothing\n"
                     << "    Electronics\n"
                     << "    Entertainment\n\n"; 
                cout << "Category of choice:  ";
                cin >> category;
                category = toUpperCase(category);

                if (category != "CLOTHING" && category != "ELECTRONICS" && category != "ENTERTAINMENT") {
                    cout << endl << "Clothing, Electronics, and Entertainment are the only categories accepted!" << endl << endl;
                }
            } while (category != "CLOTHING" && category != "ELECTRONICS" && category != "ENTERTAINMENT");

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
                                cout << string(76, '-') << endl << "\t\tDisplaying Items by Category" << endl << string(76, '-') << endl;

                                cout << left << setw(10) << "ID" << left << setw(25) << "Name" << left << setw(12) << "Quantity" << left << setw(16) << "Price" << left << setw(20) << "Category" << endl;
                                cout << string(76, '-') << endl;

                                itemFound = true;
                            }
                            
                            string category = items[j].getCategory();
                            double price = items[j].getPrice(); 

                            cout << fixed << setprecision(2) << left << setw(10) << items[j].getID() << left << setw(25) << items[j].getName() << left << setw(12) << items[j].getQuantity() << "P" << left << setw(15) << price << left << setw(20) << category << endl;
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

            if (!categoryFound) {
                cout << "Invalid category!" << endl;
            }

            cout << endl << "Returning to Main Menu..." << endl;
            system("pause");
            system("cls");

        }

        void displayAllItems() override {

            cout << string(76, '-') << endl;
            cout << "                             Display All Items" << endl;
            cout << string(76, '-') << endl;

            if (itemCount == 0) {
                cout << endl << "There are no items in the inventory!" << endl;
            } else {
                cout << left << setw(10) << "ID"
                     << setw(25) << "Name"
                     << setw(12) << "Quantity"
                     << setw(15) << "Price"
                     << setw(20) << "Category" << endl;
                cout << string(76, '-') << endl;

                for (int i = 0; i < itemCount; i++) {
                    cout << fixed << setprecision(2) <<
                    left << setw(10) << items[i].getID()
                         << setw(25) << items[i].getName()
                         << setw(12) << items[i].getQuantity()
                         << setw(15) << fixed << setprecision(2) << items[i].getPrice()
                         << setw(20) << items[i].getCategory()
                         << endl;
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
            cout << "                           Search Item" << endl;
            cout << string(76, '-') << endl;

             if (itemCount == 0) {
                cout << endl << "There are no items in the inventory.\n\n";                     //To display when there are no added products in the inventory
                cout << "Returning to the Inventory Menu...\n";
                system("pause");
                system("cls");
                return;
            }

            bool itemFound = false;

            while (!itemFound) {
                cout << "Input Item ID: ";
                cin >> id;
                id = toUpperCase(id);
                //validation (should still recognize lowercase letters even if initialized product id has a capital letter and numbers)
                
                for (int i = 0; i < itemCount; i++) {
                    if (items[i].getID() == id) {
                    itemFound = true;
                    system("cls");

                    cout << string(76, '-') << endl;
                    cout << "\t\t\t\tSearch Item" << endl;
                    cout << string(76, '-') << endl;

                    cout << left << setw(10) << "ID"
                        << setw(20) << "Name"
                        << setw(10) << "Quantity"
                        << setw(10) << "Price"
                        << setw(15) << "Category" << endl;
                    cout << string(76, '-') << endl;

                    string category = items[i].getCategory();
                    double price = items[i].getPrice(); 
                    cout << fixed << setprecision(2) << left << setw(10) << items[i].getID() << left << setw(25) << items[i].getName() << left << setw(12) << items[i].getQuantity() << "P" << left << setw(15) << price << left << setw(20) << category << endl;

                    cout << string(76, '-') << endl;
                    break;
                }
            }
            if (!itemFound) {
                char tryAgain = 'N';
                cout << "Item not found! Do you want to try again? (Y/N): ";
                cin >> tryAgain;

                if (toupper(tryAgain) == 'Y') {
                    continue;
                }
                else if (toupper(tryAgain) == 'N') {
                    cout << endl << "Returning to Main Menu.." << endl;
                    system("pause");
                    system("cls");
                    return; 
                }
                else {
                    cout << endl << "Only enter 'Y' or 'N'!" << endl << endl;
                }
            }
        }
            cout << endl << "Returning to the Inventory Menu...\n";
            system("pause");
            system("cls");
            
        }

void sortItem() override {
    int sortChoice = 0, orderChoice = 0;

    cout << string(76, '-') << endl;
    cout << "                           Sort Items" << endl;
    cout << string(76, '-') << endl;

    if (itemCount == 0) {
        cout << endl << "There are no items in the inventory.\n\n";
        cout << "Returning to the Inventory Menu...\n";
        system("pause");
        system("cls");
        return;
    }

    cout << "Do you want to sort items? (1 - Yes, 2 - No): ";
    cin >> sortChoice;

    if (sortChoice == 2) {
        cout << "Displaying items in the default order (as added):\n";
        displayAllItems();
        return;
    }

    cout << "Sort by:" << endl
         << "   1 - Quantity" << endl
         << "   2 - Price" << endl;
    cout << "Choice: ";
    cin >> sortChoice;

    if (sortChoice != 1 && sortChoice != 2) {
        cout << "Invalid input for sorting option. Please try again.\n";
        return;
    }

    cout << "\nSort order:" << endl
         << "   1 - Ascending" << endl
         << "   2 - Descending" << endl;
    cout << "Choice: ";
    cin >> orderChoice;

    if (orderChoice != 1 && orderChoice != 2) {
        cout << "Invalid input for sorting order. Please try again.\n";
        return;
    }

    // Sorting using Bubble Sort
    bool swapped;
    for (int i = 0; i < itemCount - 1; i++) {
        swapped = false;
        for (int j = 0; j < itemCount - i - 1; j++) {
            // Sort by Quantity
            if (sortChoice == 1) {
                if ((orderChoice == 1 && items[j].getQuantity() > items[j + 1].getQuantity()) ||
                    (orderChoice == 2 && items[j].getQuantity() < items[j + 1].getQuantity())) {
                    Item temp = items[j];
                    items[j] = items[j + 1];
                    items[j + 1] = temp;
                    swapped = true;
                }
            }
            // Sort by Price
            else if (sortChoice == 2) {
                if ((orderChoice == 1 && items[j].getPrice() > items[j + 1].getPrice()) ||
                    (orderChoice == 2 && items[j].getPrice() < items[j + 1].getPrice())) {
                    Item temp = items[j];
                    items[j] = items[j + 1];
                    items[j + 1] = temp;
                    swapped = true;
                }
            }
        }
        if (!swapped) {
            break;  // Break if no elements were swapped
        }
    }

    // Display sorted items in table format
    cout << left << setw(10) << "ID"
         << setw(25) << "Name"
         << setw(12) << "Quantity"
         << setw(15) << "Price"
         << setw(20) << "Category" << endl;
    cout << string(76, '-') << endl;

    for (int i = 0; i < itemCount; i++) {
        cout << left << setw(10) << items[i].getID()
             << setw(25) << items[i].getName()
             << setw(12) << items[i].getQuantity()
             << setw(15) << fixed << setprecision(2) << items[i].getPrice()
             << setw(20) << items[i].getCategory() << endl;
    }

    cout << "Items sorted successfully!" << endl;
    cout << endl << "Returning to the Inventory Menu...\n";
    system("pause");
    system("cls");
}

       
       void displayLowStockItems() {
            cout << string(76, '-') << endl;
            cout << "                             Low Stock Items" << endl;
            cout << string(76, '-') << endl;

            if (itemCount == 0) {
                cout << endl << "There are no items in the inventory!" << endl;
                cout << endl << "Returning to Main Menu..." << endl;
                system("pause");
                system("cls");
                return;
        }

            bool lowStockFound = false;

            for (int i = 0; i < itemCount; i++) {
                if (items[i].getQuantity() <= 5) {

                    if (!lowStockFound) {
                        cout << left << setw(10) << "ID"
                             << setw(25) << "Name"
                             << setw(12) << "Quantity"
                             << setw(15) << "Price"
                             << setw(20) << "Category" << endl;
                        cout << string(76, '-') << endl;
                        lowStockFound = true;
                    }
                    cout << left << setw(10) << items[i].getID()
                         << setw(25) << items[i].getName()
                         << setw(12) << items[i].getQuantity()
                         << setw(15) << fixed << setprecision(2) << items[i].getPrice()
                         << setw(20) << items[i].getCategory() << endl;
                }
            }

                if (!lowStockFound) {
                cout << endl << "No low stock items found!" << endl;
            } 
                cout << string(76, '-') << endl;
                cout << endl << "Returning to the Inventory Menu...\n";
                system("pause");
                system("cls");    
       }
};

int main () {

    InventorySystem inventory;
    int choice;

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
        cout << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        system("cls");

        switch (choice) {
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
                cout << "Invalid input. Kindly enter numbers 1 to 9 only.\n\n";
                cout << "Returning to the Inventory Menu...\n";
                system("pause");
                system("cls");
        }
    } while (choice != 9);

    return 0;

}