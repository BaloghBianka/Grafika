# Abandoned Amusement Park - OpenGL Application

---

## Description

The goal of the Abandoned Amusement Park project is to create an interactive virtual amusement park where the player can freely explore the area. The park contains various attractions, such as a carousel, a roller coaster, and a Ferris wheel. The player can navigate with the keyboard and mouse and interact with the objects.

The 3D models are created using Blender and rendered with OpenGL technology. The application is implemented in the C programming language.&#x20;

---

## **Main Features**

1. **Camera Control**

   * 360° rotation and free movement.
   * Navigation with mouse and keyboard.

2. **Objects and Models**

   * Carousel, roller coaster, and an abandoned Ferris wheel.
   * The models are loaded from separate files in `.obj` format.

3. **Animation and Interaction**

   * Animated rotation of the carousel and Ferris wheel.

   * Interactions controlled by the keyboard.

4. **Textures and Rendering**

   * Detailed texturing of all objects.

5. **Lights and Atmosphere**

   * Dynamically adjustable lights (`+` and `-` keys).

6. **User Guide**

   * Pressing `F1` displays a detailed user guide.

---

##  \*\*Additional Features \*\*

1. **Fog** -Fog effect for a mysterious atmosphere.
2. **Shadows ** -Simulation of water and reflections.
3. **Particle System** – Rain animation at game startup.

---

## Project Structure

```
│
├── src/                 # Source Code
├── include/             # Header Files
├── assets/              # Models and Textures (.obj, .png, .jpeg)
│   ├── models/          # OBJ Models
│   └── textures/        # PNG Textures
├── shaders/             # Shader Programs
├── doc/                 # Documentation and User Guide
```

---

## **Compilation and Execution**

To compile and run the program:

```bash
make
./amusementPark
```

