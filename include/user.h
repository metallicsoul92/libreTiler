#ifndef USER_H_
#define USER_H_

struct _userProject{

//size of the individual tiles
  uint8_t tileSizeX;
  uint8_t tileSizeY;
//amount of tilesets the project uses.
//are we really gonna need more then UCHAR_MAX?
  uint8_t tilesetCount;
  uint8_t pad;
  //we really gonna need more then USHORT_MAX
  uint16_t mapSizeX;
  uint16_t mapSizeY;


  char * name;
  // path/to/project/name.ltp
  char * projectPath;
  //
  char ** tileSetPaths;
}


#endif
