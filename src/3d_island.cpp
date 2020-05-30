#include "3d_island.h"

void drawDot(float x, float y, float z) {
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
    glPopMatrix();
}

vec3f Island3D::endOfCannon()
{
    float J = CANNON_LENGTH * cosf(degToRad(cannonRotation));

    float x = J * sinf(degToRad(cannonPitch));
    float y = CANNON_LENGTH * cosf(degToRad(cannonPitch));
    float z = x * tanf(degToRad(cannonRotation));

    // Apply our constant modifications to set the correct coordinates
    x = -x;
    y = y + (-CANNON_BASE_OFFSET + GUN_BOX_HEIGHT);

    return { x, y, z };
}

Island3D::Island3D()
{
    this->texture = new Texture("../src/sand.jpg");
	this->cannon = new Cylinder(CANNON_RADIUS, CANNON_LENGTH, 64);
    this->cannonBaseMiddle = new Cylinder(0.1, 0.25, 64);
    this->cannonGunBaseCylinder = new HalfCylinder(CANNON_BASE_CYLINDER_RADIUS, CANNON_BASE_CYLINDER_SIZE, 64);

    this->gunBox = new Rectangle3D(GUN_BOX_HEIGHT, CANNON_BASE_CYLINDER_RADIUS * 2, CANNON_BASE_CYLINDER_SIZE);
}

void Island3D::draw()
{
    texture->enable();

    glColor3f(0.9, 0.8, 0.5);

    // Very very bottom cylinder
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glRotatef(-90, 1.0, 0, 0);

    GLUquadric *qobj = gluNewQuadric();
    gluCylinder(qobj, radius, radius, 0.5, 40, 40);
    glPopMatrix();

    // Sphere
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    glRotatef(-90, 1.0, 0, 0);
    glutSolidSphere(radius, 40, 40);
    glPopMatrix();

    // Cylinder Base (Middle)
    glPushMatrix();
    glTranslatef(0, -0.49, 0);
    cannonBaseMiddle->draw();
    glPopMatrix();

    // Boxy box
    glPushMatrix();
    glTranslatef(0, -CANNON_BASE_OFFSET, 0);
    glRotatef(cannonRotation - 180, 0.0, 1.0, 0.0);
    gunBox->draw();
    glPopMatrix();

    // Cylinder Base (Gun Base)
    glPushMatrix();
    glTranslatef(0, -CANNON_BASE_OFFSET + GUN_BOX_HEIGHT/2, 0);
    glRotatef(cannonRotation, 0.0, 1.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glTranslatef(0, -CANNON_BASE_CYLINDER_SIZE/2, 0);
    cannonGunBaseCylinder->draw();
    glPopMatrix();

	// Cannon
	glPushMatrix();

    glTranslatef(0, -CANNON_BASE_OFFSET + GUN_BOX_HEIGHT, 0);
    // Rotation
    glRotatef(cannonRotation, 0.0, 1.0, 0.0);
    // Pitch
    glRotatef(cannonPitch, 0.0, 0.0, 1.0);

    cannon->draw();
	glPopMatrix();

    // Used for testing where the cannon is
    glPushMatrix();
    // Start of behind of cannon
    drawDot(0.0, 0 - CANNON_BASE_OFFSET + GUN_BOX_HEIGHT, 0.0);
    // End of cannon pos
    drawDot(-CANNON_LENGTH, 0 - CANNON_BASE_OFFSET + GUN_BOX_HEIGHT, 0.0);

    vec3f end = endOfCannon();
    //printf("Cannon rotation %f p: %f x: %f y: %f z: %f\n", cannonRotation, cannonPitch, end.x, end.y, end.z);

    drawDot(end.x, end.y, end.z);

    glPopMatrix();

    texture->disable();
}

void Island3D::tiltCannonUp()
{
    if (cannonPitch + CANNON_TILT_SPEED > CANNON_TILT_MAX)
        return;
    
    cannonPitch += CANNON_TILT_SPEED;
}

void Island3D::tiltCannonDown()
{
    //printf("%f %f\n", cannonPitch, cannonPitch + CANNON_TILT_SPEED);
    if (cannonPitch + CANNON_TILT_SPEED < CANNON_TILT_MIN) {
        //printf("RETURNEDDD");
        return;
    }

    cannonPitch -= CANNON_TILT_SPEED;
}

bool Island3D::collision(vec3f location)
{
    float dist = calcVectorDistance(location, {0, -0.5, 0});
    if (dist <= radius)
        return true;
    return false;
}