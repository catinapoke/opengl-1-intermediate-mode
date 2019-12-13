# Learning OpenGL 
Started learning OpenGL from scratch, so right now it's OpenGL 1.1(intermediate mode) specification

**Program opportunities**:
1. Tracking camera *that's rotating vertical from 0° to 85° and whole 360° horizontal (it also has zoom option)*
2. Real fps counter*: count frames and divide it on time every 1 second (almost, usually it's like 1.04sec)*
3. Count elapsed time by using windows functions
2. MSAA settings
2. Filtering settings  
Filtering types  
1)Linear filtering  
2)Bilinear filtering  
3)Bilinear filtering with mipmaps  
4)Trilinear filtering  
5)Anisotropic filtering х2  
6)Anisotropic filtering х4  
7)Anisotropic filtering х8  
8)Anisotropic filtering х16  
9)Anisotropic filtering х32  
4. Load materials and light attributes from file (filename.json)
5. Load scene template objects attributes from scene.json
5. Load mesh from [wavefront .obj](https://en.wikipedia.org/wiki/Wavefront_.obj_file) file
6. Load textures using DevIL library
6. GameObjects on field 21x21
6. Using factory pattern to create GameObjects
7. Player can spawn bomb that explodes after some time
8. Bomb fuse shows in left-upper corner of window
7. Moving game objects by player - bomb or light objects
8. Moving monster that kills player if it's in 1 block around monster
9. Portal can teleport player to the next one with same color
8. Using Lee's path finding algorithms for monster's moving
9. Using events of GameObjects to handle them
8. Using VBO and EBO buffers
9. Code splitted up by Data, Display and Simulation parts(.cpp and .h)


**Used libraries**:
1. [freeglut](http://freeglut.sourceforge.net/) - open-source alternative to the OpenGL Utility Toolkit (GLUT) library
2. [GLM](https://glm.g-truc.net/0.9.9/index.html) - C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications
3. [GLEW](http://glew.sourceforge.net/) - The OpenGL Extension Wrangler Library (GLEW) is a cross-platform open-source C/C++ extension loading library.
4. [RapidJson](https://github.com/Tencent/rapidjson/) - A fast JSON parser/generator for C++ with both SAX/DOM style API

**Program in action**
Settings (FPS, MSAA, Filtering type) in the title

Controls:  
<kbd>Arrows</kbd> - Rotation *(up/down/left/right)*  
<kbd>Mouse Wheel</kbd> - Zoom *(close/further)*  
<kbd>WASD</kbd> - Player movement  
<kbd>Space</kbd> - Drop bomb *at player's position*   
<kbd>1</kbd> - Turn on/off Multisample anti-aliasing  
<kbd>2</kbd> - Change filtering type  

[GIF Link](https://media.giphy.com/media/Xc4acKcYavCncv9LZZ/giphy.gif)  
![](https://github.com/catinapoke/opengl-1-intermediate-mode/blob/master/gifs/opengl2.png)
