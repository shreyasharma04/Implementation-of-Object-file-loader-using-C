# Implementation-of-Object-file-loader-using-C
OBJ is a geometry definition file format first developed by Wave frontTechnologies for its Advanced Visualizer animation package. The file format is open and has been adopted by other 3D graphics application vendors.  The OBJ file format is a simple data-format that represents 3D geometry alone — namely, the position of each vertex, the UV position of each texture coordinate vertex, vertex normal, and the faces that make each polygon defined as a list of vertices, and texture vertices. Vertices are stored in a counter-clockwise order by default, making explicit declaration of face normal unnecessary. OBJ coordinates have no units, but OBJ files can contain scale information in a human readable comment line.  This is a basic .obj loader written in C. A C wrapper is included. It can parse vertices, texture coordinates, normal, 3 or 4 vertex faces, and .obj files. The OBJ file is in readable format you can figure out the contents of any of the files simply by opening them in OpenGL. The contents should reveal an easy structure for materials. When an object loader's activation function is called, it should open the object file and try to recognize its contents. Each object loader is therefore responsible for identifying the files it can load. On the other hand, the loader understands the object file, it reads the file and submits its contents to the host.  There is also support for non-standard object types that are relevant to raytracing.When you need to draw a more advanced object like character, house, terrain, vehicles we can't pass the vertices by ourselves for these objects so we have to use the 3D model and model are simply the meshes made of one or more number of vertices. There are many 3D modelling software’s one of them is OpenGL which is open source also.   This project is a simple obj file loader that loads the vertex, normal and texture data from an .obj file and arranges in an array to be loaded into OpenGL programs.The objective of this project is to develop a tool which could export an object file and open it in a 3D software for viewing and editing purposes.  The sub-objectives of the project are:   1. To export the object file to a 3D software application like OpenGL.   2. To view and edit object files.
