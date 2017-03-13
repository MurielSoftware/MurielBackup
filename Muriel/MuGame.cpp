#include "stdafx.h"
#include "MuGame.h"
#include "MuSceneManager.h"
#include "MuKeyboard.h"
#include "MuMouse.h"
#include "MuFirstPersonCamera.h"
#include "MuOrbitCamera.h"
#include "MuTimer.h"
#include "MuBox.h"
#include "MuShaderManager.h"
#include "MuLog.h"
#include "MuBaseMaterial.h"
#include "MuTextureManager.h"
#include "MuMeshRenderer.h"
#include "MuDiffuseMaterial.h"
#include "MuDirectionalLight.h"
#include "MuModelManager.h"
#include "MuBumpMaterial.h"
namespace Muriel
{
	Game::Game()
	{
		Init();
	}

	Game::~Game()
	{
		delete _camera;
		for (GameObject* gameObject : _gameObjects)
		{
			delete gameObject;
		}
		_gameObjects.clear();
		Log::GetInstance()->Destroy();
	}

	void Game::Init()
	{
		Keyboard::GetInstance()->Init();
		Mouse::GetInstance()->Init(true);

		CreateCamera();

		Shader* shader = ShaderManager::GetInstance()->Load("base", "data/shaders/base");
		Shader* bumpShader = ShaderManager::GetInstance()->Load("bump", "data/shaders/bump");
		Shader* directionalLightShader = ShaderManager::GetInstance()->Load("directionallight", "data/shaders/directionallight");
		Texture* texture = TextureManager::GetInstance()->Load("box", "data/textures/box.jpg");
		Texture* textureStone = TextureManager::GetInstance()->Load("stone", "data/textures/stone.jpg");
		Texture* textureStoneNormal = TextureManager::GetInstance()->Load("stoneNormal", "data/textures/stone_normal.jpg");
		BumpMaterial* boxMaterial = new BumpMaterial(bumpShader, textureStone, textureStoneNormal);
		Model* model = ModelManager::GetInstance()->Load("scooter", "data/models/scooter.ms3d");
		_directionalLight = new DirectionalLight("light", *directionalLightShader, Color(1.0f, 1.0f, 1.0f), 0.7f);
		//Box* box = new Box("box");
		//box->SetRenderer(new MeshRenderer(box, boxMaterial));
		//box->GetTransform().SetPosition(0, 0, 0);
		GameObject* gameObject = new GameObject("scooter");
		gameObject->SetModel(model);
		gameObject->SetRenderer(new MeshRenderer(gameObject, boxMaterial));
		_gameObjects.push_back(gameObject);

	}

	void Game::AddGameObject(GameObject* gameObject)
	{
		_gameObjects.push_back(gameObject);
	}

	void Game::ProccessFrame(Timer* timer)
	{
		Input(timer);
		Update(timer);
		Render(timer);
	}

	void Game::CreateCamera()
	{
		_camera = new OrbitCamera();
		_camera->Perspective(90.0f, 1.3f, 0.1f, 1000.0f);
	}

	void Game::Input(Timer* timer)
	{
		Keyboard::GetInstance()->Update();
		Mouse::GetInstance()->Update();
	}

	void Game::Update(Timer* timer)
	{
		_camera->UpdateCamera();		
	}

	void Game::Render(Timer* timer)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	//	_directionalLight->GetShader().Activate();
		for (GameObject* gameObject : _gameObjects)
		{
			//_directionalLight->GetShader().UniformMat4x4("worldMatrix", false, gameObject->GetTransform().GetWorldMatrix());
			//_directionalLight->GetShader().UniformMat4x4("projectionViewMatrix", false, _camera->GetProjectionViewMatrix());
			//_directionalLight->GetShader().UniformMat4x4("modelViewMatrix", false, _camera->GetViewMatrix());
			//_directionalLight->GetShader().UniformMat3x3("normalMatrix", false, _camera->GetNormalMatrix());
			//_directionalLight->GetShader().Uniform3f("cameraPosition", _camera->GetPosition());	

			IRenderer* renderer = gameObject->GetRenderer();
			renderer->PreRender(_camera);
			renderer->Render();
			renderer->PostRender();
		}

	//	_directionalLight->GetShader().Deactivate();

		glFlush();
		SwapBuffers(g_hDC);
	}
}