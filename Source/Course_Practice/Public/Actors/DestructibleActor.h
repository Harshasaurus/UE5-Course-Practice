// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "DestructibleActor.generated.h"

class UGeometryCollectionComponent;
class UCapsuleComponent;
UCLASS()
class COURSE_PRACTICE_API ADestructibleActor : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestructibleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Destructible")
	UGeometryCollectionComponent* GeometryCollection;

	UPROPERTY(EditAnywhere, Category = "Breakable Properties")
	TArray<TSubclassOf<class ATreasure>>TreasureClasses;

	bool bBroken = false;

protected:

UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
UCapsuleComponent* Capsule;

};
