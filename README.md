# Learning OpenGL 
Started learning OpenGL from scratch, so right now it's OpenGL 1.0(intermediate mode) specification

**Program opportunities**:
1. Tracking camera *that's rotating vertical from 0° to 85° and whole 360° horizontal (it also has zoom option)*
2. Real fps counter*: count frames and divide it on time every 1 second (almost, usually it's like 1.04sec)*
3. Count elapsed time by using windows functions
4. Load materials and light attributes from file (.json)
5. Load mesh from [wavefront .obj](https://en.wikipedia.org/wiki/Wavefront_.obj_file) file
6. GameObjects on field 21x21
7. Moving game objects
8. Using VBO and EBO buffers
9. Code splitted up by Data, Display and Simulation parts(.cpp and .h)

**Used libraries**:
1. [freeglut](http://freeglut.sourceforge.net/) - open-source alternative to the OpenGL Utility Toolkit (GLUT) library
2. [GLM](https://glm.g-truc.net/0.9.9/index.html) - C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications
3. [GLEW](http://glew.sourceforge.net/) - The OpenGL Extension Wrangler Library (GLEW) is a cross-platform open-source C/C++ extension loading library.
4. [RapidJson](https://github.com/Tencent/rapidjson/) - A fast JSON parser/generator for C++ with both SAX/DOM style API

**Program in action**
FPS in the title

Controls:
Arrows - Rotation *(up/down/left/right)*  
Mouse Wheel - Zoom *(close/further)*  
WASD - Player movement

![](https://github.com/catinapoke/opengl-1-intermediate-mode/blob/master/gifs/opengl1.gif)
