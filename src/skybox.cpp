#include "skybox.h"

Skybox::Skybox()
{
    this->textureTop = new Texture("../src/ypos.png");
    this->textureBack = new Texture("../src/zpos.png");
    this->textureFront = new Texture("../src/zneg.png");
    this->textureLeft = new Texture("../src/xneg.png");
    this->textureRight = new Texture("../src/xpos.png");
}

void Skybox::draw()
{
    glPushMatrix();

    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    textureTop->enable();
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1, 0);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1, 1);
    glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(0, 1);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();
    textureTop->disable();
    glPopMatrix();

    glPushMatrix();
    textureBack->enable();
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1, 0);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1, 1);
    glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(0, 1);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();
    textureBack->disable();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    textureFront->enable();
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1, 0);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1, 1);
    glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(0, 1);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();
    textureFront->disable();
    glPopMatrix();

    glPushMatrix();
    glRotatef(-90, 0, 1, 0);
    textureLeft->enable();
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1, 0);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1, 1);
    glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(0, 1);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();
    textureLeft->disable();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    textureRight->enable();
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1, 0);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1, 1);
    glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(0, 1);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();
    textureRight->disable();
    glPopMatrix();

    glPopMatrix();
}