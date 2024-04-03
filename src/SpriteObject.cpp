#include "header.h"
#include "SpriteObject.h"

void SpriteObject::virtDraw(){
	if (isVisible()) {
		// Calculate the source position based on the current frame indices
		int iXSource = m_iCurrentFrameX * m_iDrawWidth;
		int iYSource = m_iCurrentFrameY * m_iDrawHeight;

		// Draw the current frame with transparency
		image.renderImageWithAlpha(getEngine()->getForegroundSurface(),
			iXSource, iYSource,
			m_iCurrentScreenX + m_iStartDrawPosX,
			m_iCurrentScreenY + m_iStartDrawPosY,
			m_iDrawWidth, m_iDrawHeight);
	}
}


void AgentBaseObject::virtDraw(){
	if (isVisible()) {
		// Calculate the source position based on the current direction and frame index
		int iXSource = m_iCurrentFrameX * m_iDrawWidth;
		// Assuming each direction is in a different row
		int iYSource = m_direction * m_iDrawHeight;

		// If any part of bottom is covered by the wall
		int bottomY = getDrawingRegionBottom();
		if (!m_pTileManager->isPassableByObjectCentre(getXCentre(), bottomY, widthOffset)) {
			// Draw the image covered by the wall
			image.renderImageWithAlphaAndOverlay(getEngine()->getForegroundSurface(),
				iXSource, iYSource,
				m_iCurrentScreenX + m_iStartDrawPosX,
				m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight, 0xEBDCC7);
		}
		else {
			// Draw the current frame with transparency
			image.renderImageWithAlpha(getEngine()->getForegroundSurface(),
				iXSource, iYSource,
				m_iCurrentScreenX + m_iStartDrawPosX,
				m_iCurrentScreenY + m_iStartDrawPosY,
				m_iDrawWidth, m_iDrawHeight);
		}

	}
}

void AgentBaseObject::fixPosition() {
	DisplayableObject::fixPosition();

	if (!m_pTileManager->isPassableByObjectCentre(getXCentre(), getYCentre(), widthOffset)) {

		// If next step is not passable, roll back to last position
		m_iCurrentScreenX = m_iPrevScreenX;
		m_iCurrentScreenY = m_iPrevScreenY;
	}
	else {
		// save the postion for rolling back
		m_iPrevScreenX = m_iCurrentScreenX;
		m_iPrevScreenY = m_iCurrentScreenY;
	}
}