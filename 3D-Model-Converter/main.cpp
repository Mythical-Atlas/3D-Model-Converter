#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include "cexporter.h"
#include "cmesh.h"
#include "ctypes.h"
#include "cnode.h"
#include "canim.h"

CMesh* meshes;
int nodeIndex = 0;
CNode* nodes;

CAnim* anims;

int countNodeChildren(aiNode* node) {
	if(node->mNumChildren == 0) {return 0;}

	int count = 1;
	for(int i = 0; i < node->mNumChildren; i++) {count += countNodeChildren(node->mChildren[i]);}

	return count;
}

void loadNode(aiNode* node, int parentIndex) {
	nodes[nodeIndex].loadNode(node);
	if(parentIndex != -1) {nodes[nodeIndex].setParentIndex(parentIndex);} // doesn't really matter since it's set to -1 on load
	
	int newParentIndex = nodeIndex;
	nodeIndex++;

	int* childIndices = (int*)malloc(sizeof(int) * node->mNumChildren);
	for(int i = 0; i < node->mNumChildren; i++) {
		childIndices[i] = nodeIndex;
		loadNode(node->mChildren[i], newParentIndex);
	}

	nodes[newParentIndex].setChildIndices(childIndices);
}

int main() {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("sonic.fbx", 0);

	int meshCount = scene->mNumMeshes;
	meshes = (CMesh*)malloc(sizeof(CMesh) * meshCount);
	for(int m = 0; m < meshCount; m++) {meshes[m].loadMesh(scene->mMeshes[m]);}

	int nodeCount = countNodeChildren(scene->mRootNode) + 1;
	nodes = (CNode*)malloc(sizeof(CNode) * nodeCount);
	loadNode(scene->mRootNode, -1);

	// animChannels

	int animCount = scene->mNumAnimations;
	anims = (CAnim*)malloc(sizeof(CAnim) * animCount);
	for(int a = 0; a < animCount; a++) {anims[a].loadAnim(scene->mAnimations[a]);}

	cexport(meshes, meshCount);

	return 0;
}