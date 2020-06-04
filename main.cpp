#include <iostream>
//#include <windows.h> // Enable for window
#include <unistd.h> // Enable for mac, linux
#include "EmployeeManager.h"
using namespace std;

void startApplication();

int main()
{
    startApplication();
    return 0;
}

void startApplication(){
    while(true){
        system("clear"); // Enable for mac, linux
        
        // Options to choose an action
        cout << "\n\t\tENTER   1:   Nhap thong tin nhan vien";
        cout << "\n\t\t------------------------------------------------";
        cout << "\n\t\tENTER   2:   Tim thong tin nhan vien";
        cout << "\n\t\t------------------------------------------------";
        cout << "\n\t\tENTER   3:   Danh sach nhan vien";
        cout << "\n\t\t------------------------------------------------";
        cout << "\n\t\tENTER   4:   Import csv";
        cout << "\n\t\t------------------------------------------------";
        cout << "\n\t\tENTER   5:   Danh sach diem danh";
        cout << "\n\t\t------------------------------------------------";
        cout << "\n\t\tENTER   0:   To Exit     ";
        cout << "\n\t\t------------------------------------------------";
        cout << "\n\n\t\t   Please Enter Your Choice: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 0:
                system("clear"); // Enable for mac, linux
                
                cout<<"\n\nQUIT \n\n";
                sleep(3);
                return;
            case 1:
                cout << "Nhap thong tin nhan vien";
                EmployeeManager::instance()->insertEmployee();
                break;
            case 2:
                cout << "Tim thong tin nhan vien";
                EmployeeManager::instance()->findEmployeeById();
                break;
            case 3:
                cout << "Danh sach nhan vien";
                EmployeeManager::instance()->printEmployees();
                break;
            case 4:
                cout << "Import csv: method has not support";
                break;
            case 5:
                cout << "Diem danh: method has not support";
                break;
            case 6:
                cout << "Danh sach diem danh: method has not support";
                break;
            default:
                cout<<"\n No option! \n";
                break;
        }
        
    }
}
