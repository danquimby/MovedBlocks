#ifndef OBJECTS_H
#define OBJECTS_H

#include "helpers.h"

// Full tiled image.
// If m_nTiledTexture equal 0 than create texture from file.
static HTEXTURE    m_nTiledTexture;

struct IDrawaibleObjects {
    virtual void Render() = 0;
    virtual void Process() = 0;
};

enum GameBlockType {
    GAME_BLOCK_GRASS,
    GAME_BLOCK_ROCK,
    GAME_BLOCK_ROCK1,
    GAME_BLOCK_ROCK_SAND,
    GAME_BLOCK_PLANT,
    GAME_BLOCK_STONE,
    GAME_BLOCK_BRIDGE,
    GAME_BLOCK_ICE_ROCK,
    GAME_BLOCK_GOLD_LEAVES,
    GAME_BLOCK_GREEN_LEAVES,
    GAME_BLOCK_GROUND,
    GAME_BLOCK_TREE,
    GAME_BLOCK_TREE1
};

/*
* Class game block.
*
*/
class GameBlock : public IDrawaibleObjects {
public:

    GameBlock(GameBlockType );
    ~GameBlock();

    // Modification another GameBlockType.
    void modification(GameBlockType );
    // @override method for render to scene.
    void Render();

    // @override method for processing object.
    void Process();

    DQ::RectF area() const;
    void setArea(const DQ::RectF& );
private:
    hgeSprite*  m_pBlockImage;
    HGE*        m_pHGE;

    // Default width and height equal 64.
    // Rectangle position object to global game map.
    DQ::RectF   m_rtAreaBlock;

    // Rectangle area for show object from tiled image.
    DQ::RectF   m_rtViewAreaBlock;

};

/*
* Factory class blocks.
* @param GameBlockType Number id game block.
*/
GameBlock* createBlock(const GameBlockType );

#endif // OBJECTS_H