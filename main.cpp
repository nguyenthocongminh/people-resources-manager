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
//        system("clear"); // Enable for mac, linux
//        system("cls"); // Enable for win
        
        // Options to choose an action
        cout << "\n\t1:   Nhap thong tin nhan vien";
        cout << "\n\t------------------------------------------------";
        cout << "\n\t2:   Tim thong tin nhan vien";
        cout << "\n\t------------------------------------------------";
        cout << "\n\t3:   Danh sach nhan vien";
        cout << "\n\t------------------------------------------------";
        cout << "\n\t4:   Import csv";
        cout << "\n\t------------------------------------------------";
        cout << "\n\t5:   Danh sach diem danh";
        cout << "\n\t------------------------------------------------";
        cout << "\n\t0:   Thoat     ";
        cout << "\n\t------------------------------------------------";
        cout << "\n\n\tChon chuc nang: ";
        
        int choice;
        cin >> choice;
        
        switch (choice) {
            case 0:
                system("clear"); // Enable for mac, linux
//                system("cls"); // Enable for win
                
                cout<<"\n\nQUIT \n\n";
                sleep(1);
                return;
            case 1:
                system("clear"); // Enable for mac, linux
//                system("cls"); // Enable for win
                cout << "Nhap thong tin nhan vien\n";
                EmployeeManager::instance()->insertEmployee();
                break;
            case 2:
                system("clear"); // Enable for mac, linux
//                system("cls"); // Enable for win
                cout << "Tim thong tin nhan vien\n";
                EmployeeManager::instance()->findEmployeeById();
                break;
            case 3:
                system("clear"); // Enable for mac, linux
//                system("cls"); // Enable for win
                cout << "Danh sach nhan vien:\n";
                EmployeeManager::instance()->printEmployees();
                break;
            case 4:
                system("clear"); // Enable for mac, linux
//                system("cls"); // Enable for win
                cout << "Import csv: method has not support";
                break;
            case 5:
                system("clear"); // Enable for mac, linux
//                system("cls"); // Enable for win
                cout << "Diem danh: method has not support";
                break;
            case 6:
                system("clear"); // Enable for mac, linux
//                system("cls"); // Enable for win
                cout << "Danh sach diem danh: method has not support";
                break;
            default:
                cout<<"\n No option! \n";
                break;
        }
        
    }
}
