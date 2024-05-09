#include <stdio.h>
#include <stdbool.h>

#define CANVAS_WIDTH 10
#define CANVAS_HEIGHT 20   

//對應形狀ID
typedef enum {
    EMPTY = -1,
    I,
    J,
    L,
    O,
    S,
    T,
    Z
}ShapeId;

//對應顏色
typedef enum {
    RED = 41,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    CYAN,
    WHITE,
    BLACK = 0,
}Color;

//遊戲板上的方塊
typedef struct {
    Color color;    //這個方塊的顏色
    ShapeId shape;  //這個方塊的ID
    bool current;   //目前的狀態
}Block;

//遊戲狀態
typedef struct {
    int x;
    int y;
    int score;
    int rotate;
    int fallTime;
    ShapeId queue[4];
}State;

//方塊定義
typedef struct {
    ShapeId shape;
    Color color;
    int size;
    char rotates[4][4][4];
}Shape;

//7種方塊
Shape shapes[7] = {
    {
        .shape = I,
        .color = CYAN,
        .size = 4,
        .rotates =
        {
            {
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            },
            {
                {0, 0, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 0}
            },
            {
                {0, 0, 0, 0},
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0}
            },
            {
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 1, 0, 0}
            }
        }
    },
    {
        .shape = J,
        .color = BLUE,
        .size = 3,
        .rotates =
        {
            {
                {1, 0, 0},
                {1, 1, 1},
                {0, 0, 0}
            },
            {
                {0, 1, 1},
                {0, 1, 0},
                {0, 1, 0}
            },
            {
                {0, 0, 0},
                {1, 1, 1},
                {0, 0, 1}
            },
            {
                {0, 1, 0},
                {0, 1, 0},
                {1, 1, 0}
            }
        }
    },
    {
        .shape = L,
        .color = YELLOW,
        .size = 3,
        .rotates =
        {
            {
                {0, 0, 1},
                {1, 1, 1},
                {0, 0, 0}
            },
            {
                {0, 1, 0},
                {0, 1, 0},
                {0, 1, 1}
            },
            {
                {0, 0, 0},
                {1, 1, 1},
                {1, 0, 0}
            },
            {
                {1, 1, 0},
                {0, 1, 0},
                {0, 1, 0}
            }
        }
    },
    {
        .shape = O,
        .color = WHITE,
        .size = 2,
        .rotates =
        {
            {
                {1, 1},
                {1, 1}
            },
            {
                {1, 1},
                {1, 1}
            },
            {
                {1, 1},
                {1, 1}
            },
            {
                {1, 1},
                {1, 1}
            }
        }
    },
    {
        .shape = S,
        .color = GREEN,
        .size = 3,
        .rotates =
        {
            {
                {0, 1, 1},
                {1, 1, 0},
                {0, 0, 0}
            },
            {
                {0, 1, 0},
                {0, 1, 1},
                {0, 0, 1}
            },
            {
                {0, 0, 0},
                {0, 1, 1},
                {1, 1, 0}
            },
            {
                {1, 0, 0},
                {1, 1, 0},
                {0, 1, 0}
            }
        }
    },
    {
        .shape = T,
        .color = PURPLE,
        .size = 3,
        .rotates =
        {
            {
                {0, 1, 0},
                {1, 1, 1},
                {0, 0, 0}
            },

                {{0, 1, 0},
                {0, 1, 1},
                {0, 1, 0}
            },
            {
                {0, 0, 0},
                {1, 1, 1},
                {0, 1, 0}
            },
            {
                {0, 1, 0},
                {1, 1, 0},
                {0, 1, 0}
            }
        }
    },
    {
        .shape = Z,
        .color = RED,
        .size = 3,
        .rotates =
        {
            {
                {1, 1, 0},
                {0, 1, 1},
                {0, 0, 0}
            },
            {
                {0, 0, 1},
                {0, 1, 1},
                {0, 1, 0}
            },
            {
                {0, 0, 0},
                {1, 1, 0},
                {0, 1, 1}
            },
            {
                {0, 1, 0},
                {1, 1, 0},
                {1, 0, 0}
            }
        }
    },
};

//設定遊戲板
void setBlock(Block* block, Color color, ShapeId shape, bool current) {
    block->color = color;
    block->shape = shape;
    block->current = current;
}

//重設遊戲板
void resetBlock(Block* block) {
    block->color = BLACK;
    block->shape = EMPTY;
    block->current = false;
}

int main() {
    Block canvas[CANVAS_HEIGHT][CANVAS_WIDTH];
    Color color;
    State state = {
        .x = CANVAS_WIDTH / 2 ,
        .y = 0 ,
        .score = 0 ,
        .rotate = 0 ,
        .fallTime = 0
    };

    for (int i = 0; i < CANVAS_HEIGHT; i++) {
        for (int j = 0; j < CANVAS_WIDTH; j++) {
            resetBlock(&canvas[i][j]);
        }
    }

    for (int i = 0; i < shapes[J].size; i++) {
        for (int j = 0; j < shapes[J].size; j++) {
            if (shapes[J].rotates[0][i][j]) {
                setBlock(&canvas[state.x + i][state.y + j], shapes[J].color, shapes[J].shape, true);
            }
        }
    }

    printf("\033[0:0H\n");

    for (int i = 0; i < CANVAS_HEIGHT; i++) {
        printf("|");
        for (int j = 0; j < CANVAS_WIDTH; j++) {
            printf("\033[%dm\u3000", canvas[i][j].color);
        }
        printf("\033[0m");
        printf("|\n");
    }

    return 0;
}