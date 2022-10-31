#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include "cexporter.h"
#include "cmesh.h"

int main() {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("sonic.fbx", 0);

	/*printf("Number of child nodes from the root node: %i\n", scene->mRootNode->mNumChildren);
	printf("Number of meshes in the root node: %i\n", scene->mRootNode->mNumMeshes);
	printf("\n");

	for(int n = 0; n < scene->mRootNode->mNumChildren; n++) {
		if(scene->mRootNode->mChildren[n]->mNumMeshes != 0) {
			printf("Node index: %i\n", n);
			printf("Number of meshes: %i\n", scene->mRootNode->mChildren[n]->mNumMeshes);
		
			for(int m = 0; m < scene->mRootNode->mChildren[n]->mNumMeshes; m++) {
				printf("Mesh index: %i\n", m);
				printf("Number of vertices: %i\n", scene->mMeshes[scene->mRootNode->mChildren[n]->mMeshes[m]]->mNumVertices);
				printf("Material index: %i\n", scene->mMeshes[scene->mRootNode->mChildren[n]->mMeshes[m]]->mMaterialIndex);
			}

			getchar();
		}
	}*/

	int meshCount = scene->mNumMeshes;
	CMesh* meshes = (CMesh*)malloc(sizeof(CMesh) * meshCount);
	// scene->mRootNode->mChildren[2]->mMeshes[0]
	for(int m = 0; m < meshCount; m++) {
		meshes[m].loadVertices(scene->mMeshes[m]->mVertices, scene->mMeshes[m]->mNumVertices);
		meshes[m].loadUVCoords(scene->mMeshes[m]->mTextureCoords);
		meshes[m].loadNormals(scene->mMeshes[m]->mNormals);
		meshes[m].loadMaterialID(scene->mMeshes[m]->mMaterialIndex);
	}

	cexport(meshes, meshCount);

	return 0;
}