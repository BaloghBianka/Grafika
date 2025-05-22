#include "app.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>

void init_app(App* app, int width, int height)
{
    int error_code;
    int inited_loaders;

    app->is_running = false;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return;
    }

    app->window = SDL_CreateWindow(
        "amusement park",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    if (app->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return;
    }

    inited_loaders = IMG_Init(IMG_INIT_PNG);
    if (inited_loaders == 0) {
        printf("[ERROR] IMG initialization error: %s\n", IMG_GetError());
        return;
    }

    app->gl_context = SDL_GL_CreateContext(app->window);
    if (app->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return;
    }

    init_opengl();
    reshape(width, height);

    init_camera(&(app->camera));
    init_scene(&(app->scene));

    app->is_running = true;

    app->light_intensity_change = 0.1f;

    app->fog_end_distance = 30.0f;
    app->fog_active = true;
    app->fog_end_time = (double)SDL_GetTicks() / 1000 + 7.0; 
}


void init_opengl()
{
    glShadeModel(GL_SMOOTH); 

    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_FOG);
    float fog_color[] = {0.95f, 0.95f, 0.95f, 1.0f};
    glFogfv(GL_FOG_COLOR, fog_color);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 5.0f);
    glFogf(GL_FOG_END, 30.0f); 
}


void reshape(GLsizei width, GLsizei height)
{
    if (height == 0) {
        height = 1;
    }

    double ratio = (double)width / height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(
        -0.08 * ratio, 0.08 * ratio,  // left, right
        -0.06, 0.06,                  // bottom, top
        0.1, 10000.0                  // near, far
    );
}


void handle_app_events(App* app)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                app->is_running = false;
                break;
            case SDL_SCANCODE_W:
                set_camera_speed(&(app->camera), 5);
                break;
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), -5);
                break;
            case SDL_SCANCODE_A:
                set_camera_side_speed(&(app->camera), 5);
                break;
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), -5);
                break;
            case SDL_SCANCODE_Q:
                set_camera_vertical_speed(&(app->camera), 5);
                break;
            case SDL_SCANCODE_E:
                set_camera_vertical_speed(&(app->camera), -5);
                break;
            case SDL_SCANCODE_T:
                app->camera.locked = !app->camera.locked;
                break;
            case SDL_SCANCODE_F1:
                app->scene.display_help = !(app->scene.display_help);
                break;
                case SDL_SCANCODE_KP_PLUS:
                app->scene.light_intensity += app->light_intensity_change;
                if (app->scene.light_intensity > 1.0f)
                    app->scene.light_intensity = 1.0f;
            
                {
                    GLfloat diffuse[] = {
                        app->scene.light_intensity,
                        app->scene.light_intensity,
                        app->scene.light_intensity,
                        1.0f
                    };
                    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
                }
                break;
            
            case SDL_SCANCODE_KP_MINUS:
                app->scene.light_intensity -= app->light_intensity_change;
                if (app->scene.light_intensity < 0.0f)
                    app->scene.light_intensity = 0.0f;
            
                {
                    GLfloat diffuse[] = {
                        app->scene.light_intensity,
                        app->scene.light_intensity,
                        app->scene.light_intensity,
                        1.0f
                    };
                    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
                }
                break;
            default:
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_camera_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_D:
                set_camera_side_speed(&(app->camera), 0);
                break;
            case SDL_SCANCODE_Q:
            case SDL_SCANCODE_E:
                set_camera_vertical_speed(&(app->camera), 0);
                break;
            default:
                break;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            is_mouse_down = true;
            break;

        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            if (is_mouse_down) {
                rotate_camera(&(app->camera), mouse_x - x, mouse_y - y);
            }
            mouse_x = x;
            mouse_y = y;
            break;

        case SDL_MOUSEBUTTONUP:
            is_mouse_down = false;
            break;

        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                reshape(event.window.data1, event.window.data2);
            }
            break;

        case SDL_QUIT:
            app->is_running = false;
            break;

        default:
            break;
        }
    }
}


void update_app(App* app)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - app->uptime;
    app->uptime = current_time;

    if (app->fog_active) {
        float t = (app->fog_end_time - current_time);
        if (t <= 0.0f) {
            glDisable(GL_FOG);
            app->fog_active = false;
            app->scene.fog_active = false;  
        } else {
            float progress = 1.0f - (t / 7.0f); 
            if (progress < 0.0f) progress = 0.0f;
            if (progress > 1.0f) progress = 1.0f;

            app->fog_end_distance = 30.0f + progress * (100.0f - 30.0f);
            glFogf(GL_FOG_END, app->fog_end_distance);
        }
    }

    vec3 carousel_position = app->scene.carousel_position;
    double carousel_rotation = app->scene.carousel_rotation;

    update_camera(&(app->camera), elapsed_time, carousel_rotation, carousel_position);
    update_scene(&(app->scene), elapsed_time);
}


void render_app(App* app)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&(app->camera));
    render_scene(&(app->scene));
    glPopMatrix();

    SDL_GL_SwapWindow(app->window);
}


void destroy_app(App* app)
{
    if (app->gl_context != NULL) {
        SDL_GL_DeleteContext(app->gl_context);
    }

    if (app->window != NULL) {
        SDL_DestroyWindow(app->window);
    }

    SDL_Quit();
} 
