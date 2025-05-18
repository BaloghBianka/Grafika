#include "scene.h"

#include <GL/gl.h>

void init_scene(Scene* scene)
{
    scene->light_intensity = 0.5f;
    scene->sky_color[0] = 1.0f;  
    scene->sky_color[1] = 0.5f;  
    scene->sky_color[2] = 0.0f;  
    scene->transition_speed = 0.01f;  
}

void update_scene(Scene* scene, double elapsed_time)
{
    for (int i = 0; i < 3; ++i) {
        if (scene->sky_color[i] > 0.0f) {
            scene->sky_color[i] -= scene->transition_speed * elapsed_time;
            if (scene->sky_color[i] < 0.0f) {
                scene->sky_color[i] = 0.0f; 
            }
        }
    }
}

void render_scene(const Scene* scene)
{   
    glClearColor(scene->sky_color[0], scene->sky_color[1], scene->sky_color[2], 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    glColor3f(.4f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex3f(-50,-50,0);
        glVertex3f(50,-50,0);
        glVertex3f(50,50,0);
        glVertex3f(-50,0,0);
    glEnd();
}
void set_lighting(const Scene* scene)
{
    float intensity = scene->light_intensity;
    float ambient_light[] = { 0.4f * intensity, 0.4f * intensity, 0.4f * intensity, 1.0f };
    float diffuse_light[] = { 1.0f * intensity, 1.0f * intensity, 1.0f * intensity, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 0.0f };


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular_light);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f); 
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0f); 
}


void draw_origin()
{

}


