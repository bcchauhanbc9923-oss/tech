#include "../include/CampusGraph.h"
#include <cmath>
#include <algorithm>
#include <queue>
#include <set>

double CampusGraph::calculateDistance(const Location& loc1, const Location& loc2) const {
    double dx = loc1.x - loc2.x;
    double dy = loc1.y - loc2.y;
    return std::sqrt(dx * dx + dy * dy);
}

CampusGraph::CampusGraph() {}

void CampusGraph::addBuilding(const Building& building) {
    buildings[building.getId()] = building;
    if (adjacencyList.find(building.getId()) == adjacencyList.end()) {
        adjacencyList[building.getId()] = std::vector<Edge>();
    }
}

void CampusGraph::addPath(int fromId, int toId, double weight) {
    if (buildings.find(fromId) == buildings.end() || 
        buildings.find(toId) == buildings.end()) {
        return;
    }
    
    if (weight < 0) {
        weight = calculateDistance(buildings[fromId].getLocation(), 
                                   buildings[toId].getLocation());
    }
    
    adjacencyList[fromId].emplace_back(toId, weight);
    adjacencyList[toId].emplace_back(fromId, weight);
}

Building* CampusGraph::getBuilding(int id) {
    if (buildings.find(id) != buildings.end()) {
        return &buildings[id];
    }
    return nullptr;
}

std::vector<Building> CampusGraph::getAllBuildings() const {
    std::vector<Building> result;
    for (const auto& pair : buildings) {
        result.push_back(pair.second);
    }
    return result;
}

std::vector<int> CampusGraph::findShortestPath(int startId, int endId) {
    std::map<int, double> distances;
    std::map<int, int> previous;
    std::map<int, bool> visited;
    
    for (const auto& pair : buildings) {
        distances[pair.first] = std::numeric_limits<double>::infinity();
        visited[pair.first] = false;
    }
    
    distances[startId] = 0;
    
    for (size_t i = 0; i < buildings.size(); ++i) {
        int current = -1;
        double minDist = std::numeric_limits<double>::infinity();
        
        for (const auto& pair : buildings) {
            if (!visited[pair.first] && distances[pair.first] < minDist) {
                current = pair.first;
                minDist = distances[pair.first];
            }
        }
        
        if (current == -1 || current == endId) break;
        
        visited[current] = true;
        
        for (const auto& edge : adjacencyList[current]) {
            double newDist = distances[current] + edge.weight;
            if (newDist < distances[edge.to]) {
                distances[edge.to] = newDist;
                previous[edge.to] = current;
            }
        }
    }
    
    std::vector<int> path;
    int current = endId;
    
    while (current != startId && previous.count(current) > 0) {
        path.push_back(current);
        current = previous[current];
    }
    
    if (current == startId) {
        path.push_back(startId);
        std::reverse(path.begin(), path.end());
    }
    
    return path;
}

double CampusGraph::getPathDistance(int startId, int endId) {
    std::vector<int> path = findShortestPath(startId, endId);
    double distance = 0;
    
    for (size_t i = 0; i < path.size() - 1; ++i) {
        auto& edges = adjacencyList[path[i]];
        for (const auto& edge : edges) {
            if (edge.to == path[i + 1]) {
                distance += edge.weight;
                break;
            }
        }
    }
    
    return distance;
}

Building* CampusGraph::findBuildingByName(const std::string& name) {
    for (auto& pair : buildings) {
        if (pair.second.getName() == name) {
            return &pair.second;
        }
    }
    return nullptr;
}

std::vector<Building> CampusGraph::searchBuildings(const std::string& keyword) {
    std::vector<Building> results;
    std::string lowerKeyword = keyword;
    std::transform(lowerKeyword.begin(), lowerKeyword.end(), 
                   lowerKeyword.begin(), ::tolower);
    
    for (const auto& pair : buildings) {
        std::string lowerName = pair.second.getName();
        std::transform(lowerName.begin(), lowerName.end(), 
                       lowerName.begin(), ::tolower);
        
        if (lowerName.find(lowerKeyword) != std::string::npos) {
            results.push_back(pair.second);
        }
    }
    
    return results;
}
