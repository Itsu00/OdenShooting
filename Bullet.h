#pragma once
#include "Engine//GameObject.h"
class Bullet :
    public GameObject
{
public:
	//コンストラクタ
	Bullet(GameObject* parent);
	//初期化
	void Initialize() override;
	//更新
	void Update() override;
	//描画
	void Draw() override;
	//開放
	void Release() override;
private:
	int hModel_;//モデルのハンドル
	float speed_;//弾の速さ
};