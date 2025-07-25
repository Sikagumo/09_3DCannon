#include "Grid.h"
#include <DxLib.h>


void Grid::Draw(void)
{
	float num;	  // 線の値
	VECTOR sPos;  // 開始位置
	VECTOR ePos;  // 終了位置

	for (int i = -HNUM; i < HNUM; i++)
	{
		num = static_cast<int>(i);

		// X軸(赤)
		sPos = { -HLEN, LINE_POS_Y, (num * TERM) };
		ePos = {  HLEN, LINE_POS_Y, (num * TERM) };
		DrawGridLine(sPos, ePos, 0xFF0000);

		// Z軸(青)
		sPos = { (num * TERM), LINE_POS_Y, -HLEN };
		ePos = { (num * TERM), LINE_POS_Y,  HLEN };
		DrawGridLine(sPos, ePos, 0x0000FF);
	}

	// Y軸(緑)
	sPos = { 0.0f, LINE_POS_Y, 0.0f };
	ePos = { 0.0f, LEN + LINE_POS_Y , 0.0f };
	DrawGridLine(sPos, ePos, 0x00FF00);
}


void Grid::DrawGridLine(VECTOR& startPos, VECTOR& endPos, unsigned int coler)
{
	/*　グリッド線描画処理　*/

	DrawLine3D(startPos, endPos, coler);
	DrawSphere3D(endPos, SPHERE_RAD, SPHERE_DIV, coler, coler, true);
}
