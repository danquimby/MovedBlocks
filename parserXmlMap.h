#ifndef PARSER_XML_H
#define PARSER_XML_H

#include "helpers.h"
#include "tinyxml.h"

#include <map>

typedef std::vector<int> bitRow;
typedef std::map<int, bitRow > bitMap;

struct BitMap {
    void clean() {
        m_vContainsMap.clear();
        m_szTiledMap = DQ::SizeI();
        m_szTiledItem = DQ::SizeI();
        m_sTileFilename.clear();
    }

    DQ::SizeI   m_szTiledMap;
    DQ::SizeI   m_szTiledItem;

    // first column array, second row array.
    bitMap      m_vContainsMap;

    // File name to png tiled image.
    std::string m_sTileFilename;
};
/*
* Parsing from special file (*.tmx) and creating an array of iD objects.
*
*/
class parserXmlMap
{
public:
    // @param _filename Path to file (*.tmx) http://www.mapeditor.org/
    parserXmlMap(const std::string& /*_filename*/);
    ~parserXmlMap();

    /*
    * @param _filename Path to file (*.tmx) http://www.mapeditor.org/
    * @return If don't parse map <code>false<code> otherwise <code>true<code>.
    */
    bool parseNewMap(const std::string& );
    bitMap getContains() const;
    bitRow getRow(int _row);

private:
    // Bit full parser map from special file.
    BitMap      bitMap;
};

#endif// PARSER_XML