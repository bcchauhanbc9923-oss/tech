#include "../include/NavigationServer.h"
#include <sstream>
#include <fstream>

NavigationServer::NavigationServer(int port) : port(port) {
    campus = std::make_unique<CampusGraph>();
    initializeCampus();
}

void NavigationServer::initializeCampus() {
    // Add sample buildings to the campus
    Building lib1(1, "Main Library", 10, 20, "Central library with study areas");
    lib1.addFacility("Study Rooms");
    lib1.addFacility("Computer Lab");
    campus->addBuilding(lib1);
    
    Building sci(2, "Science Building", 30, 20, "Chemistry, Biology, Physics departments");
    sci.addFacility("Labs");
    sci.addFacility("Lecture Halls");
    campus->addBuilding(sci);
    
    Building eng(3, "Engineering Hall", 30, 40, "Engineering and Technology programs");
    eng.addFacility("Computer Lab");
    eng.addFacility("Workshop");
    campus->addBuilding(eng);
    
    Building cafe(4, "Student Cafeteria", 20, 30, "Dining and meeting place");
    cafe.addFacility("Food Court");
    cafe.addFacility("Seating Area");
    campus->addBuilding(cafe);
    
    Building admin(5, "Administration Building", 10, 40, "Admin offices and registrar");
    admin.addFacility("Registrar Office");
    admin.addFacility("Dean Office");
    campus->addBuilding(admin);
    
    Building gym(6, "Sports Complex", 50, 50, "Athletic facilities");
    gym.addFacility("Gym");
    gym.addFacility("Swimming Pool");
    campus->addBuilding(gym);
    
    // Connect buildings with paths
    campus->addPath(1, 2);
    campus->addPath(1, 4);
    campus->addPath(1, 5);
    campus->addPath(2, 3);
    campus->addPath(2, 4);
    campus->addPath(3, 4);
    campus->addPath(3, 6);
    campus->addPath(4, 5);
    campus->addPath(4, 6);
    campus->addPath(5, 6);
}

void NavigationServer::start() {
    // In a real implementation, this would start an HTTP server
    // For now, we'll focus on the API logic
}

void NavigationServer::stop() {
    // Stop server logic
}

std::string NavigationServer::getAllBuildings() {
    std::stringstream json;
    json << "[";
    
    auto buildings = campus->getAllBuildings();
    for (size_t i = 0; i < buildings.size(); ++i) {
        const auto& b = buildings[i];
        json << "{\"id\":" << b.getId() << ",\"name\":\"" << b.getName() 
             << "\",\"location\":{\"x\":" << b.getLocation().x 
             << ",\"y\":" << b.getLocation().y 
             << "},\"description\":\"" << b.getDescription() << "\"}";
        
        if (i < buildings.size() - 1) json << ",";
    }
    
    json << "]";
    return json.str();
}

std::string NavigationServer::getBuilding(int id) {
    auto buildings = campus->getAllBuildings();
    for (const auto& b : buildings) {
        if (b.getId() == id) {
            std::stringstream json;
            json << "{\"id\":" << b.getId() << ",\"name\":\"" << b.getName() 
                 << "\",\"location\":{\"x\":" << b.getLocation().x 
                 << ",\"y\":" << b.getLocation().y 
                 << "},\"description\":\"" << b.getDescription() << "\"}";
            return json.str();
        }
    }
    return "{}";
}

std::string NavigationServer::getPath(int fromId, int toId) {
    auto path = campus->findShortestPath(fromId, toId);
    std::stringstream json;
    json << "{\"path\":[";
    
    for (size_t i = 0; i < path.size(); ++i) {
        json << path[i];
        if (i < path.size() - 1) json << ",";
    }
    
    json << "],\"distance\":" << campus->getPathDistance(fromId, toId) << "}";
    return json.str();
}

std::string NavigationServer::searchBuildings(const std::string& keyword) {
    auto results = campus->searchBuildings(keyword);
    std::stringstream json;
    json << "[";
    
    for (size_t i = 0; i < results.size(); ++i) {
        const auto& b = results[i];
        json << "{\"id\":" << b.getId() << ",\"name\":\"" << b.getName() 
             << "\",\"location\":{\"x\":" << b.getLocation().x 
             << ",\"y\":" << b.getLocation().y 
             << "},\"description\":\"" << b.getDescription() << "\"}";
        
        if (i < results.size() - 1) json << ",";
    }
    
    json << "]";
    return json.str();
}

std::string NavigationServer::getDistance(int fromId, int toId) {
    std::stringstream json;
    json << "{\"from\":" << fromId << ",\"to\":" << toId 
         << ",\"distance\":" << campus->getPathDistance(fromId, toId) << "}";
    return json.str();
}
