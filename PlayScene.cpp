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
	//Instantiate<Enemy>(this);
	const int enemyCount = 3;
	enemyCount_ = enemyCount;
	for (int i = 0; i < enemyCount; i++)
	{
		Enemy* pEnemy = Instantiate<Enemy>(this);
		pEnemy->SetPosition(XMFLOAT3(0.0f, 0.0f, 20.0f + i * 8.0f));
	}
	gameStarted_ = false;

	Camera::SetPosition(XMFLOAT3(0.0f, 10.0f, -12.0f));
	Camera::SetTarget(XMFLOAT3(0.0f, -5.0f, 20.0f));
}

void PlayScene::Update()
{
	if (enemyCount_ <= 0) {
		SceneManager* pSceneManager = (SceneManager*)(this->GetParent());
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}

	/*if (!gameStarted_) {
		if (FindObject("Enemy") != nullptr) {
			gameStarted_ = true;
		}
		return;
	}
	GameObject* enemy = FindObject("Enemy");
	if (enemy == nullptr || enemy->IsDead()) {
		SceneManager* pSceneManager = (SceneManager*)(this->GetParent());
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}*/
}

void PlayScene::Draw(){}

void PlayScene::Release(){}

void PlayScene::OnEnemyKilled()
{
	enemyCount_--;
}