#ifndef SCENE_H
#define SCENE_H

#include "camera.h"

typedef struct Scene
{
    float rotation_angle; //hány fokkal forgassuk el a gömböt minden egyes képkocka kirajzolásánál.
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene *scene);

/**
 * Update the scene.
 */
void update_scene(Scene* scene);

/**
 * Render the scene objects.
 */
void render_scene(const Scene *scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();
void draw_sphere(float radius, int slices, int stacks);

#endif /* SCENE_H */
