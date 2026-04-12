// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Treasure.h"
#include "Characters\Hero.h"
#include "Kismet/GameplayStatics.h"

void ATreasure::OnSphereOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHero* Hero = Cast<AHero>(OtherActor);
	if (Hero) {
		Hero->SetOverlappingMyActor(this);
		if (PickupSound) {
			UGameplayStatics::PlaySoundAtLocation(
				this,
				PickupSound,
				GetActorLocation());
		}
		Destroy();
	}
}
