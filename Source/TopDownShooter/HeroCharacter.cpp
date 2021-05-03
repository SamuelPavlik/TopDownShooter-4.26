// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include "Weapon.h"
#include "TopDownShooterGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TopDownShooter.h"

AHeroCharacter::AHeroCharacter() {
	Tags.Add(FRIENDLY);
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(GetRootComponent());	
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));	
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
}

void AHeroCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (bRotationEnabled)
		RotateCharacter();
}

void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//move logic
	PlayerInputComponent->BindAxis("MoveUp", this, &AHeroCharacter::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHeroCharacter::MoveRight);

	//fire logic
	FInputActionBinding PullTriggerBinding("Fire", EInputEvent::IE_Pressed);
	PullTriggerBinding.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() {
		Weapon->PullTrigger();
	});
	FInputActionBinding ReleaseTriggerBinding("Fire", EInputEvent::IE_Released);
	ReleaseTriggerBinding.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() {
		Weapon->ReleaseTrigger();
	});
	PlayerInputComponent->AddActionBinding(PullTriggerBinding);
	PlayerInputComponent->AddActionBinding(ReleaseTriggerBinding);

	//reload logic
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &AHeroCharacter::ReloadWeapon);

	//pause logic
	FInputActionBinding PauseBinding("Pause", EInputEvent::IE_Pressed);
	PauseBinding.ActionDelegate.GetDelegateForManualSet().BindLambda([this]() {
		GameMode->PauseGame();
	});
	PlayerInputComponent->AddActionBinding(PauseBinding);
}

void AHeroCharacter::Kill() {
	if (APlayerController* HeroController = Cast<APlayerController>(GetController())) {
		DisableInput(HeroController);
		bRotationEnabled = false;
		Weapon->StopShooting();

		FTimerDelegate TimerCallback;
		TimerCallback.BindLambda([this] {
			Weapon->Destroy();
			Destroy();
			GameMode->RespawnPlayer();
			GameMode->ResetScore();
		});
		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, TimerCallback, 3, false);
	}
}

void AHeroCharacter::BeginPlay() {
	Super::BeginPlay();

	GameMode = Cast<ATopDownShooterGameModeBase>(GetWorld()->GetAuthGameMode());
}

void AHeroCharacter::RotateCharacter() {
	if (APlayerController* HeroController = Cast<APlayerController>(GetController())) {
		FHitResult Hit;
		HeroController->GetHitResultUnderCursorByChannel(
			UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility),
			true,
			Hit);
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Hit.Location);
		HeroController->SetControlRotation(TargetRotation);
	}
}

void AHeroCharacter::MoveUp(float AxisValue) {
	AddMovementInput(FVector::XAxisVector, AxisValue);
}

void AHeroCharacter::MoveRight(float AxisValue) {
	AddMovementInput(FVector::YAxisVector, AxisValue);
}

void AHeroCharacter::ReloadWeapon() {
	if (!bIsReloading) {
		if (Weapon->Reload()) {
			ReloadEffect();
		}
		else {
			NoClipsEffect();
		}
	}
}
