#include "scene.h"

#include <math.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <obj/load.h>
#include <obj/draw.h>

#include <GL/gl.h>


void init_scene(Scene* scene)
{
    scene->carousel_rotation = 0.0;

    scene->charmap_id = load_texture("assets/textures/charmap.png");

    scene->sky_texture = load_texture("assets/textures/Sky.jpg");
    scene->grass_texture = load_texture("assets/textures/skybox_bottom.jpg");
    scene->help_image = load_texture("assets/textures/help.png");
    load_model(&(scene->wheel), "assets/models/ferris_wheel.obj");
    scene->texture_wheel = load_texture("assets/textures/wheel.png");
    load_model(&(scene->carousel), "assets/models/carousel.obj");
    scene->texture_carousel = load_texture("assets/textures/carousel.png");
    load_model(&(scene->rollercoaster), "assets/models/rollercoster2.obj");
    scene->texture_rollercoaster = load_texture("assets/textures/cube.png");
    load_model(&(scene->boatSwing), "assets/models/boat_swing.obj");
    scene->texture_boatSwing = load_texture("assets/textures/boatSwing.png");
    load_model(&(scene->merryGoRound), "assets/models/merry_go_round.obj");
    scene->texture_merryGoRound = load_texture("assets/textures/wheel.png");
    load_model(&(scene->freeFallTower), "assets/models/freefalltower.obj");
    scene->texture_freeFallTower = load_texture("assets/textures/freeFallTower.png");

    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 0.0;
    scene->material.specular.green = 0.0;
    scene->material.specular.blue = 0.0;

    scene->material.shininess = 3.0;
    scene->light_intensity = 4.0f;

    scene->carousel_position.x = 10.0;
    scene->carousel_position.y = -15.0;
    scene->carousel_position.z = -1.0;

    scene->display_help = false;
}

void set_lighting(const Scene* scene)
{
    float intensity = scene->light_intensity;
    float ambient_light[] = { 0.4f * intensity, 0.4f * intensity, 0.4f * intensity, 1.0f };
    float diffuse_light[] = { 1.0f * intensity, 1.0f * intensity, 1.0f * intensity, 1.0f };
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 0.0f };

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



void set_material(const Material* material, float alpha)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue,
        alpha
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue,
        alpha
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue,
        alpha
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void help(GLuint Help_menu)
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, Help_menu);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}


void update_scene(Scene* scene, double time)
{
    scene->carousel_rotation = fmod(scene->carousel_rotation + 20.0 * time, 360.0);
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material), 1.0f);
    set_lighting(scene);

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    render_floor(scene->grass_texture);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    render_skybox(scene->sky_texture);
    glPopMatrix();

    set_material(&(scene->material), 1.0f);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(32, 10, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(8.0f, 9.0f, 8.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_rollercoaster);
    draw_model(&(scene->rollercoaster));
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(10, -15, -1);
    glRotatef(scene->carousel_rotation, 0, 0, 1);
    glRotatef(90, 90, 0, 1);
    glBindTexture(GL_TEXTURE_2D, scene->texture_carousel);
    draw_model(&(scene->carousel));
    glPopMatrix();


    set_material(&(scene->material), 1.0f);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(17, 25, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(8.0f, 9.0f, 8.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_freeFallTower);
    draw_model(&(scene->freeFallTower));
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16, -30, 0);
    glScalef(5.0f, 5.0f, 5.0f);
     glRotatef(90, 1, 0, 0);
    glBindTexture(GL_TEXTURE_2D, scene->texture_boatSwing);
    draw_model(&(scene->boatSwing));
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glPushMatrix();
    glTranslatef(10, 16, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(4.0f, 4.0f, 4.0f);
    glBindTexture(GL_TEXTURE_2D, scene->texture_wheel);
    draw_model(&(scene->wheel));
    glPopMatrix();

    if (scene->fog_active)
    {
        glTranslatef(15, 18, 0);
        glRotatef(-90.0f, 0, 0, 1); 
        glScalef(2.0f, 2.0f, 2.0f);
        glColor3f(1, 1, 1);
        draw_string(scene, "Bianka's AMUSEMENT PARK");    
    }

    if (scene->display_help) {
        glPushMatrix();
    
        // Tegyük a kamera elé, középre
        glTranslatef(0, 5, -20);
        glScalef(0.1f, 0.1f, 0.1f);  // Legyen jól látható
        glColor3f(1, 1, 1);  // Fehér szín
    
        const char* help_text[] = {
            "Hasznalati utmutato",
            "W - Elore",
            "S - Hatra",
            "A - Balra",
            "D - Jobbra",
            "Q - Felfele",
            "E - Lefele",
            "Eger + huzas - Kamera forgatasa",
            "T - Korhinta felszallas",
            "F1 - Sugo megjelenitese/elrejtese",
            "+ - Vilagitas erositese",
            "- - Vilagitas csokkentese",
            "ESC - Kilepes"
        };
    
        size_t i;
        for (i = 0; i < sizeof(help_text) / sizeof(help_text[0]); i++) {
            draw_string(scene, help_text[i]);
            glTranslatef(0.0f, -100.0f, 0.0f);  
        }
    
        glPopMatrix();
    }



    glDisable(GL_LIGHTING);
    glLineWidth(3.0f); 
 
    glPushMatrix();
    glPopMatrix();
    glEnable(GL_LIGHTING);

}

void render_floor(GLuint texture_name)
{
    float size = 50.0f;
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_name);
    glRotatef(-90, 1, 0, 0);

    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);

    glVertex3f(-size, 0, -size);
    glVertex3f(size, 0, -size);
    glVertex3f(size, 0, size);
    glVertex3f(-size, 0, size);

    glEnd();
    
    glPopMatrix();
}


void render_skybox(GLuint texture_name) {
    glPushMatrix();
    glDepthMask(GL_FALSE);

    glBindTexture(GL_TEXTURE_2D, texture_name);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-50.0f, 50.0f, -50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(50.0f, 50.0f, -50.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(50.0f, -50.0f, 50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, 50.0f, -50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(50.0f, 50.0f, 50.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, -50.0f, 50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, -50.0f, 50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, 50.0f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, 50.0f, 50.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-50.0f, -50.0f, 50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-50.0f, 50.0f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, 50.0f, -50.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, 50.0f, -50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, 50.0f, -50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, 50.0f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, 50.0f, 50.0f);

    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, -50.0f, -50.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, -50.0f, 50.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-50.0f, -50.0f, 50.0f);

    glEnd();

    glDepthMask(GL_TRUE);
    glPopMatrix();
}

void draw_string(const Scene* scene, const char* s)
{
    float FONT_WIDTH = 1.0 / 16;
    float FONT_HEIGHT = 1.0 / 8;
    float FONT_X_WIDTH = 0.5;

    glBindTexture(GL_TEXTURE_2D, scene->charmap_id);
    glBegin(GL_QUADS);
    float x = 2.0;
    for (int i = 0; s[i] != 0; ++i) {
        char c = s[i];
        if (c >= 32 && c < 127) {
            int row = c / 16 + 1;
            int column = c % 16;
            float u = FONT_WIDTH * column;
            float v = FONT_HEIGHT * row;

            glNormal3f(0, 1, 0);
            glTexCoord2f(u, v);
            glVertex3f(x, 0, 0);

            glNormal3f(0, 1, 0);
            glTexCoord2f(u + FONT_WIDTH, v);
            glVertex3f(x + FONT_X_WIDTH, 0, 0);

            glNormal3f(0, 1, 0);
            glTexCoord2f(u + FONT_WIDTH, v - FONT_HEIGHT);
            glVertex3f(x + FONT_X_WIDTH, 0, 1);

            glNormal3f(0, 1, 0);
            // 0 0
            glTexCoord2f(u, v - FONT_HEIGHT);
            glVertex3f(x, 0, 1);

            x += FONT_X_WIDTH;
        }
    }
    glEnd();
}
