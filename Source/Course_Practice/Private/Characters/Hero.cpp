// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Hero.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Actors/MyActor.h"
#include "Weapons/Weapon.h"
#include "Animation/AnimMontage.h"
#include "Components/BoxComponent.h"


// Sets default values
AHero::AHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())){
			 
			Subsystem->AddMappingContext(HeroMappingContext, 0);

		}
	}

	Tags.Add(FName("Hero"));

}

void AHero::Move(const FInputActionValue& Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;

	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
	

}

void AHero::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
	

	
}

void AHero::JumpStarted(const FInputActionValue& Value)
{
	if (ActionState == EActionState::EAS_Attacking) return;
	Jump();

}

void AHero::JumpStopped(const FInputActionValue& Value)
{
	
	StopJumping();

}

void AHero::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingMyActor);
	if (OverlappingWeapon) {

		OverlappingWeapon->Equip(GetMesh(), FName("hand_rSocket"), this, this);
		
		CharacterState = ECharacterState::EquippedOneHandWeapon;
		OverlappingMyActor = nullptr;
		EquippedWeapon = OverlappingWeapon;

	}
	else {
		if (CanDisarm()) {

			PlayEquipMontage(FName("Unequip"));
			CharacterState = ECharacterState::ECS_Unequipped;
			ActionState = EActionState::EAS_EquippingWeapon;
		}
		else if (CanArm()) {

			PlayEquipMontage(FName("Equip"));
			CharacterState = ECharacterState::EquippedOneHandWeapon;
			ActionState = EActionState::EAS_EquippingWeapon;
		}
	}
}

void AHero::Attack()
{	
	
	if (CanAttack()) {

		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;

	}
}




void AHero::PlayEquipMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage) {

		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
		
	}
}

void AHero::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

bool AHero::CanAttack()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped &&
		!GetCharacterMovement()->IsFalling();

}


bool AHero::CanDisarm()
{
	return ActionState == EActionState::EAS_Unoccupied && 
		CharacterState != ECharacterState::ECS_Unequipped;
}

bool AHero::CanArm()
{
	return ActionState == EActionState::EAS_Unoccupied&&
		CharacterState == ECharacterState::ECS_Unequipped && 
		EquippedWeapon;

}

void AHero::Disarm()
{
	if (EquippedWeapon) {

		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
	}
}

void AHero::Arm()
{
	if (EquippedWeapon) {

		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("hand_rSocket"));
	}
}

void AHero::FinishEquipping()
{
	ActionState = EActionState::EAS_Unoccupied;
}


// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHero::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHero::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AHero::JumpStarted);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AHero::JumpStopped);
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Started, this, &AHero::EKeyPressed);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AHero::Attack);


	}

}



