#ifndef PERSONNEL_H
#define PERSONNEL_H

#include <string>
using namespace std;


class Personnel {
    friend class PersonnelBuilder;

private:
    string _id;
    string _name;
    string _dateOfBirth;
    string _address;
    string _department;

private:
    Personnel(const string &id,
              const string &name,
              const string &dateOfBirth,
              const string &address,
              const string &department);

public:
    virtual void printInfo() const;
};


#endif // PERSONNEL_H
