#include <assimp/scene.h>

#include "ctypes.h"
#include "canimChannel.h"

#ifndef CANIM_H
#define CANIM_H

class CAnim {
public:
	int nameLength;
	char* name;

	double duration;
	double ticksPerSecond;
	int channelCount;
	int* channelIndices;

	void loadAnim(aiAnimation* anim) {
		nameLength = anim->mName.length;
		name = (char*)malloc(nameLength);
		memcpy(name, anim->mName.C_Str(), nameLength);

		duration = anim->mDuration;
		ticksPerSecond = anim->mTicksPerSecond;
		channelCount = anim->mNumChannels;

		// indices handled externally
	}

	void setChannelIndices(int* channelIndices) {this->channelIndices = channelIndices;}
};

#endif