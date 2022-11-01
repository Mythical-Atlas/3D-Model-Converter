#include <assimp/scene.h>

#include "ctypes.h"

#ifndef CANIM_CHANNEL_H
#define CANIM_CHANNEL_H

class CAnimChannel {
public:
	int nodeNameLength;
	char* nodeName;

	int positionKeyCount;
	double* positionKeyTimes;
	Vec3* positionKeyValues;

	int rotationKeyCount;
	double* rotationKeyTimes;
	Quat* rotationKeyValues;

	int scaleKeyCount;
	double* scaleKeyTimes;
	Vec3* scaleKeyValues;

	void loadAnimChannel(aiNodeAnim* nodeAnim) {
		nodeNameLength = nodeAnim->mNodeName.length;
		nodeName = (char*)malloc(nodeNameLength);
		memcpy(nodeName, nodeAnim->mNodeName.C_Str(), nodeNameLength);

		positionKeyCount = nodeAnim->mNumPositionKeys;
		positionKeyTimes = (double*)malloc(sizeof(double) * positionKeyCount);
		positionKeyValues = (Vec3*)malloc(sizeof(Vec3) * positionKeyCount);
		for(int i = 0; i < positionKeyCount; i++) {
			positionKeyTimes[i] = nodeAnim->mPositionKeys[i].mTime;
			positionKeyValues[i][0] = nodeAnim->mPositionKeys[i].mValue.x;
			positionKeyValues[i][1] = nodeAnim->mPositionKeys[i].mValue.y;
			positionKeyValues[i][2] = nodeAnim->mPositionKeys[i].mValue.z;
		}

		rotationKeyCount = nodeAnim->mNumRotationKeys;
		rotationKeyTimes = (double*)malloc(sizeof(double) * rotationKeyCount);
		rotationKeyValues = (Quat*)malloc(sizeof(Quat) * rotationKeyCount);
		for(int i = 0; i < rotationKeyCount; i++) {
			rotationKeyTimes[i] = nodeAnim->mRotationKeys[i].mTime;
			rotationKeyValues[i][0] = nodeAnim->mRotationKeys[i].mValue.w;
			rotationKeyValues[i][1] = nodeAnim->mRotationKeys[i].mValue.x;
			rotationKeyValues[i][2] = nodeAnim->mRotationKeys[i].mValue.y;
			rotationKeyValues[i][3] = nodeAnim->mRotationKeys[i].mValue.z;
		}

		scaleKeyCount = nodeAnim->mNumScalingKeys;
		scaleKeyTimes = (double*)malloc(sizeof(double) * scaleKeyCount);
		scaleKeyValues = (Vec3*)malloc(sizeof(Vec3) * scaleKeyCount);
		for(int i = 0; i < scaleKeyCount; i++) {
			scaleKeyTimes[i] = nodeAnim->mScalingKeys[i].mTime;
			scaleKeyValues[i][0] = nodeAnim->mScalingKeys[i].mValue.x;
			scaleKeyValues[i][1] = nodeAnim->mScalingKeys[i].mValue.y;
			scaleKeyValues[i][2] = nodeAnim->mScalingKeys[i].mValue.z;
		}
	}
};

#endif