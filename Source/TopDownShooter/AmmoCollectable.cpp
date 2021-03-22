#include "AmmoCollectable.h"
#include "HeroCharacter.h"
#include "Weapon.h"
#include "ActorSpawner.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UAmmoCollectable::Interact(AHeroCharacter* Hero) {
	Hero->Weapon->AddClips(NumOfClips);
	GetOwner()->Destroy();
	TArray<AActor*> FoundSpawners;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("AmmoSpawner"), FoundSpawners);
	for (AActor* Actor : FoundSpawners) {
		if (AActorSpawner* Spawner = Cast<AActorSpawner>(Actor)) {
			Spawner->DecrActors();
			break;
		}
	}
}

