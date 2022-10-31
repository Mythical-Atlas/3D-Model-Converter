#include "cmesh.h"

#include <fstream>
#include <iostream>

#ifndef CEXPORTER_H
#define CEXPORTER_H

//CMesh* meshes;

const char* header = ""
	"#include <stdlib.h>\n\n"
	"#ifndef MODEL_H\n"
	"#define MODEL_H\n"
	"\n"
"";
const char* footer = ""
	"#endif"
"";

void cexport(CMesh* meshes, int meshCount) {
	FILE* fp = fopen("model.h", "w");

	fprintf(fp, header);

	fprintf(fp, "int meshCount = %i;\n", meshCount);
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
		fprintf(fp, "};\n");
		//fprintf(fp, "};\nint mesh%iMaterialID = %i;\n\n", m, meshes[m].materialID);
	}

	fprintf(fp, "void loadModelPointers() {\n");

	fprintf(fp, "\tmeshVertCounts = (int*)malloc(sizeof(int) * %i);\n", meshCount);
	for(int m = 0; m < meshCount; m++) {fprintf(fp, "\tmeshVertCounts[%i] = %i;\n", m, meshes[m].vertCount);}

	fprintf(fp, "\n\tmeshVertices = (float**)malloc(sizeof(float*) * %i);\n", meshCount);
	for(int m = 0; m < meshCount; m++) {fprintf(fp, "\tmeshVertices[%i] = &mesh%iVertices[0];\n", m, m);}

	fprintf(fp, "\n\tmeshMaterialIDs = (int*)malloc(sizeof(int) * %i);\n", meshCount);
	for(int m = 0; m < meshCount; m++) {fprintf(fp, "\tmeshMaterialIDs[%i] = %i;\n", m, meshes[m].materialID);}

	/*fprintf(fp, "meshVertices = {");
	for(int m = 0; m < meshCount; m++) {fprintf(fp, "mesh%iVertices,", m);}
	fprintf(fp, "};\n");*/

	/*fprintf(fp, "float** meshMaterialIDs = {", meshCount);
	for(int m = 0; m < meshCount; m++) {fprintf(fp, "&material%iID,", m);}
	fprintf(fp, "};\n\n");*/



	fprintf(fp, "};\n\n");
	fprintf(fp, footer);

	fclose(fp);
}

#endif