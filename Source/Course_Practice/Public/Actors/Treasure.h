// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/MyActor.h"
#include "Treasure.generated.h"

/**
 * 
 */
UCLASS()
class COURSE_PRACTICE_API ATreasure : public AMyActor
{
	GENERATED_BODY()
	
protected:
	virtual void OnSphereOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* PickupSound;

	UPROPERTY(EditAnywhere, Category = "Treasure Properties")
	int32 Gold;
};
