﻿/**
 * @file   SceneManager.cpp
 * @brief  SceneManagerクラスの実装
 * @author kotani
 */
#include "SceneManager.h"
#include "SceneBase/SceneBase.h"

namespace Lib
{
	SceneManager::SceneManager() :
		m_IsGameEnd(false),
		m_CurrentSceneName("")
	{
	}

	SceneManager::~SceneManager()
	{
		if (m_pCurrentScene != nullptr)
		{
			m_pCurrentScene->Finalize();
		}
	}
	
	bool SceneManager::Run()
	{
		if (m_CurrentSceneName == "") return m_IsGameEnd;
		switch (m_State)
		{
		case SCENE_CREATE:
			m_pCurrentScene = m_pScenes[m_CurrentSceneName];
			m_pCurrentScene->Initialize();
			m_State = SCENE_PROC;
			break;
		case SCENE_PROC:
			m_pCurrentScene->Run();
			if (m_pCurrentScene->GetSceneName() != m_CurrentSceneName)
			{
				m_State = SCENE_RELEASE;
			}
			break;
		case SCENE_RELEASE:
			m_pCurrentScene->Finalize();
			m_State = SCENE_CREATE;
			break;
		}

		return m_IsGameEnd;
	}

	void SceneManager::AddScene(SceneBase* _pScene)
	{
		m_pScenes[_pScene->GetSceneName()] = _pScene;
	}

	void SceneManager::RemoveScene(std::string _sceneName)
	{
		m_pScenes.erase(_sceneName);
	}

	void SceneManager::ChangeScene(std::string _sceneName)
	{
		if (m_pScenes.find(_sceneName) != m_pScenes.end())
		{
			m_CurrentSceneName = _sceneName;
		}
	}
}
