#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <ctime>
#include <fstream>
#include <vector>
#include <list>
#include <iomanip>

using namespace std;

// Global variable declaration
int nextAdminPage = 0;
int nextCustomerPage = 0;
//Vectors to store variable
vector<string>numbers;
vector<string>names;
vector<string>prices;
vector<string>quantities;
vector<string>discounts;
vector<string>taxes;
//Variables holds on information about a specific product
int position;
int productCount;

//Classes
class ShopPages;
// Class handles the requests of users upon starting the program
class ShopApp{
    public:
        bool status;
        int customerReply;
        void adminStartPage(){
            cout<<"Administrator Portal.\
            \n1: Are you new? Create an account?.\
            \n2: Already have an account? Login?. "<<endl;
            int adminReply; // Takes in  user reply
            cout<<">> ";
            cin>>adminReply;
            // checks reply
            if (adminReply == 1){
                ShopApp::createAccount(); // directs user to create an account
            }
            else if(adminReply == 2){
                status = ShopApp::checkAccount(); //Checks if a user has an account
                nextAdminPage = nextAdminPage + 1; // pointer for moving to next page
            }
            else{
                cout<<"Invalid input"<<endl;
            }
        }

        void customerStartPage(){
            cout<<"Hello Customer, what do you want to do?.\
            \n1: Make a purchase?\
            \n2: Lodge a complaint? "<<endl;
            cout<<">> ";
            while(!(cin>>customerReply)){
                cout<<"An error has occurred.\nEnter a number: "<<endl;
                cin.clear(); //clears input
                cin.ignore(123,'\n'); //discards previous input
            }
            if(customerReply == 0 || 1){ //Checks if input is among options
                nextCustomerPage = nextCustomerPage + 1; // pointer for moving to next page
            }else{
                cout<<"Invalid response.Enter correct option."<<endl; //when input is not among options
            }
        }

        // Creates new account for a new admin
        void createAccount(){
            string name;
            int age;
            string id;

            cout<<"Enter age: "<<endl;
            cout<<">> ";
            // checks if input is a number
            while(!(cin>>age)){
                cout<<"An error has occurred.\nEnter a number: "<<endl;
                cin.clear();  //clears input
                cin.ignore(); //discards previous input
            }

            //Takes admin's name
            cin.ignore();
            cout<<"Enter name: "<<endl;
            cout<<">> ";
            getline(cin,name); // passes name to variable

            // generates an id for the admin
            id = "";
            srand(time(NULL));
            for(int i = 0; i < 3; i++){
                stringstream ss;
                ss << rand() %10+0;
                id = id + ss.str();
            }

            //Adding new admins to admin file
            ofstream myFile;
            myFile.open("admin.csv", ios_base::app);
            myFile<<name<<","<<age<<","<<id<<endl;
            myFile.close(); // Closes file after adding data items

            //Prints admin's name and ID number
            cout<<"Name: "<<name<<endl;
            cout<<"ID: "<<id<<endl;
       }

       // Checks admin page if user has an account already
        bool checkAccount(){
            int userId;
            cout<<"Enter your ID Number"<<endl;
            cout<<">> ";

            // Checks is number entered is an int
            while(!(cin>>userId)){
                cout<<"An error has occurred.\nEnter a number: "<<endl;
                cin.clear(); //clears input
                cin.ignore(123,'\n'); //discards previous input
            }

            // opens admin file and creates a vector data structure
            ifstream myFile;
            myFile.open("admin.csv");
            vector<int>record;

            // Variable to hold items of a line in the file
            string name;
            string age;
            string id;
            while(myFile.good()){
                getline(myFile,name,',');
                getline(myFile,age,',');
                getline(myFile,id,'\n');

            // Takes ID's from the file and converts them into integers to append to the vector data structure
                int num = 0;
                stringstream ss;
                ss<<id;
                ss>>num;
                record.push_back(num);

            }
            // Closes file and removes excess last item
            myFile.close();
            int counter = 0;
            record.pop_back();

            // Checks if user has an account
            for(int i = 0; i < record.size(); i++){
                if(userId== record[i]){
                    counter = counter + 1; // Increment when account is found
                }
            }
            // returns verification status
            if(counter == 1){
                return true;
            }else{
                return false;
            }
       }
};


// Admins page for working on items of the shop
class ShopPages{
    public:
        // Gives admin login status of user
        void adminHomePage(ShopApp obj){
            if(obj.status == 0){
                cout<<"Account not found. Please create new account."<<endl;
            }else{
                cout<<"Account Verified.\n"<<endl;
                // Prints a menu to the admin
                cout<<"Welcome to the Admin page of Maxxies Shopping Center."<<endl;
                cout<<"Please select option:\
                \n1: Create product\
                \n2: Modify product\
                \n3: View available product(s)\
                \n4: Delete product\
                \n5: Read complaints\
                \n6: Delete complaints"<<endl;
                // takes an input choice from the admin
                int adminChoice;
                while(!(cin>>adminChoice)){
                    cout<<"An error has occurred.\nEnter a number(1-4): "<<endl;
                    cin.clear(); //clears input
                    cin.ignore(123,'\n'); //discards previous input
                }

                //Processing the choice of the admin
                switch(adminChoice){
                    //Creates product
                    case 1:
                        {
                        //Product variable declaration
                        string productNumber;
                        string productName;
                        double productPrice;
                        int productQuantity;
                        double productTax;
                        double productDiscount;

                        cout<<"Enter correct data for products"<<endl;
                        cout<<"Product price :"<<endl;
                        cout<<">> ";
                        while(!(cin>>productPrice)){
                            cout<<"An error has occurred.\nEnter a number: "<<endl;
                            cin.clear();  //clears input
                            cin.ignore(); //discards previous input
                        }

                        cin.ignore();
                        cout<<"Product name: "<<endl;
                        cout<<">> ";
                        getline(cin,productName);

                        cout<<"Product quantity: "<<endl;
                        cout<<">> ";
                        cin>>productQuantity;

                        cout<<"Product tax: "<<endl;
                        cout<<">> ";
                        cin>>productTax;

                        cout<<"Product discount: "<<endl;
                        cout<<">> ";
                        cin>>productDiscount;

                        // generates a number for product
                        productNumber = "";
                        srand(time(NULL));
                        for(int i = 0; i < 2; i++){
                            stringstream ss;
                            ss << rand() %10;
                            productNumber = productNumber + ss.str();
                        }

                        //Adds new product to product file
                        ofstream myFile;
                        myFile.open("product_menu.csv", ios_base::app);
                        myFile<<
                        productNumber<<","<<
                        productName<<","<<
                        productPrice<<","<<
                        productQuantity<<","<<
                        productDiscount<<","<<
                        productTax<<endl;

                        myFile.close(); // Closes file after adding data items

                        cout<<"Product created successfully"<<endl;
                        break;
                        }

                    //modifies product
                    case 2:
                        {
                        int productId;
                        cout<<"Enter the number of the product to be modified: "<<endl;
                        cout<<">> ";
                        // Checks if number entered is an int
                        while(!(cin>>productId)){
                            cout<<"An error has occurred.\nEnter a number: "<<endl;
                            cin.clear(); //clears input
                            cin.ignore(123,'\n'); //discards previous input
                        }

                        ShopPages::extractItems(productId);
                        //Handles modifications
                        ShopPages::modifyProduct();
                        cout<<"Product modified."<<endl;
                        break;
                        }

                    // View products
                    case 3:
                        {
                        //Displays items
                         ShopPages::displayItems();
                        break;
                        }

                    //Delete product
                    case 4:
                        {
                        int productId;
                        cout<<"Enter the number of the product to be deleted: "<<endl;
                        cout<<">> ";
                        // Checks if number entered is an int
                        while(!(cin>>productId)){
                        cout<<"An error has occurred.\nEnter a number: "<<endl;
                        cin.clear(); //clears input
                        cin.ignore(123,'\n'); //discards previous input
                        }
                        //calls function to verify the product and get its position
                        ShopPages::extractItems(productId);

                        if(productCount == 0){
                            cout<<"Product not available"<<endl; //When product is not in the list
                        }else{
                            //writes new items into the item file
                            ShopPages::writeToFile(2);
                            cout<<"Product deleted."<<endl;
                        }
                        break;
                        }

                    //Read complaints from file
                    case 5:
                        {
                        // Reads complaint from file and prints to admin
                        ifstream newFile;
                        newFile.open("complaint.txt",ios_base::in);
                        string text;
                        cout<<"Customer feedbacks: "<<endl;
                        while(newFile.good()){
                            getline(newFile,text,'\n');
                            cout<<"\n"<<text<<endl;
                        }
                        newFile.close();
                        break;
                        }

                    //Clears complaints from file
                    case 6:
                        {
                        // Clears complaints from file
                        ifstream newFile;
                        newFile.open("complaint.txt",ofstream::out | ofstream::trunc);
                        newFile.close();
                        cout<<"Feedbacks deleted."<<endl;
                        break;
                        }
                    default:
                        cout<<"Choice not available. Enter correct input"<<endl;
                    }
                }
        }
        //Customer page for user
        void customerHomePage(ShopApp obj){
            if(obj.customerReply == 1){
                // Displays items for customers
                ShopPages::displayItems();
                //variable to hold number of times a customer wants to shop
                int purchaseNumber;
                cout<<"How many different purchases do you want to make?"<<endl;
                while(!(cin>>purchaseNumber)){
                    cout<<"An error has occurred.\nEnter a number: "<<endl;
                    cin.clear(); //clears input
                    cin.ignore(123,'\n'); //discards previous input
                }
                for(int i =0; i < purchaseNumber; i++){
                   //Takes the id of desired product
                    cout<<"Enter the ID of the product: "<<endl;
                    int productNumber;
                    while(!(cin>>productNumber)){
                        cout<<"An error has occurred.\nEnter a number: "<<endl;
                        cin.clear(); //clears input
                        cin.ignore(123,'\n'); //discards previous input
                    }
                    //Clears vectors before extraction
                    numbers.clear();
                    names.clear();
                    prices.clear();
                    quantities.clear();
                    discounts.clear();
                    taxes.clear();
                    //Extracts items ready for modifications after sale
                    ShopPages::extractItems(productNumber);

                    // checks if product is available
                    if(productCount == 0){
                        cout<<"Product not available"<<endl;
                    }
                    else{ //when product is available
                        double price;
                        stringstream sp;
                        sp<<prices[position];
                        sp>>price;

                        double tax;
                        stringstream st;
                        st<<taxes[position];
                        st>>tax;

                        double discount;
                        stringstream spo;
                        spo<<discounts[position];
                        spo>>discount;

                        int quantity;
                        stringstream ss;
                        ss<<quantities[position];
                        ss>>quantity;

                        cout<<"How many would you like to get?"<<endl;
                        int productQuantity;
                        while(!(cin>>productQuantity)){
                            cout<<"An error has occurred.\nEnter a number: "<<endl;
                            cin.clear(); //clears input
                            cin.ignore(123,'\n'); //discards previous input
                        }

                        if(quantity < productQuantity && quantity != 0){ //comapares available quantity and requested quantity
                            //When available quantity is less
                            cout<<"Sorry, requested quantity of product not available"<<endl;
                            cout<<"Would you want the remaining quantity of "<<quantities[position]<<".(Yes/No)"<<endl;
                            string response;
                            cin.ignore();
                            getline(cin,response);
                            //Asks if user wants quantity available
                            if(response == "YES" || response == "Y" || response == "y"){
                                //Generates price
                                string newPrice;
                                stringstream snp;
                                snp<<(((price*tax)+price)-discount)*quantity;
                                newPrice = snp.str();
                                //Converts the requested quantity to string
                                string newQuantity;
                                stringstream nq;
                                nq<<quantity;
                                newQuantity = nq.str();

                                ofstream customerInvoice;
                                customerInvoice.open("invoice.txt", ios_base::app);
                                customerInvoice<<" Maxxies Shopping Center."<<endl;
                                customerInvoice<<"------------------------------------------"<<endl;
                                customerInvoice<<"           Customer Invoice                "<<endl;
                                customerInvoice<<"------------------------------------------"<<endl;
                                customerInvoice<<"Items purchased:"<<endl;
                                customerInvoice<<"    Item:     "+ names[position] +""<<endl;
                                customerInvoice<<"    Quantity: "+ newQuantity +""<<endl;
                                customerInvoice<<"    Amount:   GHS"+newPrice +""<<endl;
                                customerInvoice<<"    Tax:      "+taxes[position]+""<<endl;
                                customerInvoice<<"    Discount: "+discounts[position]+""<<endl;
                                customerInvoice<<"Thanks for shopping with us......."<<endl;
                                customerInvoice.close();
                                //Change the product quantity to 0 after sale
                                quantities[position] = "0";
                                //writes to file
                                ShopPages::writeToFile(1);

                                cout<<"Your invoice has been generated. Proceed to the invoice.txt to claim it. Thank You"<<endl;
                            }
                            else{
                                cout<<"Thanks for shopping with us."<<endl;
                            }
                        //When the quantity of the product is zero
                        }else if(quantity == 0){
                            cout<<"Sorry, product has run down."<<endl;
                        }else{ //When available quantity is more than requested amount
                            string newPrice;
                            stringstream snp;
                            snp<<(((price*tax)+price)-discount) * productQuantity;
                            newPrice = snp.str();

                            //Converts the requested quantity to string
                            string newQuantity;
                            stringstream nq;
                            nq<<productQuantity;
                            newQuantity = nq.str();

                            ofstream customerInvoice;
                            customerInvoice.open("invoice.txt", ios_base::app);
                            customerInvoice<<" Maxxies Shopping Center."<<endl;
                            customerInvoice<<"------------------------------------------"<<endl;
                            customerInvoice<<"           Customer Invoice                "<<endl;
                            customerInvoice<<"------------------------------------------"<<endl;
                            customerInvoice<<"Items purchased:"<<endl;
                            customerInvoice<<"    Item:     "+ names[position] +""<<endl;
                            customerInvoice<<"    Quantity: "+ newQuantity +""<<endl;
                            customerInvoice<<"    Amount:   GHS"+newPrice +""<<endl;
                            customerInvoice<<"    Tax:      "+taxes[position]+""<<endl;
                            customerInvoice<<"    Discount: "+discounts[position]+""<<endl;
                            customerInvoice<<"Thanks for shopping with us......."<<endl;
                            customerInvoice.close();
                            //sets a new quantity for the product after sales
                            quantity = quantity - productQuantity;
                            stringstream sq;
                            sq<<quantity;
                            //updates the new quantities
                            quantities[position]=sq.str();
                            //writes to file
                            ShopPages::writeToFile(1);

                            cout<<"Your invoice has been generated. Proceed to the invoice.txt to claim it. Thank You"<<endl;
                        }
                    }
                }

            }
            else{ //Takes complaints from users
                cout<<"Enter your complaint(Type Done on a new line to exist):"<<endl;
                string complaint;
                string line;

                //Takes multipl lines of input string
                while (getline(cin, line))
                {
                    if (line == "Done")
                        break;
                    complaint += line;
                }
                //writes complaints into file
                ofstream newFile;
                newFile.open("complaint.txt", ios_base::app);
                newFile<<complaint<<endl;
                newFile.close();
                cout<<"Your complaint has been received. Thanks for the feedback."<<endl;

            }
        }

        //function displays items
        void displayItems(){
            // Opens file to read product data
            ifstream myFile;
            myFile.open("product_menu.csv",ios_base::in);
            //Local variables to hold product data
            string number;
            string name;
            string price;
            string quantity;
            string tax;
            string discount;

            cout<<setfill('-')<<setw(10)<<"ITEMS"<<setfill('-')<<setw(10)<<"\n";
            while(myFile.good()){
                getline(myFile,number,',');
                getline(myFile,name,',');
                getline(myFile,price,',');
                getline(myFile,quantity,',');
                getline(myFile,discount,',');
                getline(myFile,tax,'\n');
                //Prints out product data
                if(number == ""){ //prevents printing same item
                    continue;
                }else{
                    cout<<left<<setw(10)<<"ID :        "<<number<<"\n";
                    cout<<left<<setw(10)<<"Name :      "<<name<<"\n";
                    cout<<left<<setw(10)<<"Price :     GHS "<<price<<"\n";
                    cout<<left<<setw(10)<<"Quantity :  "<<quantity<<"\n";
                    cout<<left<<setw(10)<<"Discount :  "<<discount<<"\n";
                    cout<<left<<setw(10)<<"Tax :       "<<tax<<"\n";
                    cout<<setfill('-')<<setw(50)<<"-"<<endl;
                }
            }
            myFile.close();
        }

        //Extracts, checks whether an item is there and and update the position of the item
        void extractItems(int x){
            ifstream itemFile;
            itemFile.open("product_menu.csv", ios_base::in);

            // variables to hold contents of files when reading
            string number;
            string name;
            string price;
            string quantity;
            string discount;
            string tax;

            while(!itemFile.eof()){
                getline(itemFile,number,',');
                getline(itemFile,name,',');
                getline(itemFile,price,',');
                getline(itemFile,quantity,',');
                getline(itemFile,discount,',');
                getline(itemFile,tax,'\n');

                numbers.push_back(number);
                names.push_back(name);
                prices.push_back(price);
                quantities.push_back(quantity);
                discounts.push_back(discount);
                taxes.push_back(tax);
            }
            productCount = 0;
            position = -1;

            // Checks if product is in the list
            for(int i = 0; i < numbers.size()-1; i++){
                int num = 0;
                stringstream ss;
                ss<<numbers[i];
                ss>>num;
                if(x == num){
                    position = i; // Updates the position on the product in the list
                    productCount = productCount + 1;
                }
            }
            itemFile.close();
        }

        // Makes modifications on a requested product
        void modifyProduct(){
            if(productCount == 0){
            cout<<"Product not available"<<endl; //When product is not in the list
            }else{
            // menu for modifying product
            cout<<"What do you want to modify from the product?"<<endl;
            cout<<"\nModify Product.\
            \n1: Name of product\
            \n2: Price of product\
            \n3: Quantity of product available \
            \n4: Tax on product\
            \n5: Discount on product\
            \n6: Modify whole product"<<endl;

            //gets suitable response from user
            int response;
            while(!(cin>>response) || response == 0){
                cout<<"An error has occurred.\nEnter correct option: "<<endl;
                cin.clear(); //clears input
                cin.ignore(123,'\n'); //discards previous input
            }
            if(response == 1){ //when response is to change name of the product
                string temp;
                cin.ignore();
                cout<<"New name:"<<endl;
                cout<<">> ";
                getline(cin,temp);
                names[position] = temp;
            }
            else if(response == 2){ //when response is to change price of the product
                string temp;
                cin.ignore();
                cout<<"New price:"<<endl;
                cout<<">> ";
                getline(cin,temp);
                prices[position] = temp;
            }
            else if(response == 3){ //when response is to change quantity of the product
                string temp;
                cin.ignore();
                cout<<"New quantity:"<<endl;
                cout<<">> ";
                getline(cin,temp);
                quantities[position] = temp;
            }
             else if(response == 4){ //when response is to change tax on the product
                string temp;
                cin.ignore();
                cout<<"New tax:"<<endl;
                cout<<">> ";
                getline(cin,temp);
                taxes[position] = temp;
            }
             else if(response == 5){ //when response is to change discount on the product
                string temp;
                cin.ignore();
                cout<<"New discount:"<<endl;
                cout<<">> ";
                getline(cin,temp);
                discounts[position] = temp;
             }
            else if(response == 6){  //when modifying the whole product data
                //local variables to store new inputs for product modification
                string productName;
                string productPrice;
                string productQuantity;
                string productTax;
                string productDiscount;

                //makes update on each product data
                cin.ignore();
                cout<<"Name of product: "<<endl;
                cout<<">> ";
                getline(cin,productName);
                names[position]=productName;

                cout<<"Price of product :"<<endl;
                cout<<">> ";
                getline(cin,productPrice);
                prices[position]=productPrice;

                cout<<"Quantity of product available: "<<endl;
                cout<<">> ";
                getline(cin,productQuantity);
                quantities[position]=productQuantity;

                cout<<"Tax on product: "<<endl;
                cout<<">> ";
                getline(cin,productTax);
                taxes[position]=productTax;

                cout<<"Discount on product: "<<endl;
                cout<<">> ";
                getline(cin,productDiscount);
                discounts[position]=productDiscount;
            }else{
                cout<<"Invalid input. Try again."<<endl; // when there is an invalid input
            }
            ShopPages::writeToFile(1);
            }
        }

        //Writes items into file
        void writeToFile(int x){
            //writes new items into the item file
            ofstream newFile;
            newFile.open("product_menu.csv", ios_base::trunc);
            if(x == 1){                    //writes for a modified product so not to add excess
                for(int i = 0; i < numbers.size()-1;i++){
                    if(numbers[i] == ""){
                        continue;
                    }else{
                        newFile<<
                        numbers[i]<<","<<
                        names[i]<<","<<
                        prices[i]<<","<<
                        quantities[i]<<","<<
                        discounts[i]<<","<<
                        taxes[i]<<endl;
                    }
                }
            }else{   // writes for when product it to be deleted
                for(int i = 0; i < numbers.size()-1;i++){
                    if(i == position){
                        continue;
                    }else{
                        newFile<<
                        numbers[i]<<","<<
                        names[i]<<","<<
                        prices[i]<<","<<
                        quantities[i]<<","<<
                        discounts[i]<<","<<
                        taxes[i]<<endl;
                    }
                }
            }
            newFile.close();
        }
};


int main(){
    //class instantiations
    ShopApp shop;
    ShopPages admin;
    //welcome message
    cout<<"WELCOME TO MAXXIES SHOPPING CENTER"<<endl;
    cout<<setfill('-')<<setw(50)<<"-"<<endl;
    cout<<"\n"<<"How may we help you?\
                \n1: Administrator\
                \n2: Customer"<<endl;
    int reply;
    while(!(cin>>reply)){
        cout<<"An error has occurred.\nEnter a number: "<<endl;
        cin.clear(); //clears input
        cin.ignore(123,'\n'); //discards previous input
    }
    if (reply == 1){
        shop.adminStartPage(); //Directs user to the admin start page
        }
    else if (reply == 2){
        shop.customerStartPage();   //Directs user to the customer start page
        }
    else{
        cout<< "Follow instructions. Input must be in the range of options given."<<endl;
        }
    // Enables the next page for the admin
    if(nextAdminPage == 1){
        admin.adminHomePage(shop);
    }
    // Enables the next page for the custoemr
    else if(nextCustomerPage == 1){
        admin.customerHomePage(shop);
    }
    return 0;
}
