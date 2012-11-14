#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "libtcod.hpp"

#define NX 80
#define NY 48

#define NTOWNS 2
#define NITEMS 4
#define NREGIONS 4
#define NITEMS_REGION (NITEMS/NREGIONS)

uint32 seed = (uint32)time(NULL);
TCODRandom *rng = TCODRandom::getInstance();

struct Town
{
	int x, y;

	int maxCount[NITEMS];
	int count[NITEMS];

	float minPrice[NITEMS];
	float maxPrice[NITEMS];
	float price[NITEMS];

	float productionRate[NITEMS];
};

void setup_economy(Town towns[NTOWNS], float delta_t)
{
	int maxCountLow[2] = {50, 75};
	float minPriceLow[2] = {1.0f, 10.0f};
	float maxPriceLow[2] = {25.0f, 50.0f};
	float productionRateLow[2] = {3.75f/delta_t, 4.25f/delta_t};

	int maxCountMed[2] = {25, 50};
	float minPriceMed[2] = {5.0f, 15.0f};
	float maxPriceMed[2] = {50.0f, 75.0f};
	float productionRateMed[2] = {3.25f/delta_t, 3.75f/delta_t};

	int maxCountHigh[2] = {5, 15};
	float minPriceHigh[2] = {10.0f, 20.0f};
	float maxPriceHigh[2] = {75.0f, 100.0f};
	float productionRateHigh[2] = {2.75f/delta_t, 3.25f/delta_t};

	int maxCount[NREGIONS][2];
	float minPrice[NREGIONS][2];
	float maxPrice[NREGIONS][2];
	float productionRate[NREGIONS][2];

	int iLow = 0, iHigh = 2;

	for(int i = 0; i < NTOWNS; i++)
	{
		towns[i].x = rng->getInt(0, NX - 1);
		towns[i].y = rng->getInt(0, NY - 1);

		// Region 1
		if(towns[i].x >= NX/2 && towns[i].y >= NY/2)
		{
			iLow = 0;
			iHigh = 2;
		}

		// Region 2
		if(towns[i].x < NX/2 && towns[i].y >= NY/2)
		{
			iLow = 1;
			iHigh = 3;
		}

		// Region 3
		if(towns[i].x < NX/2 && towns[i].y < NY/2)
		{
			iLow = 2;
			iHigh = 0;
		}

		// Region 4
		if(towns[i].x >= NX/2 && towns[i].y < NY/2)
		{
			iLow = 3;
			iHigh = 1;
		}

		for(int l = 0; l < NREGIONS; l++)
		{
			if(l == iLow)
			{
				for(int m = 0; m < 2; m++) maxCount[l][m] = maxCountLow[m];
				for(int m = 0; m < 2; m++) minPrice[l][m] = minPriceLow[m];
				for(int m = 0; m < 2; m++) maxPrice[l][m] = maxPriceLow[m];
				for(int m = 0; m < 2; m++) productionRate[l][m] = productionRateLow[m];
			}
			else if(l == iHigh)
			{
				for(int m = 0; m < 2; m++) maxCount[l][m] = maxCountHigh[m];
				for(int m = 0; m < 2; m++) minPrice[l][m] = minPriceHigh[m];
				for(int m = 0; m < 2; m++) maxPrice[l][m] = maxPriceHigh[m];
				for(int m = 0; m < 2; m++) productionRate[l][m] = productionRateHigh[m];
			}
			else
			{
				for(int m = 0; m < 2; m++) maxCount[l][m] = maxCountMed[m];
				for(int m = 0; m < 2; m++) minPrice[l][m] = minPriceMed[m];
				for(int m = 0; m < 2; m++) maxPrice[l][m] = maxPriceMed[m];
				for(int m = 0; m < 2; m++) productionRate[l][m] = productionRateMed[m];
			}

			for(int k = 0; k < NITEMS_REGION; k++)
			{
				int j = l*NITEMS_REGION + k;

				towns[i].maxCount[j] = rng->getInt(maxCount[l][0], maxCount[l][1]);
				towns[i].count[j] = rng->getInt(1, towns[i].maxCount[j]);

				towns[i].minPrice[j] = rng->getFloat(minPrice[l][0], minPrice[l][1]);
				towns[i].maxPrice[j] = rng->getFloat(maxPrice[l][0], maxPrice[l][1]);
				towns[i].price[j] = rng->getFloat(towns[i].minPrice[j], towns[i].maxPrice[j]);

				towns[i].productionRate[j] = rng->getFloat(productionRate[l][0], productionRate[l][1]);
			}
		}
	}
}

void output_economy(FILE *fout, Town towns[NTOWNS], float t)
{
	fprintf(fout, "%f ", t);
	for(int i = 0; i < NTOWNS; i++)
	{
		for(int j = 0; j < NITEMS; j++)
		{
			fprintf(fout, "%02d %02d ", towns[i].count[j], (int)towns[i].price[j]);
		}
		fprintf(fout, " ");
	}
	fprintf(fout, "\n");
}

void update_economy(Town towns[NTOWNS], float delta_t)
{
	int totalCount[NITEMS];
	int totalMaxCount[NITEMS];

	// Tally the total number of items
	for(int j = 0; j < NITEMS; j++)
	{
		totalCount[j] = 0;
		totalMaxCount[j] = 0;
		for(int i = 0; i < NTOWNS; i++)
		{
			totalCount[j] += towns[i].count[j];
			totalMaxCount[j] += towns[i].maxCount[j];
		}
	}

	// Update item prices
	for(int i = 0; i < NTOWNS; i++)
	{
		for(int j = 0; j < NITEMS; j++)
		{
			float a = 0.5f*(towns[i].maxPrice[j] - towns[i].minPrice[j]);
			float b = 4.0f*(1.0f - 2.0f*(float)totalCount[j]/(float)totalMaxCount[j]);
			towns[i].price[j] = a*(tanh(b) + 1.0f) + towns[i].minPrice[j];
			towns[i].price[j] = CLAMP(towns[i].minPrice[j], towns[i].maxPrice[j], towns[i].price[j]);
		}
	}

	// Update the number of items
	for(int i = 0; i < NTOWNS; i++)
	{
		for(int j = 0; j < NITEMS; j++)
		{
			// Sales for each item, from each town
			int sales = rng->getInt(1, 5);
			if(towns[i].count[j] <= 0) sales = 0;

			// Update item count
			towns[i].count[j] += (int)(towns[i].productionRate[j]*delta_t) - sales;
			towns[i].count[j] = CLAMP(0, towns[i].maxCount[j], towns[i].count[j]);
		}
	}
}

int main(void)
{
	float t = 0.0f, tmax = 400.0f, delta_t = 1.0f/25.0f;
	Town towns[NTOWNS];
	FILE *fout = fopen("economy.dat", "w");

	setup_economy(towns, delta_t);
	output_economy(fout, towns, t);

	while(t < tmax)
	{
		update_economy(towns, delta_t);
		t += delta_t;
		output_economy(fout, towns, t);
	}

	fclose(fout);

	return 1;
}
