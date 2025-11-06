Vaibhav B, [06-11-2025 22:32]
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <dos.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

// ===== Base Class =====
class Vehicle {
protected:
    int x, y;       // position
    int speed;      // speed
    int color;      // color
    string name;    // vehicle name

public:
    Vehicle(int xpos, int ypos, int spd, int col, string n)
        : x(xpos), y(ypos), speed(spd), color(col), name(n) {}

    virtual void draw() = 0;
    virtual void move() {
        x += speed;
    }

    void setSpeed(int s) { speed = s; }
    void moveUp() { y -= 10; }
    void moveDown() { y += 10; }
    void moveForward() { x += 10; }

    int getX() { return x; }
    int getY() { return y; }
    string getName() { return name; }
};

// ===== Derived Classes =====
class Car : public Vehicle {
public:
    Car(int xpos, int ypos, int spd, int col)
        : Vehicle(xpos, ypos, spd, col, "Car") {}

    void draw() {
        setcolor(color);
        rectangle(x, y, x + 70, y + 30);
        rectangle(x + 15, y - 20, x + 55, y);
        setfillstyle(SOLID_FILL, color);
        floodfill(x + 20, y + 5, color);
        setcolor(WHITE);
        fillellipse(x + 15, y + 32, 7, 7);
        fillellipse(x + 55, y + 32, 7, 7);
    }
};

class Truck : public Vehicle {
public:
    Truck(int xpos, int ypos, int spd, int col)
        : Vehicle(xpos, ypos, spd, col, "Truck") {}

    void draw() {
        setcolor(color);
        rectangle(x, y - 10, x + 100, y + 30);
        rectangle(x + 70, y - 30, x + 100, y - 10);
        setfillstyle(SOLID_FILL, color);
        floodfill(x + 10, y, color);
        setcolor(WHITE);
        fillellipse(x + 20, y + 32, 8, 8);
        fillellipse(x + 80, y + 32, 8, 8);
    }
};

class Bike : public Vehicle {
public:
    Bike(int xpos, int ypos, int spd, int col)
        : Vehicle(xpos, ypos, spd, col, "Bike") {}

    void draw() {
        setcolor(color);
        line(x, y, x + 40, y - 15);
        line(x + 40, y - 15, x + 70, y);
        line(x, y, x + 70, y);
        setfillstyle(SOLID_FILL, color);
        floodfill(x + 35, y - 5, color);
        setcolor(WHITE);
        fillellipse(x + 10, y + 10, 6, 6);
        fillellipse(x + 60, y + 10, 6, 6);
    }
};

// ===== Helper: Draw Track & Finish Line =====
void drawTrack(int finishX) {
    setcolor(WHITE);
    outtextxy(180, 20, (char*)"=== OOPCG PROJECT: ADVANCED CAR RACING GAME ===");

    // Tracks
    line(50, 400, getmaxx() - 50, 400);
    line(50, 300, getmaxx() - 50, 300);
    line(50, 200, getmaxx() - 50, 200);

    // Finish line pattern
    for (int i = 150; i < 450; i += 20)
        rectangle(finishX, i, finishX + 10, i + 10);
}

// ===== Main Function =====
int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    srand(time(0));

    int finishX = getmaxx() - 150;

    // Create vehicles
    Vehicle* player = new Car(60, 380, 0, YELLOW);   // player-controlled car
    Vehicle* cpu1 = new Truck(60, 280, rand() % 6 + 4, CYAN);
    Vehicle* cpu2 = new Bike(60, 180, rand() % 7 + 5, GREEN);

    bool raceOver = false;
    string winner = "";

    outtextxy(200, 250, (char*)"Press any key to START the race...");
    getch();

    while (!raceOver) {
        cleardevice();
        drawTrack(finishX);

        // Draw and move CPU cars
        cpu1->draw();
        cpu1->move();

        cpu2->draw();
        cpu2->move();

        // Draw player car
        player->draw();

        // Player control
        if (kbhit()) {
            char ch = getch();
            if (ch == 72) player->moveUp();      // Up arrow
            if (ch == 80) player->moveDown();    // Down arrow
            if (ch == 77) player->moveForward(); // Right arrow
        }

        // Check for winner
        if (player->getX() + 70 >= finishX) { winner = "You (Player Car)"; raceOver = true; }
        if (cpu1->getX() + 100 >= finishX) { winner = cpu1->getName(); raceOver = true; }
        if (cpu2->getX() + 70 >= finishX) { winner = cpu2->getName(); raceOver = true; }

        delay(60);
    }

Vaibhav B, [06-11-2025 22:32]
// Final screen
    cleardevice();
    settextstyle(3, 0, 4);
    setcolor(YELLOW);
    outtextxy(180, 200, (char*)"=== RACE FINISHED ===");

    string msg = "Winner: " + winner;
    outtextxy(180, 260, (char*)msg.c_str());

    if (winner == "You (Player Car)")
        outtextxy(180, 320, (char*)"* Congratulations! You won the race! *");
    else
        outtextxy(180, 320, (char*)"Better luck next time!");

    delay(4000);

    delete player;
    delete cpu1;
    delete cpu2;
    closegraph();
    return 0;
}