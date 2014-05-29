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
    DQ::PointF positionView() const;
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
class CapturePosition {
public:
    // @param Position scene.
    // @param Pointer game block for capture.
    CapturePosition(const DQ::PointF&, const GameBlock* );

    // @param Set new position to scene view.
    void setNewPositionView(const DQ::PointF& );
    // Update move.
    // @return Vector for animation position in scene.
    DQ::PointF update();

    // Clear pointer game block and stop capture.
    void cleanCapture();

    // @param Set new pointer game block.
    void setCapture(const GameBlock* );
private:
    // Capture object.
    GameBlock*  m_pCaptureBlock;

    // Position view scene.
    DQ::PointF  m_ptVectorView;

    // Speed animation position.
    int         m_nSpeed;
};

    /*
    // Get a Vector between object A and Target
    double _nx = objT.X - objA.X;
    double _ny = objT.Y - objA.Y;
    // Get Distance
    double _distance = Math.Sqrt((_nx*_nx) + (_ny*_ny));

    // Normalize vector (make it length of 1.0)
    double _vx = _nx / _distance;
    double _vy = _ny / _distance;

    // Move object based on vector and speed
    objA.X += (float)_vx * objA.Speed;
    objA.Y += (float)_vy * objA.Speed;

    if (_distance < 0.5)
    {
    int a = 1;
    }
    */

#endif // OBJECTS_H