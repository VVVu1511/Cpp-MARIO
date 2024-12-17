#include "VerticalPipe.h"

int VerticalPipe::m_id = 0;

VerticalPipe::VerticalPipe(){
	m_id++;

	this->m_connectToUnderground = false;
	this->m_connectToGround = false;

	if (m_id == 2) {
		this->m_connectToUnderground = true;
	}

	else if (m_id == 12) {
		this->m_connectToGround = true;
	}


}

bool VerticalPipe::connectToUnderground(){
	return this->m_connectToUnderground;
}

bool VerticalPipe::connectToGround(){
	return this->m_connectToGround;
}
