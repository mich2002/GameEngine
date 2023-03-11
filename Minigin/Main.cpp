#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSCounterComponent.h"
#include "GameObject.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "RotatorComponent.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	const auto pBackgroundTexture = dae::ResourceManager::GetInstance().LoadTexture("background.tga");
	const auto pFontTitle = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const auto pFontFpsCounter = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	const auto pLogoTexture = dae::ResourceManager::GetInstance().LoadTexture("logo.tga");
	const auto pCharacterTexture = dae::ResourceManager::GetInstance().LoadTexture("character.png");
	const auto pSecondaryCharacterTexture = dae::ResourceManager::GetInstance().LoadTexture("SecondaryCharacter.png");

	const auto pBackground = scene.CreateGameObject();
	pBackground->GetComponent<dae::TransformComponent>()->SetLocalPosition(0, 0);
	pBackground->AddComponent<dae::TextureComponent>()->SetTexture(pBackgroundTexture);

	const auto pTitle = scene.CreateGameObject();
	pTitle->GetComponent<dae::TransformComponent>()->SetLocalPosition(80, 60);
	pTitle->AddComponent<dae::TextureComponent>();
	pTitle->AddComponent<dae::TextComponent>()->SetText("Programming 4 Assignment");
	pTitle->GetComponent<dae::TextComponent>()->SetFont(pFontTitle);

	const auto pLogo = scene.CreateGameObject();
	pLogo->GetComponent<dae::TransformComponent>()->SetLocalPosition(216, 180);
	pLogo->AddComponent<dae::TextureComponent>()->SetTexture(pLogoTexture);

	const auto pFpsCounter = scene.CreateGameObject();
	pFpsCounter->GetComponent<dae::TransformComponent>()->SetLocalPosition(2, 2);
	pFpsCounter->AddComponent<dae::TextureComponent>();
	pFpsCounter->AddComponent<dae::TextComponent>()->SetFont(pFontFpsCounter);
	pFpsCounter->GetComponent<dae::TextComponent>()->SetColor(252, 226, 5);
	pFpsCounter->AddComponent<dae::FPSCounterComponent>();

	const auto pWorldCenter = scene.CreateGameObject();
	pWorldCenter->GetComponent<dae::TransformComponent>()->SetLocalPosition({ 640 / 2.f, 300,0 });

	const auto pCharacter = pWorldCenter->CreateGameObject();
	pCharacter->GetComponent<dae::TransformComponent>()->SetLocalPosition({ 20,0,0 });
	pCharacter->AddComponent<dae::RotatorComponent>()->SetPivot(pCharacter->GetParent()->GetComponent<dae::TransformComponent>()->GetWorldPosition());
	pCharacter->AddComponent<dae::TextureComponent>()->SetTexture(pCharacterTexture);

	const auto pSecondaryCharacter = pCharacter->CreateGameObject();
	pSecondaryCharacter->GetComponent<dae::TransformComponent>()->SetLocalPosition({ 20,0,0 });
	pSecondaryCharacter->AddComponent<dae::RotatorComponent>()->SetPivot(pSecondaryCharacter->GetParent()->GetComponent<dae::TransformComponent>()->GetWorldPosition());
	pSecondaryCharacter->GetComponent<dae::RotatorComponent>()->SetSpeed(100);
	pSecondaryCharacter->AddComponent<dae::TextureComponent>()->SetTexture(pSecondaryCharacterTexture);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
};