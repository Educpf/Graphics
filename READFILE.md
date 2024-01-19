

# Hello

- This is my process of learning how do graphics work!
- I am going to follow the Udemy course by -----, and the youtuber Cherno

- I hope I can learn this, and enjoy this harsh journey

# Lessons

## Shaders and the rendering Pipeline

  **Rendering Pipeline**

- series of stages that take place in order to render an image to the screen
- Fours stages are programmable via "Shaders"

  **Shaders**
- Pieces of code written in either GLSL (OPENGL Shading Language) or **HLSL** (HIgh-level Shading Language) if using Direc3D
- GLSL is based on C

### Pipeline Stages

1. Vertex Specification
2. Vertex Shader - Prog.
3. Tessellation - Prog.
4. Geometry Shader - Prog.
5. Vertex Post-Processing
6. Primitive Assembly
7. Rasterization 
8. Fragment Shader - Prog.
9. Per-Sample Operations

#### Vertex Specification

- Settings up the data of the vertices of the primitives to render
- **primitive** is a simple shape made using one or more vertices
- triangles most common, but also points, lines and quads. 
- Step done in the application itself

##### Used structures VAOs and VBOs

- **VAO** -> Vertex Array Objects -> defines what data vertex has (position, colour, texture, normal etc...)
- **VBO** -> Vertex Buffer Objects -> defines the data itself

All of this gets stored in the RAM of the GPU to improve performance

- **attribute pointers** where and how shaders can acess vertex data, actually connect those structures to the shaders

###### The steps for creation

- Generate a VAO ID
- Bind the VAO with that ID
- Generate a VBO ID
- Bind the VBO with that ID (automatically attaches VBO and VAO previously created - indentation in code for clearness)
- Attach the vertex data to that VBO
- Define the Attribute Pointer formatting (How is the data formatted inside the VBO ? groups of 3 | spaced appart| float | integers??)
- Enable Attribute Pointer
- Unbind the VAO and VBO, ready to the next object to be bound

###### Initiate the draw

1. Activate Shader Program you want to use - Predefined code/compiled in a different file
2. Bind VAO of object you want to draw
3. Call glDrawArrays, which initiates the rest of the pipeline

#### Vertex Shader

- **NOT OPTIONAL**
- Handles vertices **individually** (possible change vertices using matrixes, offset them etc...)
- Must store something in **gl_Position** as it is used by later stages (where final vertice position is defined)
- Can specify additional outputs that can be picked up and used by user_defined shaders later in the pipeline (pass colours or other attributes)
- Inputs consist of the vertex data itself

Simple example:
```c++
#version 330

layout (location=0) in vec30 pos;

void main()
{
    gl_Position = vec4(pos, 1.0);
}
```
- Define version of GLSL now syncronises with OPENGL version

#### Tesselation



























