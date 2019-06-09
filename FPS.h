#pragma once
class FPS
{
public:
	FPS();
	~FPS();

	/**
	@brief	�t���[�����̏���
	*/
	void Update();

private:
	/**
	@brief	FPS���ݒ�l���傫���Ȃ�Ȃ����߂̐���
	*/
	void Wait();

	const Uint32 setFps;				//�t���[�����[�g�̍ō��l
	const Uint32 oneFrameTickCount;		//�P�t���[���ɂ����鎞��
	Uint32 fpsCount;					//�t���[���̃J�E���^�[
	Uint32 frameStartTickTime;			//FPS�̌v�Z���n�߂����̎���
	Uint32 fps;							//�v�Z�����t���[�����[�g

};

