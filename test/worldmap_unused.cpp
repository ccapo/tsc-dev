// Adds nHill randomly to the height map
void WorldMap::addHill(TCODHeightMap *hmap, int nHill, float baseRadius, float radiusVar, float h)
{
  for(int i = 0; i < nHill; i++)
  {
    float hillMinRadius = baseRadius*(1.0f - radiusVar);
    float hillMaxRadius = baseRadius*(1.0f + radiusVar);
    float radius = game.rng->getFloat(hillMinRadius, hillMaxRadius);
    float theta = game.rng->getFloat(0.0f, 2.0f*M_PI);  // Between (0.0, 2.0*pi)
    float dist = game.rng->getFloat(0.0f, static_cast<float>(MIN(IMAGE_WIDTH2, IMAGE_HEIGHT2)/2 - radius));
    int xh = static_cast<int>(IMAGE_WIDTH2/2 + cos(theta)*dist);
    int yh = static_cast<int>(IMAGE_HEIGHT2/2 + sin(theta)*dist);
    hmap->addHill(static_cast<float>(xh), static_cast<float>(yh), radius, h);
  }
}

// Builds the world heightmap
void WorldMap::generateHM(TCODHeightMap *hmap)
{
  hmap->clear();
  addHill(hmap, 600, 16.0*IMAGE_WIDTH2/400, 0.7f, 0.3f);
  hmap->normalize();
  //        mulx      muly      addx  addy  octaves  delta  scale
  hmap->addFbm(game.terrain,  2.20*IMAGE_WIDTH2/800,  2.20*IMAGE_HEIGHT2/800,  -20.0f,  15.0f,  32.0f,  0.0f,  2.0f);
  hmap->normalize(-hMax, hMax);

  hmap->add(-0.1f);
  hmap->clamp(-hMax, hMax);
  hmap->normalize(-hMax, hMax);
}

// Number of colours in colour map
#define NCOLOURMAP 5

// Method for constructing the world map
void WorldMap::generateMap()
{
  TCODHeightMap *hmap = new TCODHeightMap(IMAGE_WIDTH2, IMAGE_HEIGHT2);

  // Heightmap Thresholds
	float hWater = 0.0f;
	float hSand = 0.1f;
	float hGrass = 0.5f;
	float hMax = 1.0f;

  // Colour map
  TCODColor colourMap[NCOLOURMAP];
  int i = 0;
  colourMap[i++] = TCODColor(47,47,64);    // 0, deep water
  colourMap[i++] = TCODColor(111,127,159); // 1, water-sand transition
  colourMap[i++] = TCODColor(191,191,159); // 2, sand
  colourMap[i++] = TCODColor(63,127,31);   // 3, sand-grass transition
  colourMap[i++] = TCODColor(31,63,31);    // 4, grass

  generateHM(hmap);

  for(int x = 0; x < IMAGE_WIDTH2; x++)
  {
    for(int y = 0; y < IMAGE_HEIGHT2; y++)
    {
      int offset = x + IMAGE_WIDTH2*y;
      float h = hmap->getValue(x, y);

      if(h >= hGrass)
      {
        float coef = (h - hGrass)/(hMax - hGrass);
        subcells[offset].baseColour = TCODColor::lerp(colourMap[3], colourMap[4], coef);
        fov2x->setProperties(x, y, true, true);
      }
      else if(h >= hSand)
      {
        float coef = (h - hSand)/(hGrass - hSand);
        subcells[offset].baseColour = TCODColor::lerp(colourMap[2], colourMap[3], coef);
        fov2x->setProperties(x, y, true, true);
      }
      else if(h >= hWater)
      {
        float coef = (h - hWater)/(hSand - hWater);
        subcells[offset].baseColour = TCODColor::lerp(colourMap[1], colourMap[2], coef);
        fov2x->setProperties(x, y, true, false);
      }
      else
      {
        float coef = ABS(h);
        subcells[offset].baseColour = TCODColor::lerp(colourMap[1], colourMap[0], coef);
        subcells[offset].isWater = true;
        fov2x->setProperties(x, y, true, false);
      }
      img->putPixel(x, y, subcells[offset].baseColour);
      //img_thumb->putPixel(x, y, subcells[offset].baseColour);
    }
  }

  // Set walk and transparent information in the normal resolution map
  for(int x = 0; x < IMAGE_WIDTH; x++)
  {
    for(int y = 0; y < IMAGE_HEIGHT; y++)
    {
      bool trans = true, walk = true;
      if(!isFov2xTransparent(2*x    , 2*y    )) trans = false;
      if(!isFov2xTransparent(2*x + 1, 2*y    )) trans = false;
      if(!isFov2xTransparent(2*x    , 2*y + 1)) trans = false;
      if(!isFov2xTransparent(2*x + 1, 2*y + 1)) trans = false;
      if(!isFov2xWalkable(2*x    , 2*y    )) walk = false;
      if(!isFov2xWalkable(2*x + 1, 2*y    )) walk = false;
      if(!isFov2xWalkable(2*x    , 2*y + 1)) walk = false;
      if(!isFov2xWalkable(2*x + 1, 2*y + 1)) walk = false;
      fov1x->setProperties(x, y, trans, walk);
    }
  }

  // Assign the location of all the places on the world map
  nlocations = NWORLD;
  addWorldMapLocations();

  delete hmap;
  hmap = NULL;
  //img->save("data/img/worldmap0.png");
  //img_thumb->save("data/img/worldmap_thumb0.png");
}

void CaveMap::saveMap()
{
  char fname[CHARMAX];
  sprintf(fname, "cavemap_%02d.png", game.caveID + 1);

  // Save the map as a PNG
  TCODImage tmp(MAP_WIDTH2, MAP_HEIGHT2);

  for(int x = 0; x < MAP_WIDTH2; x++)
  {
    for(int y = 0; y < MAP_HEIGHT2; y++)
    {
      tmp.putPixel(x, y, fov2x->isTransparent(x,y) ? TCODColor::lightGrey : TCODColor::darkGrey);
    }
  }

  tmp.putPixel(2*game.player.x    , 2*game.player.y - 1, TCODColor::blue);
  tmp.putPixel(2*game.player.x - 1, 2*game.player.y    , TCODColor::blue);
  tmp.putPixel(2*game.player.x    , 2*game.player.y    , TCODColor::blue);
  tmp.putPixel(2*game.player.x + 1, 2*game.player.y    , TCODColor::blue);
  tmp.putPixel(2*game.player.x    , 2*game.player.y + 1, TCODColor::blue);

  tmp.putPixel(2*upx    , 2*upy - 1, TCODColor::green);
  tmp.putPixel(2*upx - 1, 2*upy    , TCODColor::green);
  tmp.putPixel(2*upx    , 2*upy    , TCODColor::green);
  tmp.putPixel(2*upx + 1, 2*upy    , TCODColor::green);
  tmp.putPixel(2*upx    , 2*upy + 1, TCODColor::green);

  tmp.putPixel(2*downx    , 2*downy - 1, TCODColor::red);
  tmp.putPixel(2*downx - 1, 2*downy    , TCODColor::red);
  tmp.putPixel(2*downx    , 2*downy    , TCODColor::red);
  tmp.putPixel(2*downx + 1, 2*downy    , TCODColor::red);
  tmp.putPixel(2*downx    , 2*downy + 1, TCODColor::red);

  tmp.save(fname);
}
