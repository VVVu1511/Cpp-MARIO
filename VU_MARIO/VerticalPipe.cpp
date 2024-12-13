#include "VerticalPipe.h"

int VerticalPipe::m_id = 0;

VerticalPipe::VerticalPipe(){
	m_id++;

	if (m_id == 1) {
		this->m_connectToUnderground = true;
		this->m_connectToGround = false;
	}

	else if (m_id == 12) {
		this->m_connectToGround = true;
		this->m_connectToUnderground = false;
	}

	else {
		this->m_connectToUnderground = false;
		this->m_connectToGround = false;
	}


}

bool VerticalPipe::connectToUnderground(){
	return this->m_connectToUnderground;
}

bool VerticalPipe::connectToGround(){
	return this->m_connectToGround;
}
