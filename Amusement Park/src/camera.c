#include "camera.h"
#include "scene.h"
#include <GL/gl.h>

#include <math.h>
#include <SDL2/SDL_stdinc.h>

void init_camera(Camera* camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 1.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    camera->is_preview_visible = false;
    camera->locked = false;
}

void update_camera(Camera* camera, double time, double carousel_rotation, vec3 carousel_position)
{
    if (camera->locked) {
        double angle = degree_to_radian(carousel_rotation); // jobbrol balra forgás

        double radius = 2.0;

        double x_offset = radius * cos(angle);
        double y_offset = radius * sin(angle);

        camera->position.x = carousel_position.x + x_offset;
        camera->position.y = carousel_position.y + y_offset;
        camera->position.z = carousel_position.z + 2.0f; // fix magasság

        camera->rotation.x = 0.0;
        camera->rotation.y = 0.0;
        camera->rotation.z = 180.0 - carousel_rotation; // nézzen középre
    } else {
        double angle = degree_to_radian(camera->rotation.z);
        double side_angle = degree_to_radian(camera->rotation.z + 90.0);

        camera->position.x += cos(angle) * camera->speed.y * time;
        camera->position.y += sin(angle) * camera->speed.y * time;
        camera->position.x += cos(side_angle) * camera->speed.x * time;
        camera->position.y += sin(side_angle) * camera->speed.x * time;
        camera->position.z += camera->speed.z * time;
    }
}

void calculate_camera_rotation(Camera* camera, vec3 direction) {
    float length = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);

    camera->rotation.z = atan2(direction.y, direction.x) * 180.0 / M_PI;
    camera->rotation.x = atan2(direction.z, length) * 180.0 / M_PI;
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void set_camera_vertical_speed(Camera* camera, double speed)
{
    camera->speed.z = speed;
}

void show_texture_preview()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}
