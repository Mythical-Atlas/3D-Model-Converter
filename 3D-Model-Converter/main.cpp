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
CAnimChannel* animChannels;
CAnim* anims;

int countNodeChildren(aiNode* node, int prevCount) {
	int newCount = prevCount + 1;
	for(int i = 0; i < node->mNumChildren; i++) {newCount = countNodeChildren(node->mChildren[i], newCount);}
	return newCount;
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

	int nodeCount = countNodeChildren(scene->mRootNode, 0);
	nodes = (CNode*)malloc(sizeof(CNode) * nodeCount);
	loadNode(scene->mRootNode, -1);

	int animCount = scene->mNumAnimations;
	anims = (CAnim*)malloc(sizeof(CAnim) * animCount);
	for(int a = 0; a < animCount; a++) {anims[a].loadAnim(scene->mAnimations[a]);}

	int channelIndex = 0;
	int animChannelCount = 0;
	for(int a = 0; a < animCount; a++) {animChannelCount += scene->mAnimations[a]->mNumChannels;}
	animChannels = (CAnimChannel*)malloc(sizeof(CAnimChannel) * animChannelCount);

	for(int a = 0; a < animCount; a++) {
		int* channelIndices = (int*)malloc(sizeof(int) * scene->mAnimations[a]->mNumChannels);
		for(int c = 0; c < scene->mAnimations[a]->mNumChannels; c++) {
			animChannels[channelIndex].loadAnimChannel(scene->mAnimations[a]->mChannels[c]);
			channelIndices[c] = channelIndex++;
		}

		anims[a].setChannelIndices(channelIndices);
	}

	exportRaw(nodeCount, nodes, meshCount, meshes, animCount, anims, animChannelCount, animChannels);

	return 0;
}