#ifndef ACTIONMODULE_H
#define ACTIONMODULE_H

#include <string>
using namespace std;

bool addPersonnel(string id,
                  string name,
                  string dateOfBirth,
                  string address,
                  string department);
bool searchPersonnel(string id);

#endif // ACTIONMODULE_H
