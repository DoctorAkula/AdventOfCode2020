#include"load.h"
#include<stdbool.h>
static const int cubeSide = 1024; /*One gig of memory for a 3D volume*/
static const int bitCubeSide = (cubeSide >> 3);
static const int Center = (cubeSide >> 1);
/*Adjacent Voxels*/
static const int adcntVox[26][3] = 
{{-1,0,0},{1,0,0},{0,-1,0},{-1,-1,0},{1,-1,0},{0,1,0},{-1,1,0},{1,1,0},{0,0,-1},{-1,0,-1},{1,0,-1},{0,-1,-1},{-1,-1,-1},
{1,-1,-1},{0,1,-1},{-1,1,-1},{1,1,-1},{0,0,1},{-1,0,1},{1,0,1},{0,-1,1},{-1,-1,1},{1,-1,1},{0,1,1},{-1,1,1},{1,1,1}};
static void ThreeDimBitWrite(unsigned char *volume, long long x, long long y, long long z, bool set){
	unsigned long long linearized = (x >> 3) + (y * bitCubeSide) + (z * bitCubeSide * bitCubeSide);
	if(set)
		volume[linearized] |= (1u << (x & 0x7u));
	else
		volume[linearized] &=~(1u << (x & 0x7u));
}
static bool ThreeDimBitRead(unsigned char *volume, long long x, long long y, long long z){
	unsigned long long linearized = (x >> 3) + (y * bitCubeSide) + (z * bitCubeSide * bitCubeSide);
	return (volume[linearized] >> (x & 0x7)) & 1;
}
static unsigned char ThreeDimByteRead(unsigned char *volume, long long x, long long y, long long z){
	unsigned long long linearized = (x >> 3) + (y * bitCubeSide) + (z * bitCubeSide * bitCubeSide);
}
void day17_1(){
	char *input = loadinput("../input/day17-1.txt");
	unsigned long long volume = ((1024 * 1024 * 1024) >> 3);
	unsigned char *playingVolume[2] = {
	calloc(volume, sizeof(char)),
	calloc(volume, sizeof(char))};
	for(int i = 0; i < volume; i++){
		playingVolume[0][i] = 0;
		playingVolume[1][i] = 0;
	}
	int hack = 0;
	int bounds[3] = {12,12,3}; /*The Bounding Box Size*/
	int offsets[3] = {Center - (bounds[0] >> 1),
			  Center - (bounds[1] >> 1),
			  Center -((bounds[2] + 1) >> 1)};
	printf("xoff: %d\nyoff: %d\nzoff: %d\n", offsets[0],
						 offsets[1],
						 offsets[2]);
	for(int i = 0; i < 64; i++)
	{
		int x = (i & 0x7);
		int y = (i >> 3);
		if(input[i + hack] == '#')
			ThreeDimBitWrite(playingVolume[0], 
					offsets[0] + x,
					offsets[1] + y,
					511, true);
		printf("%d",
		ThreeDimBitRead(playingVolume[0], 
					offsets[0] + x,
					offsets[1] + y,
					511));
		if(x == 7){
			puts("");
			hack++;
		}
	}
	/*Iterate GOL 6 times*/
	for(int i = 0; i < 6; i++)
	{
		/*Go Through Volume*/
		for(int x = 0; x < bounds[0]; x++)
			for(int y = 0; y < bounds[1]; y++)
				for(int z = 0; z < bounds[2]; z++){
					/*Check Adjacent*/
					int adjCount = 0;
					for(int w = 0; w < 26; w++){
						if(ThreeDimBitRead(playingVolume[i & 1],
							offsets[0] + x + adcntVox[w][0],
							offsets[1] + y + adcntVox[w][1],
							offsets[2] + z + adcntVox[w][2]))
							adjCount++;
					}
					/*Is Active*/
					if(ThreeDimBitRead(playingVolume[i & 1],
								 offsets[0] + x,
							 	 offsets[1] + y,
								 offsets[2] + z)){
						/*Check if voxel should be dead*/
						if(!((adjCount == 2) || (adjCount == 3)))
							ThreeDimBitWrite(playingVolume[!(i & 1)],
									 offsets[0] + x,
									 offsets[1] + y,
									 offsets[2] + z, false);
						else
							ThreeDimBitWrite(playingVolume[!(i & 1)],
									 offsets[0] + x,
									 offsets[1] + y,
									 offsets[2] + z, true);
						/*Not Active*/
					}else{
						/*Check if voxel should be alive*/
						if(adjCount == 3)
							ThreeDimBitWrite(playingVolume[!(i & 1)],
									 offsets[0] + x,
									 offsets[1] + y,
									 offsets[2] + z, true);
						else
							ThreeDimBitWrite(playingVolume[!(i & 1)],
									 offsets[0] + x,
									 offsets[1] + y,
									 offsets[2] + z, false);
					}
				}
		/*Print Out Volume*/
		printf("\n----------Iteration: %d----------\n", i);
		for(int z = 0; z < bounds[2]; z++){
			printf("\nZ: %d\n", offsets[2] + z);
			for(int y = 0; y < bounds[1]; y++){
				for(int x = 0; x < bounds[0]; x++){
					printf("%d",
					ThreeDimBitRead(playingVolume[!(i & 1)], 
								offsets[0] + x,
								offsets[1] + y,
								offsets[2] + z));
				}
				putchar('\n');
			}
		}
		bounds[0] += 2;
		bounds[1] += 2;
		bounds[2] += 2;
		offsets[0]--;
		offsets[1]--;
		offsets[2]--;
	}
	/*Count Active*/
	int activeCount = 0;
	for(int z = 0; z < bounds[2]; z++)
		for(int y = 0; y < bounds[1]; y++)
			for(int x = 0; x < bounds[0]; x++){
					if(ThreeDimBitRead(playingVolume[0], 
								offsets[0] + x,
								offsets[1] + y,
								offsets[2] + z)){
						activeCount++;
					}
			}
	printf("Active Elements: %d\n", activeCount);
	free(playingVolume[0]);
	free(playingVolume[1]);
	free(input);
}
