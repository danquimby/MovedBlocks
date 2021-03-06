#include "parserXmlMap.h"


parserXmlMap::parserXmlMap(const std::string& _filename) {
    parseNewMap(_filename);
}

parserXmlMap::~parserXmlMap() {
}

bitMap parserXmlMap::getContains() const {
    return bitMap.m_vContainsMap;
}

bitRow parserXmlMap::getRow(int _column) {
    bitMap::iterator it = bitMap.m_vContainsMap.find(_column);
    if (it == bitMap.m_vContainsMap.end()) 
        return bitRow();
    return it->second;
}

bitObjectItems parserXmlMap::getComplexObjects() const {
    return bitMap.m_vContinObjects;
}

bool parserXmlMap::parseNewMap(const std::string& _filename) {
    int firstTileID;
    bitMap.clean();
    TiXmlDocument levelFile(_filename.c_str());

    // Load xml map.
    if(!levelFile.LoadFile())
    {
//        std::cout << "Loading level \"" << _filename << "\" failed." << std::endl;
        return false;
    }

    TiXmlElement *map;
    map = levelFile.FirstChildElement("map");

    // Example map: <map version="1.0" orientation="orthogonal" width="10" height="10" tilewidth="34" tileheight="34">
    bitMap.m_szTiledMap = DQ::SizeI(atoi(map->Attribute("width")), atoi(map->Attribute("height")));
    bitMap.m_szTiledItem = DQ::SizeI(atoi(map->Attribute("tilewidth")), atoi(map->Attribute("tileheight")));

    
    TiXmlElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    // Source - path to tiled image.
    TiXmlElement *image;
    image = tilesetElement->FirstChildElement("image");
    bitMap.m_sTileFilename = image->Attribute("source");

    TiXmlElement *gameObjects;
    TiXmlElement *gameObjectsProperty;
    gameObjects  = map->FirstChildElement("objectgroup")->FirstChildElement("object");
    while(gameObjects)
    {
        BitObjectItem   bitItem;
        bitItem.m_pPosition = DQ::PointI(atoi(gameObjects->Attribute("x")) / SPRITE_WIDTH, atoi(gameObjects->Attribute("y")) / SPRITE_HEIGHT);
        bitItem.m_szSizeObject = DQ::SizeI(atoi(gameObjects->Attribute("width")) / SPRITE_WIDTH, atoi(gameObjects->Attribute("height")) / SPRITE_HEIGHT);
        gameObjectsProperty = gameObjects->FirstChildElement("properties")->FirstChildElement("property");
        while(gameObjectsProperty)
        {
            bitItem.m_sData = gameObjectsProperty->Attribute("value");
            gameObjectsProperty = gameObjectsProperty->NextSiblingElement("property");

        }
        bitMap.m_vContinObjects.push_back(bitItem);
        gameObjects = gameObjects->NextSiblingElement("object");
    }
    // Work with layers.
    TiXmlElement *layerElement;
    layerElement = map->FirstChildElement("layer");

    while(layerElement)
    {

        // Contains <data>
        TiXmlElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if(!layerDataElement)
        {
            DBOUT("Bad map. No layer information found.");
        }

        // Contains <tile> - description of each layer of tiles.
        TiXmlElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if(!tileElement)
        {
            DBOUT("Bad map. No tile information found.");
            return false;
        }

        int row = 0;
        int column = 0;
        bitRow vRow;
        while(tileElement)
        {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;
            vRow.push_back(tileGID);

            tileElement = tileElement->NextSiblingElement("tile");
            if (++row >= bitMap.m_szTiledMap.width())
            {
                row = 0;
                bitMap.m_vContainsMap[column++] = vRow;
                vRow.clear();
            }
        }
        layerElement = layerElement->NextSiblingElement("layer");
    }
    return true;
}