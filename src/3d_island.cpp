#include "3d_island.h"

Island3D::Island3D(int segments)
{
    this->texture = new Texture("../src/sand.jpg");
    this->setSegments(segments);

    this->resetTrajectoryData();
}

Island3D::~Island3D()
{
    delete texture;
    delete qobj;
    delete sphere;
    delete cannon;
    delete cannonBaseMiddle;
    delete cannonGunBaseCylinder;
    delete gunBox;
    delete bottomCylinder;
}

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

void Island3D::setSegments(int segments)
{
    if (this->sphere)
        delete this->sphere;
    if (this->cannon)
        delete this->cannon;
    if (this->cannonBaseMiddle)
        delete this->cannonBaseMiddle;
    if (this->cannonGunBaseCylinder)
        delete this->cannonGunBaseCylinder;
    if (this->gunBox)
        delete this->gunBox;
    if (this->bottomCylinder)
        delete this->bottomCylinder;

    this->segments = segments;

    this->sphere = new Sphere(ISLAND_BASE_RADIUS, segments, segments);
    this->cannon = new Cylinder(CANNON_RADIUS, CANNON_LENGTH, segments);
    this->cannonBaseMiddle = new Cylinder(CANNON_BASE_CYLINDER_RADIUS, CANNON_BASE_CYLINDER_HEIGHT, segments);
    this->cannonGunBaseCylinder = new HalfCylinder(CANNON_BASE_HALF_CYLINDER_RADIUS, CANNON_BASE_HALF_CYLINDER_SIZE, segments);

    this->gunBox = new Rectangle3D(GUN_BOX_HEIGHT, CANNON_BASE_HALF_CYLINDER_RADIUS * 2, CANNON_BASE_HALF_CYLINDER_SIZE);
    this->bottomCylinder = new Cylinder(ISLAND_BASE_RADIUS, 0.5, segments);
}

void Island3D::resetTrajectoryData()
{
    r0 = endOfCannon();
    v0 = sphericalToCartesian(cannonSph);
    r = endOfCannon();
    v = v0;
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
    if (this->time - shootTime >= cooldownTime)
    {
        shootTime = this->time;

        // Create a new projectile and return it
        Projectile3D *projectile = new Projectile3D(endOfCannon(), cannonSph, false, segments);
        return projectile;
    }
    return NULL;
}

Defence3D *Island3D::defence()
{
    // Check for defence shoot cooldown
    if (this->time - defenceTime >= cooldownTime)
    {
        defenceTime = this->time;

        // Create a new defence and return it
        Defence3D *defence = new Defence3D(endOfCannon(), cannonSph, defenceTime);
        return defence;
    }
    return NULL;
}

void Island3D::draw(bool showNormals)
{

    glColor4f(0.08, 0.08, 1.0, 1.0);

    //glColor3f(0.9, 0.8, 0.5);

    glColor3f(0.8, 0.8, 0.8);
    texture->enable();
    // Very very bottom cylinder
    glPushMatrix();
    glTranslatef(0, -1 + 0.25, 0); // Start from the bottom

    bottomCylinder->draw(showNormals);

    glPopMatrix();

    // Sphere
    glPushMatrix();
    glTranslatef(location.x, location.y, location.z); // 0.0, -0.5, 0.0
    glRotatef(-90, 1.0, 0, 0);
    //glutSolidSphere(ISLAND_BASE_RADIUS, 40, 40);
    sphere->draw(showNormals);
    texture->disable();
    glPopMatrix();

    //glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT2);
    GLfloat light_ambient[] = {0.13, 0.32, 0.55, 1.0};
    GLfloat light_diffuse[] = {0.13, 0.32, 0.55, 1.0};
    GLfloat light_position[] = {0.0, 0.0, 0.0, 0.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_emission[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat high_shininess[] = {100.0};

    //glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    //glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);

    glLightfv(GL_LIGHT2, GL_POSITION, light_position);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);

    glColor4f(0.13, 0.32, 0.55, 1.0);

    // Cylinder Base (Middle)
    glPushMatrix();
    glTranslatef(0, location.y + CANNON_BASE_CYLINDER_OFFSET_FROM_SPHERE + CANNON_BASE_CYLINDER_HEIGHT / 2, 0);
    cannonBaseMiddle->draw(showNormals);
    glPopMatrix();

    // Origin of the gunbox
    float BOX_OFFSET = location.y + CANNON_BASE_CYLINDER_OFFSET_FROM_SPHERE + CANNON_BASE_CYLINDER_HEIGHT + GUN_BOX_HEIGHT / 2;

    /*GLfloat light_ambient3[] = { 0.1, 0.3, 0.9, 1.0 };
    GLfloat light_diffuse3[] = { 0.3, 0.3, 0.1, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_ambient3);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse3);*/

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
    cannonGunBaseCylinder->draw(showNormals);
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
    cannon->draw(showNormals);
    glPopMatrix();

    // Used for testing where the cannon is
    glPushMatrix();
    // End of cannon pos
    //drawDot(-CANNON_LENGTH, BOX_OFFSET + GUN_BOX_HEIGHT / 2 + CANNON_RADIUS, 0.0);
    vec3f end = endOfCannon();
    drawDot(end.x, end.y, end.z);
    glPopMatrix();

    /*GLfloat light_ambient2[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_diffuse2[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_emission2[] = { 0.0, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_ambient2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_ambient2);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission2);*/

    glDisable(GL_LIGHT2);
    glEnable(GL_LIGHT0);
}

void Island3D::drawTrajectory(Wave3D *wave)
{
    vec3f rTemp = r;
    vec3f vTemp = v;

    //drawDot(r.x, r.y, r.z);

    // Turn off lighting because
    glDisable(GL_LIGHTING);

    // Draw velocity vector
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(rTemp.x, rTemp.y, rTemp.z);
    glVertex3f(v.x, rTemp.y, v.z);
    glEnd();

    // Draw Trajectory Curve
    float t = 0.01;
    // Wave intersection
    float y = wave->getYfromXZ(rTemp.x, 0.0);

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    while (rTemp.y > y)
    {
        rTemp.x += vTemp.x * t;
        rTemp.y += vTemp.y * t;
        rTemp.z += vTemp.z * t;
        vTemp.y += g * t;

        glVertex3f(rTemp.x, rTemp.y, rTemp.z);
        y = wave->getYfromXZ(rTemp.x, rTemp.z);
    }
    glEnd();

    glEnable(GL_LIGHTING);
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
    //printf("tilt %f\n", cannonSph.a);
    if (cannonSph.a + CANNON_TILT_SPEED > CANNON_TILT_MAX)
        return;

    cannonSph.a += CANNON_TILT_SPEED;
    this->resetTrajectoryData();
}

void Island3D::tiltCannonDown()
{
    if (cannonSph.a - CANNON_TILT_SPEED < CANNON_TILT_MIN)
        return;

    cannonSph.a -= CANNON_TILT_SPEED;
    this->resetTrajectoryData();
}

void Island3D::rotateCannonRight()
{
    //printf("%f\n", cannonSph.polar);
    if (cannonSph.polar <= 0.0)
        cannonSph.polar = 360;

    cannonSph.polar -= CANNON_ROTATION_SPEED;
    this->resetTrajectoryData();
}

void Island3D::rotateCannonLeft()
{
    //printf("%f\n", cannonSph.polar);
    if (cannonSph.polar >= 360.0)
        cannonSph.polar = 0.0;

    cannonSph.polar += CANNON_ROTATION_SPEED;
    this->resetTrajectoryData();
}

void Island3D::increaseCannonPower()
{
    cannonSph.magnitude += CANNON_POWER_INCREASE_FACTOR;
    this->resetTrajectoryData();
}

void Island3D::decreaseCannonPower()
{
    if (cannonSph.magnitude - CANNON_POWER_INCREASE_FACTOR < 0)
    {
        cannonSph.magnitude = 0;
        return;
    }
    cannonSph.magnitude -= CANNON_POWER_DECREASE_FACTOR;
    this->resetTrajectoryData();
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
    if (health > 0)
        health--;
}

void Island3D::point()
{
    score++;
}

bool Island3D::getAlive()
{
    if (health > 0)
        return true;
    return false;
}