// I3D Assignment 01 - Island Defence

#ifndef M_PI
#define M_PI 3.141592653589793238463
#endif

#include "opengl.h"

#include "vec2f.h"
#include "vec2fPolar.h"
#include "vec3f.h"
#include "colour.h"

#include "wave.h"
#include "island.h"
#include "boat.h"
#include "3d_wave.h"
#include "3d_island.h"
#include "3d_boat.h"
#include "seafloor.h"
#include "random.h"
#include "keyboard.h"
#include "mouse.h"
#include "cylinder.h"

#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <list>
#include <string>

const int milli = 1000;
const float windowSize = 1;

// Game objects
Wave3D *wave = new Wave3D(windowSize, 64, 0.07, 9, 0.25 * M_PI, 0, -0.5);
vec2f boat1location = {-0.5, 0};
Boat *boat1 = new Boat(boat1location, 0, 45, 0);
vec2f boat2location = {0.5, 0};
Boat *boat2 = new Boat(boat2location, 0, 135, 1);
Island *island = new Island();
Island3D *island3D = new Island3D();
Seafloor *seafloor; // We cannot load the texture in here, initalise it during init func
Random *random = new Random();
Keyboard *keyboard = new Keyboard();
Mouse *mouse = new Mouse();

std::list<Boat3D *> boats;

typedef struct
{
    int windowHeight;
    int windowWidth;
    bool runnning;
    float startTime;
    int frames;
    float FPS;
    float FPSInterval;
    float lastFPSTime;
    bool wireframe;
    float keyPressTime;
    float updateBoatTime;
    float boatCreationTime;
} global_t;

global_t global = {600, 600, true, 0.0, 0, 0.0, 1, 0.0, false, -1, -1, -1};

// Application Functions
void myinit();
void myReshape(int w, int h);
void display();
void update();
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void keyPress(unsigned char key);
void displayFPS();
void updateProjectiles(float dt);
void updateDefences(float dt);

// Draw funcitons
void drawAxis(float length);
void drawCircle(vec2f location, float r);

// Calc functions
float radToDeg(float rad);
float degToRad(float deg);
float gradToRad(float grad);
float calcGrad(float x1, float y1, float x2, float y2);

void mouseMotion(int x, int y);
void mouseFunction(int button, int state, int x, int y);
void keyPressSpecial(int key);
void keyUpSpecial(int key, int x, int y);
void keyDownSpecial(int key, int x, int y);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

    glutInitWindowSize(global.windowWidth, global.windowHeight);
    glutCreateWindow("Island Defence");

    myinit();

    //glEnable(GL_DEPTH_TEST);

    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutSpecialFunc(keyDownSpecial);
    glutSpecialUpFunc(keyUpSpecial);
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouseFunction);

    glutMainLoop();
}

// Application Functions

void myinit()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glShadeModel(GL_FLAT);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    seafloor = new Seafloor(windowSize); // We have to initialise it here or at least import the texture here

    // Set global start time
    global.startTime = glutGet(GLUT_ELAPSED_TIME) / (float)milli;

    // std::cout << radToDeg(gradToRad(calcVectorGrad({-1, 1, -1}, {0, 0, 0}))) << std::endl;
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	//gluPerspective(45.0, ((float)w / (float)h), 0.01, 100);

    glOrtho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set global window dimensions
    global.windowWidth = w;
    global.windowHeight = h;
}

void display()
{
    // Error variable
    GLenum err;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.8f, 0.8f, 0.8f);
    // FPS Counter
    glLoadIdentity();
    displayFPS();
    glLoadIdentity();

	//Draw Health Bars
	island->drawHealth();
	boat1->drawHealth();
	boat2->drawHealth();

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	GLfloat light_ambient[] = { 0.8, 0.8, 0.65, 0.75 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.65, 0.75 };
	GLfloat light_position[] = { 1.0, 1.0, 0.8, 0.0 };

    /*glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);*/

    if (global.wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glRotatef(mouse->cameraRotationX, 0, 1.0, 0);
    glRotatef(mouse->cameraRotationY, 1.0, 0, 0);

    float scale = mouse->zoomValue;
    glScalef(scale, scale, scale);

    // Start Wireframe
    if (global.wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Draw Axis
    drawAxis(windowSize);

	glDisable(GL_LIGHT0);
    // Draw seafloor
    glPushMatrix();
    seafloor->draw();
    glPopMatrix();

    // Draw Wave
    glPushMatrix();
    wave->drawAdvanced();
    glPopMatrix();

	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Draw 3D Island
    glPushMatrix();
    island3D->draw();
    glPopMatrix();

    // Draw Island
    // island->draw();

    // Draw AI Boats
    for (std::list<Boat3D *>::iterator boat = boats.begin();
         boat != boats.end(); ++boat)
    {
        (*boat)->draw();
    }

    // Draw Boat 1
    glPushMatrix();
    boat1->setLocation({boat1->getLocation().x,
                        wave->getYfromX(boat1->getLocation().x)});
    boat1->setBoatDeg(wave->getGrad(boat1->getLocation().x));
    boat1->setScale(0.1);
    boat1->draw();
    glPopMatrix();
    // Draw Boat 1 Axis
    glPushMatrix();
    glTranslatef(boat1->getLocation().x, boat1->getLocation().y, 0.0);
    glRotatef(boat1->getBoatDeg(), 0, 0, 1.0);
    drawAxis(0.1);
    glPopMatrix();
    // Hitbox (Uncomment for visual)
    // drawCircle(boat1->getLocation(), boat1->getScale());

    // Draw Boat 2
    glPushMatrix();
    boat2->setLocation({boat2->getLocation().x,
                        wave->getYfromX(boat2->getLocation().x)});
    boat2->setBoatDeg(wave->getGrad(boat2->getLocation().x));
    boat2->setScale(0.1);
    boat2->draw();
    glPopMatrix();
    // Draw Boat 2 Axis
    glPushMatrix();
    glTranslatef(boat2->getLocation().x, boat2->getLocation().y, 0.0);
    glRotatef(boat2->getBoatDeg(), 0, 0, 1.0);
    drawAxis(0.1);
    glPopMatrix();
    // Hitbox (Uncomment for visual)
    // drawCircle(boat2->getLocation(), boat2->getScale());

    // Projectile creation location (Uncomment for visual)
    // drawCircle(island->getCannonLocation(), 0.01);
    // drawCircle(boat1->getCannonLocation(), 0.01);
    // drawCircle(boat2->getCannonLocation(), 0.01);

    // Draw Projectiles
    /*if (island->getProjectileExists())
        island->drawProjectile(wave);
    if (boat1->getProjectileExists())
        boat1->drawProjectile(wave);
    if (boat2->getProjectileExists())
        boat2->drawProjectile(wave);

    // Draw Defences
    if (boat1->getDefenceExists())
        boat1->drawDefence(wave);
    if (boat2->getDefenceExists())
        boat2->drawDefence(wave);

    // End Wireframe
    if (global.wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Game Over Message
    if (!global.runnning)
    {
        glPushMatrix();
        std::string text = "Game Over";
        int len = text.length();
        float dist = ((float)(len * 9) / global.windowWidth);
        glTranslatef(-dist, 0.0, 0.0);
        glColor3f(0.0, 0.0, 0.0);
        glRasterPos2f(0, 0);
        for (int i = 0; i < len; i++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
        glPopMatrix();
    }*/
	
	glDisable(GL_LIGHTING);
    glPopMatrix();

    glutSwapBuffers();

    global.frames++;

    while ((err = glGetError()) != GL_NO_ERROR)
        printf("display: %s\n", gluErrorString(err));
}

void update()
{
    // Last time only accessable in this function and value retained
    static float lastT = -1.0;
    // t: time since start (seconds) | dt: difference time from lastT (seconds)
    float t;
    float dt;

    t = glutGet(GLUT_ELAPSED_TIME) / (float)milli - global.startTime;

    if (lastT < 0.0)
    {
        lastT = t;
        return;
    }

    dt = t - lastT;
    // Move Wave
    if (wave->getAnimate())
        wave->moveWave(glutGet(GLUT_ELAPSED_TIME) / (float)milli / 2);

    // Keypresses
    if (global.keyPressTime + 20 < glutGet(GLUT_ELAPSED_TIME))
    {
        std::list<unsigned char> *pressed = keyboard->getPressed();

        for (std::list<unsigned char>::iterator i = pressed->begin();
             i != pressed->end(); ++i)
        {
            keyPress(*i);
        }

        // Loop through the special list
        std::list<int>* pressedSpecial = keyboard->getPressedSpecial();

        for (std::list<int>::iterator i = pressedSpecial->begin();
            i != pressedSpecial->end(); ++i)
        {
            keyPressSpecial(*i);
        }
        global.keyPressTime = glutGet(GLUT_ELAPSED_TIME);
    }

    // Create Boat AI
    if (global.boatCreationTime + 3000 < glutGet(GLUT_ELAPSED_TIME))
    {
        float location = (float)random->getRandom(-1000, 1000) / 1000;
        int side = random->getRandom(1, 4);

        vec3f boat3DLocation = {0, 0, 0};

        switch (side)
        {
        case 1:
            boat3DLocation.x = location;
            boat3DLocation.z = 1;
            break;
        case 2:
            boat3DLocation.x = 1;
            boat3DLocation.z = location;
            break;
        case 3:
            boat3DLocation.x = location;
            boat3DLocation.z = -1;
            break;
        case 4:
            boat3DLocation.x = -1;
            boat3DLocation.z = location;
            break;
        }

        boat3DLocation.y = wave->getYfromXZ(boat3DLocation.x, boat3DLocation.z);

        Boat3D *boat3D = new Boat3D(boat3DLocation, 0, 0, 45);

        boats.push_back(boat3D);

        global.boatCreationTime = glutGet(GLUT_ELAPSED_TIME);
    }

    // Update AI Boats
    if (global.updateBoatTime + 20 < glutGet(GLUT_ELAPSED_TIME))
    {
        for (std::list<Boat3D *>::iterator boat = boats.begin();
             boat != boats.end(); ++boat)
        {
            float dist = 0.0007;

            vec3f location = (*boat)->getLocation();
            float destX = 0;
            float destZ = 0;

            float grad = calcGrad(location.x, location.z, destX, destZ);
            // std::cout << grad << std::endl;
            float rad = gradToRad(grad);
            // std::cout << rad << std::endl;
            float deg = radToDeg(rad);
            // std::cout << deg << std::endl;

            float xChange = dist * cos(deg);
            float zChange = dist * sin(deg);

            location.x += xChange;
            location.z += zChange;

            location.y = wave->getYfromXZ(location.x, location.z);

            (*boat)->setPrevLocation();
            (*boat)->setLocation(location);
            (*boat)->updateBoatRotation();

            vec3f prevLocation = (*boat)->getPrevLocation();
            prevLocation.y = wave->getYfromXZ(prevLocation.x, prevLocation.z);
            grad = calcVectorGrad(prevLocation, location);
            // std::cout << gradToDeg(1) << std::endl;
            (*boat)->setBoatDeg(gradToDeg(grad));

            // (*boat)->calcBoatDegFromPrev();
        }

        for (std::list<Boat3D *>::iterator boat = boats.begin();
             boat != boats.end(); ++boat)
        {
            bool collision = island3D->collision((*boat)->getLocation());
            if (collision)
            {
                boats.erase(boat);
                break;
                std::cout << "Colides" << std::endl;
            }
        }

        global.updateBoatTime = glutGet(GLUT_ELAPSED_TIME);
    }

    // Update Defence and Projectile Locations
    updateDefences(dt);
    updateProjectiles(dt);

    // Boat 1 Defences
    std::list<Defence *> *defences1 = boat1->getDefences();
    for (std::list<Defence *>::iterator d = defences1->begin();
         d != defences1->end(); ++d)
    {
        (*d)->increaseRadius();
    }
    // Boat 2 Defences
    std::list<Defence *> *defences2 = boat2->getDefences();
    for (std::list<Defence *>::iterator d = defences2->begin();
         d != defences2->end(); ++d)
    {
        (*d)->increaseRadius();
    }
    lastT = t;

    // Counter
    dt = t - global.lastFPSTime;
    if (dt > global.FPSInterval)
    {
        global.FPS = global.frames / dt;
        global.lastFPSTime = t;
        global.frames = 0;
    }

    glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
    if (mouse->moveCamera)
    {
        if (x < mouse->lastMouse1X)
        {
            mouse->cameraRotationX++;
        }
        else if (x > mouse->lastMouse1X)
        {
            mouse->cameraRotationX--;
        }
        if (y < mouse->lastMouse1Y)
        {
            mouse->cameraRotationY++;
        }
        else if (y > mouse->lastMouse1Y)
        {
            mouse->cameraRotationY--;
        }
        mouse->lastMouse1X = x;
        mouse->lastMouse1Y = y;
    }
    else if (mouse->zoom)
    {
        if (y < mouse->lastMouse2Y)
        {
            mouse->zoomValue += 0.01;
        }
        else if (y > mouse->lastMouse2Y)
        {
            if (mouse->zoomValue - 0.01 > 0.01)
                mouse->zoomValue -= 0.01;
        }
        mouse->lastMouse2Y = y;
    }
}

void mouseFunction(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouse->moveCamera = true;
        mouse->mouse1XDown = x + mouse->mouse1XUp;
        mouse->mouse1YDown = y + mouse->mouse1YUp;
        // std::cout << x << " : " << y << std::endl;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        mouse->moveCamera = false;
        mouse->mouse1XUp = mouse->cameraRotationX;
        mouse->mouse1YUp = mouse->cameraRotationY;
        // std::cout << x << " : " << y << std::endl;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        mouse->zoom = true;
        mouse->mouse2YDown = y;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
    {
        mouse->zoom = false;
        mouse->mouse2YUp = y;
    }
}

void keyDown(unsigned char key, int x, int y)
{
    // Keyboard single presses, else require holding
    switch (key)
    {
    case 27: // ESC - Quit Game
        exit(EXIT_SUCCESS);
        break;
    case 'n': // Wave - Normal
        wave->toggleNormal();
        break;
    case 't': // Wave - Tangent
        wave->toggleTangent();
        break;
    case 45: // Wave Segments (-)
        wave->decreaseNumSegments();
        break;
    case 61: // Wave Segments (+)
        wave->increaseNumSegments();
        break;
    case 'g': // Wave Toggle Animation
        wave->toggleAnimation();
        break;
    case 'q': // Wave Wireframe
        global.wireframe = !global.wireframe;
        break;
    default:
        keyboard->keyDown(key);
        break;
    }
}

void keyDownSpecial(int key, int x, int y)
{
    // Keyboard single presses, else require holding
    switch (key)
    {
    default:
        keyboard->keyDownSpecial(key);
        break;
    }
}

void keyUp(unsigned char key, int x, int y)
{
    keyboard->keyUp(key);
}

void keyUpSpecial(int key, int x, int y)
{
    keyboard->keyUpSpecial(key);
}

void keyPressSpecial(int key)
{
    // Keypress functionality for simultaneous holding
    if (global.runnning)
    {
        switch (key)
        {
        case GLUT_KEY_LEFT:
            island3D->cannonRotation -= CANNON_ROTATION_SPEED;
            break;
        case GLUT_KEY_RIGHT:
            island3D->cannonRotation += CANNON_ROTATION_SPEED;
            break;
        }
        /*default:
            keyboard->keyDownSpecial(key);
            break;
        }*/
        glutPostRedisplay();
    }
}

void keyPress(unsigned char key)
{
    // Keypress functionality for simultaneous holding
    if (global.runnning)
    {
        switch (key)
        {
        case 'f': // Island Cannon Left
            island->cannonLeft(2.5);
            break;
        case 'h': // Island Cannon Right
            island->cannonRight(2.5);
            break;
        case 32: // Island Cannon Fire
            island->shoot();
            break;
        case 'a': // Cannon Tilt Down
            island3D->tiltCannonDown();
            break;
        case 'd': // Cannon Tilt Up
            island3D->tiltCannonUp();
            break;
        case 'w': // Boat Left Cannon left
            boat1->cannonLeft(5);
            break;
        case 's': // Boat Left Cannon Right
            boat1->cannonRight(5);
            break;
        case 'e': // Boat Left Fire
            boat1->shoot();
            break;
        case 'r': // Boat Left Defence
            boat1->defence();
            break;
        case 'j': // Boat Right Move Left
            boat2->moveLeft(0.01);
            break;
        case 'l': // Boat Right Move Right
            boat2->moveRight(0.01);
            break;
        case 'i': // Boat Right Cannon Left
            boat2->cannonLeft(5);
            break;
        case 'k': // Boat Right Cannon Right
            boat2->cannonRight(5);
            break;
        case 'o': // Boat Right Fire
            boat2->shoot();
            break;
        case 'p': // Boat Right Defence
            boat2->defence();
            break;
        default:
            break;
        }
        glutPostRedisplay();
    }
}

void displayFPS()
{
    colour col = {1.0, 1.0, 1.0, 1.0};

    // Display FPS Counter
    glPushMatrix();
    std::string text = "FPS: " + std::to_string((int)global.FPS);
    int len = text.length();
    float dist = ((float)(len * 9) / global.windowWidth * 2);
    glTranslatef(0.95 - dist, 0.92, 0.0);
    glColor3f(col.r, col.g, col.b);
    glRasterPos2f(0, 0);
    for (int i = 0; i < len; i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    glPopMatrix();

    // Display FPS counter update time in seconds
    glPushMatrix();
    text = "Frame Time: " + std::to_string((int)global.FPSInterval);
    len = text.length();
    dist = ((float)(len * 9) / global.windowWidth * 2);
    glTranslatef(0.95 - dist, 0.86, 0.0);
    glColor3f(col.r, col.g, col.b);
    glRasterPos2f(0, 0);
    for (int i = 0; i < len; i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    glPopMatrix();

    // Display Tessellation Count
    glPushMatrix();
    text = "Tessellation: " + std::to_string(wave->getNumSegments());
    len = text.length();
    dist = ((float)(len * 9) / global.windowWidth * 2);
    glTranslatef(0.95 - dist, 0.80, 0.0);
    glColor3f(col.r, col.g, col.b);
    glRasterPos2f(0, 0);
    for (int i = 0; i < len; i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    glPopMatrix();
}

void updateProjectiles(float dt)
{
    // Update All Projectiles
    island->updateProjectile(dt);
    boat1->updateProjectile(dt);
    boat2->updateProjectile(dt);

    // Lambda function for collision detection
    auto projectileCollision = [&](std::list<Projectile *> *projectiles) {
        bool collision = false;

        for (std::list<Projectile *>::iterator p = projectiles->begin();
             p != projectiles->end(); ++p)
        {
            vec2f location = (*p)->getLocation();

            // Boat 1 Defences
            std::list<Defence *> *defences1 = boat1->getDefences();
            for (std::list<Defence *>::iterator d = defences1->begin();
                 d != defences1->end(); ++d)
            {
                if ((*p)->getCollision((*d)->getRadius(), (*d)->getLocation()))
                    collision = true;
            }
            // Boat 2 Defences
            std::list<Defence *> *defences2 = boat2->getDefences();
            for (std::list<Defence *>::iterator d = defences2->begin();
                 d != defences2->end(); ++d)
            {
                if ((*p)->getCollision((*d)->getRadius(), (*d)->getLocation()))
                    collision = true;
            }

            // Island
            if (!(*p)->getIsBoat())
            {
                // Boat 1 Collision
                if ((*p)->getCollision(boat1->getScale(), boat1->getLocation()))
                {
                    collision = true;
                    if (boat1->damage())
                        global.runnning = false;
                }
                // Boat 2 Collision
                if ((*p)->getCollision(boat2->getScale(), boat2->getLocation()))
                {
                    collision = true;
                    if (boat2->damage())
                        global.runnning = false;
                }
            }
            else
            {
                // Island Collision
                if (island->collision(location))
                {
                    collision = true;
                    if (island->damage())
                        global.runnning = false;
                }

                //Boats
                if ((*p)->getBoatNum() == 0)
                {
                    // Boat 2 Collision
                    if ((*p)->getCollision(boat2->getScale(),
                                           boat2->getLocation()))
                    {
                        collision = true;
                        if (boat2->damage())
                            global.runnning = false;
                    }
                }
                else if ((*p)->getBoatNum() == 1)
                {
                    // Boat 1 Collision
                    if ((*p)->getCollision(boat1->getScale(),
                                           boat1->getLocation()))
                    {
                        collision = true;
                        if (boat1->damage())
                            global.runnning = false;
                    }
                }
            }

            // Wave Collision
            if (wave->getYfromX(location.x) >= location.y)
                collision = true;

            if (collision)
            {
                projectiles->erase(p);
                return collision;
            }
        }
        return collision;
    };

    // Lambda function calls for all projectiles
    if (island->getProjectileExists())
        if (projectileCollision(island->getProjectiles()))
            island->removeProjectile();
    if (boat1->getProjectileExists())
        if (projectileCollision(boat1->getProjectiles()))
            boat1->removeProjectile();
    if (boat2->getProjectileExists())
        if (projectileCollision(boat2->getProjectiles()))
            boat2->removeProjectile();
}

void updateDefences(float dt)
{
    // Update All Defences
    boat1->updateDefence(dt);
    boat2->updateDefence(dt);

    // Lambda function for collision detection
    auto defenceCollision = [&](std::list<Defence *> *defences) {
        bool collision = false;

        for (std::list<Defence *>::iterator d = defences->begin();
             d != defences->end(); ++d)
        {
            vec2f location = (*d)->getLocation();
            // Wave Collision
            if (wave->getYfromX(location.x) >= location.y)
            {
                defences->erase(d);
                collision = true;
                break;
            }
        }

        return collision;
    };

    // Lambda function calls for all defences
    if (boat1->getDefenceExists())
        if (defenceCollision(boat1->getDefences()))
            boat1->removeDefence();
    if (boat2->getDefenceExists())
        if (defenceCollision(boat2->getDefences()))
            boat2->removeDefence();
}

// Draw funcitons

void drawAxis(float length)
{
    // X Axis
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(length, 0, 0);
    glEnd();

    // Y Axis
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, length, 0);
    glEnd();

    // Z Axis
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, length);
    glEnd();
    glColor3f(1, 1, 1);
}

void drawCircle(vec2f location, float r)
{
    const float numSegments = 50;

    float x = location.x;
    float y = location.y;

    // Drawing segments of circle
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; i++)
    {
        float theta = 2.0 * M_PI * float(i) / float(numSegments);
        float x1 = cos(theta) * r;
        float y1 = sin(theta) * r;
        glVertex2f(x1 + x, y1 + y);
    }
    glEnd();
}