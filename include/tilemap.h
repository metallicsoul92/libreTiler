#ifndef TILEMAP_H_
#define TILEMAP_H_

//Model
// determines the type of data the tilemap is, can be either
// a tileset to copy tiles from or a tilemap to copy tiles to
enum displayType{
  TYPE_TILE_MAP = 0,
  TYPE_TILE_SET = 1
};

//foward declare
struct _tilemap;
typedef struct _tilemap tilemap_t;

struct _tile{
  uint8_t offsetX;
  uint8_t offsetY;
  tilemap * parentMap;
  void **data;
};

typedef struct _tile tile_t;

struct _tilemap{
  uint8_t tileSizeX;
  uint8_t tileSizeY;
  uint16_t mapSizeX;
  uint16_t mapSizeY;
  enum displayType type;

  char * mapName;
  //this will equate to tile_t tiles[tileSizeY][tileSizeX]
  tile_t **tiles;
};

//View




//Controller




#endif
