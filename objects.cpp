#include "objects.h"

GameBlock::GameBlock() {
    m_pHGE = DQ::cloneHGE();

// If global texture don't load, then load image.
    if (!m_nTiledTexture)
#ifdef _DEBUG
        m_pHGE->Texture_Load("../data/tiled.png");
#else
        m_pHGE->Texture_Load("data/tiled.png");
#endif

}

GameBlock::~GameBlock() {

}

void GameBlock::Render() {

}

void GameBlock::Process() {

}

DQ::RectF GameBlock::area() const {
    return m_rtAreaBlock;
}
void GameBlock::setArea(const DQ::RectF& _area) {
    m_rtAreaBlock = _area;
}
