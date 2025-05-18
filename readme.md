# ArchimedesPrincipleOnShip

An interactive Qt 6.8.0 C++ application that visualizes the **transversal ship stability** based on Archimedes' principle.

🛳️ **Features**:
- Interactive 2D cross-section of a ship
- Real-time computation of:
  - KG (center of gravity)
  - KB (center of buoyancy)
  - KM (metacenter)
  - GM (metacentric height)
  - Draft
- Visual markers for KG, KB, KM
- Click-to-edit interface to update ship parameters

🧪 Built with:
- Qt Widgets
- Custom painter interface
- Physics simplified for rectangular hulls

🔧 Future plans:
- Graphs of stability curves
- Export functionality
- Integration with real hydrostatic curves

## Build Instructions

```bash
mkdir build && cd build
cmake ..
make
./ArchimedesPrincipleOnShip
