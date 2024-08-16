# Maze Solver with BFS and OpenCV

This project implements a maze solver using the Breadth-First Search (BFS) algorithm and visualizes the process with OpenCV. The program allows users to interactively select the starting point of the maze and visualizes the pathfinding process in real-time.

## Features

- **Maze Visualization**: Displays the maze and updates the visualization as the BFS algorithm explores the maze.
- **Interactive Start Point Selection**: Users can click on the maze to set the starting point.
- **Breadth-First Search (BFS)**: Uses BFS to find the shortest path from the start point to a predefined goal.

## Requirements

- **OpenCV**: Required for rendering the maze and handling user interactions. Install OpenCV using your package manager or build it from source.

## Compilation

To compile the program, use the following command:

```sh
g++ -o maze_solver maze_solver.cpp `pkg-config --cflags --libs opencv4`
