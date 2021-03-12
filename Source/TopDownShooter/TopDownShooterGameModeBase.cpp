// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "TopDownShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "TopDownShooter.h"

void ATopDownShooterGameModeBase::PauseGame() {
	ChangeMenuWidget(PauseWidgetClass);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void ATopDownShooterGameModeBase::UnpauseGame() {
	ChangeMenuWidget(nullptr);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void ATopDownShooterGameModeBase::RespawnPlayer() {
	DestroyAllEnemies();
	if (UWorld* World = GetWorld()) {
		AActor* Hero = World->SpawnActor(HeroCharacterClass.Get(), &PlayerSpawnTransform);
		World->GetFirstPlayerController()->Possess(Cast<APawn>(Hero));
		GameEnemySpawner->Reset();
	}
}

void ATopDownShooterGameModeBase::IncrementScore() {
	Score++;
}

void ATopDownShooterGameModeBase::ResetScore() {
	Score = 0;
}

void ATopDownShooterGameModeBase::DestroyAllEnemies() {
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), ENEMY, FoundEnemies);
	for (AActor* Found : FoundEnemies) {
		Found->Destroy();
	}
}

void ATopDownShooterGameModeBase::BeginPlay() {
	Super::BeginPlay();

	//find player start transform
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
	PlayerSpawnTransform = FoundActors[0]->GetActorTransform();

	//set mouse cursor settings
	if (UWorld* World = GetWorld()) {
		World->GetFirstPlayerController()->bShowMouseCursor = true;
		FInputModeGameAndUI InputMode;
		InputMode.SetHideCursorDuringCapture(false);
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		World->GetFirstPlayerController()->SetInputMode(InputMode);
	}

	//get enemy spawner
	TArray<AActor*> FoundSpawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), GameEnemySpawner->StaticClass(), FoundSpawners);
	GameEnemySpawner = Cast<AEnemySpawner>(FoundSpawners[0]);

}

void ATopDownShooterGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass) {
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}