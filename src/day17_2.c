#include"load.h"
#include<stdbool.h>
static const int cubeSide = 256; /*Four gigs of memory for a 4D volume*/
static const int bitCubeSide = (cubeSide >> 3);
static const int Center = (cubeSide >> 1);
/*Adjacent Voxels*/
static const int adcntVox[80][4] = 
{
 {-1,0,0,0},{1,0,0,0},{0,-1,0,0},{-1,-1,0,0},{1,-1,0,0},{0,1,0,0},{-1,1,0,0},{1,1,0,0},{0,0,-1,0},{-1,0,-1,0},{1,0,-1,0},{0,-1,-1,0},{-1,-1,-1,0},
 {1,-1,-1,0},{0,1,-1,0},{-1,1,-1,0},{1,1,-1,0},{0,0,1,0},{-1,0,1,0},{1,0,1,0},{0,-1,1,0},{-1,-1,1,0},{1,-1,1,0},{0,1,1,0},{-1,1,1,0},{1,1,1,0},
 {0,0,0,-1},
 {-1,0,0,-1},{1,0,0,-1},{0,-1,0,-1},{-1,-1,0,-1},{1,-1,0,-1},{0,1,0,-1},{-1,1,0,-1},{1,1,0,-1},{0,0,-1,-1},{-1,0,-1,-1},{1,0,-1,-1},{0,-1,-1,-1},{-1,-1,-1,-1},
 {1,-1,-1,-1},{0,1,-1,-1},{-1,1,-1,-1},{1,1,-1,-1},{0,0,1,-1},{-1,0,1,-1},{1,0,1,-1},{0,-1,1,-1},{-1,-1,1,-1},{1,-1,1,-1},{0,1,1,-1},{-1,1,1,-1},{1,1,1,-1},
 {0,0,0,1},
 {-1,0,0,1},{1,0,0,1},{0,-1,0,1},{-1,-1,0,1},{1,-1,0,1},{0,1,0,1},{-1,1,0,1},{1,1,0,1},{0,0,-1,1},{-1,0,-1,1},{1,0,-1,1},{0,-1,-1,1},{-1,-1,-1,1},
 {1,-1,-1,1},{0,1,-1,1},{-1,1,-1,1},{1,1,-1,1},{0,0,1,1},{-1,0,1,1},{1,0,1,1},{0,-1,1,1},{-1,-1,1,1},{1,-1,1,1},{0,1,1,1},{-1,1,1,1},{1,1,1,1},
};
static void FourDimBitWrite(unsigned char *volume, long long x, long long y, long long z, long long w, bool set){
	unsigned long long linearized = (x >> 3) + (y * bitCubeSide) + (z * bitCubeSide * bitCubeSide) + (w * bitCubeSide * bitCubeSide * bitCubeSide);
	if(set)
		volume[linearized] |= (1u << (x & 0x7u));
	else
		volume[linearized] &=~(1u << (x & 0x7u));
}
static bool FourDimBitRead(unsigned char *volume, long long x, long long y, long long z, long long w){
	unsigned long long linearized = (x >> 3) + (y * bitCubeSide) + (z * bitCubeSide * bitCubeSide) + (w * bitCubeSide * bitCubeSide * bitCubeSide);
	return (volume[linearized] >> (x & 0x7)) & 1;
}
void day17_2(){
	char *input = loadinput("../input/day17-1.txt");
	unsigned long long volume = ((256llu * 256llu * 256llu * 256llu) >> 3);
	unsigned char *playingVolume[2] = {
	calloc(volume, sizeof(char)),
	calloc(volume, sizeof(char))};
	for(int i = 0; i < volume; i++){
		playingVolume[0][i] = 0;
		playingVolume[1][i] = 0;
	}
	int hack = 0;
	int bounds[4] = {12,12,3,3}; /*The Bounding Box Size*/
	int offsets[4] = {Center - (bounds[0] >> 1),
			  Center - (bounds[1] >> 1),
			  Center -((bounds[2] + 1) >> 1),
			  Center -((bounds[2] + 1) >> 1)};
	printf("xoff: %d\nyoff: %d\nzoff: %d\n", offsets[0],
						 offsets[1],
						 offsets[2]);
	for(int i = 0; i < 64; i++)
	{
		int x = (i & 0x7);
		int y = (i >> 3);
		if(input[i + hack] == '#')
			FourDimBitWrite(playingVolume[0], 
					offsets[0] + x,
					offsets[1] + y,
					127,
					127, true);
		printf("%d",
		FourDimBitRead(playingVolume[0], 
					offsets[0] + x,
					offsets[1] + y,
					127,
					127));
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
				for(int z = 0; z < bounds[2]; z++)
					for(int w = 0; w < bounds[3]; w++){
						/*Check Adjacent*/
						int adjCount = 0;
						for(int c = 0; c < 80; c++){
							if(FourDimBitRead(playingVolume[i & 1],
								offsets[0] + x + adcntVox[c][0],
								offsets[1] + y + adcntVox[c][1],
								offsets[2] + z + adcntVox[c][2],
								offsets[3] + w + adcntVox[c][3]))
								adjCount++;
						}
						/*Is Active*/
						if(FourDimBitRead(playingVolume[i & 1],
									 offsets[0] + x,
									 offsets[1] + y,
									 offsets[2] + z,
									 offsets[3] + w)){
							/*Check if voxel should be dead*/
							if(!((adjCount == 2) || (adjCount == 3)))
								FourDimBitWrite(playingVolume[!(i & 1)],
										 offsets[0] + x,
										 offsets[1] + y,
										 offsets[2] + z,
										 offsets[3] + w, false);
							else
								FourDimBitWrite(playingVolume[!(i & 1)],
										 offsets[0] + x,
										 offsets[1] + y,
										 offsets[2] + z,
										 offsets[3] + w, true);
							/*Not Active*/
						}else{
							/*Check if voxel should be alive*/
							if(adjCount == 3)
								FourDimBitWrite(playingVolume[!(i & 1)],
										 offsets[0] + x,
										 offsets[1] + y,
										 offsets[2] + z,
										 offsets[3] + w, true);
							else
								FourDimBitWrite(playingVolume[!(i & 1)],
										 offsets[0] + x,
										 offsets[1] + y,
										 offsets[2] + z,
										 offsets[3] + w, false);
						}
					}
				
		/*Print Out Volume*/
		printf("\n----------Iteration: %d----------\n", i);
		for(int w = 0; w < bounds[3]; w++){
			for(int z = 0; z < bounds[2]; z++){
				printf("\nZ: %d W: %d\n", offsets[2] + z, offsets[3] + w);
				for(int y = 0; y < bounds[1]; y++){
					for(int x = 0; x < bounds[0]; x++){
						printf("%d",
						FourDimBitRead(playingVolume[!(i & 1)], 
									offsets[0] + x,
									offsets[1] + y,
									offsets[2] + z,
									offsets[3] + w));
					}
					putchar('\n');
				}
			}
		}
		bounds[0] += 2;
		bounds[1] += 2;
		bounds[2] += 2;
		bounds[3] += 2;
		offsets[0]--;
		offsets[1]--;
		offsets[2]--;
		offsets[3]--;
	}
	/*Count Active*/
	int activeCount = 0;
	for(int w = 0; w < bounds[3]; w++)
		for(int z = 0; z < bounds[2]; z++)
			for(int y = 0; y < bounds[1]; y++)
				for(int x = 0; x < bounds[0]; x++){
						if(FourDimBitRead(playingVolume[0], 
									offsets[0] + x,
									offsets[1] + y,
									offsets[2] + z,
									offsets[3] + w)){
							activeCount++;
						}
				}
	printf("Active Elements: %d\n", activeCount);
	free(playingVolume[0]);
	free(playingVolume[1]);
	free(input);
}
