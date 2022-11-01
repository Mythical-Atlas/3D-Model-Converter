#include "cmesh.h"
#include "cnode.h"
#include "canim.h"
#include "canimChannel.h"

#include <fstream>
#include <iostream>

#ifndef CEXPORTER_H
#define CEXPORTER_H

//CMesh* meshes;

const char* header = ""
	"// auto-generated code by Ben Correll's 3D Model Converter\n\n"
	"#include <stdlib.h>\n\n"
	"#ifndef MODEL_H\n"
	"#define MODEL_H\n"
	"\n"
"";

void cexport(int nodeCount, CNode* nodes, int meshCount, CMesh* meshes, int animCount, CAnim* anims, int channelCount, CAnimChannel* channels) {
	FILE* fp = fopen("model.h", "w");

	fprintf(fp, header);

	fprintf(fp, "/*--------------------------------------------------NODES--------------------------------------------------*/\n");
	fprintf(fp, "int nodeCount = %i;\n", nodeCount);
	fprintf(fp, "int* nodeNameLengths;\n");
	fprintf(fp, "const char** nodeNames;\n");
	fprintf(fp, "float** nodeTransformations;\n");
	fprintf(fp, "int* nodeParentIndices;\n");
	fprintf(fp, "int* nodeChildCounts;\n");
	fprintf(fp, "int** nodeChildIndices;\n");
	fprintf(fp, "int* nodeMeshCounts;\n");
	fprintf(fp, "int** nodeMeshIndices;\n\n");

	for(int n = 0; n < nodeCount; n++) {
		//fprintf(fp, "int node%iNameLength = %i;\n", n, nodes[n].nameLength);
		fprintf(fp, "const char* node%iName = \"", n);
		for(int c = 0; c < nodes[n].nameLength; c++) {fprintf(fp, "%c", nodes[n].name[c]);}
		fprintf(fp, "\";\n");

		fprintf(fp, "float node%iTransformation[16] = {%ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff};\n", n,
			nodes[n].transformation.a1, nodes[n].transformation.a2, nodes[n].transformation.a3, nodes[n].transformation.a4,
			nodes[n].transformation.b1, nodes[n].transformation.b2, nodes[n].transformation.b3, nodes[n].transformation.b4,
			nodes[n].transformation.c1, nodes[n].transformation.c2, nodes[n].transformation.c3, nodes[n].transformation.c4,
			nodes[n].transformation.d1, nodes[n].transformation.d2, nodes[n].transformation.d3, nodes[n].transformation.d4
		);

		//fprintf(fp, "int node%iParentIndex = %i;\n", n, nodes[n].parentIndex);

		//fprintf(fp, "int node%iChildCount = %i;\n", n, nodes[n].childCount);
		if(nodes[n].childCount > 0) {
			fprintf(fp, "int node%iChildIndices[%i] = {", n, nodes[n].childCount);
			for(int i = 0; i < nodes[n].childCount; i++) {fprintf(fp, "%i, ", nodes[n].childIndices[i]);}
			fprintf(fp, "};\n");
		}

		//fprintf(fp, "int node%iMeshCount = %i;\n", n, nodes[n].meshCount);
		if(nodes[n].meshCount > 0) {
			fprintf(fp, "int node%iMeshIndices[%i] = {", n, nodes[n].meshCount);
			for(int i = 0; i < nodes[n].meshCount; i++) {fprintf(fp, "%i, ", nodes[n].meshIndices[i]);}
			fprintf(fp, "};\n");
		}
		fprintf(fp, "\n");
	}

	fprintf(fp, "/*--------------------------------------------------MESHES--------------------------------------------------*/\n");
	fprintf(fp, "\nint meshCount = %i;\n", meshCount);
	fprintf(fp, "int* meshVertCounts;\n");
	fprintf(fp, "float** meshVertices;\n");
	fprintf(fp, "int* meshMaterialIDs;\n\n");

	for(int m = 0; m < meshCount; m++) {
		//fprintf(fp, "const int mesh%iVertCount = %i;\n", m, meshes[m].vertCount);
		fprintf(fp, "float mesh%iVertices[%i] = {\n", m, meshes[m].vertCount * 8);
		for(int v = 0; v < meshes[m].vertCount; v++) {
			fprintf(fp, "\t%ff, %ff, %ff,", meshes[m].vertices[v][0], meshes[m].vertices[v][1], meshes[m].vertices[v][2]);
			fprintf(fp, "\t%ff, %ff,", meshes[m].uvCoords[v][0], meshes[m].uvCoords[v][1]);
			fprintf(fp, "\t%ff, %ff, %ff,\n", meshes[m].normals[v][0], meshes[m].normals[v][1], meshes[m].normals[v][2]);
		}
		fprintf(fp, "};\n\n");
		//fprintf(fp, "};\nint mesh%iMaterialID = %i;\n\n", m, meshes[m].materialID);
	}
	
	fprintf(fp, "/*--------------------------------------------------ANIMATIONS--------------------------------------------------*/\n");
	fprintf(fp, "\nint animationCount = %i;\n", animCount);
	fprintf(fp, "int* animationNameLengths;\n");
	fprintf(fp, "const char** animationNames;\n");
	fprintf(fp, "double* animationDurations;\n");
	fprintf(fp, "double* animationTicksPerSeconds;\n");
	fprintf(fp, "int* animationChannelCounts;\n");
	fprintf(fp, "int** animationChannelIndices;\n\n");

	for(int a = 0; a < animCount; a++) {
		fprintf(fp, "int animation%iNameLength = %i;\n", a, anims[a].nameLength);
		fprintf(fp, "const char* animation%iName = \"", a);
		for(int c = 0; c < anims[a].nameLength; c++) {fprintf(fp, "%c", anims[a].name[c]);}
		fprintf(fp, "\";\n");

		fprintf(fp, "double animation%iDuration = %lf;\n", a, anims[a].duration);
		fprintf(fp, "double animation%iTicksPerSeconds = %lf;\n", a, anims[a].ticksPerSecond);

		fprintf(fp, "int animation%iChannelCount = %i;\n", a, anims[a].channelCount);
		fprintf(fp, "int animation%iChannelIndices[%i] = {", a, anims[a].channelCount);
		for(int i = 0; i < anims[a].channelCount; i++) {fprintf(fp, "%i, ", anims[a].channelIndices[i]);}
		fprintf(fp, "};\n\n");
	}

	fprintf(fp, "/*--------------------------------------------------ANIMATION CHANNELS--------------------------------------------------*/\n");
	fprintf(fp, "\nint animationChannelCount = %i;\n", channelCount);
	fprintf(fp, "int* animationChannelNodeNameLengths;\n");
	fprintf(fp, "const char** animationChannelNodeNames;\n");
	fprintf(fp, "int* animationChannelPositionKeyCounts;\n");
	fprintf(fp, "double** animationChannelPositionKeyTimes;\n");
	fprintf(fp, "float** animationChannelPositionKeyValues;\n");
	fprintf(fp, "int* animationChannelRotationKeyCounts;\n");
	fprintf(fp, "double** animationChannelRotationKeyTimes;\n");
	fprintf(fp, "float** animationChannelRotationKeyValues;\n");
	fprintf(fp, "int* animationChannelScaleKeyCounts;\n");
	fprintf(fp, "double** animationChannelScaleKeyTimes;\n\n");
	fprintf(fp, "float** animationChannelScaleKeyValues;\n\n");

	for(int a = 0; a < channelCount; a++) {
		fprintf(fp, "int animationChannel%iNodeNameLength = %i;\n", a, channels[a].nodeNameLength);
		fprintf(fp, "const char* animationChannel%iNodeName = \"", a);
		for(int c = 0; c < channels[a].nodeNameLength; c++) {fprintf(fp, "%c", channels[a].nodeName[c]);}
		fprintf(fp, "\";\n");
		
		//                                              POSITION

		fprintf(fp, "int animationChannel%iPositionKeyCount = %i;\n", a, channels[a].positionKeyCount);

		fprintf(fp, "double animationChannel%iPositionKeyTimes[%i] = {", a, channels[a].positionKeyCount);
		for(int k = 0; k < channels[a].positionKeyCount; k++) {fprintf(fp, "%lf, ", channels[a].positionKeyTimes[k]);}
		fprintf(fp, "};\n");

		fprintf(fp, "float animationChannel%iPositionKeyValues[%i] = {\n", a, channels[a].positionKeyCount * 3);
		for(int k = 0; k < channels[a].positionKeyCount; k++) {fprintf(fp, "\t%f, %f, %f,\n", channels[a].positionKeyValues[k][0], channels[a].positionKeyValues[k][1], channels[a].positionKeyValues[k][2]);}
		fprintf(fp, "};\n");

		//                                              ROTATION

		fprintf(fp, "int animationChannel%iRotationKeyCount = %i;\n", a, channels[a].rotationKeyCount);

		fprintf(fp, "double animationChannel%iRotationKeyTimes[%i] = {", a, channels[a].rotationKeyCount);
		for(int k = 0; k < channels[a].rotationKeyCount; k++) {fprintf(fp, "%lf, ", channels[a].rotationKeyTimes[k]);}
		fprintf(fp, "};\n");

		fprintf(fp, "float animationChannel%iRotationKeyValues[%i] = {\n", a, channels[a].rotationKeyCount * 4);
		for(int k = 0; k < channels[a].rotationKeyCount; k++) {fprintf(fp, "\t%f, %f, %f, %f,\n", channels[a].rotationKeyValues[k][0], channels[a].rotationKeyValues[k][1], channels[a].rotationKeyValues[k][2], channels[a].rotationKeyValues[k][3]);}
		fprintf(fp, "};\n");

		//                                              SCALE

		fprintf(fp, "int animationChannel%iScaleKeyCount = %i;\n", a, channels[a].scaleKeyCount);

		fprintf(fp, "double animationChannel%iScaleKeyTimes[%i] = {", a, channels[a].scaleKeyCount);
		for(int k = 0; k < channels[a].scaleKeyCount; k++) {fprintf(fp, "%lf, ", channels[a].scaleKeyTimes[k]);}
		fprintf(fp, "};\n");

		fprintf(fp, "float animationChannel%iScaleKeyValues[%i] = {\n", a, channels[a].scaleKeyCount * 3);
		for(int k = 0; k < channels[a].scaleKeyCount; k++) {fprintf(fp, "\t%f, %f, %f,\n", channels[a].scaleKeyValues[k][0], channels[a].scaleKeyValues[k][1], channels[a].scaleKeyValues[k][2]);}
		fprintf(fp, "};\n\n");
	}

	fprintf(fp, "void loadModelPointers() {\n");

	// nodes

	fprintf(fp, "\tnodeNameLengths = (int*)malloc(sizeof(int) * %i);\n", nodeCount);
	for(int m = 0; m < nodeCount; m++) {fprintf(fp, "\tnodeNameLengths[%i] = %i;\n", m, nodes[m].nameLength);}

	fprintf(fp, "\n\tnodeNames = (const char**)malloc(sizeof(const char*) * %i);\n", nodeCount);
	for(int m = 0; m < nodeCount; m++) {fprintf(fp, "\tnodeNames[%i] = &node%iName[0];\n", m, m);}

	fprintf(fp, "\n\tnodeTransformations = (float**)malloc(sizeof(float*) * %i);\n", nodeCount);
	for(int m = 0; m < nodeCount; m++) {fprintf(fp, "\tnodeTransformations[%i] = &node%iTransformation[0];\n", m, m);}

	fprintf(fp, "\n\tnodeParentIndices = (int*)malloc(sizeof(int) * %i);\n", nodeCount);
	for(int m = 0; m < nodeCount; m++) {fprintf(fp, "\tnodeParentIndices[%i] = %i;\n", m, nodes[m].parentIndex);}

	fprintf(fp, "\n\tnodeChildCounts = (int*)malloc(sizeof(int) * %i);\n", nodeCount);
	for(int m = 0; m < nodeCount; m++) {fprintf(fp, "\tnodeChildCounts[%i] = %i;\n", m, nodes[m].childCount);}

	fprintf(fp, "\n\tnodeChildIndices = (int**)malloc(sizeof(int*) * %i);\n", nodeCount);
	for(int m = 0; m < nodeCount; m++) {if(nodes[m].childCount > 0) {fprintf(fp, "\tnodeChildIndices[%i] = &node%iChildIndices[0];\n", m, m);}}

	fprintf(fp, "\n\tnodeMeshCounts = (int*)malloc(sizeof(int) * %i);\n", nodeCount);
	for(int m = 0; m < nodeCount; m++) {fprintf(fp, "\tnodeMeshCounts[%i] = %i;\n", m, nodes[m].meshCount);}

	fprintf(fp, "\n\tnodeMeshIndices = (int**)malloc(sizeof(int*) * %i);\n", nodeCount);
	for(int m = 0; m < nodeCount; m++) {if(nodes[m].meshCount > 0) {fprintf(fp, "\tnodeMeshIndices[%i] = &node%iMeshIndices[0];\n", m, m);}}

	// meshes

	fprintf(fp, "\n\tmeshVertCounts = (int*)malloc(sizeof(int) * %i);\n", meshCount);
	for(int m = 0; m < meshCount; m++) {fprintf(fp, "\tmeshVertCounts[%i] = %i;\n", m, meshes[m].vertCount);}

	fprintf(fp, "\n\tmeshVertices = (float**)malloc(sizeof(float*) * %i);\n", meshCount);
	for(int m = 0; m < meshCount; m++) {fprintf(fp, "\tmeshVertices[%i] = &mesh%iVertices[0];\n", m, m);}

	fprintf(fp, "\n\tmeshMaterialIDs = (int*)malloc(sizeof(int) * %i);\n", meshCount);
	for(int m = 0; m < meshCount; m++) {fprintf(fp, "\tmeshMaterialIDs[%i] = %i;\n", m, meshes[m].materialID);}

	// animations

	fprintf(fp, "\n\tanimationNameLengths = (int*)malloc(sizeof(int) * %i);\n", animCount);
	for(int m = 0; m < animCount; m++) {fprintf(fp, "\tanimationNameLengths[%i] = %i;\n", m, anims[m].nameLength);}

	fprintf(fp, "\n\tanimationNames = (const char**)malloc(sizeof(const char*) * %i);\n", animCount);
	for(int m = 0; m < animCount; m++) {fprintf(fp, "\tanimationNames[%i] = &animation%iName[0];\n", m, m);}

	fprintf(fp, "\n\tanimationDurations = (double*)malloc(sizeof(double) * %i);\n", animCount);
	for(int m = 0; m < animCount; m++) {fprintf(fp, "\tanimationDurations[%i] = %lf;\n", m, anims[m].duration);}

	fprintf(fp, "\n\tanimationTicksPerSeconds = (double*)malloc(sizeof(double) * %i);\n", animCount);
	for(int m = 0; m < animCount; m++) {fprintf(fp, "\tanimationTicksPerSeconds[%i] = %lf;\n", m, anims[m].ticksPerSecond);}

	fprintf(fp, "\n\tanimationChannelCounts = (int*)malloc(sizeof(int) * %i);\n", animCount);
	for(int m = 0; m < animCount; m++) {fprintf(fp, "\tanimationChannelCounts[%i] = %i;\n", m, anims[m].channelCount);}

	fprintf(fp, "\n\tanimationChannelIndices = (int**)malloc(sizeof(int*) * %i);\n", animCount);
	for(int m = 0; m < animCount; m++) {fprintf(fp, "\tanimationChannelIndices[%i] = &animation%iChannelIndices[0];\n", m, m);}

	// channels

	fprintf(fp, "\n\tanimationChannelNodeNameLengths = (int*)malloc(sizeof(int) * %i);\n", channelCount);
	for(int m = 0; m < channelCount; m++) {fprintf(fp, "\tanimationChannelNodeNameLengths[%i] = %i;\n", m, channels[m].nodeNameLength);}

	fprintf(fp, "\n\tanimationChannelNodeNames = (const char**)malloc(sizeof(const char*) * %i);\n", channelCount);
	for(int m = 0; m < channelCount; m++) {fprintf(fp, "\tanimationChannelNodeNames[%i] = &animationChannel%iNodeName[0];\n", m, m);}

	fprintf(fp, "\n\tanimationChannelPositionKeyCounts = (int*)malloc(sizeof(int) * %i);\n", channelCount);
	for(int m = 0; m < channelCount; m++) {fprintf(fp, "\tanimationChannelPositionKeyCounts[%i] = %i;\n", m, channels[m].positionKeyCount);}

	fprintf(fp, "\n\tanimationChannelPositionKeyTimes = (double**)malloc(sizeof(double*) * %i);\n", channelCount);
	for(int m = 0; m < channelCount; m++) {fprintf(fp, "\tanimationChannelPositionKeyTimes[%i] = &animationChannel%iPositionKeyTimes[0];\n", m, m);}

	fprintf(fp, "\n\tanimationChannelPositionKeyValues = (float**)malloc(sizeof(float*) * %i);\n", channelCount);
	for(int m = 0; m < channelCount; m++) {fprintf(fp, "\tanimationChannelPositionKeyValues[%i] = &animationChannel%iPositionKeyValues[0];\n", m, m);}

	fprintf(fp, "\n\tanimationChannelRotationKeyCounts = (int*)malloc(sizeof(int) * %i);\n", channelCount);
	for(int m = 0; m < channelCount; m++) {fprintf(fp, "\tanimationChannelRotationKeyCounts[%i] = %i;\n", m, channels[m].rotationKeyCount);}

	fprintf(fp, "\n\tanimationChannelRotationKeyTimes = (double**)malloc(sizeof(double*) * %i);\n", channelCount);
	for(int m = 0; m < channelCount; m++) {fprintf(fp, "\tanimationChannelRotationKeyTimes[%i] = &animationChannel%iRotationKeyTimes[0];\n", m, m);}

	fprintf(fp, "\n\tanimationChannelRotationKeyValues = (float**)malloc(sizeof(float*) * %i);\n", channelCount);
	for(int m = 0; m < channelCount; m++) {fprintf(fp, "\tanimationChannelRotationKeyValues[%i] = &animationChannel%iRotationKeyValues[0];\n", m, m);}

	fprintf(fp, "\n\tanimationChannelScaleKeyCounts = (int*)malloc(sizeof(int) * %i);\n", channelCount);
	for(int m = 0; m < channelCount; m++) {fprintf(fp, "\tanimationChannelScaleKeyCounts[%i] = %i;\n", m, channels[m].scaleKeyCount);}

	fprintf(fp, "\n\tanimationChannelScaleKeyTimes = (double**)malloc(sizeof(double*) * %i);\n", channelCount);
	for(int m = 0; m < channelCount; m++) {fprintf(fp, "\tanimationChannelScaleKeyTimes[%i] = &animationChannel%iScaleKeyTimes[0];\n", m, m);}

	fprintf(fp, "\n\tanimationChannelScaleKeyValues = (float**)malloc(sizeof(float*) * %i);\n", channelCount);
	for(int m = 0; m < channelCount; m++) {fprintf(fp, "\tanimationChannelScaleKeyValues[%i] = &animationChannel%iScaleKeyValues[0];\n", m, m);}

	fprintf(fp, "};\n\n#endif");

	fclose(fp);
}

#endif