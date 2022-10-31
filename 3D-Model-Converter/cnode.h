#include <assimp/scene.h>

#include "ctypes.h"
#include "canim.h"

#ifndef CNODE_H
#define CNODE_H

class CNode {
public:
	int nameLength;
	char* name;

	Mat4x4 transformation;
	int parentIndex;

	int childCount;
	int* childIndices;

	int meshCount;
	int* meshIndices;

	void loadNode(aiNode* node) {
		nameLength = node->mName.length;
		name = (char*)malloc(nameLength);
		memcpy(name, node->mName.C_Str(), nameLength);

		transformation.a1 = node->mTransformation.a1;
		transformation.a2 = node->mTransformation.a2;
		transformation.a3 = node->mTransformation.a3;
		transformation.a4 = node->mTransformation.a4;
		transformation.b1 = node->mTransformation.b1;
		transformation.b2 = node->mTransformation.b2;
		transformation.b3 = node->mTransformation.b3;
		transformation.b4 = node->mTransformation.b4;
		transformation.c1 = node->mTransformation.c1;
		transformation.c2 = node->mTransformation.c2;
		transformation.c3 = node->mTransformation.c3;
		transformation.c4 = node->mTransformation.c4;
		transformation.d1 = node->mTransformation.d1;
		transformation.d2 = node->mTransformation.d2;
		transformation.d3 = node->mTransformation.d3;
		transformation.d4 = node->mTransformation.d4;

		parentIndex = -1;

		childCount = node->mNumChildren;
		// indices will have to be externally handled
		
		meshCount = node->mNumMeshes;
		meshIndices = (int*)node->mMeshes;
	}

	void setParentIndex(int parentIndex) {this->parentIndex = parentIndex;}
	void setChildIndices(int* childIndices) {
		this->childIndices = childIndices;
	}
};

#endif