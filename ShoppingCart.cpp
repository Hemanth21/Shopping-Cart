#include "iostream"
#include "algorithm"
#include "iomanip"
#include "cmath"
#include "fstream"

using namespace std;

int qty;
int price;
string name;
string cname;
string mobno;

int main();

int swapfiles(){
  ofstream fp1;
  fstream fp;
  string h;
  fp1.open("stock.txt",ios::trunc);
  fp.open("temp.txt");
  while(!fp.eof()){
    fp >> name;
    fp >> qty;
    fp >> price;
    if(fp.eof())break;
    fp1 << name << "  ";
    fp1 << qty <<  "  ";
    fp1 << price << "\n";
    }
  fp.close();
  fp1.close();
  fp1.open("temp.txt",ios::trunc);
  fp1.close();
  return 0;
}


int findproduct(string s){
  ifstream fp;
  string productname;
  fp.open("stock.txt");
  while(!fp.eof()){
    fp >> productname;
    if(productname==s)
       return 1;
  }
  fp.close();
  return 0;
}


int addtocart(){
  string s;
  string pname;
  int nqty,flag=0;
  fstream fp,fp1,fp2;
  fp1.open("bill.dat",ios::app);
  fp2.open("temp.txt",ios::app);
  cout << "Enter the Product Name:";
  cin  >> name;
  if(findproduct(name)){
    cout << "Enter the Product Quantity:";
    cin  >> nqty;
    fp.open("stock.txt");
    while(!fp.eof()){
    fp >> pname;
    fp >> qty;
    fp >> price;
    if(fp.eof())break;
    if(name==pname ){
      if(qty-nqty>=0){
      qty=qty-nqty;
      int pr=nqty*price;
      fp1 << pname << " ";
      fp1 << nqty <<  " ";
      fp1 << pr << "\n";
    }
    else
      cout << "\n" << "Requested Quantity is not available!" << "\n\n";
   }
  fp2 << pname << " ";
  fp2 << qty << " ";
  fp2 << price << "\n";
  }
}
  else
      cout << "Item Not Found" << "\n\n";
   system("pause");
   fp.close();
   fp1.close();
   fp2.close();
   swapfiles();
  return 0;
}


int display(int ca){
  cout << "\n" << "********************* Welcome to Shopping Cart ********************* " << "\n\n";
  cout << "\n";
  cout << "   Product Name            Available Stock         Price" << "\n";
  cout << "_____________________________________________________________" << "\n\n";
  ifstream fp;
  string s;
  int k=0;
  fp.open("stock.txt");
  if(!fp.eof()){
  while(!fp.eof()){
    fp >> name;
    fp >> qty;
    fp >> price;
    if(fp.eof())break;
    if((qty>0 && ca==1) || ca==0){
    cout << setw(3) << ++k << ". ";
    cout << name << setw(30-name.length());
    cout << qty << setw(20);
    cout << price << "\n";
  }
    }
    fp.close();
    cout << "_____________________________________________________________" << "\n\n";
  }else
    cout << "Please Come Back Soon ! Stock Not Available";

  return 0;
}

int generatebill(){
  system("cls");
  cout << "\n" << "********************* Welcome to Shopping Cart ********************* " << "\n\n";
  cout << "\n";
  fstream fp;
  int bill=0,k=0;
  fp.open("bill.dat");
  if(!fp.eof()){
  cout << "   Product Name                 quantity              Price" << "\n";
  cout << "_____________________________________________________________" << "\n\n";
  while(!fp.eof()){
    fp >> name;
    fp >> qty;
    fp >> price;
    if(fp.eof())break;
    bill=bill+price;
    if(qty>0){
    cout << setw(3) << ++k << ". ";
    cout << name << setw(30-name.length());
    cout << qty << setw(20);
    cout << price << "\n";
    }
    }
    fp.close();
  }
  cout << "_____________________________________________________________" << "\n\n";
  cout << "\n" << setw(50) << "Total Amount in Rupees:"<< setw(5) << bill << " /-\n\n";
  ofstream fp1;
  fp1.open("bill.dat",ios::trunc);
  fp1.close();
  cout << "Customer Name :" << cname <<"\n";
  cout << "Mobile Number :" << mobno <<"\n\n";
  cout << "Kindly Check the bill and pay the Amount." << "\n\n\n";
  cout <<setw(60)<< "Thank You! Visit Again." <<"\n\n";
  system("pause");
  main();
  return 0;
}


int addproduct(){
  fstream fp;
  cout << "Enter the Product Name:";
  cin  >> name;
  if(!findproduct(name)){
    cout << "Enter the Product Quantity:";
    cin  >> qty;
    cout << "Enter the Product Price:";
    cin  >> price;
    fp.open("stock.txt",ios::app);
    fp << name <<"   ";
    fp << qty  <<"   ";
    fp << price  <<"\n" ;
    fp.close();
  }
  else
    cout << "You Have Entered Already Existed Item" << "\n\n";
  system("pause");
  return 0;
}

int updatestock(){
  fstream fp;
  fstream fp1;
  fp.open("bill.dat",ios::trunc);
  fp.close();
  int nqty=0;
  string pname;
  cout << "Enter the Product Name:";
  cin  >> pname;
  if(findproduct(pname)){
    cout << "Enter the Change in Product Quantity:";
    cin  >> nqty;
    fp.open("stock.txt");
    fp1.open("temp.txt");
    while(!fp.eof()){
      fp >> name;
      fp >> qty;
      fp >> price;
      if(fp.eof())break;
      if(pname==name)
        qty=qty+(nqty);
      fp1 << name <<"   ";
      fp1 << qty  <<"   ";
      fp1 << price  <<"\n" ;
    }
    fp1.close();
    fp.close();
    swapfiles();
  }
  else
    cout << "Sorry ! Item Not Found" << "\n\n";
  system("pause");
  return 0;
}


int updateprice(){
  fstream fp;
  fstream fp1;
  int nprice=0;
  string pname;
  string file1="stock.txt";
  string file2="temp.txt";
  cout << "Enter the Product Name:";
  cin  >> pname;
  if(findproduct(pname)){
    cout << "Enter the Change in Product Price:";
    cin  >> nprice;
    fp.open(file1);
    fp1.open(file2);
    while(!fp.eof()){
      fp >> name;
      fp >> qty;
      fp >> price;
      if(fp.eof())break;
      if(pname==name)
        price=nprice+(price);
      fp1 << name <<"   ";
      fp1 << qty  <<"   ";
      fp1 << price  <<"\n" ;
    }
    fp1.close();
    fp.close();
    swapfiles();
  }
  else
    cout << "Sorry ! Item Not Found" << "\n\n";
  system("pause");
  return 0;
}


int manageproduct(){
  while(1){
    int n;
    system("cls");
    display(0);
    cout << "Admin Operations:" << "\n";
    cout << "_____________________________________________________________" << "\n\n";
    cout << "1.Add Product" << "\n";
    cout << "2.Update Stock" << "\n";
    cout << "3.Update Price" << "\n";
    cout << "4.Main Menu" << "\n\n";
    cout << "Enter Your Choice:";
    cin >> n;
    cout << "\n";

  switch(n){
    case 1:addproduct();
           break;
    case 2:updatestock();
           break;
    case 3:updateprice();
           break;
    case 4:return 0;
           break;
    default:cout << "Kindly Select the valid option." << "\n";
  }
}
system("pause");
  return 0;
}


int changepassword(){
  ofstream fp;
  string a;
  fp.open("password.txt",ios::trunc);
  cout << "Enter New Password: ";
  cin >> a;
  if(fp << a)
    cout << "Password Sucessfully Changed" << "\n";
  fp.close();
  cout << "\n";
  system("pause");
  return 0;
}


int admin(){
  fstream fp;
  string password,epassword;
  cout << "Please Enter the Password: ";
  cin >>epassword;
  fp.open("password.txt");
  getline(fp,password);
  if(password==epassword){
      fp.close();
      while(1){
        int n;
        system("cls");
        cout << "\n" << "********************* Welcome to Shopping Cart ********************* " << "\n\n";
        cout << "1.Manage Products" << "\n";
        cout << "2.Change password" << "\n";
        cout << "3.Logout" << "\n\n";
        cout << "Enter Your Choice:";
        cin >> n;
        cout << "\n";

      switch(n){
        case 1:manageproduct();
               break;
        case 2:changepassword();
               break;
        case 3:return 0;
               break;
        default:cout << "Kindly Select the valid option." << "\n";
      }
    }
  }
  else
       cout << "\n" << "Invalid Password" << "\n";
  return 0;
}


int customer(){
  ofstream fp;
  fp.open("bill.dat",ios::trunc);
  fp.close();
  cout << "Enter Your Name:";
  cin >> cname;
  cout << "Enter Mobile No:" ;
  cin >> mobno;
  while(1){
    int n;
    system("cls");
    fstream fp;
    fp.open("stock.txt");
    string s;
    fp >> s;
    if(fp.eof()){
    cout <<  "\n" <<"Out of Stock ! Please come back soon" << "\n";
    fp.close();
    return 0;
    }
    display(1);
    cout << "Admin Operations:" << "\n";
    cout << "_____________________________________________________________" << "\n\n";
    cout << "1.Add to Cart" << "\n";
    cout << "2.Generate Bill and Exit" << "\n\n";
    cout << "Enter Your Choice:";
    cin >> n;
    cout << "\n";

  switch(n){
    case 1:addtocart();
           break;
    case 2:generatebill();
           break;
    default:cout << "Kindly Select the valid option." << "\n";
  }
}
system("pause");
  return 0;
}


int main(){
  int n;

  while(1){
    system("cls");
    cout << "\n" << "********************* Welcome to Shopping Cart ********************* " << "\n\n";
    cout << "1.Admin" << "\n";
    cout << "2.Customer" << "\n";
    cout << "3.Exit" << "\n\n";
    cout << "Enter Your Choice:";
    cin >> n;
    cout << "\n";

  switch(n){
    case 1:admin();
           break;
    case 2:customer();
           break;
    case 3:exit(0);
          break;
    default:cout << "Kindly Select the valid option." << "\n";
  }
  cout << "\n";
  system("pause");
  }
  return 0;
}
