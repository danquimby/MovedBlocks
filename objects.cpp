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

void GameBlock::Render() {
    m_pBlockImage->Render(0,0);
}

void GameBlock::Process() {

}

DQ::RectF GameBlock::area() const {
    return m_rtAreaBlock;
}

void GameBlock::setArea(const DQ::RectF& _area) {
    m_rtAreaBlock = _area;
}

void GameBlock::_init(const GameBlockType _type) {
    if (_type > GAME_BLOCK_MAX) return;

    m_pBlockImage = new hgeSprite(g_nTiledTexture,(float) (_type % 10) * 64,(float) (_type / 10) * 64,64,64);
}
