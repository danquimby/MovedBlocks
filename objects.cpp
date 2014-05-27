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
    m_pBlockImage->Render((float) m_ptPostionOnGrid.X() * SPRITE_WIDTH, (float) m_ptPostionOnGrid.Y() * SPRITE_HEIGHT);
}

void GameBlock::Process() {

}

DQ::RectF GameBlock::area() const {
    return DQ::RectF();
}

void GameBlock::_init(const GameBlockType _type) {
    if (_type > GAME_BLOCK_MAX) return;
    m_pBlockImage = new hgeSprite(g_nTiledTexture,(float) (_type % 10) * SPRITE_WIDTH,(float) (_type / 10) * SPRITE_HEIGHT,SPRITE_WIDTH,SPRITE_HEIGHT);
}
