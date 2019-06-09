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

};

