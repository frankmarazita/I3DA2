#include "3d_island.h"

// Util for debugging, remove later
void drawDot(float x, float y, float z)
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
    glPopMatrix();
}

Island3D::Island3D()
{
    this->texture = new Texture("../src/sand.jpg");
    this->cannon = new Cylinder(CANNON_RADIUS, CANNON_LENGTH, 64);
    this->cannonBaseMiddle = new Cylinder(CANNON_BASE_CYLINDER_RADIUS, CANNON_BASE_CYLINDER_HEIGHT, 64);
    this->cannonGunBaseCylinder = new HalfCylinder(CANNON_BASE_HALF_CYLINDER_RADIUS, CANNON_BASE_HALF_CYLINDER_SIZE, 64);

    this->gunBox = new Rectangle3D(GUN_BOX_HEIGHT, CANNON_BASE_HALF_CYLINDER_RADIUS * 2, CANNON_BASE_HALF_CYLINDER_SIZE);
}

vec3f Island3D::endOfCannon()
{
    float J = CANNON_LENGTH * cosf(degToRad(CANNON_ROTATION_OFFSET + cannonSph.polar));

    float x = J * sinf(degToRad(CANNON_PITCH_OFFSET + cannonSph.a));
    float y = CANNON_LENGTH * cosf(degToRad(CANNON_PITCH_OFFSET + cannonSph.a));
    float z = x * tanf(degToRad(CANNON_ROTATION_OFFSET + cannonSph.polar));

    // Apply our constant modifications to set the correct coordinates
    x = -x;
    float BOX_OFFSET = location.y + CANNON_BASE_CYLINDER_OFFSET_FROM_SPHERE + CANNON_BASE_CYLINDER_HEIGHT + GUN_BOX_HEIGHT / 2;
    y = y + BOX_OFFSET + GUN_BOX_HEIGHT / 2 + CANNON_RADIUS;

    return {x, y, z};
}

Projectile3D *Island3D::shoot()
{
    // Check for projectile shoot cooldown
    if (glutGet(GLUT_ELAPSED_TIME) - shootTime >= cooldownTime)
    {
        shootTime = glutGet(GLUT_ELAPSED_TIME);

        // Create a new projectile and return it
        Projectile3D *projectile = new Projectile3D(endOfCannon(), cannonSph, false, 0);
        return projectile;
    }
    return NULL;
}

Defence3D *Island3D::defence()
{
    // Check for defence shoot cooldown
    if (glutGet(GLUT_ELAPSED_TIME) - defenceTime >= cooldownTime)
    {
        defenceTime = glutGet(GLUT_ELAPSED_TIME);

        // Create a new defence and return it
        Defence3D *defence = new Defence3D(endOfCannon(), cannonSph, defenceTime);
        return defence;
    }
    return NULL;
}

void Island3D::draw()
{
    texture->enable();

    glColor4f(col.r, col.g, col.b, col.a);

    glColor3f(0.9, 0.8, 0.5);

    // Very very bottom cylinder
    glPushMatrix();
    glTranslatef(0, -1, 0); // Start from the bottom
    glRotatef(-90, 1.0, 0, 0);

    GLUquadric *qobj = gluNewQuadric();
    gluCylinder(qobj, ISLAND_BASE_RADIUS, ISLAND_BASE_RADIUS, 0.5, 40, 40);
    glPopMatrix();

    // Sphere
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(location.x, location.y, location.z); // 0.0, -0.5, 0.0
    glRotatef(-90, 1.0, 0, 0);
    glutSolidSphere(ISLAND_BASE_RADIUS, 40, 40);
    glPopMatrix();

    // Cylinder Base (Middle)
    glPushMatrix();
    glTranslatef(0, location.y + CANNON_BASE_CYLINDER_OFFSET_FROM_SPHERE + CANNON_BASE_CYLINDER_HEIGHT / 2, 0);
    cannonBaseMiddle->draw();
    glPopMatrix();

    // Origin of the gunbox
    float BOX_OFFSET = location.y + CANNON_BASE_CYLINDER_OFFSET_FROM_SPHERE + CANNON_BASE_CYLINDER_HEIGHT + GUN_BOX_HEIGHT / 2;

    // Boxy box
    glPushMatrix();
    glTranslatef(0, BOX_OFFSET, 0);
    glRotatef(cannonSph.polar, 0.0, 1.0, 0.0);
    gunBox->draw();
    glPopMatrix();

    // Half Cylinder Base (Gun Base)
    glPushMatrix();
    glTranslatef(0, BOX_OFFSET + GUN_BOX_HEIGHT / 2, 0); // Directly above the gunbox
    // Rotate the half cylinder by rotation
    glRotatef(cannonSph.polar, 0.0, 1.0, 0.0);
    // Rotates the half cylinder so it's not sideways
    glRotatef(-90, 1.0, 0.0, 0.0);
    cannonGunBaseCylinder->draw();
    glPopMatrix();

    // Cannon
    glPushMatrix();

    // Placed above the box
    glTranslatef(0.0, BOX_OFFSET + GUN_BOX_HEIGHT / 2 + CANNON_RADIUS, 0);
    // Rotation
    glRotatef(CANNON_ROTATION_OFFSET + cannonSph.polar, 0.0, 1.0, 0.0);
    // Pitch
    glRotatef(CANNON_PITCH_OFFSET + cannonSph.a, 0.0, 0.0, 1.0);
    // Shifts the cannon across after rotations so its centered inside the gun
    glTranslatef(0.0, CANNON_BASE_CYLINDER_HEIGHT / 2, 0.0);
    cannon->draw();
    glPopMatrix();

    // Used for testing where the cannon is
    glPushMatrix();
    // End of cannon pos
    drawDot(-CANNON_LENGTH, BOX_OFFSET + GUN_BOX_HEIGHT / 2 + CANNON_RADIUS, 0.0);
    vec3f end = endOfCannon();
    drawDot(end.x, end.y, end.z);
    glPopMatrix();

    texture->disable();
}

void Island3D::drawHealth()
{
    float x = -0.95 + 0.005 * 100;
    glPushMatrix();
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.95, 0.95);
    glVertex2f(-0.95, 0.92);
    glVertex2f(x, 0.92);
    glVertex2f(x, 0.95);
    glEnd();
    glPopMatrix();

    x = -0.95 + 0.005 * health;
    glPushMatrix();
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.95, 0.95);
    glVertex2f(-0.95, 0.92);
    glVertex2f(x, 0.92);
    glVertex2f(x, 0.95);
    glEnd();
    glPopMatrix();
}

void Island3D::drawScore()
{
    glPushMatrix();
    std::string text = "Score: " + std::to_string((int)score);
    int len = text.length();
    glTranslatef(-0.95, 0.86, 0.0);
    glColor3f(1, 1, 0);
    glRasterPos2f(0, 0);
    for (int i = 0; i < len; i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    glPopMatrix();
}

void Island3D::tiltCannonUp()
{
    printf("tilt %f\n", cannonSph.a);
    if (cannonSph.a + CANNON_TILT_SPEED > CANNON_TILT_MAX)
        return;

    cannonSph.a += CANNON_TILT_SPEED;
}

void Island3D::tiltCannonDown()
{
    if (cannonSph.a - CANNON_TILT_SPEED < CANNON_TILT_MIN)
        return;

    cannonSph.a -= CANNON_TILT_SPEED;
}

void Island3D::rotateCannonLeft()
{
    //printf("%f\n", cannonSph.polar);
    if (cannonSph.polar <= 0.0)
        cannonSph.polar = 360;

    cannonSph.polar -= CANNON_ROTATION_SPEED;
}

void Island3D::rotateCannonRight()
{
    //printf("%f\n", cannonSph.polar);
    if (cannonSph.polar >= 360.0)
        cannonSph.polar = 0.0;

    cannonSph.polar += CANNON_ROTATION_SPEED;
}

void Island3D::increaseCannonPower()
{
    cannonSph.magnitude += CANNON_POWER_INCREASE_FACTOR;
}

void Island3D::decreaseCannonPower()
{
    if (cannonSph.magnitude - CANNON_POWER_INCREASE_FACTOR < 0)
    {
        cannonSph.magnitude = 0;
        return;
    }
    cannonSph.magnitude -= CANNON_POWER_DECREASE_FACTOR;
}

bool Island3D::collision(vec3f otherLocation, float otherRadius)
{
    float dist = calcVectorDistance(otherLocation, location);
    if (dist <= ISLAND_BASE_RADIUS + otherRadius)
        return true;
    return false;
}

void Island3D::damage()
{
    health--;
}

void Island3D::point()
{
    score++;
}