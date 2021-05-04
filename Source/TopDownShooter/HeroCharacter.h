// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "HeroCharacter.generated.h"

class AWeapon;
class ATopDownShooterGameModeBase;
class UCameraComponent;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHealthUpdate);

/**
 * 
 */
UCLASS()
class TOPDOWNSHOOTER_API AHeroCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bWavingPressed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsReloading;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AWeapon* Weapon;

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly)
	FOnHealthUpdate OnHealthUpdate;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USpringArmComponent* CameraArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent* Camera;

private:
	ATopDownShooterGameModeBase* GameMode;

	bool bRotationEnabled = true;

	FVector CurrentMovement;

public:
	AHeroCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AffectHealth(float Delta) override;

	virtual void Kill() override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void NoClipsEffect();

	UFUNCTION(BlueprintImplementableEvent)
	void ReloadEffect();

private:
	void RotateCharacter();

	void MoveUp(float AxisValue);

	void MoveRight(float AxisValue);

	void ReloadWeapon();
};
