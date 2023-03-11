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
	auto& scene = real::SceneManager::GetInstance().CreateScene("Demo");

	const auto pBackgroundTexture = real::ResourceManager::GetInstance().LoadTexture("background.tga");
	const auto pFontTitle = real::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	const auto pFontFpsCounter = real::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	const auto pLogoTexture = real::ResourceManager::GetInstance().LoadTexture("logo.tga");
	const auto pCharacterTexture = real::ResourceManager::GetInstance().LoadTexture("Character.png");
	const auto pSecondaryCharacterTexture = real::ResourceManager::GetInstance().LoadTexture("SecondaryCharacter.png");

	const auto pBackground = scene.CreateGameObject();
	pBackground->GetComponent<real::TransformComponent>()->SetLocalPosition(0, 0);
	pBackground->AddComponent<real::TextureComponent>()->SetTexture(pBackgroundTexture);

	const auto pTitle = scene.CreateGameObject();
	pTitle->GetComponent<real::TransformComponent>()->SetLocalPosition(80, 60);
	pTitle->AddComponent<real::TextureComponent>();
	pTitle->AddComponent<real::TextComponent>()->SetText("Programming 4 Assignment");
	pTitle->GetComponent<real::TextComponent>()->SetFont(pFontTitle);

	const auto pLogo = scene.CreateGameObject();
	pLogo->GetComponent<real::TransformComponent>()->SetLocalPosition(216, 180);
	pLogo->AddComponent<real::TextureComponent>()->SetTexture(pLogoTexture);

	const auto pFpsCounter = scene.CreateGameObject();
	pFpsCounter->GetComponent<real::TransformComponent>()->SetLocalPosition(2, 2);
	pFpsCounter->AddComponent<real::TextureComponent>();
	pFpsCounter->AddComponent<real::TextComponent>()->SetFont(pFontFpsCounter);
	pFpsCounter->GetComponent<real::TextComponent>()->SetColor(252, 226, 5);
	pFpsCounter->AddComponent<real::FPSCounterComponent>();

	const auto pWorldCenter = scene.CreateGameObject();
	pWorldCenter->GetComponent<real::TransformComponent>()->SetLocalPosition({ 640 / 2.f, 300,0 });

	const auto pCharacter = pWorldCenter->CreateGameObject();
	pCharacter->GetComponent<real::TransformComponent>()->SetLocalPosition({ 20,0,0 });
	pCharacter->AddComponent<real::RotatorComponent>()->SetPivot(pCharacter->GetParent()->GetComponent<real::TransformComponent>()->GetWorldPosition());
	pCharacter->AddComponent<real::TextureComponent>()->SetTexture(pCharacterTexture);

	const auto pSecondaryCharacter = pCharacter->CreateGameObject();
	pSecondaryCharacter->GetComponent<real::TransformComponent>()->SetLocalPosition({ 20,0,0 });
	pSecondaryCharacter->AddComponent<real::RotatorComponent>()->SetPivot(pSecondaryCharacter->GetParent()->GetComponent<real::TransformComponent>()->GetWorldPosition());
	pSecondaryCharacter->GetComponent<real::RotatorComponent>()->SetSpeed(100);
	pSecondaryCharacter->AddComponent<real::TextureComponent>()->SetTexture(pSecondaryCharacterTexture);
}

int main(int, char* []) {
	real::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
};