#ifndef _SPOT_POLYGON_H_
#define _SPOT_POLYGON_H_

#include "scene3d.h"

class CSpotPolygon :public CScene3D
{
public:
	enum FLASHING
	{
		FLASHING_NONE = 0,
		FLASHING_ADD,
		FLASHING_SUB,
		FLASHING_MAX,
	};

	CSpotPolygon(PRIORITY Priority = PRIORITY_FADE);
	~CSpotPolygon();

	static CSpotPolygon *Create(D3DXVECTOR3 pos, int nNumber);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetFlashing(void);
	void EndFlashing(void);
	
	void SetIsDraw(const bool bIsDraw) { m_bIsDraw = bIsDraw; }
	void SetNumber(int nNumber) { m_nNumber = nNumber; }

private:
	void Flasing(void);

	FLASHING m_eFlashing;
	bool m_bIsDraw;
	int m_nNumber;
};
#endif // !_SPOT_POLYGON_H_
