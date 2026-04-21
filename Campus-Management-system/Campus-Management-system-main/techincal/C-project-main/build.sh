#!/bin/bash
# Build script for Campus Navigation System

set -e  # Exit on error

echo "=== Building Campus Navigation System ==="
echo ""

# Create build directory if it doesn't exist
if [ ! -d "build" ]; then
    echo "Creating build directory..."
    mkdir -p build
fi

cd build

# Run CMake
echo "Configuring with CMake..."
cmake ..

# Build the project
echo "Building project..."
if command -v make &> /dev/null; then
    make
else
    echo "GNU Make not found. Using cmake build..."
    cmake --build . --config Release
fi

cd ..

echo ""
echo "=== Build Complete ==="
echo ""
echo "To run the navigation system:"
echo "  ./build/navigate"
echo ""
echo "To view the frontend:"
echo "  cd frontend"
echo "  python3 -m http.server 8000"
echo "  # Then open http://localhost:8000 in your browser"
