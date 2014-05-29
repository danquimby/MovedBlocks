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

CapturePosition::CapturePosition(const DQ::PointF&, const GameBlock* ) {

}

void CapturePositionsetNewPositionView(const DQ::PointF& ) {

}

DQ::PointF CapturePosition::update() {

    return DQ::PointF();
}

void CapturePosition::cleanCapture() {

}

void CapturePosition::setCapture(const GameBlock* ) {

}
