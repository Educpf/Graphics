

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

- Only appeard in OpenGl 4
- Allows you to divide data in to smaller primites (ex. quads -> triangles)
- Can be used to add higher levels of detail dynamically (ex. when you get closer to something. Used in water)

#### Geometry Shader

- handles primitives (groups of vertices) [recall, VertexShader handles vertices]
- takes primitives then emits their vertices to create the given primitive, or even new primitive
- Can alter data given to it to modify given primitives, or even create new ones
- Can even alter the primitive types (points, line, triangles, etc) - take one type ouput another

#### Vertex Post-Processing

Sometimes stages are considered different ones

**Transform Feedback** (if enabled):
- Result of Vertex and Geometry stages saved to buffers for later use
- Instead of going through all the Vertex Geometry stages every single time, if saved, those steps can be skiped
- For heavly defined programs
**Clipping**:
- Primitives that won't be visible are removed
- Positions converted from "clip-space" to "window-space"

#### Primitive Assembly

- Mathematically define everything as a primitive
- Vertices are converted in to a series of primitives (ex. rendering triangles, 6 vertices would become 2 triangles, 3 vertices each)
- **Face culling** - the removal of primitives that can't be seen, or are facing "away" from the viewer

#### Rasterization

- Converts primitives into "Fragments"
Fragments - pieces of data for each pixel, obtained from the rasterization process
- Fragment data will be interpolated based on its position relative to each vertex

#### Fragment Shader

- Optional but its rare not being used - Exceptions are cases when only depth or stencil data is required (ex. shadow maps)
- Handles data for each fragment
- Most important output is the color of the pixel that the fragment covers
- Handles all the light, textures and shadows

Simple example
```c++
#version 330

out vec4 colour;
void main()
{
    colour = vec4(1.0, 0.0, 0.0, 1.0);
}
```
- Version needs to match the OpenGL and other shaders version
- Full read colour in this case
- No need to be called exactly colour
- **in** catches output from **Vertex Shader**

#### Per-sample Operations

- Series of test runs to see if the fragment should be drawn
- **Depth test** - most important test. Determines if something is in front of the point being drawn
- **Coloud Bending** - using defined operations, fragment colours are "blended" together with overlapping fragments. Usually used to handle transparent objects
- Fragment data written to currently **bound Framebuffer** (usually the default buffer) - possible to draw to a new buffer, besides the two normal buffers
- Lastly, buffer swap in the application


**PIPELINE is OVER!**

### On the origin of shaders

- Shader Programs are a group of shaders associated with one another
- Created in OPENGL via a series of functions.

### Creating a Shader Program

1. Create empty program
2. Create empty shaders
3. Attach shader source to shaders
4. Complite shaders
5. Attach shaders to program
6. Link program (creates executables from shaders and link them together)
7. Validate program (optional but highly advised because debugging shaders is a pain)

### Using a shader program 

- When you create a shader, an ID is given (like with VAOs and VBOs)
- Simply call **glUseProgram(shaderID)**
- All draw calls from then on will use that shader
- shaderID 0 means no shader

## Summary

- Rendering Pipeline consist of several stages
- Four stages are programmable via shaders (Vertex, Tessellation, Geometry, Fragment)
- Vertex Shader is mandatory
- Verices: User-defined points in space
- Primitives: Groups of vertices that make a simple shape (usually a triangle)
- Fragments: Per-pixel data created from primitives
- Vertex Array Object (VAO): WHAT data a vertex hax
- Vertex Buffer Object (VBO): The vertex data itself
- Shader programs are created with at least a Vertex Shader and then activated before use
