#include "objects.h"

GameBlock::GameBlock(const GameBlockType _type, const DQ::PointI& _ptGrid) {
    m_ptPostionOnGrid = _ptGrid;

    m_pHGE = DQ::cloneHGE();
// If global texture don't load, then load image.
    if (!g_nTiledTexture)
#ifdef _DEBUG
        g_nTiledTexture = m_pHGE->Texture_Load("../data/tiled.png");
#else
        g_nTiledTexture = m_pHGE->Texture_Load("data/tiled.png");
#endif
    _init(_type);

}

GameBlock::~GameBlock() {
    if (!m_pBlockImage)
        delete m_pBlockImage;
}

void GameBlock::setPositionObject(const DQ::PointI& _newGrid) {
    m_ptPostionOnGrid = _newGrid;
}

void GameBlock::moveObject(const DQ::PointI& _vecDirection) {

}

void GameBlock::Render(const DQ::PointF& _ptOffset) {
    m_pBlockImage->Render(
        (float) (m_ptPostionOnGrid.X() * SPRITE_WIDTH + _ptOffset.X()),
        (float) (m_ptPostionOnGrid.Y() * SPRITE_HEIGHT + _ptOffset.Y())
        );
}

void GameBlock::Process() {

}

DQ::PointI GameBlock::positionGrid() const {
    return m_ptPostionOnGrid;
}

DQ::PointF GameBlock::positionView() const {
    return DQ::PointF((float) m_ptPostionOnGrid.X() * SPRITE_WIDTH, (float) m_ptPostionOnGrid.Y() * SPRITE_HEIGHT);
}

void GameBlock::_init(const GameBlockType _type) {
    if (_type > GAME_BLOCK_MAX) return;
    m_pBlockImage = new hgeSprite(g_nTiledTexture,(float) (_type % 10) * SPRITE_WIDTH,(float) (_type / 10) * SPRITE_HEIGHT,SPRITE_WIDTH,SPRITE_HEIGHT);
}

/*
* Create complex block.
*
*/
GameBlock* createBlock(const GameBlockType _type, const DQ::PointI& _ptPosition) {
    GameBlock* block;
    if (_type == GAME_BLOCK_NONE || _type > GAME_BLOCK_MAX) return 0;
    int type = (int)_type;
    block = new GameBlock((GameBlockType)--type);
    block->setPositionObject(_ptPosition);
    return block;
}

AnimationMovePosition::AnimationMovePosition() {
    m_nSpeed = 0;
}
AnimationMovePosition::AnimationMovePosition(const DQ::PointF& _ptFrom, const DQ::PointF& _ptTarget ) {
    setNewPositionsForMoved(_ptFrom, _ptTarget);
}

void AnimationMovePosition::setNewPositionsForMoved(const DQ::PointF& _ptFrom, const DQ::PointF& _ptTarget) {
    m_nSpeed = 1;
    m_ptVectorFromPoint = _ptFrom;
    m_ptVectorTarget = _ptTarget;

    DBOUT(m_ptVectorFromPoint.Y());
    DBOUT(" m_ptVectorFromPoint \n");
    DBOUT(m_ptVectorTarget.Y());
    DBOUT(" m_ptVectorTarget \n");

}

DQ::PointF AnimationMovePosition::updatePositions() {

    if (m_nSpeed == 0.f) return DQ::PointF(0, 0);

    float vectorX = 0.f;
    float vectorY = 0.f;

    // Get a Vector between object A and Target.
    double _nx = m_ptVectorTarget.X() - m_ptVectorFromPoint.X();
    double _ny = m_ptVectorTarget.Y() - m_ptVectorFromPoint.Y();

    // Get Distance.
    double _distance = sqrt((_nx*_nx) + (_ny*_ny));

    // Normalize vector (make it length of 1.0)
    double _vx = _nx / _distance;
    double _vy = _ny / _distance;

    // Move object based on vector and speed
    vectorX += (float)_vx * m_nSpeed;
    vectorY += (float)_vy * m_nSpeed;

    m_ptVectorFromPoint += DQ::PointF(vectorX, vectorY);
    if (_distance < 1.5)
    {
        m_nSpeed = 0;
    }
    return DQ::PointF(vectorX, vectorY).negative();
}

