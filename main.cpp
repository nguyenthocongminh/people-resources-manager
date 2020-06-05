#ifdef _WIN32
#include <windows.h> // Enable for window
#define _CLEAR system("cls")
#define _SLEEP(n) Sleep(n)
#endif
#if defined(unix) || defined(__unix__) || defined(__unix)
#include <unistd.h> // Enable for mac, linux
#define _CLEAR system("clear")
#define _SLEEP(n) sleep(n)
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
        
        _CLEAR;

        switch (choice) {
            case 0:
                cout<<"\n\nQUIT \n\n";
                _SLEEP(1);
                return;
            case 1:
                cout << "Nhap thong tin nhan vien\n";
                EmployeeManager::instance()->insertEmployee();
                break;
            case 2:
                cout << "Tim thong tin nhan vien\n";
                EmployeeManager::instance()->findEmployeeById();
                break;
            case 3:
                cout << "Danh sach nhan vien:\n";
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
