# Bezier Curve Drawing

This project provides a simple implementation of drawing a Bezier curve using the Bezier algorithm. The project includes a `Bezier` class, which allows the creation and rendering of a Bezier curve based on four control points.

## Contents

- [Bezier.h](#bezierh)
- [Bezier.cpp](#beziercpp)

## Bezier.h

This header file defines the `Bezier` class, which encapsulates the functionality for creating and drawing a Bezier curve. Key functionalities include:

- Initializing the Bezier curve with four control points.
- Drawing the Bezier curve and adding vertices and colors to the provided vectors.

## Bezier.cpp

This source file contains the implementation of the `Bezier` class. It includes functions for:

- Initializing the Bezier curve with four control points.
- Adding vertices and colors to the provided vectors for rendering.

## Usage

To use the Bezier curve drawing functionality, follow these steps:

1. **Include the necessary files**: Include the `Bezier.h` header file in your project.

   ```cpp
   #include "Bezier.h"
   ```
2. **Create an instance of the Bezier class:**
```cpp
  Point3D p0(0.0, 0.0, 0.0);
  Point3D p1(1.0, 1.0, 0.0);
  Point3D p2(2.0, 0.0, 0.0);
  Point3D p3(3.0, 1.0, 0.0);

  Bezier bezierCurve(p0, p1, p2, p3);
```
3. **Draw the Bezier curve:**
```cpp
vector<float> vertices;
vector<float> colors;

bezierCurve.drawCurve(p0, p1, p2, p3, vertices, colors);
// Render the vertices and colors using OpenGL
```
![Bezier](../drawBezier.png)
