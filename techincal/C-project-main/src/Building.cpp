#include "../include/Building.h"

Building::Building(int id, const std::string& name, double x, double y, 
                   const std::string& description)
    : id(id), name(name), description(description), location(x, y) {}

int Building::getId() const {
    return id;
}

std::string Building::getName() const {
    return name;
}

std::string Building::getDescription() const {
    return description;
}

Location Building::getLocation() const {
    return location;
}

std::vector<std::string> Building::getFacilities() const {
    return facilities;
}

void Building::addFacility(const std::string& facility) {
    facilities.push_back(facility);
}

void Building::setDescription(const std::string& desc) {
    description = desc;
}
