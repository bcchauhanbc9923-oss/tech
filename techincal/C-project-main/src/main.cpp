#include "include/NavigationServer.h"
#include <iostream>
#include <fstream>

int main() {
    std::cout << "=== Campus Navigation System ===" << std::endl;
    
    NavigationServer server(8080);
    
    // Generate JSON API responses
    std::cout << "\nAll Buildings:" << std::endl;
    std::string allBuildings = server.getAllBuildings();
    std::cout << allBuildings << std::endl;
    
    // Save to file for frontend
    std::ofstream buildingsFile("frontend/data/buildings.json");
    buildingsFile << allBuildings;
    buildingsFile.close();
    
    // Example: Get path from Library (1) to Engineering (3)
    std::cout << "\n\nPath from Library (1) to Engineering (3):" << std::endl;
    std::string path = server.getPath(1, 3);
    std::cout << path << std::endl;
    
    // Example: Search buildings
    std::cout << "\n\nSearch for 'Lab':" << std::endl;
    std::string search = server.searchBuildings("Lab");
    std::cout << search << std::endl;
    
    // Get distance
    std::cout << "\n\nDistance from Library (1) to Cafeteria (4):" << std::endl;
    std::string distance = server.getDistance(1, 4);
    std::cout << distance << std::endl;
    
    std::cout << "\n\nJSON data exported to frontend/data/buildings.json" << std::endl;
    
    return 0;
}
