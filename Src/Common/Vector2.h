#pragma once

class Vector2
{
public:

	int x; // X座標
	int y; // Y座標


	/// <summary>
	/// デフォルトコンストラクタ
	/// </summary>
	Vector2(void);


	Vector2(const int& X, const int& Y);


	/// <summary>
	/// 通常デストラクタ
	/// </summary>
	~Vector2(void) = default;


#pragma region 四則演算
	/// <summary>
	/// 加算処理
	/// </summary>
	/// <param name="vec">２つ目のVector2</param>
	/// <returns>足した値</returns>
	Vector2 operator+(const Vector2& vec)const;

	/// <summary>
	/// 加算処理
	/// </summary>
	/// <param name="vec">２つ目のVector2</param>
	void operator+=(const Vector2& vec);

	/// <summary>
	/// 減算処理
	/// </summary>
	/// <param name="vec">２つ目のVector2</param>
	/// <returns>引いた値</returns>
	Vector2 operator-(const Vector2& vec)const;

	/// <summary>
	/// 減算処理
	/// </summary>
	/// <param name="vec">２つ目のVector2</param>
	void operator-=(const Vector2& vec);

	/// <summary>
	/// 乗算処理
	/// </summary>
	/// <param name="vec">２つ目のVector2</param>
	/// <returns>掛けた値</returns>
	Vector2 operator*(const Vector2& vec)const;

	/// <summary>
	/// 乗算処理
	/// </summary>
	/// <param name="vec">２つ目のVector2</param>
	void operator*=(const Vector2& vec);

	/// <summary>
	/// 除算処理
	/// </summary>
	/// <param name="vec">２つ目のVector2</param>
	/// <returns>足した値</returns>
	Vector2 operator/(const Vector2& vec)const;

	/// <summary>
	/// 除算処理
	/// </summary>
	/// <param name="vec">２つ目のVector2</param>
	void operator/=(const Vector2& vec);

#pragma endregion
};