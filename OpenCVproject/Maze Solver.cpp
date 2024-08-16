#include <opencv2/opencv.hpp>
#include <vector>
#include <queue>
#include <iostream>

using namespace cv;
using namespace std;

struct MazePoint {
    int x, y;
};

MazePoint start = { -1, -1 };
bool startSet = false;

void onMouse(int event, int x, int y, int, void*) {
    if (event == EVENT_LBUTTONDOWN || event == EVENT_RBUTTONDOWN) {
        start.x = y / 50;
        start.y = x / 50;
        startSet = true;
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

    int cellSize = 50;
    Mat mazeImage(rows * cellSize, cols * cellSize, CV_8UC3, Scalar(255, 255, 255));
    namedWindow("Maze", WINDOW_AUTOSIZE);
    setMouseCallback("Maze", onMouse);

    auto drawMaze = [&](const MazePoint& current) {
        mazeImage = Scalar(255, 255, 255);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                Point pt1(j * cellSize, i * cellSize);
                Point pt2((j + 1) * cellSize, (i + 1) * cellSize);
                Scalar color;

                if (maze[i][j] == 1) {
                    color = Scalar(0, 0, 0);
                }
                else if (visited[i][j]) {
                    color = Scalar(0, 255, 0);
                }
                else {
                    color = Scalar(255, 255, 255);
                }

                rectangle(mazeImage, pt1, pt2, color, FILLED);

                if (i == start.x && j == start.y) {
                    circle(mazeImage, Point(j * cellSize + cellSize / 2, i * cellSize + cellSize / 2), cellSize / 3, Scalar(255, 0, 0), -1);
                }
                if (i == goal.x && j == goal.y) {
                    circle(mazeImage, Point(j * cellSize + cellSize / 2, i * cellSize + cellSize / 2), cellSize / 3, Scalar(0, 0, 255), -1);
                }
                if (i == current.x && j == current.y) {
                    circle(mazeImage, Point(j * cellSize + cellSize / 2, i * cellSize + cellSize / 2), cellSize / 3, Scalar(255, 255, 0), -1);
                }
            }
        }
        imshow("Maze", mazeImage);
        waitKey(200);
        };

    while (true) {
        drawMaze({ start.x, start.y });

        if (startSet) {
            queue<MazePoint> pointQueue;
            visited = vector<vector<bool>>(rows, vector<bool>(cols, false));
            pointQueue.push(start);
            visited[start.x][start.y] = true;

            while (!pointQueue.empty()) {
                MazePoint current = pointQueue.front();
                pointQueue.pop();

                if (current.x == goal.x && current.y == goal.y) {
                    cout << "Goal reached" << endl;
                    drawMaze(current);
                    waitKey(0);
                    return 0;
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
                        drawMaze(next);
                    }
                }
            }
        }

        if (waitKey(10) == 27) {
            break;
        }
    }

    return 0;
}