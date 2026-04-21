let buildings = [];
let routes = [];
let selectedPath = [];

// Initialize the application
document.addEventListener('DOMContentLoaded', function() {
    loadBuildings();
    setupCanvasClickListener();
});

// Load buildings data
function loadBuildings() {
    // Sample data - in production, this would fetch from the C++ backend API
    buildings = [
        { id: 1, name: "Main Library", location: { x: 100, y: 150 }, description: "Central library with study areas" },
        { id: 2, name: "Science Building", location: { x: 300, y: 150 }, description: "Chemistry, Biology, Physics departments" },
        { id: 3, name: "Engineering Hall", location: { x: 300, y: 350 }, description: "Engineering and Technology programs" },
        { id: 4, name: "Student Cafeteria", location: { x: 200, y: 250 }, description: "Dining and meeting place" },
        { id: 5, name: "Administration Building", location: { x: 100, y: 350 }, description: "Admin offices and registrar" },
        { id: 6, name: "Sports Complex", location: { x: 500, y: 450 }, description: "Athletic facilities" }
    ];

    // Graph connections
    routes = [
        { from: 1, to: 2 }, { from: 1, to: 4 }, { from: 1, to: 5 },
        { from: 2, to: 3 }, { from: 2, to: 4 }, { from: 3, to: 4 },
        { from: 3, to: 6 }, { from: 4, to: 5 }, { from: 4, to: 6 }, { from: 5, to: 6 }
    ];

    populateSelects();
    displayBuildings();
    drawMap();
}

// Populate dropdown selects
function populateSelects() {
    const startSelect = document.getElementById('startBuilding');
    const endSelect = document.getElementById('endBuilding');
    
    buildings.forEach(building => {
        const option1 = document.createElement('option');
        option1.value = building.id;
        option1.textContent = building.name;
        startSelect.appendChild(option1);

        const option2 = document.createElement('option');
        option2.value = building.id;
        option2.textContent = building.name;
        endSelect.appendChild(option2);
    });
}

// Display all buildings
function displayBuildings() {
    const container = document.getElementById('buildingsList');
    container.innerHTML = '';

    buildings.forEach(building => {
        const card = document.createElement('div');
        card.className = 'building-card';
        card.innerHTML = `
            <span class="building-id">#${building.id}</span>
            <h3>${building.name}</h3>
            <p>${building.description}</p>
            <p><strong>Location:</strong> (${building.location.x}, ${building.location.y})</p>
        `;
        card.onclick = () => selectBuilding(building.id);
        container.appendChild(card);
    });
}

// Search buildings
function searchBuildings() {
    const query = document.getElementById('searchInput').value.toLowerCase();
    const resultsDiv = document.getElementById('searchResults');
    resultsDiv.innerHTML = '';

    if (!query) {
        resultsDiv.innerHTML = '<p style="color: #999;">Enter a search term</p>';
        return;
    }

    const results = buildings.filter(b => 
        b.name.toLowerCase().includes(query) || 
        b.description.toLowerCase().includes(query)
    );

    if (results.length === 0) {
        resultsDiv.innerHTML = '<p style="color: #999;">No buildings found</p>';
        return;
    }

    results.forEach(building => {
        const item = document.createElement('div');
        item.className = 'result-item';
        item.innerHTML = `
            <strong>${building.name}</strong>
            <p>${building.description}</p>
            <button onclick="selectStart(${building.id})" style="margin-top: 5px; padding: 5px 10px; background: #667eea; color: white; border: none; border-radius: 4px; cursor: pointer;">Use as Start</button>
            <button onclick="selectEnd(${building.id})" style="margin-top: 5px; margin-left: 5px; padding: 5px 10px; background: #764ba2; color: white; border: none; border-radius: 4px; cursor: pointer;">Use as End</button>
        `;
        resultsDiv.appendChild(item);
    });
}

// Helper functions for search results
function selectStart(buildingId) {
    document.getElementById('startBuilding').value = buildingId;
}

function selectEnd(buildingId) {
    document.getElementById('endBuilding').value = buildingId;
}

// Get directions between two buildings
function getDirections() {
    const startId = parseInt(document.getElementById('startBuilding').value);
    const endId = parseInt(document.getElementById('endBuilding').value);

    if (!startId || !endId) {
        alert('Please select both start and end points');
        return;
    }

    if (startId === endId) {
        alert('Start and end points must be different');
        return;
    }

    const path = findPath(startId, endId);
    selectedPath = path;

    const resultsDiv = document.getElementById('directionResults');
    resultsDiv.innerHTML = '';

    if (path.length === 0) {
        resultsDiv.innerHTML = '<p style="color: #ef4444;">No route found</p>';
        return;
    }

    let distance = 0;
    for (let i = 0; i < path.length - 1; i++) {
        distance += calculateDistance(path[i], path[i + 1]);
    }

    let routeHTML = '<div class="result-item"><strong>Route Found</strong>';
    routeHTML += '<p><strong>Distance:</strong> ' + distance.toFixed(2) + ' units</p>';
    routeHTML += '<p><strong>Route:</strong> ';
    
    path.forEach((id, index) => {
        const building = buildings.find(b => b.id === id);
        routeHTML += building.name;
        if (index < path.length - 1) routeHTML += ' → ';
    });
    
    routeHTML += '</p><p><strong>Steps:</strong> ' + (path.length - 1) + '</p></div>';
    resultsDiv.innerHTML = routeHTML;

    drawMap();
}

// Find shortest path using BFS
function findPath(start, end) {
    const queue = [[start]];
    const visited = new Set([start]);

    while (queue.length > 0) {
        const path = queue.shift();
        const current = path[path.length - 1];

        if (current === end) {
            return path;
        }

        for (let route of routes) {
            let neighbor = null;
            if (route.from === current && !visited.has(route.to)) {
                neighbor = route.to;
            } else if (route.to === current && !visited.has(route.from)) {
                neighbor = route.from;
            }

            if (neighbor) {
                visited.add(neighbor);
                queue.push([...path, neighbor]);
            }
        }
    }

    return [];
}

// Calculate distance between two buildings
function calculateDistance(id1, id2) {
    const b1 = buildings.find(b => b.id === id1);
    const b2 = buildings.find(b => b.id === id2);
    
    const dx = b1.location.x - b2.location.x;
    const dy = b1.location.y - b2.location.y;
    
    return Math.sqrt(dx * dx + dy * dy);
}

// Draw campus map
function drawMap() {
    const canvas = document.getElementById('campusCanvas');
    const ctx = canvas.getContext('2d');

    // Clear canvas
    ctx.fillStyle = '#ffffff';
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    // Draw grid
    ctx.strokeStyle = '#f0f0f0';
    ctx.lineWidth = 1;
    for (let i = 0; i < canvas.width; i += 50) {
        ctx.beginPath();
        ctx.moveTo(i, 0);
        ctx.lineTo(i, canvas.height);
        ctx.stroke();
    }
    for (let i = 0; i < canvas.height; i += 50) {
        ctx.beginPath();
        ctx.moveTo(0, i);
        ctx.lineTo(canvas.width, i);
        ctx.stroke();
    }

    // Draw routes
    ctx.strokeStyle = '#999999';
    ctx.lineWidth = 2;
    routes.forEach(route => {
        const b1 = buildings.find(b => b.id === route.from);
        const b2 = buildings.find(b => b.id === route.to);
        ctx.beginPath();
        ctx.moveTo(b1.location.x, b1.location.y);
        ctx.lineTo(b2.location.x, b2.location.y);
        ctx.stroke();
    });

    // Draw selected path if exists
    if (selectedPath.length > 1) {
        ctx.strokeStyle = '#ef4444';
        ctx.lineWidth = 4;
        for (let i = 0; i < selectedPath.length - 1; i++) {
            const b1 = buildings.find(b => b.id === selectedPath[i]);
            const b2 = buildings.find(b => b.id === selectedPath[i + 1]);
            ctx.beginPath();
            ctx.moveTo(b1.location.x, b1.location.y);
            ctx.lineTo(b2.location.x, b2.location.y);
            ctx.stroke();
        }
    }

    // Draw buildings
    buildings.forEach(building => {
        const isInPath = selectedPath.includes(building.id);
        
        ctx.fillStyle = isInPath ? '#ef4444' : '#667eea';
        ctx.fillRect(building.location.x - 12, building.location.y - 12, 24, 24);
        
        ctx.strokeStyle = '#333333';
        ctx.lineWidth = 2;
        ctx.strokeRect(building.location.x - 12, building.location.y - 12, 24, 24);

        // Draw building label
        ctx.fillStyle = '#333333';
        ctx.font = 'bold 10px Arial';
        ctx.textAlign = 'center';
        ctx.fillText(building.id, building.location.x, building.location.y + 4);
    });
}

// Select building on map
function selectBuilding(buildingId) {
    document.getElementById('startBuilding').value = buildingId;
}

// Setup canvas click listener
function setupCanvasClickListener() {
    const canvas = document.getElementById('campusCanvas');
    canvas.addEventListener('click', function(event) {
        const rect = canvas.getBoundingClientRect();
        const x = event.clientX - rect.left;
        const y = event.clientY - rect.top;

        // Check if click is on a building
        for (let building of buildings) {
            const dx = x - building.location.x;
            const dy = y - building.location.y;
            if (Math.sqrt(dx * dx + dy * dy) < 15) {
                selectBuilding(building.id);
                break;
            }
        }
    });
}
