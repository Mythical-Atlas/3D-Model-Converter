#include <assimp/scene.h>

#include "ctypes.h"

#ifndef CMESH_H
#define CMESH_H

class CMesh {
public:
	int vertCount;
	Vec3* vertices;
	Vec2* uvCoords;
	Vec3* normals;
	int materialID;

	void loadMesh(aiMesh* mesh) {
		this->loadVertices(mesh->mVertices, mesh->mNumVertices);
		this->loadUVCoords(mesh->mTextureCoords);
		this->loadNormals(mesh->mNormals);
		this->loadMaterialID(mesh->mMaterialIndex);
	}

	void loadVertices(aiVector3D* mVertices, int vertCount) {
		this->vertCount = vertCount;

		vertices = (Vec3*)malloc(sizeof(Vec3) * vertCount);
		for(int v = 0; v < vertCount; v++) {
			vertices[v][0] = mVertices[v].x;
			vertices[v][1] = mVertices[v].y;
			vertices[v][2] = mVertices[v].z;
		}
	}

	void loadUVCoords(aiVector3D* mTextureCoords[AI_MAX_NUMBER_OF_TEXTURECOORDS]) {
		uvCoords = (Vec2*)malloc(sizeof(Vec2) * vertCount);
		for(int v = 0; v < vertCount; v++) {
			uvCoords[v][0] = mTextureCoords[0][v].x;
			uvCoords[v][1] = mTextureCoords[0][v].y;
		}
	}

	void loadNormals(aiVector3D* mNormals) {
		normals = (Vec3*)malloc(sizeof(Vec3) * vertCount);
		for(int v = 0; v < vertCount; v++) {
			normals[v][0] = mNormals[v].x;
			normals[v][1] = mNormals[v].y;
			normals[v][2] = mNormals[v].z;
		}
	}

	void loadMaterialID(int materialID) {this->materialID = materialID;}
};

#endif