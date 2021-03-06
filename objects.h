#ifndef OBJECTS_H
#define OBJECTS_H

#include <math.h>
#include "helpers.h"


// Full tiled image.
// If m_nTiledTexture equal 0 than create texture from file.
static HTEXTURE    g_nTiledTexture;

struct IDrawaibleObjects {

    //@param offset This grid point.
    virtual void Render(const DQ::PointF& /*offset*/) = 0;
    virtual void Process() = 0;
};

class BaseObject {
public:
    BaseObject(BaseObject* parent = 0) {
        if (parent)
            parent->addChild(this);
    }
    virtual ~BaseObject() {
        for (int i = 0; i < (int)m_vParents.size();++i)
        {
            if (m_vParents[i])
                delete m_vParents[i];
        }
    }
    std::vector<BaseObject*> getChild() const {
        return m_vParents;
    }
    void addChild(BaseObject* _parent) {
        m_vParents.push_back(_parent);
    }
private:
    std::vector<BaseObject*>    m_vParents;
};

enum GameBlockType {
    GAME_BLOCK_NONE,
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
    GAME_BLOCK_MAX = GAME_BLOCK_TREE1
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

    DQ::PointI positionGrid() const;


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
* @param _ptPosition Position game block to scene(in grid pointer).
* @return If don't create object <code>null<code> otherwise current new pointer.
*/
GameBlock* createBlock(const GameBlockType ,const DQ::PointI& /*_ptPosition*/);

// Animation position from position view to position target.
class AnimationMovePosition {
public:
    AnimationMovePosition();
    // @param Point from moved.
    // @param Point target.
    AnimationMovePosition(const DQ::PointF&, const DQ::PointF& );

    // @param Point from moved.
    // @param Point target.
    void setNewPositionsForMoved(const DQ::PointF&, const DQ::PointF& );

    // Update move.
    // @return Vector for animation position in scene.
    DQ::PointF updatePositions();

protected:
    // Speed animation position.
    int         m_nSpeed;

private:
    // Position view scene.
    DQ::PointF  m_ptVectorFromPoint;

    // Position view scene.
    DQ::PointF  m_ptVectorTarget;

};

// Calculation from grid to pixels.
DQ::PointF calculationFromGrid(const DQ::PointI& );
DQ::PointF calculationFromGrid(const DQ::PointF& );
#endif // OBJECTS_H