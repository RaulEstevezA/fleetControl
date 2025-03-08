# Fleet Management System

## Overview
This project is a **fleet management system** written in C, developed as part of the "Fundamentos de la Programación" (Fundamentals of Programming) course at **Universitat Oberta de Catalunya (UOC)**. The system provides comprehensive functionalities to manage fleets and vehicles, including registration, modification, deletion, and various analytical tools. It also incorporates platform-specific compilation logic to ensure compatibility across **Windows and macOS**. The project was completed in **December 2004**.

## Features
### **Fleet Management**
- **Fleet Registration**: Allows users to register a new fleet with company details.
- **Vehicle Management**:
  - Add new vehicles to a fleet, including details like license plate, fuel type, mileage, acquisition date, and cost.
  - Delete vehicles from a fleet.
  - Modify vehicle details such as fuel type, mileage, acquisition cost, and operational status.

### **Fleet Analysis & Reporting**
- **List all vehicles** in the fleet with their attributes.
- **Filter vehicles** that exceed a specified mileage.
- **List vehicles based on acquisition year**.
- **Calculate cost-to-mileage ratio**, determining the most cost-efficient vehicle.
- **Count vehicles exceeding a user-defined mileage threshold**.
- **Operational status tracking**: Identify active and inactive vehicles.

### **Cross-Platform Compatibility**
- Uses **conditional compilation** to ensure correct execution on different operating systems:
  - `#ifdef _WIN32` for Windows.
  - `#else` for macOS and Linux.
- **Screen Clearing**:
  - Uses `system("cls")` on Windows.
  - Uses `system("clear")` on macOS/Linux.
- **Time Delays**:
  - Uses `Sleep()` for Windows.
  - Uses `usleep()` for macOS/Linux.

## Compilation and Execution
### **Windows**:
```sh
gcc -o fleetControl fleetControl.c -Wall
fleetControl.exe
```

### **macOS/Linux**:
```sh
gcc -o fleetControl fleetControl.c -Wall
./fleetCrontol
```

## **Usage Instructions**
1. **Run the program** and navigate through the interactive menu.
2. **Register a fleet** before adding vehicles.
3. **Perform various operations** such as:
   - Listing registered vehicles.
   - Modifying or deleting vehicle details.
   - Calculating vehicle efficiency and cost-related statistics.
4. **Exit the program** when finished.

## **Code Structure**
The program follows a structured approach, implementing modular functions:
- `imprimirMenu()`: Displays the main menu.
- `darDeAltaUnaFlota()`: Registers a new fleet.
- `darDeAltaUnVehiculo()`: Registers a new vehicle.
- `borrarUnVehiculo()`: Deletes a vehicle from the fleet.
- `modificarVehiculo()`: Modifies vehicle attributes.
- `listarVehiculos()`: Displays all vehicles in the fleet.
- `listarPorKilometraje()`: Lists vehicles exceeding a given mileage.
- `vehiculosAnyo()`: Lists vehicles based on their acquisition year.
- `kilometrajePorCosto()`: Computes cost-to-mileage efficiency.
- `superarKilometros()`: Counts vehicles exceeding a given mileage.

## **Video Demonstration**
For a better understanding of the project, watch the video demonstration on YouTube: **[Fleet Management System](https://youtu.be/2WM3lx8Oy_Q)**.

## **Requirements**
- GCC compiler.
- Compatible with **Windows** and **macOS/Linux**.
- Terminal or command prompt.

## **Author**
This project was developed as part of an academic assignment at **Universitat Oberta de Catalunya (UOC)**.

