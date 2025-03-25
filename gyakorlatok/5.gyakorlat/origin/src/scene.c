#include "scene.h"

#include <OpenGL/gl.h>
#include <math.h>

void init_scene(Scene* scene)
{
    scene->rotation_angle = 0;
}

void update_scene(Scene* scene)
{
    scene->rotation_angle += 0.05;
    if (scene->rotation_angle > 360) {
        scene->rotation_angle -= 360;
    }
}



void render_scene(const Scene* scene)
{
draw_origin();
glBegin(GL_QUADS);

glColor3f(1, 0, 0);
glVertex3f(0, 0, 0);
glVertex3f(0, 0, 1);
glVertex3f(1, 0, 1);
glVertex3f(1, 0, 0);

glColor3f(0, 1, 0);
glVertex3f(0, 0, 0);
glVertex3f(0, 0, 1);
glVertex3f(1, 0, 1);
glVertex3f(1, 0, 0);

glEnd();

/* glBegin(GL_TRIANGLES);

glColor3f(1, 1, 0);   
glVertex3f(0.25, 0.25, 0.25);

glColor3f(0, 1, 1);   
glVertex3f(0.75, 0.25, 0.25);

glColor3f(1, 0, 1);  
glVertex3f(0.5, 0.75, 0.5);

glEnd(); */
glPushMatrix();
glTranslatef(0.5, 0.5, 0.5);              
glRotatef(scene->rotation_angle, 0, 1, 0);   
glTranslatef(-0.5, -0.5, -0.5);           
draw_sphere(0.3, 6, 6);                     
glPopMatrix();



/* draw_sphere(0.3, 6, 6);
 */}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void draw_sphere(float radius, int slices, int stacks)
{
    float phi, theta;
    float x, y, z;
    float pi = M_PI;

    for (int i = 0; i < stacks; ++i)
    {
        float phi1 = pi * i / stacks;
        float phi2 = pi * (i + 1) / stacks;

        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(0.5, 0.5, 0.5); 

        for (int j = 0; j <= slices; ++j)
        {
            float theta = 2 * pi * j / slices;

            x = radius * sin(phi1) * cos(theta);
            y = radius * cos(phi1);
            z = radius * sin(phi1) * sin(theta);
            glVertex3f(x + 0.5f, y + 0.5f, z + 0.5f); 

            x = radius * sin(phi2) * cos(theta);
            y = radius * cos(phi2);
            z = radius * sin(phi2) * sin(theta);
            glVertex3f(x + 0.5f, y + 0.5f, z + 0.5f);
        }

        glEnd();
    }
}