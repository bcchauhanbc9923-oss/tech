# Campus Navigation System - Quick Start Guide

## Overview
This is a comprehensive campus navigation system with:
- ✅ C++ backend (graph-based pathfinding)
- ✅ Interactive web frontend (HTML/CSS/JavaScript)
- ✅ Building and facility management
- ✅ Shortest path algorithms

## Project Files

### Backend (C++)
```
include/
├── Building.h              # Building class definition
├── CampusGraph.h           # Graph data structure for pathfinding
└── NavigationServer.h      # Server API definitions

src/
├── Building.cpp            # Building implementation
├── CampusGraph.cpp         # Graph pathfinding implementation
├── NavigationServer.cpp    # API implementation
└── main.cpp                # Main entry point
```

### Frontend
```
frontend/
├── index.html              # Main UI
├── style.css               # Styling and layout
└── script.js               # Interactive functionality
```

### Build Files
```
CMakeLists.txt              # CMake configuration
Makefile                    # Alternative Makefile build
build.sh                    # Linux/Mac build script
build.bat                   # Windows build script
```

## Quick Start

### Option 1: Build Using Makefile (Recommended)
```bash
cd /workspaces/C-project
make
./navigate
```

### Option 2: Build Using CMake
```bash
cd /workspaces/C-project
cmake -B build
cmake --build build
./build/navigate
```

### Option 3: Using Build Scripts
**Linux/Mac:**
```bash
cd /workspaces/C-project
chmod +x build.sh
./build.sh
./build/navigate
```

**Windows:**
```cmd
cd C:\workspaces\C-project
build.bat
.\build\Release\navigate.exe
```

## Running the Frontend

After building the backend, open the frontend:

```bash
cd /workspaces/C-project/frontend
python3 -m http.server 8000
```

Then open your browser to: **http://localhost:8000**

## Features Guide

### Search Buildings
1. Enter a keyword in the search field
2. View results with building information
3. Click "Use as Start" or "Use as End" buttons

### Get Directions
1. Select a starting building from the dropdown
2. Select a destination building
3. Click "Find Route"
4. View the path highlighted on the map

### Interactive Map
- **Blue squares**: Buildings (numbered)
- **Gray lines**: Available paths
- **Red lines**: Your selected route
- **Click on buildings**: Select as starting point

### Building Directory
- View all buildings with details
- See facilities available at each building
- Click buildings to select as start point

## Campus Buildings

| ID | Building | Description |
|----|----------|-------------|
| 1 | Main Library | Central library with study areas |
| 2 | Science Building | Chemistry, Biology, Physics departments |
| 3 | Engineering Hall | Engineering and Technology programs |
| 4 | Student Cafeteria | Dining and meeting place |
| 5 | Administration Building | Admin offices and registrar |
| 6 | Sports Complex | Athletic facilities |

## Technical Details

### Pathfinding Algorithm
- **Algorithm**: Dijkstra's Shortest Path
- **Time Complexity**: O((V + E) log V)
- **Data Structure**: Graph with adjacency lists
- **Distance Metric**: Euclidean distance

### Key Classes
- `Building`: Represents a campus building with location and facilities
- `CampusGraph`: Manages the campus map, buildings, and pathfinding
- `NavigationServer`: Provides API endpoints and manages the system

## Extending the System

### Add a New Building
Edit `src/NavigationServer.cpp`, in the `initializeCampus()` method:

```cpp
Building newBld(7, "New Building", 100, 200, "Description");
newBld.addFacility("Facility name");
campus->addBuilding(newBld);
```

### Connect Buildings
```cpp
campus->addPath(buildingId1, buildingId2);
// or with custom distance:
campus->addPath(buildingId1, buildingId2, distance);
```

### Update Frontend Map
Modify the `buildings` array in `frontend/script.js` to match your C++ backend data.

## Troubleshooting

### Build Fails
- Ensure g++ or clang is installed: `which g++`
- Check C++ standard support: `g++ --version`
- Try: `make clean && make`

### Frontend Not Loading
- Check frontend directory exists: `ls frontend/`
- Verify all files are present: `ls frontend/*.{html,css,js}`
- Ensure port 8000 is not in use

### Path Not Found
- Verify buildings are connected with `addPath()`
- Check that start and end building IDs are correct
- Ensure both buildings exist in the system

## Browser Compatibility
- ✅ Chrome/Chromium
- ✅ Firefox
- ✅ Safari
- ✅ Edge
- ✅ All modern browsers supporting HTML5 Canvas

## Performance Notes
- Handles 6+ buildings efficiently
- Pathfinding calculates instantly
- Frontend renders smoothly with canvas
- Extensible to thousands of buildings

## Next Steps
1. Build the backend: `make`
2. Run the backend: `./navigate`
3. Start the frontend server: `cd frontend && python3 -m http.server 8000`
4. Open browser: `http://localhost:8000`
5. Try searching for buildings and planning routes!

## Resources
- **CMake**: https://cmake.org/
- **C++17**: https://en.cppreference.com/
- **HTML5 Canvas**: https://developer.mozilla.org/en-US/docs/Web/API/Canvas_API
- **Graph Algorithms**: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
