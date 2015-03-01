#pragma once

#include "tmxmi_VS\stdafx.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"
#include "sssf\game\Game.h"
#include "sssf\gsm\state\GameStateManager.h"
#include "xmlfi\XMLFileImporter.h"

// XML TEXT
static const string		MAP_ELEMENT				= "map";
static const string		ORIENTATION_ATT			= "orientation";
static const string		ORTHOGONAL_VAL			= "orthogonal";
static const string		ISOMETRIC_VAL			= "isometric";
static const string		WIDTH_ATT				= "width";
static const string		HEIGHT_ATT				= "height";
static const string		TILEWIDTH_ATT			= "tilewidth";
static const string		TILEHEIGHT_ATT			= "tileheight";
static const string		SPACING_ATT				= "spacing";
static const string		MARGIN_ATT				= "margin";
static const string		IMAGEWIDTH_ATT			= "imagewidth";
static const string		IMAGEHEIGHT_ATT			= "imageheight";
static const string		TILESET_ELEMENT			= "tileset";
static const string		FIRSTGID_ATT			= "firstgid";
static const string		NAME_ATT				= "name";
static const string		IMAGE_ELEMENT			= "image";
static const string		SOURCE_ATT				= "source";
static const string		COLOR_KEY_ATT			= "trans";
static const string		IMAGELAYER_ELEMENT		= "imagelayer";
static const string		LAYER_ELEMENT			= "layer";
static const string		OBJECT_GROUP_ELEMENT	= "objectgroup";
static const string		OBJECT_ELEMENT			= "object";
static const string		GID_ATT					= "gid";
static const string		X_ATT					= "x";
static const string		Y_ATT					= "y";
static const string		DATA_ELEMENT			= "data";
static const string		PROPERTIES_ELEMENT		= "properties";
static const string		PROPERTY_ELEMENT		= "property";
static const string		COLLIDABLE_ATT			= "collidable";
static const string		VALUE_ATT				= "value";
static const string		TILE_ELEMENT			= "tile";

enum MapType {ORTHOGONAL_MAP, ISOMETRIC_MAP};
enum LayerType {TILED, IMAGE, SPARSE};

struct TileSetInfo
{
	int firstgid;
	string name;
	int tilewidth;
	int tileheight;
	string sourceImage;
	int sourceImageWidth;
	int sourceImageHeight;
	string transparencyColor;
	int spacing;
	int margin;
};

struct LayerInfo
{
	string name;
	bool collidable;
	LayerType type;
};

struct TiledLayerInfo : LayerInfo
{
	int width;
	int height;
	vector<int> gids;
	TileSetInfo *tileSetInfo;
};

struct SparseLayerInfo : LayerInfo
{
	list<int> gidS;
	list<int> xS;
	list<int> yS;
	TileSetInfo *tileSetInfo;
};

struct ImageLayerInfo : LayerInfo
{
	int imagewidth;
	int imageheight;
	string imageSource;
};

class TMXMapImporter : public XMLFileImporter
{
protected:
	MapType mapType;
	int width;
	int height;
	int tileWidth;
	int tileHeight;
	list<TileSetInfo> tileSetInfos;
	list<LayerInfo*> layerInfos;
//	map<string, TiledLayerInfo> tiledLayerInfos;
//	map<string, ImageLayerInfo> imageLayerInfos;
//	map<string, SparseLayerInfo> sparseLayerInfos;
	wstring dir;
	wstring mapLevelFilePath;
	int largestLayerWidth;
	int largestLayerHeight;

public:
	TMXMapImporter() {}
	~TMXMapImporter(){}
	bool loadWorld(Game *game, wstring initDir, wstring mapLevelFileName);

	// THESE ARE ALL THE HELPER METHODS
private:
	bool buildWorldFromInfo(Game *game);
	void buildTiledLayer(Game *game, TiledLayerInfo *tli, int idOffset);
	void buildImageLayer(Game *game, ImageLayerInfo *ili, int idOffset);
	void buildSparseLayer(Game *game, SparseLayerInfo *sli, int idOffset);
	void calculateWorldDimensions();
	bool loadMapInfo();
	void loadTileSetInfo(const TiXmlNode *node);
	void loadTiledLayerInfo(const TiXmlNode *node);
	void loadImageLayerInfo(const TiXmlNode *node);
	void loadSparseLayerInfo(const TiXmlNode *node);
	bool loadOrthographicMap(const TiXmlElement *pElem);
	bool loadIsometricMap(const TiXmlElement *pElem);
	TileSetInfo* getTileSetForId(int id);
};