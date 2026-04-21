#ifndef NAVIGATION_SERVER_H
#define NAVIGATION_SERVER_H

#include "CampusGraph.h"
#include <string>
#include <memory>

class NavigationServer {
private:
    std::unique_ptr<CampusGraph> campus;
    int port;

public:
    NavigationServer(int port = 8080);
    
    void initializeCampus();
    void start();
    void stop();
    
    // API methods
    std::string getAllBuildings();
    std::string getBuilding(int id);
    std::string getPath(int fromId, int toId);
    std::string searchBuildings(const std::string& keyword);
    std::string getDistance(int fromId, int toId);
};

#endif
