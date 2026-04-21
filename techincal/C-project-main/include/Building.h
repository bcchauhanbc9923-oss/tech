#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>
#include <map>

struct Location {
    double x, y;
    Location(double x = 0, double y = 0) : x(x), y(y) {}
};

class Building {
private:
    int id;
    std::string name;
    std::string description;
    Location location;
    std::vector<std::string> facilities;

public:
    Building(int id, const std::string& name, double x, double y, 
             const std::string& description = "");
    
    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    Location getLocation() const;
    std::vector<std::string> getFacilities() const;
    
    void addFacility(const std::string& facility);
    void setDescription(const std::string& desc);
};

#endif
