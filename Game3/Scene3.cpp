#include "stdafx.h"

#include "PlayerData.h"
#include "Player.h"
#include "UI_Player.h"
#include "PlayerObserver.h"

#include "Item.h"

#include "Scene3.h"

extern bool DEBUG_MODE;
extern bool NONE_SCENE;
extern bool TEXT_LOG;
extern bool FREE_CAM;

extern int CreateCount;
mutex value_mutex;


Scene3::Scene3()
{
	//grid = Grid::Create();
	value_mutex.lock();
	Sleep(100);
	CreateCount++;
	value_mutex.unlock();
	//cam1 = Camera::Create();
	//cam1->LoadFile("Cam2.xml");

	deferred = new Deferred;
	post = UI::Create();
	post->LoadFile("Deferred.xml");

	value_mutex.lock();
	Sleep(100);
	CreateCount++;
	value_mutex.unlock();


	player = PlayerData::Create();
	player->MainCamSet();
	ResizeScreen();

	value_mutex.lock();
	Sleep(1000);
	CreateCount++;
	value_mutex.unlock();

	ChangeScene = true;
}

Scene3::~Scene3()
{
}

void Scene3::Init()
{

}

void Scene3::Release() {}

void Scene3::Update()
{
	static bool isOnece = false;

	if (isOnece) {
		ChangeScene = false;
	}
	isOnece = true;


	ImGui::Text("FPS : %d", TIMER->GetFramePerSecond());

	if (DEBUG_MODE) {
		ImGui::Text("MonsterVector Size : %d ", MonMGR->GetMonsterVector().size());
		deferred->RenderDetail();
	}

	LIGHT->RenderDetail();

	ImGui::Begin("Hierarchy", nullptr);
	//grid->RenderHierarchy();
	//cam1->RenderHierarchy();
	player->Hierarchy();

	//item->actor->RenderHierarchy();

	ImGui::End();

	post->Update();
	//grid->Update();
	//

	if (not ChangeScene) {
		player->Update();

	}
	Camera::main->Update();
}

void Scene3::LateUpdate()
{


	player->LateUpdate();
}

void Scene3::PreRender()
{
	LIGHT->Set();
	Camera::main->Set();

	deferred->SetTarget();

	player->DeferredRender(RESOURCE->shaders.Load("4.Cube_Deferred.hlsl"));
	//item->Render(RESOURCE->shaders.Load("4.Cube_Deferred.hlsl"));

}

void Scene3::Render()
{
	deferred->Render();
	//grid->Render();

	player->Render();
}

void Scene3::ResizeScreen()
{
	Camera::main->viewport.x = 0.0f;
	Camera::main->viewport.y = 0.0f;
	Camera::main->viewport.width = App.GetWidth();
	Camera::main->viewport.height = App.GetHeight();
	Camera::main->width = App.GetWidth();
	Camera::main->height = App.GetHeight();
}
