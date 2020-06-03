#ifndef PERSONNELBUILDER_H
#define PERSONNELBUILDER_H

#include <string>
using namespace std;

class Personnel;

class PersonnelBuilder {
    friend class PersonelBuilderFactory;

private:
    Personnel *_personnnel;

private:
    PersonnelBuilder();
    PersonnelBuilder(Personnel &personnel);

public:
    ~PersonnelBuilder();

public:
    PersonnelBuilder &create(const string &id,
                             const string &name,
                             const string &dateOfBirth,
                             const string &address,
                             const string &department);
    PersonnelBuilder &create(Personnel &personnel);

    PersonnelBuilder &clear();

public:
    PersonnelBuilder &setId(const string &id);
    PersonnelBuilder &setName(const string &name);
    PersonnelBuilder &setDateOfBirth(const string &dateOfBirth);
    PersonnelBuilder &setAddress(const string &address);
    PersonnelBuilder &setDepartment(const string &department);

public:
    Personnel *build();
};

#endif // PERSONNELBUILDER_H
