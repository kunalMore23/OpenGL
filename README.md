# Solar Panel Simulator

## Overview

The Solar Panel Simulator is an OpenGL-based application that simulates a solar panel system in 3D space. The application visualizes solar panels and allows users to interact with the scene, including zooming in and out.

## Features

- **Solar Panel Visualization**: The application renders a 3D representation of a solar panel system.

- **Zoom Functionality**: Users can zoom in and out using a zoom slider, adjusting the size of the sun in the scene.

## Project Structure

- **`Solar_Panel_Simulator` Directory**: Contains the main application files.
  - `OpenGLWindow.h` and `OpenGLWindow.cpp`: Implement the main OpenGL window and rendering logic.
  - `Solar_Panel_System.h` and `Solar_Panel_System.cpp`: Define the solar panel system and its behavior.

- **`Shaders` Directory**: Contains the vertex and fragment shader files.
  - `vShader.glsl`: Implements the vertex shader with rotation and translation logic.
  - `fShader.glsl`: Implements the fragment shader for rendering colors.

## Dependencies

- **Qt**: The project uses the Qt framework for handling GUI components and OpenGL integration.

## Build and Run Instructions

1. **Dependencies Installation**: Ensure that Qt is installed on your system.

2. **Build the Project**: Use Qt Creator or your preferred IDE to build the project.

3. **Run the Application**: Execute the compiled application to launch the Solar Panel Simulator.

## Usage

- **Zoom Slider**: Adjust the zoom slider to change the size of the sun in the scene.

- **Mouse Interaction**: Interact with the scene using mouse movements. For example, left-click and drag to rotate the view.
