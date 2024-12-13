#pragma once
#include "Block.h"

class VerticalPipe : public Block{
private:
	bool m_connectToUnderground;
	bool m_connectToGround;
	static int m_id;
public:
	VerticalPipe();
	bool connectToUnderground() override;
	bool connectToGround() override;
};