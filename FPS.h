//=============================================================================
//	@file	FPS.h
//	@brief	フレームレートを制御する
//	@autor	居本 和哉
//	@date	2020/02/29
//=============================================================================

#pragma once
class FPS
{
public:
	FPS();
	~FPS();

	/**
	@brief	フレーム毎の処理
	*/
	void Update();

	float GetDeltaTime() {return deltaTime;}

private:
	/**
	@brief	FPSが設定値より大きくならないための制御
	*/
	void Wait();

	const Uint32 setFps;				//フレームレートの最高値
	const Uint32 oneFrameTickCount;		//１フレームにかける時間
	Uint32 fpsCount;					//フレームのカウンター
	Uint32 frameStartTickTime;			//FPSの計算を始めた時の時間
	Uint32 fps;							//計算したフレームレート
	int beforetickCount;				//前のフレームのかかった時間
	float deltaTime;					//現在のフレームのかかった時間

};

