#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{   
    Model wheel;
    Model carousel;
    Model rollercoaster;
    Model boatSwing;
    Model merryGoRound;
    Model freeFallTower;
    float carousel_rotation;
    Material material;
    GLuint texture_rollercoaster;
    GLuint grass_texture;
    GLuint sky_texture;
    GLuint texture_carousel;
    GLuint texture_wheel;
    GLuint texture_seat;
    GLuint texture_boatSwing;
    GLuint texture_merryGoRound;
    GLuint texture_freeFallTower;
    GLuint help_image;
    GLuint charmap_id;
	bool display_help;
    float light_intensity;
    vec3 carousel_position;
    bool fog_active;
} Scene;


/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material, float alpha);

void update_scene(Scene* scene, double time);
/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

void help(GLuint Help_menu);

void render_floor(GLuint texture_name);

void render_skybox(GLuint texture_name);

void draw_string(const Scene* scene, const char* s);

#endif /* SCENE_H */