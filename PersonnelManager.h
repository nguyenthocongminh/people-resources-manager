#ifndef PERSONNELMANAGER_H
#define PERSONNELMANAGER_H

#include "list"
#include "string"
using namespace std;


class Personnel;

class PersonnelManager {
public:
    typedef list<Personnel *> PersonnelList;

private:
    static PersonnelManager *_instance;
    PersonnelList _personnelList;

private:
    PersonnelManager();

public:
    ~PersonnelManager();

public:
    static PersonnelManager *instance();

public:
    const PersonnelList &personnelList() const;
    Personnel *personnel(const string &id) const;

public:
    bool addPersonnel(Personnel *personnel);

public:
    void printPersonnels() const;
    void printPersonnelsByNameAscending() const;
    void printPersonnelsByNameDescending() const;
};

#endif // PERSONNELMANAGER_H
