//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// Paddle Width and Height
#define PADDLE_W WIDTH / 8
#define PADDLE_H HEIGHT / 80

// Bricks Width and Height
#define BRICK_W WIDTH / 11 - 1 
#define BRICK_H HEIGHT / 65

// prototypes
void initBricks(GWindow window, GRect bricks[][COLS]);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void initCheckBricks(bool check_bricks[][COLS]);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    GRect bricks_obj[ROWS][COLS];
    initBricks(window, bricks_obj);
    
    // Two dimensional array to detect if there are bricks in a certain position
    bool check_bricks[ROWS][COLS];
    initCheckBricks(check_bricks);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // get a velocity for the ball
    double velocity = drand48() + 0.9;

    // waits for a mouse's click to start the game as is in the staff's implementation
    waitForClick();

    // The side that ball must go
    double side = 1.5;

    // object: variable to detect collisions 
    GObject object;

    // index to access brick's elements
    int i, j;

    // keep track of old velocity
    double old_vel = velocity;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // TODO
        GEvent event = getNextEvent(MOUSE_EVENT);
        move(ball, velocity, side);

         // if we heard one
         if (event != NULL)
         {
             // if the event was movement
             if (getEventType(event) == MOUSE_MOVED)
             {
                 // ensure the paddlee follows the cursor
                 double x = getX(event) - getWidth(paddle) / 2;
                 double y = HEIGHT - 50 - (PADDLE_H / 2);
                 setLocation(paddle, x, y);
             }
         }
         // bounce off right edge of window
         if (getX(ball) + getWidth(ball) >= getWidth(window))
         {
             velocity = -velocity;
         }
        // bounce off left edge of window
         else if (getX(ball) <= 0)
         {
             velocity = -velocity;
         }
         if (getY(ball) + getHeight(ball) >= getHeight(window))
         {
             --lives;
             if (lives == 0) {
                 break;
             }
             else {
                waitForClick();
                setLocation(ball, WIDTH / 2 - (getWidth(ball) / 2), HEIGHT / 2);
             }
          }
         // bounce off left edge of window
        else if (getY(ball) <= 0)
        {
            side = -side;  
        }
        object = detectCollision(window, ball);
        if (object == paddle)
        {
            side = -side;
            velocity = (velocity < 0) ? -old_vel : old_vel;
        }
       else {
           for (i = 0; i < ROWS; ++i) {
                for (j = 0; j < COLS; ++j) { 
                    if (object == bricks_obj[i][j] && check_bricks[i][j] == true) {
                        side = -side;
                        velocity = (velocity < 0) ? -0.75 : 0.75;
                        ++points;
                        removeGWindow(window, bricks_obj[i][j]);
                        check_bricks[i][j] = false;
                        updateScoreboard(window, label, points);
                    }
                }
            }
        } 
        if (points == bricks) {
            break;
        }
        // linger before moving again
        pause(5);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window, GRect bricks[][COLS])
{
    // TODO
    //GRect bricks[ROWS][COLS];
    int i, j;
    char *COLORS[ROWS] = {"RED","BLUE","GREEN","YELLOW","PINK"};
    for (i = 0; i < ROWS; ++i, ++(*COLORS)) {
        for (j = 0; j < COLS; ++j) {
            bricks[i][j] = newGRect(0, 0,  BRICK_W , BRICK_H);
            setFilled(bricks[i][j], true);
            setColor(bricks[i][j], COLORS[i]);
            add(window, bricks[i][j]);
            setLocation(bricks[i][j],  BRICK_W + j * (BRICK_W + 5) - BRICK_W, (BRICK_H + i - 5) * (BRICK_H + 5) - BRICK_H);
        }
    }    
    return;
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval ball = newGOval(0, 110, 20, 20);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    setLocation(ball, WIDTH / 2 - (getWidth(ball) / 2), HEIGHT / 2);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    GRect paddle = newGRect(0, 0,  PADDLE_W , PADDLE_H);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    setLocation(paddle, WIDTH / 2 - (PADDLE_W / 2)  , HEIGHT - 50 - (PADDLE_H / 2));
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel label = newGLabel("0");
    setFont(label, "SansSerif-36");
    add(window, label);
    setLocation(label, (getWidth(window) - getWidth(label)) / 2, (getHeight(window) - getHeight(label)) / 2);
    return label;
}

/**
 * Init the check_bricks bool 2d array
 */
void initCheckBricks(bool check_bricks[][COLS])
{
    int i, j;
    for (i = 0; i < ROWS; ++i) {
        for (j = 0; j < COLS; ++j) {
            check_bricks[i][j] = true;
        }
    }
    return;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
