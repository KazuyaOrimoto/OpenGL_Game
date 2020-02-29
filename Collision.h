//=============================================================================
//	@file	Collision.h
//	@brief	当たり判定に使うクラスや構造体
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once
#include "Math.h"
#include <vector>
#include <map>



//線分
struct LineSegment
{
	/**
	@param	線分の開始地点のポジション
	@param	線分の終了地点のポジション
	*/
    LineSegment(const Vector3& _start, const Vector3& _end);
	
	/**
	@brief	線分上の点を返す
	@param	入力値 t（L(t) = Start + (End - Start)t）
	@return 線分上の点のポジション
	*/
	Vector3 PointOnSegment(float _t) const;
	
	/**
	@brief	点と線分の間の最短距離を返す
	@param	任意の点のポジション
	@return 最短距離
	*/
    float MinDistanceSquared(const Vector3& _point)const;

	/**
	@brief	線分と線分の間の最短距離を返す
	@param	判定する線分の構造体１
	@param	判定する線分の構造体２
	@return 最短距離
	*/
    static float MinDistanceSquared(const LineSegment& _line1,const LineSegment& _line2);

	//線分の開始地点
    Vector3 start;
	//線分の終了地点
    Vector3 end;
};

//平面
struct Plane
{
	/**
	@param	平面の法線ベクトル
	@param	平面と原点の符号つき最短距離
	*/
    Plane(const Vector3& _normal, float _distance);

	/**
	@param	平面上の点1
	@param	平面上の点2
	@param	平面上の点3
	*/
    Plane(const Vector3& _vec1, const Vector3& _vec2, const Vector3& _vec3);

	/**
	@brief	点と平面の最短距離を返す
	@param	任意の点のポジション
	@return 符号つき最短距離
	*/
    float SignedDistance(const Vector3& _point);

	//平面の法線ベクトル
    Vector3 normal;
	//平面と原点の符号つき最短距離
    float distance;
};

//球
struct Sphere
{
	/**
	@param	球体の中心座標
	@param	球体の半径
	*/
    Sphere(const Vector3& _center, const float _radius);
    
	/**
	@brief	球体に点が含まれているかどうか
	@param	任意の点
	@return true : 当たっている , false : 当たっていない
	*/
	bool Contains(const Vector3& _point)const;

	//球体の中心座標
    Vector3 center;
	//球体の半径
    float radius;
};

//軸並行バウンディングボックス(Axis-Aligned Bounding Box)
struct AABB
{
	/**
	@param	最小のx,y,zの値のポジション
	@param	最大のx,y,zの値のポジション
	*/
    AABB(const Vector3& _min,const Vector3& _max);

	/**
	@brief	最小値と最大値を各成分ごとに更新する
	@param	任意の点のポジション
	*/
    void UpdateMinMax(const Vector3& _point);

	/**
	@brief	当たり判定ボックスの回転
	@param	回転軸と回転表す値（Quaternion）
	*/
    void Rotate(const Quaternion& _quaternion);
    
	/**
	@brief	ボックスに点が含まれているかどうか
	@param	任意の点
	@return true : 当たっている , false : 当たっていない
	*/
	bool Contains(const Vector3& _point)const;
    
	/**
	@brief	点とボックスの最短距離を返す
	@param	任意の点
	@return 最短距離
	*/
	float MinDistanceSquared(const Vector3& _point)const;

    Vector3 min;
    Vector3 max;
};

//有向バウンディングボックス（Oriented Bounding Box）
//未実装
struct OBB
{
	//中心の座標
    Vector3 center;
	//回転クォータニオン
    Quaternion rotation;
	//ボックスの広がり（幅、高さ、奥行き）
    Vector3 extents;
};

//カプセル
struct Capsule
{
	/**
	@param	始点となる点の座標
	@param	終点となる点の座標
	@param	カプセルの半径
	*/
    Capsule(const Vector3& _start,const Vector3& _end,float _radius);

	/**
	@brief	カプセルの始点と終点の線分上の点を返す
	@param	入力値 t（L(t) = Start + (End - Start)t）
	@return 線分上の点のポジション
	*/
    Vector3 PointOnSegment(float _t)const;

	/**
	@brief	カプセルに点が含まれているかどうか
	@param	任意の点
	@return true : 当たっている , false : 当たっていない
	*/
    bool Contains(const Vector3& _point)const;

	//カプセルを構成する線分
    LineSegment segment;
	//カプセルの半径
    float radius;
};

//凸ポリゴン
struct ConvexPolygon
{
	/**
	@brief	２次元のポリゴンに点が含まれているかどうか
	@param	任意の点
	@return true : 当たっている , false : 当たっていない
	*/
    bool Contains(const Vector2& _point)const;

	//頂点の可変長コンテナ
    std::vector<Vector2> vertices;
};

/**
@brief	球と球の当たり判定
@param	球の構造体１
@param	球の構造体２
@return true : 当たっている , false : 当たっていない
*/
bool Intersect(const Sphere& _sphere1,const Sphere& _sphere2);

/**
@brief	ボックスとボックスの当たり判定
@param	ボックスの構造体１
@param	ボックスの構造体２
@return true : 当たっている , false : 当たっていない
*/
bool Intersect(const AABB& _AABB1, const AABB& _AABB2);

/**
@brief	カプセルとカプセルの当たり判定
@param	カプセルの構造体１
@param	カプセルの構造体２
@return true : 当たっている , false : 当たっていない
*/
bool Intersect(const Capsule& _capsule1, const Capsule& _capsule2);

/**
@brief	球とボックスの当たり判定
@param	球の構造体
@param	ボックスの構造体
@return true : 当たっている , false : 当たっていない
*/
bool Intersect(const Sphere& _sphere, const AABB& _AABB);

/**
@brief	線分と球の当たり判定
@param	線分の構造体
@param	球の構造体
@param	線分の始点から接触している点までの値tを格納する
@return true : 当たっている , false : 当たっていない
*/
bool Intersect(const LineSegment& _line, const Sphere& _sphere, float& _outT);

/**
@brief	線分と平面の当たり判定
@param	線分の構造体
@param	平面の構造体
@param	線分の始点から接触している点までの値tを格納する
@return true : 当たっている , false : 当たっていない
*/
bool Intersect(const LineSegment& _line, const Plane& _plane, float& _outT);

/**
@brief	線分とボックスの当たり判定
@param	線分の構造体
@param	ボックスの構造体
@param	線分の始点から接触している点までの値tを格納する
@param	線分の始点から接触した面の法線ベクトルを格納する
@return true : 当たっている , false : 当たっていない
*/
bool Intersect(const LineSegment& _line, const AABB& _AABB, float& _outT,
    Vector3& outNorm);

/**
@brief	球スイープの当たり判定
@param	１フレーム前の球１の構造体
@param	現在のフレームの球１の構造体
@param	１フレーム前の球２の構造体
@param	現在のフレームの球２の構造体
@param	線分の始点から接触している点までの値tを格納する
@return true : 当たっている , false : 当たっていない
*/
bool SweptSphere(const Sphere& _sphere1, const Sphere& _sphere2,
    const Sphere& _sphere3, const Sphere& _sphere4, float& _outT);
