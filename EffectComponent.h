#pragma once
#include "Component.h"
#include <string>
#include "Math.h"

class EffectComponent :
    public Component
{
public:
    EffectComponent(GameObject* _owner);
    ~EffectComponent();

    /**
    @brief	フレーム毎の処理
    @param	最後のフレームを完了するのに要した時間
    */
    virtual void Update(float _deltaTime) override;

    void LoadEffect(std::string _filename);
    void Stop();
    void Play();

    void SetPosition(const Vector3& _pos) { position = _pos;}
    void SetRotation(const Quaternion& _rot) { rotation = _rot; }
    void SetSize(const Vector3& _size) { size = _size; }

    Vector3 GetPosition() const { return position; }
    Quaternion GetRotation() const { return rotation; }
    Vector3 GetSize() const { return size; }

private:
    int handle;
    Vector3 position;
    Quaternion rotation;
    Vector3 size;
};

