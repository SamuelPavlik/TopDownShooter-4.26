#include "Collectable.h"
#include "Components/ShapeComponent.h"
#include "HeroCharacter.h"

UCollectable::UCollectable() {
	PrimaryComponentTick.bCanEverTick = true;

	//CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
}

void UCollectable::BeginPlay() {
	if (AActor* Owner = GetOwner()) {
		CollisionVolume = Owner->FindComponentByClass<UShapeComponent>();
		CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &UCollectable::OnHeroBeginOverlap);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Assign"));
		//CollisionVolume->SetupAttachment(Owner->GetRootComponent());
	}
}

void UCollectable::Interact(AHeroCharacter* Hero) {
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Interacting"));
	unimplemented();
}

void UCollectable::OnHeroBeginOverlap(UPrimitiveComponent*, AActor* Actor, UPrimitiveComponent*, int32, bool, const FHitResult&) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap"));

	if (AHeroCharacter* Hero = Cast<AHeroCharacter>(Actor)) {
		Interact(Hero);
	}
}
