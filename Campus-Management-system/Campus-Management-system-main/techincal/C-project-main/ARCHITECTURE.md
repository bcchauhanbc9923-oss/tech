# Campus Navigation System - Architecture Overview

## System Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                    Campus Navigation System                     │
└─────────────────────────────────────────────────────────────────┘

┌─────────────────────────────┐         ┌──────────────────────────┐
│      C++ BACKEND            │         │    WEB FRONTEND          │
│                             │         │                          │
│  Core Components:           │         │  UI Components:          │
│  ├── Building.cpp           │         │  ├── index.html          │
│  ├── CampusGraph.cpp        │         │  ├── style.css           │
│  ├── NavigationServer.cpp   │         │  └── script.js           │
│  └── main.cpp               │         │                          │
│                             │         │  Features:               │
│  Algorithms:                │         │  ├── Building Search     │
│  ├── Dijkstra's Algorithm   │         │  ├── Route Planning      │
│  ├── Graph Search           │         │  ├── Interactive Map     │
│  ├── Distance Calculation   │         │  └── Building Directory  │
│  └── Path Finding           │         │                          │
└─────────────────────────────┘         └──────────────────────────┘
           │                                       │
           └───────────────── JSON API ──────────┘


Data Flow:
┌─────────────┐      ┌──────────────┐      ┌──────────────┐
│  User Input │─────→│  JavaScript  │─────→│   Canvas &   │
│ (Browser)   │      │  Processing  │      │    Display   │
└─────────────┘      └──────────────┘      └──────────────┘
                            │
                            ↓
                     ┌──────────────┐
                     │  C++ Backend │
                     │  Algorithms  │
                     └──────────────┘
```

## Class Hierarchy

```
Building
├── Properties:
│   ├── id: int
│   ├── name: string
│   ├── description: string
│   ├── location: {x, y}
│   └── facilities: vector<string>
│
└── Methods:
    ├── getId()
    ├── getName()
    ├── getDescription()
    ├── getLocation()
    ├── getFacilities()
    ├── addFacility()
    └── setDescription()


CampusGraph
├── Properties:
│   ├── buildings: map<int, Building>
│   └── adjacencyList: map<int, vector<Edge>>
│
└── Methods:
    ├── addBuilding()
    ├── addPath()
    ├── getBuilding()
    ├── getAllBuildings()
    ├── findShortestPath()      [Dijkstra's Algorithm]
    ├── getPathDistance()
    ├── findBuildingByName()
    └── searchBuildings()


NavigationServer
├── Properties:
│   ├── campus: unique_ptr<CampusGraph>
│   └── port: int
│
├── Methods:
│   ├── initializeCampus()
│   ├── start()
│   ├── stop()
│   ├── getAllBuildings()      [JSON API]
│   ├── getBuilding()          [JSON API]
│   ├── getPath()              [JSON API]
│   ├── searchBuildings()      [JSON API]
│   └── getDistance()          [JSON API]
│
└── API Returns:
    ├── JSON format responses
    └── Ready for HTTP endpoints
```

## Data Models

### Building JSON
```json
{
  "id": 1,
  "name": "Main Library",
  "location": {
    "x": 10,
    "y": 20
  },
  "description": "Central library with study areas"
}
```

### Path Response JSON
```json
{
  "path": [1, 4, 3],
  "distance": 45.2
}
```

### Search Response JSON
```json
[
  {
    "id": 1,
    "name": "Main Library",
    "location": {"x": 10, "y": 20},
    "description": "Central library with study areas"
  },
  ...
]
```

## Algorithm: Dijkstra's Shortest Path

```
Graph Representation:
Buildings → Nodes (Vertices)
Paths → Edges with weights (distances)

Algorithm Steps:
1. Initialize distances to infinity
2. Set start distance to 0
3. While unvisited nodes exist:
   a. Find unvisited node with minimum distance
   b. Update distances to neighbors
   c. Mark node as visited
4. Reconstruct path from end to start
5. Reverse path for correct order

Time Complexity: O((V + E) log V)
Space Complexity: O(V + E)

Where:
V = Number of buildings
E = Number of paths
```

## Frontend Event Flow

```
User Interaction
      ↓
JavaScript Event Handler
      ↓
Process Search/Path Finding
      ↓
Update Data Structures
      ↓
Redraw Canvas
      ↓
Display Results
```

## Build System Options

```
Option 1: Makefile (Direct compilation)
├── make          → Build executable
├── make run      → Build and run
└── make clean    → Clean artifacts

Option 2: CMake (Cross-platform)
├── cmake -B build
├── cmake --build build
└── ./build/navigate

Option 3: Shell Scripts
├── ./build.sh    → Linux/Mac
└── build.bat     → Windows
```

## Extension Points

```
Add New Buildings:
  NavigationServer::initializeCampus() → Add Building
                                      → Register paths

Add New Features:
  CampusGraph → New algorithms
             → New search methods

Add New Facilities:
  Building → addFacility()
          → Store in facilities vector

Enhance Frontend:
  script.js → Add visualization features
           → Add filtering options
           → Add more interactivity
```

## Performance Characteristics

```
Operation              Time Complexity  Space Complexity
──────────────────────────────────────────────────────
Add Building           O(1)             O(1)
Add Path               O(1)             O(1)
Search Buildings       O(V)             O(V)
Find Path              O((V+E) log V)   O(V)
Get Distance           O(V+E)           O(1)
Display Map            O(V+E)           O(1)

V = Number of buildings
E = Number of paths/connections
```

## File Size Reference

```
Source Files:
├── Building.h              ~200 bytes
├── Building.cpp            ~600 bytes
├── CampusGraph.h           ~400 bytes
├── CampusGraph.cpp         ~800 bytes
├── NavigationServer.h      ~300 bytes
├── NavigationServer.cpp    ~1.2 KB
└── main.cpp                ~600 bytes

Frontend Files:
├── index.html              ~3 KB
├── style.css               ~5 KB
└── script.js               ~8 KB

Total Source: ~13 KB (uncompiled)
Binary: ~100-200 KB (compiled, depends on optimization)
```

## Future Enhancement Ideas

1. **Database Integration**
   - Store buildings and paths in database
   - Dynamic updates without recompilation

2. **Advanced Features**
   - 3D visualization
   - Real-time crowd density
   - Wheelchair accessibility routes

3. **User Experience**
   - Dark mode
   - Multiple language support
   - Voice-guided navigation

4. **Integration**
   - Mobile app version
   - REST API server
   - Calendar integration

5. **Performance**
   - Caching for frequent routes
   - Async processing
   - WebSocket real-time updates
```

## Deployment Guide

```
Development:
  1. Compile backend: make
  2. Run backend: ./navigate
  3. Start frontend: python3 -m http.server 8000
  4. Open: http://localhost:8000

Production:
  1. Create HTTP server wrapper (Node.js, Flask, etc.)
  2. Serve static frontend files
  3. Connect to C++ backend APIs
  4. Add SSL/TLS certificates
  5. Deploy on web server
```
