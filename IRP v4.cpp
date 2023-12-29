#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>
#include <set>

using namespace std;

void clear() {
#ifdef _WIN32
  (void)system("cls"); // For Windows
#else
  (void)system("clear"); // For Linux and macOS
#endif
}

void pressKey() {
  cout << "\npress enter to continue!" << endl;
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  getchar();
  clear();
  return;
}

class T_shirt {

private:
  string name;
  string size;
  string color;
  int quantity;
  double price;

public:
  string getName() const { return name; }
  string getSize() const { return size; }
  int getQuantity() const { return quantity; }
  double getPrice() const { return price; }
  string getColor() const { return color; }

  T_shirt() {}

  T_shirt(string name1, string size1, string color1, int quantity1,
          double price1) {
    name = name1;
    size = size1;
    color = color1;
    quantity = quantity1;
    price = price1;
  }

  void setName(string name1) { name = name1; }

  void setSize(string size1) { size = size1; }

  void setColor(string color1) { color = color1; }

  void setQuantity(int quantity1) { quantity = quantity1; }

  void setPrice(double price1) { price = price1; }
};

class Order {

private:
  double price;
  string buyPName;
  int buyQuantity;
  string phone;
  string address;
  string name;
  double totalPrice;
  string orderID;

public:
  string getBuyName() const { return buyPName; }
  double getPrice() const { return price; }
  int getBuyQuantity() const { return buyQuantity; }
  string getName() const { return name; }
  double getTotalPrice() const { return totalPrice; }
  string getPhone() const { return phone; }
  string getAddress() const { return address; }
  string getOrderID() const { return orderID; }

  Order() {}

  Order(string name1, string phone1, int quantity1, string address1,
        string buyName1, double price1, double totalPrice1, string orderID1) {
    name = name1;
    phone = phone1;
    address = address1;
    buyPName = buyName1;
    totalPrice = totalPrice1;
    price = price1;
    orderID = orderID1;
    buyQuantity = quantity1;
  }

  void setName(string name1) { name = name1; }
  void setBuyQuantity(int quantity1) { buyQuantity = quantity1; }
  void setPrice(double price1) { price = price1; }
  void setPhone(string phone1) { phone = phone1; }
  void setAddress(string address1) { address = address1; }
  void setBuyPName(string buyName1) { buyPName = buyName1; }
  void setTotalPrice(double totalPrice1) { totalPrice = totalPrice1; }
  void setOrderID(string orderID1) { orderID = orderID1; }
};

class Store {

private:
  map<string, T_shirt> t_shirts;
  map<string, Order> buy;
  string userName;
  string userAdress;
  string userPhone;
  string userColor;
  string userSize;
  string userBuyName;

public:
  int counter = 0;

  void init() {
    ifstream t_shirtsFile("Product_Catalog");

    if (!t_shirtsFile.is_open()) {
      cout << "\nerror opening file!!" << endl;
      return;
    }

    string T_Shirts;
    while (getline(t_shirtsFile, T_Shirts)) {
      istringstream iss(T_Shirts);
      string name, color, size;
      int quantity;
      double price;

      if (!(iss >> name >> color >> size >> quantity >> price) || iss.fail()) {
        cout << "\nError reading values from the file!\n";
        break;
      }

      // Create a t_shirt object with the extracted values
      class T_shirt shirt(name, size, color, quantity, price);
      t_shirts[name] = shirt;
    }

    ifstream orderFile("Purchase_Catalog");

    if (!orderFile.is_open()) {
      cout << "\nerror opening file!!" << endl;
      return;
    }

    string Order;
    while (getline(orderFile, Order)) {
      istringstream iss(Order);
      string name, phone, address, buyName, orderID;
      string quantity;
      string orderPrice;

      // Check if all values are read successfully
      if (!(getline(iss, orderID, '\t') && getline(iss, name, '\t') &&
            getline(iss, phone, '\t') && getline(iss, quantity, '\t') &&
            getline(iss, address, '\t') && getline(iss, buyName, '\t') &&
            getline(iss, orderPrice)) ||
          iss.fail()) {
        cerr << "Error reading values from the file at line: " << Order << "\n";

        break;
      }

      class Order orderObj(name, phone, stoi(quantity), address, buyName, 0.0,
                           stod(orderPrice), orderID);

      buy[orderID] = orderObj;
      counter = counter + 1;
    }
  }

  void updateProduct() {
    clear();
    string updateName;
    string updateAspect;
    cout << "\nwhat product do you want to update?\n";
    cin >> updateName;
    cout << "\nwhat aspect do you want to update?\n";
    cin >> updateAspect;
    cout << "\nwhat do you want to update it to?\n";
    if (updateAspect == "price") {
      double newPrice;
      cin >> newPrice;
      t_shirts[updateName].setPrice(newPrice);
      cout << "\nproduct updated sucessfully!!" << endl;
    } else if (updateAspect == "quantity") {
      int newQuantity;
      cin >> newQuantity;
      t_shirts[updateName].setQuantity(newQuantity);
      cout << "\nproduct updated sucessfully!!" << endl;
    } else if (updateAspect == "color") {
      string newColor;
      cin >> newColor;
      t_shirts[updateName].setColor(newColor);
      cout << "\nproduct updated sucessfully!!" << endl;
    } else if (updateAspect == "size") {
      string size;
      cin >> size;
      t_shirts[updateName].setSize(size);
      cout << "\nproduct updated sucessfully!!" << endl;
    } else if (updateAspect == "name") {
      string name;
      cin >> name;
      t_shirts[updateName].setName(name);
      cout << "\nproduct updated sucessfully!!" << endl;
    } else {
      cout << "\nerror!\n";
    }
  }

  void removeProduct() {
    clear();
    cout << "\nwhat product do you want to remove?\n";
    string name;
    cin >> name;

    if (t_shirts.find(name) != t_shirts.end()) {
      t_shirts.erase(name);
      cout << "\nproduct removed sucessfully!!" << endl;
    } else {
      cout << "\nthe product deos not exist!\n";
      return;
    }
  }

  void addProduct(string name, int quantity, bool avail, double price,
                  string size, string color) {

    if (t_shirts.find(name) != t_shirts.end()) {
      cout << "\nThis product already exists!\n";
      return; // Exit the function to avoid adding a duplicate product
    } else {
      // Additional input validation
      if (quantity < 0 || price < 0) {
        cout << "\nInvalid quantity or price! Product not added.\n";
        return; // Exit the function due to invalid input
      }

      t_shirts[name] = T_shirt(name, size, color, quantity, price);
      cout << "\nProduct added successfully!\n";
    }
  }

  void seeAll_Products() {
    clear();
    for (auto i = t_shirts.begin(); i != t_shirts.end(); i++) {
      cout << "\n";
      T_shirt &data = t_shirts[i->first];
      cout << "name: " << data.getName() << endl;
      cout << "color: " << data.getColor() << endl;
      cout << "size: " << data.getSize() << endl;
      cout << "quantity left: " << data.getQuantity() << endl;
      cout << "price: " << data.getPrice() << endl;
    }
  }

  void seeAll_Orders() {
    clear();
    for (auto i = buy.begin(); i != buy.end(); i++) {
      cout << "\n";
      Order &data = buy[i->first];
      cout << "order id: " << i->first << endl;
      cout << "user name: " << data.getBuyName() << endl;
      cout << "user phone: " << data.getPhone() << endl;
      cout << "user adress: " << data.getAddress() << endl;
      cout << "product bought: " << data.getName() << endl;
      cout << "order quantity: " << data.getBuyQuantity() << endl;
      cout << "price paid: " << data.getTotalPrice() << endl;
    }
  }

  void findOrders(string order_id) {
    clear();
    if (buy.find(order_id) != buy.end()) {
      cout << "\norder found!!\n";
      Order &data = buy[order_id];
      cout << "order id: " << order_id << endl;
      cout << "user name: " << data.getBuyName() << endl;
      cout << "user phone: " << data.getPhone() << endl;
      cout << "user adress: " << data.getAddress() << endl;
      cout << "product bought: " << data.getName() << endl;
      cout << "order quantity: " << data.getBuyQuantity() << endl;
      cout << "price paid: " << data.getTotalPrice() << endl;
    } else {
      cout << "\norder not found!!";
    }
  }

  void findProduct(string name) {
    clear();
    if (t_shirts.find(name) != t_shirts.end()) {
      cout << "\nproduct found!\n";
      T_shirt &data = t_shirts[name];
      cout << "\nname: " << data.getName() << endl;
      cout << "\ncolor: " << data.getColor() << endl;
      cout << "\nsize: " << data.getSize() << endl;
      cout << "\nquantity left: " << data.getQuantity() << endl;
      cout << "\nprice: " << data.getPrice() << endl;
    } else {
      cout << "\nproduct not found!\n";
    }
  }

  void buyProduct(string name, int userQuantity, string userBuyName,
                  string userPhone, string userAddress) {
    clear();
    if (t_shirts.find(name) == t_shirts.end()) {
      cout << "\nwanted product not found!\n";
      return;
    }

    T_shirt &data = t_shirts[name];
    if (data.getQuantity() < 1) {
      cout << "\nproduct out of stock\n";
      return;
    }

    cout << "\nname: " << data.getName() << endl;
    cout << "\ncolor: " << data.getColor() << endl;
    cout << "\nsize: " << data.getSize() << endl;
    cout << "\nprice: " << data.getPrice() << endl;
    string answer;
    cout << "\nis this your wanted product?\n";
    cin >> answer;

    if (answer == "yes") {

      cout << "\nproduct ordered!\n";
      buy[to_string(counter)] =
          Order(name, userPhone, userQuantity, userAddress, userBuyName,
                t_shirts[name].getPrice(),
                t_shirts[name].getPrice() * userQuantity, to_string(counter));
      data.setQuantity(data.getQuantity() - userQuantity);
      cout << "\nyour order id: " << counter << endl;
      counter = counter + 1;

    } else if (answer == "no") {
      cout << "\ndo you want to re-enter the product?\n";
      cin >> answer;
      if (answer == "yes") {
        cout << "\nplease re-enter product name: \n";
        cin >> name;
        buyProduct(name, userQuantity, userBuyName, userPhone, userAddress);
      }
    } else {
      cout << "\ninvalid answer!\n";
    }
  }

  int orderIDCounter = counter + 1;

  string generateOrderID() {
    return to_string(orderIDCounter);
    orderIDCounter = orderIDCounter + 1;
  }

  void productAnalysis() {
    set<string>products;
    for (const auto &data : buy) {
      products.insert(data.second.getName());
    }
    string greatestBought = "none";
    int greatestCount = 0;
    vector<string> conversion;
    for (const auto &entry : buy) {
      conversion.push_back(entry.second.getName());
    }
    string currentName = "";
    int currentCount = 0;
    for (const auto& element : products) {
      currentName = element;
      for (int j = 0; j < conversion.size(); j++) {
        if (currentName == conversion[j]) {
          currentCount = currentCount + 1;
        }
      }
      if (currentCount > greatestCount) {
        greatestCount = currentCount;
        greatestBought = currentName;
      }
      currentCount = 0;
    }
    cout << "\nThe product bought the most is: " << greatestBought << endl;
    string leastBought = "";
    long leastCount = 1000000000000000000;
    int currentCounter = 0;
    string currentIdentity = "";
    for (const auto& element : products) {
      currentIdentity = element;
      for (int j = 0; j < conversion.size(); j++) {
        if (currentIdentity == conversion[j]) {
          currentCounter = currentCounter + 1;
        }
      }
      if (currentCounter < leastCount) {
        leastCount = currentCounter;
        leastBought = currentIdentity;
      }
      currentCounter = 0;
    }


    cout << "\nThe Least bought product is: " << leastBought << endl;
  }

  void saveProduct() {
    ofstream outputFile("Product_Catalog", std::ios::out | std::ios::trunc);

    if (!outputFile.is_open()) {
      cout << "\nerror opening file\n";
      return;
    }

    for (const auto &re : t_shirts) {
      outputFile << re.second.getName() << "\t" << re.second.getColor() << "\t"
                 << re.second.getSize() << "\t" << re.second.getQuantity()
                 << "\t" << re.second.getPrice() << "\n";
    }

    outputFile.close();
  }

  void saveOrder() {
    ofstream outputFile("Purchase_Catalog", std::ios::out | std::ios::trunc);

    if (!outputFile.is_open()) {
      cout << "\nError opening file\n";
      return;
    }

    for (const auto &re : buy) {
      outputFile << re.second.getOrderID() << "\t" << re.second.getName()
                 << "\t" << re.second.getPhone() << "\t"
                 << re.second.getBuyQuantity() << "\t" << re.second.getAddress()
                 << "\t" << re.second.getBuyName() << "\t"
                 << re.second.getTotalPrice() << "\n";
    }
  }
};

int main() {

  Store s;
  s.init();

  cout << "Welcome to T-shirt shop!\n";
  cout << "\nenter username: ";
  string username;
  cin >> username;
  cout << "\nenter password: ";
  string password;
  cin >> password;
  if (username == "admin" && password == "qwerty") {
    cout << "\nwelcome!\n";
    clear();
    int choice;
    do {
      clear();
      cout << "1. add product" << endl;
      cout << "2. buy product" << endl;
      cout << "3. update product" << endl;
      cout << "4. remove product" << endl;
      cout << "5. find product" << endl;
      cout << "6. find order" << endl;
      cout << "7. see all products" << endl;
      cout << "8. see all orders" << endl;
      cout << "9. see product analysis" << endl;
      cout << "10. save and exit" << endl << endl;
      cin >> choice;

      switch (choice) {
      case 1: {
        clear();
        cin.ignore();
        cout << "enter product name: " << endl;
        string name;
        getline(cin, name);
        cout << "\nenter product color: " << endl;
        string color;
        cin >> color;
        cout << "\nenter product size: " << endl;
        string size;
        cin >> size;
        cout << "\nenter product quantity: " << endl;
        int quantity;
        cin >> quantity;
        cout << "\nenter product price: " << endl;
        double price;
        cin >> price;
        s.addProduct(name, quantity, true, price, size, color);
        pressKey();
        break;
      }
      case 2: {
        clear();
        cin.ignore();
        cout << "\nenter product name: " << endl;
        string name1;
        getline(cin, name1);

        cout << "\nenter wanted quantity: " << endl;
        int quantity1;
        cin >> quantity1;
        cin.ignore();

        cout << "\nenter your name: " << endl;
        string buyerName;
        getline(cin, buyerName);

        cout << "\nenter your phone number: " << endl;
        string phoneNumber;
        getline(cin, phoneNumber);

        cout << "\nenter your address: " << endl;
        string address;
        getline(cin, address);

        s.buyProduct(name1, quantity1, buyerName, phoneNumber, address);
        pressKey();
        break;
      }

      case 3: {
        clear();
        s.updateProduct();
        pressKey();
        break;
      }

      case 4: {
        clear();
        s.removeProduct();
        pressKey();
        break;
      }

      case 5: {
        clear();
        cout << "\nenter the product name you want to find: " << endl;
        string inputName;
        cin >> inputName;
        s.findProduct(inputName);
        pressKey();
        break;
      }

      case 6: {
        clear();
        string inputID;
        cout << "\nenter the order ID you want to find: " << endl;
        cin >> inputID;
        s.findOrders(inputID);
        pressKey();
        break;
      }

      case 7: {
        clear();
        s.seeAll_Products();
        pressKey();
        break;
      }

      case 8: {
        clear();
        s.seeAll_Orders();
        pressKey();
        break;
      }

      case 9: {
        clear();
        s.productAnalysis();
        pressKey();
        break;
      }

      case 10: {
        clear();
        s.saveOrder();
        s.saveProduct();
      }
      }

    } while (choice != 10);

  }

  else {
    cout << "\ninvalid username or password\n";
    return 0;
  }
  return 0;
}