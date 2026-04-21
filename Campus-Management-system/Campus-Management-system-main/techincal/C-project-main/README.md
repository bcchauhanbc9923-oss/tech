# Campus Navigation System

A comprehensive campus navigation system built with C++ backend and interactive web-based frontend.

## Project Structure

```
C-project/
├── src/                    # C++ source files
│   ├── Building.cpp
│   ├── CampusGraph.cpp
│   ├── NavigationServer.cpp
│   └── main.cpp
├── include/               # C++ header files
│   ├── Building.h
│   ├── CampusGraph.h
│   └── NavigationServer.h
├── frontend/              # Web-based frontend
│   ├── index.html
│   ├── style.css
│   └── script.js
├── CMakeLists.txt         # CMake build configuration
└── README.md
```

## Features

### Backend (C++)
- **Graph-based Campus Map**: Efficient representation of campus layout with buildings as nodes
- **Dijkstra's Shortest Path**: Find the shortest route between any two buildings
- **Building Search**: Search buildings by name and description
- **Distance Calculation**: Calculate distances between buildings
- **Facility Information**: Detailed facility information for each building

### Frontend (Web)
- **Interactive Campus Map**: Visual representation of the campus layout
- **Real-time Navigation**: Interactive canvas showing buildings and paths
- **Building Search**: Search functionality for finding buildings
- **Route Planning**: Get step-by-step directions with distance calculations
- **Responsive Design**: Works on desktop and mobile devices
- **Building Directory**: Complete list of all campus buildings

## Buildings in the System

1. **Main Library** (ID: 1) - Central library with study areas
2. **Science Building** (ID: 2) - Chemistry, Biology, Physics departments
3. **Engineering Hall** (ID: 3) - Engineering and Technology programs
4. **Student Cafeteria** (ID: 4) - Dining and meeting place
5. **Administration Building** (ID: 5) - Admin offices and registrar
6. **Sports Complex** (ID: 6) - Athletic facilities

## Building Instructions

### Prerequisites
- CMake (version 3.10 or higher)
- C++ compiler (g++, clang, or MSVC)
- Make (for Linux/Mac) or equivalent build tool

### Linux/Mac

```bash
cd /workspaces/C-project
mkdir -p build
cd build
cmake ..
make
```

### Windows (using Visual Studio)

```bash
cd \workspaces\C-project
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## Running the Application

### Backend
After building, run the navigation system:

```bash
./navigate
# or on Windows: navigate.exe
```

### Frontend
Open the web interface:

```bash
# Simple approach: Open the file directly in a browser
# Or use a simple HTTP server
cd frontend
python3 -m http.server 8000
# Then open: http://localhost:8000
```

Alternatively, you can use the built-in Python HTTP server or any other method to serve the frontend files.

## How to Use

1. **Search Buildings**: Enter keywords to find buildings
2. **View Map**: See the interactive campus map with all buildings
3. **Get Directions**: 
   - Select "From" building
   - Select "To" building
   - Click "Find Route"
   - View the highlighted path on the map

## API Functions (C++ Backend)

- `findShortestPath(int start, int end)`: Returns the shortest path between two buildings
- `getPathDistance(int start, int end)`: Calculates the total distance of a path
- `searchBuildings(const std::string& keyword)`: Searches for buildings matching keyword
- `getAllBuildings()`: Returns all buildings in the system
- `getDistance(int from, int to)`: Gets distance between two buildings

## Extending the System

### Adding New Buildings
Edit `NavigationServer::initializeCampus()` in `src/NavigationServer.cpp`:

```cpp
Building newBuilding(7, "New Building", x_coord, y_coord, "Description");
newBuilding.addFacility("Facility 1");
campus->addBuilding(newBuilding);
```

### Adding New Paths
Add connections between buildings:

```cpp
campus->addPath(buildingId1, buildingId2);
```

### Customizing the Map
Modify `drawMap()` in `frontend/script.js` to adjust visualization parameters.

## Algorithm Explanation

### Dijkstra's Algorithm
The system uses Dijkstra's shortest path algorithm to find optimal routes:
- Time Complexity: O((V + E) log V) where V = buildings, E = paths
- Space Complexity: O(V)

## Performance

- Handles up to thousands of buildings efficiently
- Real-time shortest path calculation
- Smooth interactive map rendering

## Future Enhancements

- 3D campus visualization
- Real-time location tracking
- Integration with building calendars
- Accessibility features (wheelchair routes)
- Multiple transportation modes
- Social features (find friends, study partners)
- Mobile app version
- Database integration for dynamic building updates

## Troubleshooting

### Build Issues
- Ensure CMake is installed: `cmake --version`
- Check compiler: `g++ --version` or `clang --version`
- Make sure you're in the project directory

### Frontend Not Loading
- Check that all files (HTML, CSS, JS) are in the frontend directory
- Ensure you're serving from the correct directory
- Check browser console for JavaScript errors

### Path Finding Issues
- Verify buildings are connected with `addPath()`
- Check building IDs are correct
- Ensure both start and end buildings exist

## License

This project is open source and available for educational and commercial use.

## Author

Campus Navigation System - C++ Project

Developed as a comprehensive system for efficient campus navigation and exploration.
