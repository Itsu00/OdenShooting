#include "PlayScene.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include "Player.h"
#include "Enemy.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene"), hModel_(-1)
{
}

void PlayScene::Initialize()
{
	Instantiate<Player>(this);//Plaeyrのインスタンス＝プレイヤーオブジェクトを作る
	Instantiate<Enemy>(this);
	gameStarted_ = false;

	Camera::SetPosition(XMFLOAT3(0.0f, 13.0f, -9.5f));
	Camera::SetTarget(XMFLOAT3(0.0f, -7.0f, 15.0f));
}

void PlayScene::Update()
{
	if (!gameStarted_) {
		if (FindObject("Enemy") != nullptr) {
			gameStarted_ = true;
		}
		return;
	}
	GameObject* enemy = FindObject("Enemy");
	if (enemy == nullptr || enemy->IsDead()) {
		SceneManager* pSceneManager = (SceneManager*)(this->GetParent());
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}