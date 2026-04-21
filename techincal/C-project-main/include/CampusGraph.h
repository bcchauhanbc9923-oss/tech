#ifndef CAMPUS_GRAPH_H
#define CAMPUS_GRAPH_H

#include "Building.h"
#include <map>
#include <vector>
#include <queue>
#include <limits>

class Edge {
public:
    int to;
    double weight;
    
    Edge(int to, double weight) : to(to), weight(weight) {}
};

class CampusGraph {
private:
    std::map<int, Building> buildings;
    std::map<int, std::vector<Edge>> adjacencyList;
    
    double calculateDistance(const Location& loc1, const Location& loc2) const;

public:
    CampusGraph();
    
    void addBuilding(const Building& building);
    void addPath(int fromId, int toId, double weight = -1);
    
    Building* getBuilding(int id);
    std::vector<Building> getAllBuildings() const;
    
    std::vector<int> findShortestPath(int startId, int endId);
    double getPathDistance(int startId, int endId);
    
    Building* findBuildingByName(const std::string& name);
    std::vector<Building> searchBuildings(const std::string& keyword);
};

#endif
