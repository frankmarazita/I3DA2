// I3D Assignment 02 - Island Defence

#ifndef M_PI
#define M_PI 3.141592653589793238463
#endif

#include "opengl.h"

#include "vec2f.h"
#include "vec3f.h"
#include "colour.h"

#include "3d_wave.h"
#include "3d_island.h"
#include "3d_boat.h"
#include "seafloor.h"
#include "random.h"
#include "keyboard.h"
#include "mouse.h"
#include "skybox.h"
#include "time.h"
#include "effect.h"

#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <list>
#include <vector>
#include <string>

#define DEFAULT_SEGMENTS 64

typedef struct
{
    int milli;
    float worldSize;
    int windowHeight;
    int windowWidth;
    bool runnning;
    float startTime;
    int frames;
    float FPS;
    float FPSInterval;
    float lastFPSTime;
    bool wireframe;
    bool lighting;
    bool textures;
    bool pause;
    float keyPressTime;
    float updateBoatTime;
    float boatCreationTime;
    int segments;
    bool showNormals;
    bool gameStarted;
} global_t;

global_t global = {1000, 1, 600, 600, true, 0.0, 0, 0.0, 1, 0.0, false, true, true, false, -1, -1, -1, 64, false, false};

// Game objects
Wave3D *wave = new Wave3D(global.worldSize, DEFAULT_SEGMENTS, 0.07, 9, 0.25 * M_PI, 0, -0.5);
Island3D *island3D;
Seafloor *seafloor;
Skybox *skybox;
Random *random = new Random();
Keyboard *keyboard = new Keyboard();
Mouse *mouse = new Mouse();
Time *time;

std::list<Projectile3D *> projectiles;
std::list<Defence3D *> defences;
std::vector<Boat3D *> boats;
std::vector<Effect *> effects;

// Application Functions
void myinit();
void myReshape(int w, int h);
void display();
void update();
void keyDown(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void keyPress(unsigned char key);
void displayFPS();
void condCheckLighting();

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

    glEnable(GL_DEPTH_TEST);

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

    seafloor = new Seafloor(global.worldSize); // We have to initialise it here or at least import the texture here
    skybox = new Skybox();
    island3D = new Island3D(DEFAULT_SEGMENTS);
    time = new Time();

    // Set global start time
    time->update(glutGet(GLUT_ELAPSED_TIME));
    global.startTime = glutGet(GLUT_ELAPSED_TIME) / (float)global.milli;
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ((float)w / (float)h), 0.01, 100);

    //glOrtho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set global window dimensions
    global.windowWidth = w;
    global.windowHeight = h;
}

// Check whether or not to enable lighting again
void condCheckLighting()
{
    GLfloat mat_specular[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };

    if (global.lighting)
    {
        glEnable(GL_LIGHTING);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
    }
    else
    {
        glDisable(GL_LIGHTING);
    }
}

void display()
{
    // Error variable
    GLenum err;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glColor3f(0.8f, 0.8f, 0.8f);
    glLoadIdentity();

    // Moves the direction of the camera in line with the rotation of the cannon with an offset on the x axis
    vec3fSpherical sph = {0.9, 0.0, 165.0 + island3D->cannonSph.polar};
    vec3f xyz;
    xyz = sphericalToCartesian(sph);

    gluLookAt(xyz.x, 0.3, xyz.z, 0.0, 0.0, 0.0, xyz.x, 1.0, xyz.z);

    // Default lighting
    GLfloat light_ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_specular[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat light_position[] = {0.5, 0.5, 0.0, 0.0};
    GLfloat mat_emission[] = {0.0, 0.0, 0.0, 1.0};

    skybox->draw();

    condCheckLighting();

    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    if (global.wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (global.textures)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);

    glRotatef(mouse->cameraRotationX, 0, 1.0, 0);
    glRotatef(mouse->cameraRotationY, 1.0, 0, 0);

    float scale = mouse->zoomValue;
    glScalef(scale, scale, scale);

    // Start Wireframe
    if (global.wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Draw seafloor
    seafloor->draw();

    // Draw Wave
    glPushMatrix();
    wave->drawAdvanced();
    glPopMatrix();

    // Draw 3D Island
    glPushMatrix();
    island3D->draw(global.showNormals);
    island3D->drawTrajectory(wave);
    glPopMatrix();

    // The trajectory of the island re-enables lighting, check whether we disabled it
    condCheckLighting();

    // Draw AI Boats
    for (int i = 0; i < boats.size(); i++)
    {
        boats[i]->draw(global.showNormals);
    }

    // Draw projectiles 3D
    for (std::list<Projectile3D *>::iterator projectile = projectiles.begin();
         projectile != projectiles.end(); ++projectile)
    {
        (*projectile)->draw(wave, global.showNormals);
    }

    if (global.lighting)
    {
        glEnable(GL_LIGHTING);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
    }
    else
    {
        glDisable(GL_LIGHTING);
    }

    // Draw defences 3D
    for (std::list<Defence3D *>::iterator defence = defences.begin();
         defence != defences.end(); ++defence)
    {
        (*defence)->draw(wave);
    }

    // Draw effects
    for (int i = 0; i < effects.size(); i++)
    {
        effects[i]->draw();
    }

    glDisable(GL_LIGHTING);
    glPopMatrix();

    // Push forward a matrix so we can draw to the screen
    glMatrixMode(GL_PROJECTION);                // change the current matrix to PROJECTION
    double matrix[16];                          // 16 doubles in stack memory
    glGetDoublev(GL_PROJECTION_MATRIX, matrix); // get the values from PROJECTION matrix to local variable
    glLoadIdentity();                           // reset PROJECTION matrix to identity matrix
    glOrtho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW); // change current matrix to MODELVIEW matrix again
    glLoadIdentity();           // reset it to identity matrix
    glPushMatrix();             // push current state of MODELVIEW matrix to stack

    // Draw Island OSD
    island3D->drawHealth();
    island3D->drawScore();
    displayFPS();

    // Paused Message
    if (!global.gameStarted)
    {
        glPushMatrix();
        std::string text = "Press SPACE to start...";
        int len = text.length();
        float dist = ((float)(len * 9) / global.windowWidth);
        glTranslatef(-dist, 0.0, 0.0);
        glColor3f(0.0, 0.0, 0.0);
        glRasterPos2f(0, 0);
        for (int i = 0; i < len; i++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
        glPopMatrix();
    }

    // Paused Message
    if (time->paused && global.runnning && global.gameStarted)
    {
        glPushMatrix();
        std::string text = "Paused";
        int len = text.length();
        float dist = ((float)(len * 9) / global.windowWidth);
        glTranslatef(-dist, 0.0, 0.0);
        glColor3f(0.0, 0.0, 0.0);
        glRasterPos2f(0, 0);
        for (int i = 0; i < len; i++)
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
        glPopMatrix();
    }

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
    }

    // Reset back
    glPopMatrix();               // get MODELVIEW matrix value from stack
    glMatrixMode(GL_PROJECTION); // change current matrix mode to PROJECTION
    glLoadMatrixd(matrix);       // reset
    glMatrixMode(GL_MODELVIEW);  // change current matrix mode to MODELVIEW

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

    t = time->getTime() / (float)global.milli - global.startTime;

    if (lastT < 0.0)
    {
        lastT = t;
        return;
    }

    dt = t - lastT;

    time->update(glutGet(GLUT_ELAPSED_TIME));
    if (time->paused)
        return;

    for (int i = 0; i < boats.size(); i++)
    {
        Boat3D *boat = boats[i];
        boat->time = time->getTime();
    }
    island3D->time = time->getTime();

    for (int i = 0; i < effects.size(); i++)
    {
        Effect *effect = effects[i];
        effect->time = time->getTime();
    }

    // printf("time: %i %i\n", time->glutTime, time->getTime());

    // Keypresses
    if (global.keyPressTime + 20 < time->getTime())
    {
        std::list<unsigned char> *pressed = keyboard->getPressed();

        for (std::list<unsigned char>::iterator i = pressed->begin();
             i != pressed->end(); ++i)
        {
            keyPress(*i);
        }

        // Loop through the special list
        std::list<int> *pressedSpecial = keyboard->getPressedSpecial();

        for (std::list<int>::iterator i = pressedSpecial->begin();
             i != pressedSpecial->end(); ++i)
        {
            keyPressSpecial(*i);
        }
        global.keyPressTime = time->getTime();
    }

    // Move Wave
    if (wave->getAnimate())
    {
        wave->moveWave(time->getTime() / (float)global.milli / 2);
        wave->update();
    }

    // Create Boat AI
    if (global.boatCreationTime + 3000 < time->getTime())
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

        Boat3D *boat3D = new Boat3D(boat3DLocation, 0, 0, 45, wave->getNumSegments());
        boats.push_back(boat3D);

        global.boatCreationTime = time->getTime();
    }

    // Update AI Boats
    if (global.updateBoatTime + 20 < time->getTime())
    {
        for (int i = 0; i < boats.size(); i++)
        {
            Boat3D *boat = boats[i];

            float dist = 0.0003;

            vec3f location = boat->getLocation();
            float destX = 0;
            float destZ = 0;

            float grad = calcGrad(location.x, location.z, destX, destZ);
            float rad = gradToRad(grad);
            float deg = radToDeg(rad);

            float xChange = dist * cos(deg);
            float zChange = dist * sin(deg);

            location.x += xChange;
            location.z += zChange;

            location.y = wave->getYfromXZ(location.x, location.z);

            boat->setPrevLocation();
            boat->setLocation(location);
            boat->updateBoatRotation();

            vec3f prevLocation = boat->getPrevLocation();
            prevLocation.y = wave->getYfromXZ(prevLocation.x, prevLocation.z);
            grad = calcVectorGrad(prevLocation, location);
            deg = gradToDeg(grad);
            boat->setBoatDeg(deg);
            float initialCannonDeg = boat->getInitialCannonDeg();
            boat->setCannonDeg(initialCannonDeg - deg);
            boat->calcProjectileOrigin();
            boat->calcProjectilePower();
        }

        for (int i = 0; i < boats.size(); i++)
        {
            Boat3D *boat = boats[i];

            bool collision = island3D->collision(boat->getLocation(), boat->getHitboxRadius());
            if (collision)
            {
                Effect *effect = new Effect(boat->getLocation(), time->getTime());
                effects.push_back(effect);

                boats.erase(boats.begin() + i);
                delete boat;
                island3D->damage();
                break;
            }
        }

        for (int i = 0; i < boats.size(); i++)
        {
            Boat3D *boat = boats[i];
            Projectile3D *proj = boat->shoot();
            if (proj)
                projectiles.push_back(proj);
        }

        global.updateBoatTime = time->getTime();
    }

    // Update Defences
    for (std::list<Defence3D *>::iterator d = defences.begin();
         d != defences.end(); ++d)
    {
        (*d)->time = time->getTime();
        (*d)->updateProjectileState(dt);
        (*d)->increaseRadius();
        vec3f location = (*d)->getLocation();
        float radius = (*d)->getRadius();

        if (wave->getYfromXZ(location.x, location.z) > location.y)
        {
            delete *d;
            defences.erase(d);
            break;
        }
    }

    // Update Projectiles
    for (std::list<Projectile3D *>::iterator p = projectiles.begin();
         p != projectiles.end(); ++p)
    {
        (*p)->updateProjectileState(dt);
        vec3f location = (*p)->getLocation();
        float radius = (*p)->getRadius();
        bool isBoat = (*p)->getIsBoat();

        if (wave->getYfromXZ(location.x, location.z) > location.y)
        {
            delete *p;
            projectiles.erase(p);
            break;
        }

        if (isBoat)
        {
            bool collision = island3D->collision(location, radius);
            if (collision)
            {
                island3D->damage();
                delete *p;
                projectiles.erase(p);
                break;
            }
        }
        else
        {
            bool erase = false;
            for (int i = 0; i < boats.size(); i++)
            {
                Boat3D *boat = boats[i];
                bool collision = boat->collision(location, radius);
                if (collision)
                {
                    Effect *effect = new Effect(boat->getLocation(), time->getTime());
                    effects.push_back(effect);

                    boats.erase(boats.begin() + i);
                    delete boat;
                    island3D->point();
                    erase = true;
                    break;
                }
            }
            if (erase)
            {
                delete *p;
                projectiles.erase(p);
                break;
            }
        }

        bool erase = false;
        for (std::list<Defence3D *>::iterator d = defences.begin();
             d != defences.end(); ++d)
        {
            if ((*d)->collision(location, radius))
            {
                erase = true;
                break;
            }
        }
        if (erase)
        {
            delete *p;
            projectiles.erase(p);
            break;
        }
    }

    // Update Effects
    for (int i = 0; i < effects.size(); i++)
    {
        effects[i]->update(dt);
    }

    for (int i = 0; i < effects.size(); i++)
    {
        Effect *effect = effects[i];
        if (effect->getNumParticles() == 0)
        {
            effects.erase(effects.begin() + i);
            delete effect;
            break;
        }
    }

    if (!island3D->getAlive())
    {
        time->pause();
        global.runnning = false;
    }

    // Counter
    lastT = t;
    dt = t - global.lastFPSTime;
    if (dt > global.FPSInterval)
    {
        global.FPS = global.frames / dt;
        global.lastFPSTime = t;
        global.frames = 0;
    }

    if (!global.gameStarted && !time->paused)
        time->pause();

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
    int numSegments;
    // Keyboard single presses, else require holding
    switch (key)
    {
    case 'w': // Increase Cannon Power
        island3D->increaseCannonPower();
        break;
    case 's': // Decrease Cannon Power
        island3D->decreaseCannonPower();
        break;
    case 'p': // Toggle Wireframe
        global.wireframe = !global.wireframe;
        break;
    case 'l': // Toggle Lighting
        global.lighting = !global.lighting;
        break;
    case 'n': // Normals and Tangents
        global.showNormals = !global.showNormals;
        wave->toggleNormal();
        wave->toggleTangent();
        break;
    case 't': // Toggle Textures
        global.textures = !global.textures;
        break;
    case 'h': // Pause/Resume Game Animations
        if (!global.gameStarted)
            break;
        global.pause = !global.pause;
        wave->toggleAnimation();
        time->toggle();
        break;
    case 32:
        if (!global.gameStarted)
        {
            global.gameStarted = true;
            time->resume();
        }
        else
        {
            keyboard->keyDown(key);
        }
        break;
    case 61: // Wave Segments (+)
        global.segments *= 2;
        wave->setNumSegments(global.segments);
        island3D->setSegments(global.segments);
        break;
    case 45: // Wave Segments (-)
        // Halve the number of segments
        numSegments = global.segments / 2;
        // Check for minimum 4
        if (numSegments >= 4)
        {
            global.segments = numSegments;
            wave->setNumSegments(numSegments);
            island3D->setSegments(numSegments);
        }
        break;
    case 27: // ESC - Quit Game
        exit(EXIT_SUCCESS);
        break;
    case 'q':
        exit(EXIT_SUCCESS);
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
        case GLUT_KEY_LEFT: // Cannon Rotate Left
            island3D->rotateCannonLeft();
            break;
        case GLUT_KEY_RIGHT: // Cannon Rotate Right
            island3D->rotateCannonRight();
            break;
        }
        glutPostRedisplay();
    }
}

void keyPress(unsigned char key)
{
    Projectile3D *proj;
    Defence3D *defence;
    // Keypress functionality for simultaneous holding
    if (global.runnning)
    {
        switch (key)
        {
        case 'a': // Cannon Tilt Up
            island3D->tiltCannonUp();
            break;
        case 'd': // Cannon Tilt Down
            island3D->tiltCannonDown();
            break;
        case 32: // Island Cannon Fire
            if (global.gameStarted)
            {
                proj = island3D->shoot();
                if (proj)
                    projectiles.push_back(proj);
            }
            break;
        case 'v': // Island Cannon Defence
            defence = island3D->defence();
            if (defence)
                defences.push_back(defence);
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

    // Display Cannon Magnitude
    glPushMatrix();
    text = "Power: " + std::to_string(island3D->cannonSph.magnitude);
    len = text.length();
    dist = ((float)(len * 9) / global.windowWidth * 2);
    glTranslatef(0.95 - dist, 0.74, 0.0);
    glColor3f(col.r, col.g, col.b);
    glRasterPos2f(0, 0);
    for (int i = 0; i < len; i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    glPopMatrix();
}