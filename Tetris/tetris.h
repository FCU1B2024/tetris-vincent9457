#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>

#define CANVAS_WIDTH 10
#define CANVAS_HEIGHT 20

#define FALL_DELAY 500
#define RENDER_DELAY 100

#define LEFT_KEY 0x25
#define RIGHT_KEY 0x27
#define ROTATE_KEY 0x26
#define DOWN_KEY 0x28
#define FALL_KEY 0x20
#define HOLD_KEY 0x58

#define LEFT_FUNC() GetAsyncKeyState(LEFT_KEY) & 0x8000
#define RIGHT_FUNC() GetAsyncKeyState(RIGHT_KEY) & 0x8000
#define ROTATE_FUNC() GetAsyncKeyState(ROTATE_KEY) & 0x8000
#define DOWN_FUNC() GetAsyncKeyState(DOWN_KEY) & 0x8000
#define FALL_FUNC() GetAsyncKeyState(FALL_KEY) & 0x8000
#define HOLD_FUNC() GetAsyncKeyState(HOLD_KEY) & 0x8000

typedef enum {
    RED = 41,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYAN,
    WHITE,
    BLACK = 0,
} Color;

typedef enum {
    EMPTY = -1,
    I,
    J,
    L,
    O,
    S,
    T,
    Z
} ShapeId;

typedef struct {
    ShapeId shape;
    Color color;
    int size;
    char rotates[4][4][4];
} Shape;

typedef struct {
    int x;
    int y;
    int score;
    int rotate;
    int fallTime;
    ShapeId queue[7];
    ShapeId hold;
    bool holdUsed;
} State;

typedef struct {
    Color color;
    ShapeId shape;
    bool current;
} Block;

void setBlock(Block* block, Color color, ShapeId shape, bool current);
void resetBlock(Block* block);
void printCanvas(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State* state);
bool move(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], int originalX, int originalY, int originalRotate, int newX, int newY, int newRotate, ShapeId shapeId);
int clearLine(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH]);
void logic(Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH], State* state);
void generateRandomSequence(ShapeId* queue);

#endif // TETRIS_H
