#ifdef _WIN32
#include <windows.h> // Enable for window
#define _CLEAR system("cls")
#define _SLEEP(n) Sleep(n)
#endif
#if defined(unix) || defined(__unix__) || defined(__unix) || defined(__APPLE__)
#include <unistd.h> // Enable for mac, linux
#define _CLEAR system("clear")
#define _SLEEP(n) sleep(n)
#endif

#include <iostream>

#include "EmployeeManager.h"
using namespace std;

void startApplication();
void wait();

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
        cout << "\n\t5:   Diem danh";
        cout << "\n\t------------------------------------------------";
        cout << "\n\t6:   Tim theo ten";
        cout << "\n\t------------------------------------------------";
        cout << "\n\t7:   Lich su diem danh";
        cout << "\n\t------------------------------------------------";
        cout << "\n\t8:   Lich su diem danh multiple thread";
        cout << "\n\t------------------------------------------------";
        cout << "\n\t0:   Thoat     ";
        cout << "\n\t------------------------------------------------";
        cout << "\n\n\tChon chuc nang: ";
        
        int choice;
        cin >> choice;
        _CLEAR;
        
        switch (choice) {
            case 0:
                _CLEAR;
                cout<<"\n\nQUIT \n\n";
                _SLEEP(1);
                return;
            case 1:
                _CLEAR;
                cout << "Nhap thong tin nhan vien\n";
                EmployeeManager::instance()->insertEmployee();
                wait();
                break;
            case 2:
                _CLEAR;
                cout << "Tim thong tin nhan vien\n";
                EmployeeManager::instance()->findEmployeeById();
                cin.ignore(1);
                wait();
                break;
            case 3:
                _CLEAR;
                cout << "Danh sach nhan vien:\n";
                EmployeeManager::instance()->printEmployees();
                cin.ignore(1);
                wait();
                break;
            case 4:
                _CLEAR;
                EmployeeManager::instance()->importCsv();
                wait();
                break;
            case 5:
                _CLEAR;
                EmployeeManager::instance()->addCheckPoint();
                wait();
                break;
            case 6:
                _CLEAR;
                EmployeeManager::instance()->searchByName();
                wait();
                break;
            case 7:
                _CLEAR;
                EmployeeManager::instance()->checkpointHistory();
                cin.ignore(1);
                wait();
                break;
            case 8:
                _CLEAR;
                EmployeeManager::instance()->checkpointHistoryMultiThread();
                cin.ignore(1);
                wait();
                break;
            default:
                cout<<"\n No option! \n";
                break;
        }
        
    }
}

void wait()
{
    cout<<"\n-------------------------\nNhan Enter de tiep tuc ......\n"<<endl;
    cin.get();
}
