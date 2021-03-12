// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

void ABaseCharacter::CalculateHealth(float Delta) {
	Health += Delta;
	CalculateDead();
}

void ABaseCharacter::CalculateDead() {
	if (Health <= 0)
		IsDead = true;
	else
		IsDead = false;
}

void ABaseCharacter::AffectHealth(float Delta) {
	if (IsDead)
		return;
	CalculateHealth(Delta);
	if (Health <= 0)
		Kill();
}

void ABaseCharacter::Kill() {
	Destroy();
}

bool ABaseCharacter::IsKilled() {
	return IsDead;
}
