// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MenuPawn.generated.h"

UCLASS()
class TOPDOWNSHOOTER_API AMenuPawn : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

public:
	// Sets default values for this pawn's properties
	AMenuPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
