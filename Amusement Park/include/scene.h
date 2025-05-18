#ifndef SCENE_H
#define SCENE_H

#include "camera.h"

typedef struct Scene
{
    float light_intensity;
    float sky_color[3];   
    float transition_speed;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double elapsed_time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

#endif /* SCENE_H */