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

	fprintf(fp, "int nodeCount = %i;\n\n", nodeCount);

	for(int n = 0; n < nodeCount; n++) {
		fprintf(fp, "int node%iNameLength = %i;\n", n, nodes[n].nameLength);
		fprintf(fp, "const char* node%iName = \"", n);
		for(int c = 0; c < nodes[n].nameLength; c++) {fprintf(fp, "%c", nodes[n].name[c]);}
		fprintf(fp, "\";\n");

		fprintf(fp, "float node%iTransformation[16] = {%ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff};\n", n,
			nodes[n].transformation.a1, nodes[n].transformation.a2, nodes[n].transformation.a3, nodes[n].transformation.a4,
			nodes[n].transformation.b1, nodes[n].transformation.b2, nodes[n].transformation.b3, nodes[n].transformation.b4,
			nodes[n].transformation.c1, nodes[n].transformation.c2, nodes[n].transformation.c3, nodes[n].transformation.c4,
			nodes[n].transformation.d1, nodes[n].transformation.d2, nodes[n].transformation.d3, nodes[n].transformation.d4
		);

		fprintf(fp, "int node%iParentIndex = %i;\n", n, nodes[n].parentIndex);

		fprintf(fp, "int node%iChildCount = %i;\n", n, nodes[n].childCount);
		fprintf(fp, "int node%iChildIndices[%i] = ", n, nodes[n].childCount);
		for(int i = 0; i < nodes[n].childCount; i++) {}

		fprintf(fp, "int node%iMeshCount = %i;\n", n, nodes[n].meshCount);
	}

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



	fprintf(fp, "};\n\n#endif");

	fclose(fp);
}

#endif