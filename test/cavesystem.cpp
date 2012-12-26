#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <time.h>

#define NSIZE 32
#define NMAPS 64
#define NBORDER 8

int main()
{
	static const int dx[NBORDER] = {-1,  0, +1, -1, +1, -1,  0, +1};
	static const int dy[NBORDER] = {-1, -1, -1,  0,  0, +1, +1, +1};
	int g_depthMax = -1;

	// Map Data Structure
	struct MapData
	{
		bool occupied;
		int mapID;
		int depth;
	} mapData[NSIZE][NSIZE];

	// Initialize random number generator
	srand((unsigned)time(NULL));

	// Initialize mapData
	for(int r = 0; r < NSIZE; r++)
	{
		for(int c = 0; c < NSIZE; c++)
		{
			mapData[r][c].occupied = false;
			mapData[r][c].mapID = -1;
			mapData[r][c].depth = 0;
		}
	}

	// Seed Diffusion-Limited-Aggregation Random Cave System
	mapData[NSIZE/2][NSIZE/2].occupied = true;
	mapData[NSIZE/2][NSIZE/2].mapID = 0;
	mapData[NSIZE/2][NSIZE/2].depth = 1;
	//printf("Map: %d, Depth: %d\n", mapData[NSIZE/2][NSIZE/2].mapID, mapData[NSIZE/2][NSIZE/2].depth);

	// Add A New Map, One At A Time
	for(int i = 1; i < NMAPS; i++)
	{
		// Start Map Position At Random
		unsigned int x, y;
		OVER: do
		{
			x = rand() % (NSIZE - 2) + 1;
			y = rand() % (NSIZE - 2) + 1;
		} while( mapData[y][x].occupied );

		// Random Walk Map Position Until Adjacent To Other Existing Maps
		bool vacant = true;
		for(int j = 0; j < NBORDER; j++) vacant = vacant && !mapData[y + dy[j]][x + dx[j]].occupied;
		while( vacant )
		{
			unsigned int k = rand() % NBORDER;
			x += dx[k];
			y += dy[k];
			if(x < 1 || x >= NSIZE - 1 || y < 1 || y >= NSIZE - 1) goto OVER; // Start Over If We Leave The Grid
			vacant = true;
			for(int j = 0; j < NBORDER; j++) vacant = vacant && !mapData[y + dy[j]][x + dx[j]].occupied;
		}

		// Store Information For New Map
		mapData[y][x].occupied = true;
		mapData[y][x].mapID = i;

		// Determine Maximum Depth Of Adjacent Maps
		int depthMax = 0;
		for(int j = 0; j < NBORDER; j++)
		{
			if( mapData[y + dy[j]][x + dx[j]].depth >= depthMax ) depthMax = mapData[y + dy[j]][x + dx[j]].depth;
		}

		// Assign Depth = Max. Depth + 1
		mapData[y][x].depth = ++depthMax;

		// Keep Track Of Global Max. Depth
		if( depthMax >= g_depthMax ) g_depthMax = depthMax; 

		//printf("Map: %d, Depth: %d\n", mapData[y][x].mapID, mapData[y][x].depth);
		//printf("Connected Maps: ");
		//for(int j = 0; j < NBORDER; j++)
		//{
		//	if( mapData[y + dy[j]][x + dx[j]].depth >= depthMax - 1 ) printf("(%d, %d) ", mapData[y + dy[j]][x + dx[j]].mapID, mapData[y + dy[j]][x + dx[j]].depth);
		//}
		//printf("\n");
	}
	//printf("Max Depth: %d\n", g_depthMax);

	// Store Map Information In A PGM Image
	FILE *fout = fopen("image.pgm", "w");
	fprintf(fout, "P2\n%d %d\n%d\n", NSIZE, NSIZE, g_depthMax + 1);
	for(int r = 0; r < NSIZE; r++)
	{
		for(int c = 0; c < NSIZE; c++)
		{
			fprintf(fout, "%d ", mapData[r][c].occupied ? mapData[r][c].depth : g_depthMax + 1);
		}
		fprintf(fout, "\n");
	}
	fclose(fout);

	// Convert PGM Image to PNG Image
	system("convert image.pgm image.png; rm image.pgm");

	return 0;
}
