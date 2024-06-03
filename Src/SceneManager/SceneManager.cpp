#include "DxLib.h"
#include "SceneManager.h"
#include "../Common.h"
#include "../Sound/SoundManager.h"

#include "SceneTitle/SceneTitle.h"
#include "ScenePlay/ScenePlay.h"
#include "SceneEdit/SceneEdit.h"
#include "SceneSelect/SceneSelect.h"
#include "SceneClear/SceneClear.h"
#include "SceneGameOver/SceneGameOver.h"

int SceneBace::g_scene_ID;

SceneManager::SceneManager()
{
	scene = nullptr;
	SceneBace::g_scene_ID = Title_Scene;
}

void SceneManager::Main()
{
	switch (SceneBace::g_scene_ID) {
	case Title_Scene: {
		if (scene != nullptr) {
			scene->Fin();
			delete scene;
		}
		scene = new SceneTitle;
		scene->Init();
		SceneBace::g_scene_ID = Loop_Scene;
		CSoundManager::StopAll();
		break;
	}
	case Play_Scene: {
		if (scene != nullptr) {
			scene->Fin();
			delete scene;
		}
		scene = new ScenePlay;
		scene->Init();
		SceneBace::g_scene_ID = Loop_Scene;
		CSoundManager::StopAll();
		CSoundManager::Play(CSoundManager::SOUNDID_BGM, DX_PLAYTYPE_LOOP);
		break;
	}
	case Clear_Scene: {
		if (scene != nullptr) {
			scene->Fin();
			delete scene;
		}
		scene = new SceneClear;
		scene->Init();
		SceneBace::g_scene_ID = Loop_Scene;
		CSoundManager::StopAll();
		break;
	}
	}

	if (scene != nullptr) {
		scene->Step();
		scene->Draw();
	}
}