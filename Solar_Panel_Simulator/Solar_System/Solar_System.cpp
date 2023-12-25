// Solar_System.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Solar_System.h"


// This is an example of an exported variable
SOLARSYSTEM_API int nSolarSystem=0;

// This is an example of an exported function.
SOLARSYSTEM_API int fnSolarSystem(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
SolarSystem::SolarSystem()
{
    return;
}
