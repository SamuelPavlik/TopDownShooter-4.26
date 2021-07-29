// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseCharacter.h"
#include "TopDownShooterGameModeBase.generated.h"

class AActorSpawner;
class AEnemySpawner;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreUpdate);

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API ATopDownShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    /** Remove the current menu widget and create a new one from the specified class, if provided. */
    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void PauseGame();

    UFUNCTION(BlueprintCallable, Category = "UMG Game")
    void UnpauseGame();

    void RespawnPlayer();

    void IncrementScore();

private:
    void DestroyAllEnemies();

    void DestroyAllAmmo();

    void ResetScore();

public:
    UPROPERTY(BlueprintAssignable)
    FOnScoreUpdate OnScoreUpdate;

protected:
    virtual void BeginPlay() override;

    /** The widget class we will use as our menu when the game starts. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
    TSubclassOf<UUserWidget> StartingWidgetClass;

    /** The widget class we will use as our menu when the game pauses. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditAnywhere, Category = "UMG Game")
    TSubclassOf<ABaseCharacter> HeroCharacterClass;

    UPROPERTY(BlueprintReadOnly, Category = "UMG Game")
    int Score = 0;

    /** The widget instance that we are using as our menu. */
    UUserWidget* CurrentWidget;

private:
    FTransform PlayerSpawnTransform;

    AEnemySpawner* GameEnemySpawner;

    AActorSpawner* AmmoSpawner;
};
