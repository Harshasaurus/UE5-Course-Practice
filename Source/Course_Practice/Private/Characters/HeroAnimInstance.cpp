// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HeroAnimInstance.h"
#include "Characters/Hero.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Hero = Cast<AHero>(TryGetPawnOwner());
	if (Hero)
	{
		HeroCharacterMovement = Hero->GetCharacterMovement();
	}
}

void UHeroAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (HeroCharacterMovement) {

		GroundSpeed = UKismetMathLibrary::VSizeXY(HeroCharacterMovement->Velocity);
		Isfalling = HeroCharacterMovement->IsFalling();
		CharacterState = Hero->GetCharacterState();
	}
}
