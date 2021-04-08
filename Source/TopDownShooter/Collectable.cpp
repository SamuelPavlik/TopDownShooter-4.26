#include "Collectable.h"
#include "Components/SphereComponent.h"
#include "HeroCharacter.h"

UCollectable::UCollectable() {
	PrimaryComponentTick.bCanEverTick = true;

	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	CollisionVolume->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollisionVolume->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CollisionVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	CollisionVolume->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
}

void UCollectable::BeginPlay() {
	if (AActor* Owner = GetOwner()) {
		CollisionVolume = Owner->FindComponentByClass<UShapeComponent>();
		CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &UCollectable::OnHeroBeginOverlap);
		CollisionVolume->SetWorldLocation(Owner->GetActorLocation());
		CollisionVolume->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void UCollectable::Interact(AHeroCharacter* Hero) {
	unimplemented();
}

void UCollectable::OnHeroBeginOverlap(UPrimitiveComponent*, AActor* Actor, UPrimitiveComponent*, int32, bool, const FHitResult&) {
	if (AHeroCharacter* Hero = Cast<AHeroCharacter>(Actor)) {
		Interact(Hero);
	}
}
