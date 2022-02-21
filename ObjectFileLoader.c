

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<ctime>
#include <stdlib.h>
#include <string.h>
#include <iostream>


#define DEBUG_INFO

typedef struct
{
float x;
float y;
} vec2;

typedef struct
{
float x;
float y;
float z;
} vec3;


static int num_posNodes = 0;
static int num_texNodes = 0;
static int num_norNodes = 0;
static int num_indexNodes = 0;

typedef struct PositionNode {
vec3 pos;
struct PositionNode* nextNode;
} pNode;

typedef struct TextureNode {
vec2 pos;
struct TextureNode* nextNode;
} tNode;

typedef struct NormalNode {
vec3 pos;
struct NormalNode* nextNode;
} nNode;

typedef struct IndexNode {
int p1, p2, p3;
struct IndexNode* nextNode;
} iNode;

//Main loading function
float myobj_load(const char* fileName, float* faces) {
FILE* file = fopen("stall.obj", "r");
char dataType[20];
float* positionArray = NULL;
float* textureArray = NULL;
float* normalArray = NULL;
bool textureAvailable = false;
int f_count = 0;
char readVal[30];

float* finalBuffer = NULL;

if (file == NULL) {
printf("Unable to open File");
return 0;
}

pNode* headP = NULL;
pNode* currentNodeP = NULL;
pNode* tempP = NULL;

tNode* headT = NULL;
tNode* currentNodeT = NULL;
tNode* tempT = NULL;

nNode* headN = NULL;
nNode* currentNodeN = NULL;
nNode* tempN = NULL;

iNode* headI = NULL;
iNode* currentNodeI = NULL;
iNode* tempI = NULL;

while (1) {
int result = fscanf(file, "%s", &dataType);
if (result == EOF)
break;

if (strcmp(dataType, "v") == 0) { //checking if the data is for vertexPosition
float val1, val2, val3;
fscanf(file, "%f %f %f", &val1, &val2, &val3);

tempP = (pNode*)malloc(sizeof(pNode)); //creating new PositionNode and filling data
tempP->pos.x = val1;
tempP->pos.y = val2;
tempP->pos.z = val3;

if (headP != NULL) { //adding Position Node to end of Linked List
currentNodeP->nextNode = tempP;
currentNodeP = tempP;
currentNodeP->nextNode = NULL;
}
else {
headP = currentNodeP = tempP;
}
++num_posNodes;
}
else if (strcmp(dataType, "vt") == 0) {
float val1, val2;
fscanf(file, "%f %f", &val1, &val2);

tempT = (tNode*)malloc(sizeof(tNode)); //creating new TextureNode and filling data
tempT->pos.x = val1;
tempT->pos.y = val2;

if (headT != NULL) { //adding Texture Node to end of Linked List
currentNodeT->nextNode = tempT;
currentNodeT = tempT;
currentNodeT->nextNode = NULL;
}
else {
headT = currentNodeT = tempT;
}
++num_texNodes;
}
else if (strcmp(dataType, "vn") == 0) {
float val1, val2, val3;
fscanf(file, "%f %f %f", &val1, &val2, &val3);

tempN = (nNode*)malloc(sizeof(nNode)); //creating new TextureNode and filling data
tempN->pos.x = val1;
tempN->pos.y = val2;
tempN->pos.z = val3;

if (headN != NULL) { //adding Texture Node to end of Linked List
currentNodeN->nextNode = tempN;
currentNodeN = tempN;
currentNodeN->nextNode = NULL;
}
else {
headN = currentNodeN = tempN;
}

++num_norNodes;
}
else if (strcmp(dataType, "f") == 0) {
//move the file pointer 100 characters back. **Note: I am assuming that no line will be longer than that**
fseek(file, -100, SEEK_CUR);

//allocating arrays for temporary storage of attriute data

#ifdef DEBUG_INFO
printf("Positions: %d\nTextures: %d\nNormals: %d\n", num_posNodes, num_texNodes, num_norNodes);
#endif
positionArray = (float*)malloc(sizeof(float) * 3 * num_posNodes);
if (headT != currentNodeT)
textureArray = (float*)malloc(sizeof(float) * 2 * num_texNodes);
normalArray = (float*)malloc(sizeof(float) * 3 * num_norNodes);

//populating arrays from respective linked lists
int i = 0;
for (pNode* reader = headP; reader != currentNodeP->nextNode; reader = reader->nextNode) {
positionArray[i] = reader->pos.x;
positionArray[i + 1] = reader->pos.y;
positionArray[i + 2] = reader->pos.z;
#ifdef DEBUG_INFO
printf("Vertex %d: %f %f %f\n", i / 3, positionArray[i], positionArray[i + 1], positionArray[i + 2]);
#endif
i += 3;
}

// making sure that the object has textures applied
if (headT != currentNodeT) {
i = 0;
for (tNode* reader = headT; reader->nextNode != NULL; reader = reader->nextNode) {
textureArray[i] = reader->pos.x;
textureArray[i + 1] = reader->pos.y;
#ifdef DEBUG_INFO
printf("Texture %d: %f %f\n", i / 2, textureArray[i], textureArray[i + 1]);
#endif
i += 2;
}
textureAvailable = true;
}

i = 0;
for (nNode* reader = headN; currentNodeN->nextNode != reader; reader = reader->nextNode) {
normalArray[i] = reader->pos.x;
normalArray[i + 1] = reader->pos.y;
normalArray[i + 2] = reader->pos.z;
#ifdef DEBUG_INFO
printf("Normal %d: %f %f %f\n", i / 3, normalArray[i], normalArray[i + 1], normalArray[i + 2]);
#endif
i += 3;
}

while (fgets(readVal, 30, file)) {
if (readVal[0] == 'f')
++f_count;
#ifdef DEBUG_INFO
printf("Face: %d\n", f_count);
#endif
}
fseek(file, 0, SEEK_SET);
break;
}
}

// TODO now deal with the 'f' section of the file, this is going to be the real work
if (!textureAvailable) {
finalBuffer = (float*)malloc(sizeof(float) * f_count * 6 * 3);
f_count = 0;

while (1) {
int result = fscanf(file, "%s ", &dataType);
if (result == EOF)
break;

int positions[3];
int normals[3];

if (strcmp(dataType, "f") == 0) {
fscanf(file, "%d//%d %d//%d %d//%d", &positions[0], &normals[0], &positions[1], &normals[1], &positions[2], &normals[2]);
#ifdef DEBUG_INFO
printf("%d//%d %d//%d %d//%d\n", positions[0], normals[0], positions[1], normals[1], positions[2], normals[2]);
#endif
finalBuffer[f_count] = positionArray[3 * (positions[0] - 1)];
finalBuffer[f_count + 1] = positionArray[3 * (positions[0] - 1) + 1];
finalBuffer[f_count + 2] = positionArray[3 * (positions[0] - 1) + 2];
finalBuffer[f_count + 3] = normalArray[3 * (normals[0] - 1)];
finalBuffer[f_count + 4] = normalArray[3 * (normals[0] - 1) + 1];
finalBuffer[f_count + 5] = normalArray[3 * (normals[0] - 1) + 2];

finalBuffer[f_count + 6] = positionArray[3 * (positions[1] - 1)];
finalBuffer[f_count + 7] = positionArray[3 * (positions[1] - 1) + 1];
finalBuffer[f_count + 8] = positionArray[3 * (positions[1] - 1) + 2];
finalBuffer[f_count + 9] = normalArray[3 * (normals[1] - 1)];
finalBuffer[f_count + 10] = normalArray[3 * (normals[1] - 1) + 1];
finalBuffer[f_count + 11] = normalArray[3 * (normals[1] - 1) + 2];

finalBuffer[f_count + 12] = positionArray[3 * (positions[2] - 1)];
finalBuffer[f_count + 13] = positionArray[3 * (positions[2] - 1) + 1];
finalBuffer[f_count + 14] = positionArray[3 * (positions[2] - 1) + 2];
finalBuffer[f_count + 15] = normalArray[3 * (normals[2] - 1)];
finalBuffer[f_count + 16] = normalArray[3 * (normals[2] - 1) + 1];
finalBuffer[f_count + 17] = normalArray[3 * (normals[2] - 1) + 2];
f_count += 17;
}
}
faces = finalBuffer;
free(positionArray);
free(normalArray);
}
printf("Done Loading Object\n");
return f_count;
}

int main()
{
float* data = nullptr;

int faces=0;
clock_t start = clock();
myobj_load("stall.obj", data);
clock_t end = clock();

printf("Time taken: %f\n", (float)(end - start) / CLOCKS_PER_SEC);


std::cin.get();
return 0;
}
