#include"ShareData.h"

ShareData::ShareData(void* m_local, int m_type, unsigned int m_size)
{
	type = m_type;
	size = m_size;
	share = new BYTE[size];
	memcpy(share, m_local, m_size);
}

ShareData::ShareData(int m_type)
{
	type = m_type;
	share = nullptr;
}

ShareData::~ShareData()
{
	if (share!=nullptr)
	{
		delete [] share;
		share = nullptr;
	}
}
