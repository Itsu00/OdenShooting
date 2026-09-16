#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "PlayScene.h"
#include <cstdlib>

Enemy::Enemy(GameObject* parent)
	: GameObject(parent, "Enemy"), hModel_(-1), time_(0.0f)
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Oden.fbx");
	assert(hModel_ >= 0);

	transform_.scale_ = { 0.5f, 0.5f, 0.5f };
	transform_.rotate_ = { 0.0f, 0.0f, 0.0f };

	time_ = static_cast<float>(rand() % 628) / 100.0f; //0〜2π相当のランダムな初期位相
	amplitude_ = 8.0f + static_cast<float>(rand() % 500) / 100.0f;
	speed_ = 0.03f + static_cast<float>(rand() % 100) / 10000.0f;

	SphereCollider* collider = new SphereCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), 1.0f);
	AddCollider(collider);
}

void Enemy::Update()
{
	static float time = 0.0f;

	time_ += speed_;
	transform_.position_.x = basePosition_.x + amplitude_ * sin(time_);
	/*transform_.position_ = {0.0f, 0.0f, 20.0f};
	transform_.scale_ = { 0.5f, 0.5f, 0.5f };
	transform_.rotate_ = { 0.0f, 0.0f, 0.0f };
	transform_.rotate_.y = time;//回転
	time += 0.01f;
	transform_.position_.x = 6.0f * sin(time);
	float posx = 6.0 * sin(0.2f * time);
	  float posy = cos(3.0f * time);
	  transform_.position.x = posx;
	  transform_.position.y = posy;*/
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release(){}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Bullet") {
		pTarget->KillMe();

		PlayScene* pPlayScene = (PlayScene*)(this->GetParent());
		pPlayScene->OnEnemyKilled(); // 倒れたことをPlaySceneに知らせる

		KillMe();
	}

	/*if (pTarget->GetObjectName() == "Bullet") {
		pTarget->KillMe();//Bullet消して
		KillMe();//自分も消す
	}*/
}

void Enemy::SetPosition(XMFLOAT3 pos)
{
	transform_.position_ = pos;
	basePosition_ = pos;
}