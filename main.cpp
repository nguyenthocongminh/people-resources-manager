#ifdef _WIN32
#include <windows.h> // Enable for window
#define _CLEAR system("cls")
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
#include <unistd.h> // Enable for mac, linux
#define _CLEAR system("clear")
#endif
#include <iostream>
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
                _CLEAR;
                cout<<"\n\nQUIT \n\n";
                return;
            case 1:
                _CLEAR;
                cout << "Nhap thong tin nhan vien\n";
                EmployeeManager::instance()->insertEmployee();
                break;
            case 2:
                _CLEAR;
                cout << "Tim thong tin nhan vien\n";
                EmployeeManager::instance()->findEmployeeById();
                break;
            case 3:
                _CLEAR;
                cout << "Danh sach nhan vien:\n";
                EmployeeManager::instance()->printEmployees();
                break;
            case 4:
                _CLEAR;
                cout << "Import csv: method has not support";
                break;
            case 5:
                _CLEAR;
                cout << "Diem danh: method has not support";
                break;
            case 6:
                _CLEAR;
                cout << "Danh sach diem danh: method has not support";
                break;
            default:
                cout<<"\n No option! \n";
                break;
        }
        
    }
}
