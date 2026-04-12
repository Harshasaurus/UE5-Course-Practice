// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MyActor.h"
#include "Components/SphereComponent.h"
#include "Characters/Hero.h"
#include "NiagaraComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(ItemMesh);

	Sphere->SetRelativeLocation(FVector::ZeroVector);
	Sphere->SetRelativeRotation(FRotator::ZeroRotator);
	Sphere->SetRelativeScale3D(FVector(1.0f));


	EmberEffects = CreateDefaultSubobject<UNiagaraComponent>(TEXT("EmberEffect"));
	EmberEffects->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMyActor::OnSphereOverLap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AMyActor::OnSphereEndOverLap);
}

void AMyActor::OnSphereOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHero* Hero = Cast<AHero>(OtherActor);
	if (Hero) {
		Hero->SetOverlappingMyActor(this);
	}

}

void AMyActor::OnSphereEndOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHero* Hero = Cast<AHero>(OtherActor);
	if (Hero) {
		Hero->SetOverlappingMyActor(nullptr);
	}
}

float AMyActor::TransformSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AMyActor::TransformCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWorld* World = GetWorld();
	FVector Location = GetActorLocation();
	FVector Forward = GetActorForwardVector();
	FRotator Pitch = GetActorRotation();

	RunningTime += DeltaTime;

	//AddActorWorldOffset(FVector(DeltaTime * 100.f, 0.f, 0.f));
	//AddActorWorldRotation(FRotator(0.f, DeltaTime * 100.f, 0.f));


}

