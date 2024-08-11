

# Hello

- This is my process of learning how do graphics work!
- I am going to follow the Udemy course by -----, and the youtuber Cherno

- I hope I can learn this, and enjoy this harsh journey


# Lessons

## General Ideas

- **not a library** but a specification, there is no **code** only functions that one can use
- No need to download anything, the implementation of the openGl is made by **graphics cards** manufacture
- This is the reason why games (for example) may look different in different graphics
- Kinda of cross platform - not necessarily better for that reason
- OpenGl its the easiest API to learn  - not as low level
- There is modern and 

## The resources used

### Glew

The main Extension Wrangler

- OpenGL Extension Wrangler 
- Interface for OpenGL versions above 1.1
- The builtin libraries only allow for below 1.1
- Modern OpenGL is considered to be above 3. something
- Glew can detect whether a specific extension exist on the platform 
- Alternatives are: GL3w, glLoadGen, glad, glsdk, Glee, libepoxy ... 

#### Usage

- use **#include<GL/glew.h>**
- initialize OpenGl context
- enable **glewExperimental** using **enums like** GL_TRUE
- initialize with **glewinit()**
- Check if there is errors with **GLEW_OK**
- read errors with **glewGetErrorString(result)**

### GLFW

Library to handle windows and create OpenGL context.

- Window creation and control
- process input from different sources
- allows **multiple** monitor support

### SDL

Super popular and similar to GLFW but with more functionalities (audio, threading, filesystems)

### Alternatifve

- SFML (simple and fast multimedia library) - even more features than SDL. Week OpenGl context
- GLUT (OpenGL Utility Toolkit) - no longer maintained. AVOID IT! ahahah
- Win32 API - for the purists. Lowest level for window creation 

## Shaders and the rendering Pipeline

  **Rendering Pipeline**

- series of stages that take place in order to render an image to the screen
- Fours stages are programmable via "Shaders"

  **Shaders**
- Pieces of code written in either GLSL (OPENGL Shading Language) or **HLSL** (HIgh-level Shading Language) if using Direct3D
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
- Vertex != position, is just a point of the geometry because it can contain more data. Each type of data is called an **attribute**
- **primitive** is a simple shape made using one or more vertices
- triangles most common, but also points, lines and quads. 
- Step done in the application itself

##### Used structures VAOs, VBOs and IBO 

- **VAO** -> Vertex Array Objects -> defines what data vertex has (position, colour, texture, normal etc...)
- **VBO** -> Vertex Buffer Objects -> defines the data itself
- **IBO** -> Index Buffer Objects ->  allows the program to reuse existing vertices (no need to repeat info in the VBO)

All of this gets stored in the RAM of the GPU to improve performance

- **attribute pointers** where and how shaders can acess vertex data, actually connect those structures to the shaders

###### The steps for creation

- Generate a VAO ID
- Bind the VAO with that ID
- Generate a VBO ID (```glGenBuffers(1, &bufferId)```)
- Bind the VBO with that ID (automatically attaches VBO and VAO previously created - indentation in code for clearness) (```glBindBuffer(GL_ARRAY_BUFFER, bufferId)```)
- Attach the vertex data to that VBO (```glBufferData(GL_ARRAY_BUFFER, size, data, typeUsage(GL_STATIC_DRAW))```)
- Define the Attribute Pointer formatting (How is the data formatted inside the VBO ? groups of 3 | spaced appart| float | integers??) (can be done before or after data being assigned, just needs to be after the binding)
  - ```glVertexAttribPointer(index, size, type, normalized, stride, pointer)```
    - **stride** - size of each vertex
    - **pointer** - offset in bytes of the attribute from the beggining of the vertex info
- Enable Attribute Pointer (Can be done before or after)(```glEnableVertexAttribArray()```)
- Unbind the VAO and VBO, ready to the next object to be bound

If using index buffer there some additional steps that allow the creation of such a object

- Generate a IBO ID (```glGenBuffers(1, &iboId)```)
- Bind the IBO with that ID (```glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId)```)
- Attach the indices data to that IBO (```glBufferData(GL_ELEMENT_ARRAY_BUFFER, size [in bytes of the indices array], indices, typeUsage(GL_STATIC_DRAW))```)

###### Initiate the draw

The process can **vary** if one is **using IBO or not**

1. Activate Shader Program you want to use - Predefined code/compiled in a different file
2. Bind VAO of object you want to draw

If **not using IBO**:

3. Call glDrawArrays, which initiates the rest of the pipeline

If **using IBO**:

3. Call ```glDrawElements(GL_TRIANGLES, numberOfIndices in indices array, typeOfData, nullptr)```
#### Vertex Shader

- **NOT OPTIONAL**
- Handles vertices **individually** (possible change vertices using matrixes, offset them etc...)
- Shader gets called **for each** vertex to define their position (main purpose)
- Must store something in **gl_Position** as it is used by later stages (where final vertice position is defined)
- Can specify additional outputs that can be picked up and used by user_defined shaders later in the pipeline (pass colours or other attributes)
- Inputs consist of the vertex data itself
- Attribute is acessed via its index

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

#### Fragment Shader - pixel shaders

- Optional but its rare not being used - Exceptions are cases when only depth or stencil data is required (ex. shadow maps)
- Its called for each pixel/fragment of the screen
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

- Shader is just a program that runs on the GPU
- Shader Programs are a group of shaders associated with one another
- Created in OPENGL via a series of functions.

### Creating a Shader Program

1. Create empty program (```uint program = glCreateProgram()```)
2. Create empty shaders (```uint id = glCreateShader(GL_TYPE_SHADER)```)
3. Attach shader source to shaders (```glShaderSource(id, 1 (amount of sources codes), &source, nullptr [length])```)
4. Compile shaders (```glCompileShader(id)```)
5. Error handling (sintax errors verification) (```glGetShaderiv(id, GL_COMPILE_STATUS, &result)```)
  - Returns to result if there was an error
  - Get length of the error (```glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length)```)
  - Can use **alloca** in order to create char array with specific size
  - Get the actual log (```glGetShaderInfoLog(id, length [max length of the buffer], nullptr [returns length of the message], messageBuffer)```)
6. Attach shaders to program (```glAttachError(program, shader)```)
7. Link program (creates executables from shaders and link them together) (```glLinkProgram(program)```)
8. Validate the Linking (similar to sintax shader verification) (```glGetProgramiv(program, GL_LINK_STATUS, &result)```)
9.  Validate program (optional but highly advised because debugging shaders is a pain) (```glValidateProgram(program)```)
10. Validate the validation of the program (similar to validating linking)
11. Can delete each individual shader, the intermidiate files (```glDeleteShader(shader)```)
12. May have to detach shader (```glDetachShader(program, shader)```) - can delete info necessary to debug

### Loading shaders

The different shaders are loaded into GLEW, as we saw, via a strings that contain the source code. 
One might write the shader code in the same file or do it in a different file or location and then load it, making use of the C++ fstream logic.


### Using a shader program 

- When you create a shader, an ID is given (like with VAOs and VBOs)
- Simply call **glUseProgram(shaderID)**
- All draw calls from then on will use that shader
- shaderID 0 means no shader

## Summary

- Rendering Pipeline consist of several stages
- Four stages are programmable via shaders (Vertex, Tessellation, Geometry, Fragment)
- Vertex Shader is mandatory
- Vertices: User-defined points in space
- Primitives: Groups of vertices that make a simple shape (usually a triangle)
- Fragments: Per-pixel data created from primitives
- Vertex Array Object (VAO): WHAT data a vertex hax
- Vertex Buffer Object (VBO): The vertex data itself
- Shader programs are created with at least a Vertex Shader and then activated before use

## Dealing with errors!

### No external Tools

- **glGetError()** - has been in OpenGl since the beginning (compatible with all version)
  - Every time an OpenGl functions runs and an error occurs a flag gets set internally in OpenGl insides. 
  - When we call this function we are basically just getting the flags, one at a time
  - One would need to first clear all errors, execute a function and then check for errors again!
- **glDebugMessageCallBack** - newer way of dealing with errors
  - Allows user to specify function pointer that gets executed when an errors occurs
  - Explains also what was the exact error and suggest how to fix it


## Uniforms

A way of passing information from CPU to GPU (shaders) as if declaring a variable. 

- Uniforms are set per draw, attributes are set per vertex
- Uniforms must be defined in the shader code (ex. fragment shader)
```glsl
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color

void main(){
  color = u_Color;
}
```
- In order to define the variable in CPU side, need to pay attention to **name** and **type** of the variable in question
- The definition of type needs to be done after shader being bound, called ````glUseProgram```
- After shader is created an **ID** is assigned to each uniform
- Get that location by using ```int location = glGetUniformLocation(program, variableName)```
- Location can be -1 if OpenGl didn't find it in the specified program (uniform must be used in the shader not only declared)
- Make use of the functions ```glUniform[type](location, values...)```

#### Types

glUniform...:

- 1f - single floating value
- 1i - single integer value
- 4f - vec4 floating values
- 4fv - same as above but value specified by pointer
- Matrix4fv - mat4 of floating values, specified by pointer

## Abstraction
Reasons for abstraction:

- Change names, keep consistency with a simple wrap up 

There's a need to do some abstraction to improve readability

- Vertex Buffer 
- Index Buffer
- Vertex Array (if using or not)
- Rendered (what tights everything together) - works by commanding it to draw something
  - It's responsible for the draw call (it could be thighed to individual index buffers)
  - Center pipeline
- Shaders 
  
An error can occur when program tries to destroy Vertex and Index buffer but doing so after glfwTerminate was called. This function destroys the OPENGl context, which GlGetError detects as an error. Fixing this is as simple as destroying those structures before calling that function, by creating a scope or dynamically allocating in the heap.

## Textures

Common sense: have an image on some kind of surface

But they can be much more!!! Image that can be used when rendering something, with much power!

The beginning would just be getting an image from computer into a surface in the application!

1. Load image into CPU (game engines usually have specific image extensions) - using PNG
2. Use a library to get the info from image (give filePath - receive buffer of pixel colors)
3. **Invert** the image so that pixels start from the **bottom left** corner (How OpenGl expects)
4. Upload the pixel color buffer to GPU (create texture in OpenGL via ```glGenTextures([number of textures], &id)```)
5. Bind texture when rendering (```glBindTextures([type](2d, 3d?), id)```)
6. Setup texture settings (```glTexParameter(type of data)([type], [parameter], [type of resampling??])```)
  - There are 4 **necessary parameters to be defined**
  - GL_TEXTURE_MIN_FILTER ( how it gets scaled down)
  - GL_TEXTURE_MAG_FILTER ( how it gets scaled up)
  - GL_TEXTURE_MAP_S ( how it in x ...)
  - GL_TEXTURE_MAP_T ( how it in y...)
7. Pass the data to OpenGl texture (```glTexImage2d(...)```)
8. Modify fragment(pixel)shader to read texture 
  - Shader **reads** from **integer uniform** which **slot (sampler slot)** is the texture in so we can sample from there

Texture are stored in OpenGl in **slots**. The **number of slots** depends on the GPU.

Its possible to ask OpenGl how many available slots there are!




## Math stuff required

