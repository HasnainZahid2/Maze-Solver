#include <iostream>
#include <vector>
#include <queue>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct MazePoint {
    int x, y;
};

void drawMaze(const vector<vector<int>>& maze, const MazePoint& start, const MazePoint& goal, const vector<vector<bool>>& visited, const MazePoint& current, bool showStart = false) {
    int rows = maze.size();
    int cols = maze[0].size();
    int cellSize = 50;

    Mat image(rows * cellSize, cols * cellSize, CV_8UC3, Scalar(255, 255, 255));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Rect cellRect(j * cellSize, i * cellSize, cellSize, cellSize);

            if (maze[i][j] == 1) {
                rectangle(image, cellRect, Scalar(0, 0, 0), -1);
            }
            else if (visited[i][j]) {
                rectangle(image, cellRect, Scalar(150, 150, 200), -1);
            }
            else {
                rectangle(image, cellRect, Scalar(255, 255, 255), -1);
            }

            if (showStart && i == start.x && j == start.y) {
                rectangle(image, cellRect, Scalar(0, 100, 255), -1);
            }
            else if (i == goal.x && j == goal.y) {
                rectangle(image, cellRect, Scalar(0, 255, 0), -1);
            }

            if (i == current.x && j == current.y) {
                rectangle(image, cellRect, Scalar(0, 255, 255), -1);
            }
        }
    }

    imshow("Maze", image);
    waitKey(100);
}

MazePoint selectedStart = { -1, -1 };
bool startSelected = false;

void mouseCallback(int event, int x, int y, int, void* param) {
    if (event == EVENT_LBUTTONDOWN || event == EVENT_RBUTTONDOWN && !startSelected) {
        vector<vector<int>>* maze = reinterpret_cast<vector<vector<int>>*>(param);
        int cellSize = 50;
        int row = y / cellSize;
        int col = x / cellSize;

        if ((*maze)[row][col] == 0) {
            selectedStart = { row, col };
            startSelected = true;
        }
    }
}

int main() {
    vector<vector<int>> maze = {
         {1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
         {1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
         {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1},
         {0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0},
         {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
         {1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0},
         {1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0},
         {1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0},
         {1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1}
    };

    MazePoint goal = { 3, 6 };

    int rows = maze.size();
    int cols = maze[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    namedWindow("Maze");
    setMouseCallback("Maze", mouseCallback, &maze);

    drawMaze(maze, selectedStart, goal, visited, { -1, -1 }, false);

    while (!startSelected) {
        waitKey(1);
    }

    if (startSelected) {
        queue<MazePoint> pointQueue;
        pointQueue.push(selectedStart);
        visited[selectedStart.x][selectedStart.y] = true;

        bool goalReached = false;

        while (!pointQueue.empty()) {
            MazePoint current = pointQueue.front();
            pointQueue.pop();

            drawMaze(maze, selectedStart, goal, visited, current, true);

            if (current.x == goal.x && current.y == goal.y) {
                cout << "Goal reached " << endl;
                goalReached = true;
                break;
            }

            vector<MazePoint> directions = {
                {current.x, current.y + 1},
                {current.x + 1, current.y},
                {current.x, current.y - 1},
                {current.x - 1, current.y}
            };

            for (const MazePoint& next : directions) {
                if (next.x >= 0 && next.x < rows && next.y >= 0 && next.y < cols && maze[next.x][next.y] == 0 && !visited[next.x][next.y]) {
                    pointQueue.push(next);
                    visited[next.x][next.y] = true;
                }
            }
        }

        if (!goalReached) {
            cout << "Goal not found" << endl;
        }

        waitKey(0);
    }

    return 0;
}