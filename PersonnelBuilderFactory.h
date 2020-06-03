#ifndef PERSONNELBUILDERFACTORY_H
#define PERSONNELBUILDERFACTORY_H

class Personnel;
class PersonnelBuilder;

class PersonnelBuilderFactory {
private:
    static PersonnelBuilderFactory *_instance;

public:
    PersonnelBuilderFactory();

public:
    static PersonnelBuilderFactory *instance();

public:
    PersonnelBuilder *createPersonnelBuilder() const;
    PersonnelBuilder *createPersonnelBuilder(Personnel &personnel) const;
};

#endif // PERSONNELBUILDERFACTORY_H
