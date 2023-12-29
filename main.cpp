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

  
};

int main() {

  Store s;

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
      cout << "2. update product" << endl;
      cout << "3. remove product" << endl;
      cout << "4. exit" << endl;
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
        s.updateProduct();
        pressKey();
        break;
      }

      case 3: {
        clear();
        s.removeProduct();
        pressKey();
        break;
      }


      }

    } while (choice != 4);

  }

  else {
    cout << "\ninvalid username or password\n";
    return 0;
  }
  return 0;
}