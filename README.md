# Orbital Simulation Engine

A C++ N-body gravity simulator that models orbital motion between stars, planets, moons, and other space objects. The program reads scenario files, runs a physics simulation, exports CSV data, and visualizes orbital paths using Python.

## Features

- N-body gravitational attraction
- Configurable scenario files
- Configurable simulation settings
- Collision detection
- Kinetic and potential energy tracking
- CSV data export
- Python orbit plotting and animation
- Command-line execution

## Tech Stack

- C++
- Python
- Pandas
- Matplotlib

## Project Structure

```txt
solar-system/
├── src/
│   ├── main.cpp
│   ├── Body.h
│   ├── Body.cpp
│   ├── physics.h
│   ├── physics.cpp
│   ├── LoadFiles.h
│   ├── LoadFiles.cpp
│   ├── simulation.h
│   └── simulation.cpp
│
├── scenarios/
│   ├── earthsunmoon.txt
│   ├── binary_star.txt
│   └── collision_test.txt
│
├── settings/
│   └── earthsunmoon_settings.txt
│
├── output/
│   └── results.csv
│
├── visuals/
│   └── plotdata.py
│
└── README.md
```

## Scenario File Format

Each body is created using data from a file in the following format
where 1 represents fixed and 0 is not fixed:

**name radius mass x y vx vy ax ay fixed**

Ex: Sun 20 50000 0 0 0 0 0 0 1

## Settings File Format

Settings for a scenario are represented in a file with the following values:

- G 0.1
- dt 0.01
- steps 10000
- center Sun
- output output/results.csv

## Running the Simulation

Earth, Sun, Moon Simulation
"x64\Debug\solar system.exe" "scenarios\earthsunmoon.txt" "settings\earthsunmoon_settings.txt" "output\earthsunmoon_results.csv"

Binary Star Simulation
"x64\Debug\solar system.exe" "scenarios\binarystar.txt" "settings\binarystar_settings.txt" "output\binarystar_results.csv"

Collision Simulation
"x64\Debug\solar system.exe" "scenarios\collisiontest.txt" "settings\collisiontest_settings.txt" "output\collision_results.csv"

## Simulation Output

Data is written to a file in the following csv format:

step,body,x,y,speed,distanceFromCenter,KE,PE,totalEnergy

## Visualizing the Simulation

- install python libraries: pip install pandas matplotlib
- run the script: py visuals\plotdata.py output\earthsunmoon_results.csv

