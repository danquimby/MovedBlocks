#ifndef OBJECTS_H
#define OBJECTS_H

#include "helpers.h"

// Full tiled image.
// If m_nTiledTexture equal 0 than create texture from file.
static HTEXTURE    g_nTiledTexture;

struct IDrawaibleObjects {

    //@param offset This grid point.
    virtual void Render(const DQ::PointF& /*offset*/) = 0;
    virtual void Process() = 0;
};

enum GameBlockType {
    GAME_BLOCK_GRASS,
    GAME_BLOCK_ROCK,
    GAME_BLOCK_ROCK1,
    GAME_BLOCK_ROCK_SAND,
    GAME_BLOCK_PLANT,
    GAME_BLOCK_STONE,
    GAME_BLOCK_FLOWERBED,
    GAME_BLOCK_BRIDGE,
    GAME_BLOCK_ICE_ROCK,
    GAME_BLOCK_GOLD_LEAVES,
    GAME_BLOCK_GREEN_LEAVES,
    GAME_BLOCK_GROUND,
    GAME_BLOCK_TREE,
    GAME_BLOCK_TREE1,
    GAME_BLOCK_MAX
};

/*
* Class game block.
*
*/
class GameBlock : public IDrawaibleObjects {
public:
    /*
    * @param _type idNumber for make object.
    * @param _ptGrid Position on grid global map.
    */
    GameBlock(const GameBlockType _type, const DQ::PointI& _ptGrid = DQ::PointI());
    ~GameBlock();

    // Set new position object to game grid map.
    void setPositionObject(const DQ::PointI& _newGrid);

    // Move to new direction and change object position to game grid map.
    void moveObject(const DQ::PointI& _vecDirection);

    // Modification another GameBlockType.
    void modification(const GameBlockType );

    // @override method for render to scene.
    void Render(const DQ::PointF& _ptOffset = DQ::PointF());

    // @override method for processing object.
    void Process();

    DQ::RectF area() const;
private:
    void _init(const GameBlockType );

    hgeSprite*  m_pBlockImage;
    HGE*        m_pHGE;

    // Position object to grid.
    DQ::PointI  m_ptPostionOnGrid;


};

/*
* Factory class blocks.
* @param GameBlockType Number id game block.
*/
GameBlock* createBlock(const GameBlockType );

#endif // OBJECTS_H