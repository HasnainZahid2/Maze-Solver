# Maze Solver with BFS and OpenCV

This project implements a maze solver using the Breadth-First Search (BFS) algorithm and visualizes the process with OpenCV. The program allows users to interactively select the starting point of the maze and visualizes the pathfinding process in real-time.

## Features

- **Maze Visualization**: Displays the maze and updates the visualization as the BFS algorithm explores the maze.
- **Interactive Start Point Selection**: Users can click on the maze to set the starting point.
- **Breadth-First Search (BFS)**: Uses BFS to find the shortest path from the start point to a predefined goal.

## Requirements

- **OpenCV**: Required for rendering the maze and handling user interactions. Install OpenCV using your package manager or build it from source.

## Usage
Run the Program
```sh
./maze_solver
```
- Select Start Point
 Click on an empty cell (white) in the maze to set it as the start point. The selected cell will be highlighted in orange.

## Pathfinding
- The program automatically uses BFS to find a path from the start point to the goal (predefined).
- The maze display updates in real-time, showing visited cells in light blue and the current cell being processed in cyan.
## Visualization
The maze is displayed in a window named "Maze". Colors used:

- Black: Walls (impassable cells).
- Light Blue: Visited cells.
- White: Unvisited cells.
- Orange: Start point.
- Green: Goal point.
- Cyan: Current cell being processed.
- Ending the Program
- The program waits for a key press after solving the maze or if the goal is not found.

## Code Details
- MazePoint Struct: Represents a point in the maze with x and y coordinates.
- drawMaze Function: Draws the maze, start point, goal point, and visited cells on an OpenCV Mat object.
- mouseCallback Function: Handles mouse events to set the start point when a cell is clicked.
- main Function:
  - Initializes the maze and OpenCV window.
  - Sets up the BFS algorithm to explore the maze.
  - Continuously updates the maze visualization until the goal is reached or BFS completes.


