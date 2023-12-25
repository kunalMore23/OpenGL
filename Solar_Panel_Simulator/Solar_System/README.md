# Solar Panel System Simulation

This project simulates a solar panel system using OpenGL and Qt. It includes a solar panel that follows the movement of a sun in orbit. The system demonstrates basic graphics rendering and rotation functionalities.

## Contents

- [Solar_Panel_System.h](#solar_panel_systemh)
- [Solar_Panel_System.cpp](#solar_panel_systemcpp)

## Solar_Panel_System.h

This header file defines the `Solar_Panel_System` class, which encapsulates the solar panel system. Key functionalities include:

- Initializing and managing the solar panel system.
- Drawing the solar panel, sun, and orbiting planets.
- Controlling the rotation of the solar panel and orbiting planets.
- Setting the simulation multiplier to control the speed of rotation.
- Updating the positions based on the elapsed time.

## Solar_Panel_System.cpp

This source file contains the implementation of the `Solar_Panel_System` class. It includes functions for:

- Drawing the sun with specified vertices and colors.
- Drawing orbiting planets and updating their positions.
- Drawing the solar panel, considering its orientation towards the sun.
- Controlling the rotation of the solar panel and the sun.
- Starting, stopping, and resetting the simulation.

## Usage

To use this Solar Panel System simulation, follow these steps:

1. **Include the necessary files**: Include the `Solar_Panel_System.h` header file in your project.

   ```cpp
   #include "Solar_Panel_System.h"

2. **Create an instance of the Solar_Panel_System class :**
   ```cpp
   Solar_Panel_System solarSystem;

3. **Initialize and render the solar panel system:**
   ```cpp
   in openGLWindow.cpp
   floatList vertices;
   floatList colors;
   solarSystem.showSolarPanelSystem(vertices, colors);
   *Render the vertices and colors using OpenGL*

4. **Control the simulation:**
   ```cpp
   // Example: Start revolving
   solarSystem.startRevolving();

![solarPanel](../solarPanel.png)

