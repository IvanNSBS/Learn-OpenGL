#pragma once

#define NUM_BONES_PER_VERTEX 4

struct VertexBone {
	//Skinned Mesh Data
	unsigned int boneIDs[NUM_BONES_PER_VERTEX];
	float boneWeights[NUM_BONES_PER_VERTEX];
};