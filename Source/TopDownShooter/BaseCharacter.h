// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IDamagabley.h"
#include "BaseCharacter.generated.h"

UCLASS(Blueprintable)
class TOPDOWNSHOOTER_API ABaseCharacter : public ACharacter, public IIDamagabley
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Base Character Properties")
	float Health = 100;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Base Character Properties")
	bool IsDead = false;

	virtual void CalculateHealth(float Delta);

	virtual void CalculateDead();

	virtual void AffectHealth(float Delta) override;

	virtual void Kill() override;

	virtual bool IsKilled() override;

};
