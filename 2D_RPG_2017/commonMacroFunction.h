#pragma once
//=============================================================
//	## commonMacroFunction ##
//=============================================================

//POINT
inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

//�� �׸���
inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

//RECT �����
//RECT rc = { 128, 59, 228, 159 };
//RECT rc = RectMake(128, 59, 100, 100)
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}
//RECT �߽���ǥ�� �����
inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
	return rc;
}

//Rectangle �Լ� �̿��ؼ� �簢�� �׸���
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//Ellipse �Լ� �̿��ؼ� Ÿ�� �׸���
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}
//Ellipse �Լ� �̿��ؼ� Ÿ�� �߽���ǥ�� �׸���
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

//������?
inline void Rectangle(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//�����ӷ�Ʈ �Լ� �����ε�(����ִ� ��Ʈ �����)
inline void FrameRect(HDC hdc, RECT rc, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	FrameRect(hdc, &rc, brush);
	DeleteObject(brush);
}

inline void DrawEllipse(HDC hdc, RECT rc)
{
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

//�׸� ��ĥ�ϱ�
inline void FillRect(HDC hdc, int red, int green, int blue, RECT rc)
{
	HBRUSH newBrush;
	newBrush = CreateSolidBrush(RGB(red, green, blue));
	Rectangle(hdc, rc);
	FillRect(hdc, &rc, newBrush);
	DeleteObject(newBrush);
}

//�ֺ� ������ ����
inline void FillEllipse(HDC hdc, int red, int green, int blue, RECT rc)
{
	HPEN newPen, oldPen;
	HBRUSH newBrush, oldBrush;
	newPen = CreatePen(PS_SOLID, 1, RGB(red, green, blue));
	oldPen = (HPEN)SelectObject(hdc, newPen);
	newBrush = CreateSolidBrush(RGB(red, green, blue));
	oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
	DrawEllipse(hdc, rc);
	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	DeleteObject(newPen);
	DeleteObject(newBrush);
}