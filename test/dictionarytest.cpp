#include <string.h>
#include <iostream>
#include <map>
#include <utility>

using namespace std;

enum ETemple
{
  TEMPLE_LIGHT,
  TEMPLE_FIRE,
  TEMPLE_WATER,
  TEMPLE_WIND,
  TEMPLE_EARTH,
  NTEMPLES
};

enum ETown
{
  TOWN_01 = NTEMPLES,
  TOWN_02,
  TOWN_03,
  TOWN_04,
  TOWN_05,
  TOWN_06,
  TOWN_07,
  TOWN_08,
  TOWN_09,
  TOWN_10,
  TOWN_11,
  TOWN_12,
  NTMP,
  NTOWNS = NTMP - NTEMPLES
};

enum ECaves
{
  CAVE_01 = NTEMPLES + NTOWNS,
  CAVE_02,
  CAVE_03,
  CAVE_04,
  CAVE_05,
  CAVE_06,
  CAVE_07,
  NWORLD,
  NCAVES = NWORLD - NTOWNS
};

// The class that holds information about locations
struct Location
{
  int x, y;     // Location Position
  string name;
  int sym;      // Location Symbol

  Location(): x(0), y(0), name("Home"), sym('@'){}
  Location(int x0, int y0, string name0, int sym0): x(x0), y(y0), name(name0), sym(sym0){}
};

int main()
{
  map<int, Location> n;

  n.insert(make_pair(TEMPLE_LIGHT, Location(36, 64, "Light Temple", 'A')));
  n.insert(make_pair(TEMPLE_FIRE, Location(37, 63, "Fire Temple", 'B')));
  n.insert(make_pair(TEMPLE_WIND, Location(38, 62, "Wind Temple", 'C')));
  n.insert(make_pair(TEMPLE_WATER, Location(39, 61, "Water Temple", 'D')));
  n.insert(make_pair(TEMPLE_EARTH, Location(40, 60, "Earth Temple", 'E')));
  n.insert(make_pair(TOWN_01, Location(41, 59, "Rivendell", 'F')));

  cout << "Elements in n: " << endl;
  for (int i = TEMPLE_LIGHT; i <= TOWN_01; i++)
  {
    cout << "[" << n[i].x << ", " << n[i].y << ", " << n[i].name << ", " << n[i].sym << "]" << endl;
  }
}
