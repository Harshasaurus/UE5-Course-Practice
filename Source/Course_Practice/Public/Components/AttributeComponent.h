// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COURSE_PRACTICE_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UAttributeComponent();

protected:

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//Current Health of the Actor
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float Health;
	
	UPROPERTY(EditAnywhere, Category = "Attributes")
	float MaxHealth;

public:
	void ReceiveDamage(float Damage);
	float GetHealthPercent();
	bool IsAlive();
};
