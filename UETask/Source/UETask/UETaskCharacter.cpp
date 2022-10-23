// Copyright Epic Games, Inc. All Rights Reserved.

#include "UETaskCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Item.h"
#include "InventoryComponent.h"

//////////////////////////////////////////////////////////////////////////
// AUETaskCharacter

AUETaskCharacter::AUETaskCharacter() : DefaultSpeed(600), MaxHealth(0.f), MinHealth(0.f), playerHealth(0.f)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; 
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 
	
	//Sprint ----------------
	//isSprinting = false;

	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 20;

}

//Sprint ----------------
void AUETaskCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
}

//////////////////////////////////////////////////////////////////////////
// Input

void AUETaskCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//Sprint ----------------
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AUETaskCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AUETaskCharacter::StopSprinting);

	//Heal and Damage----------
	PlayerInputComponent->BindAction("Heal", IE_Pressed, this, &AUETaskCharacter::gettingHeal);
	PlayerInputComponent->BindAction("Damage", IE_Pressed, this, &AUETaskCharacter::gettingDamage);


	PlayerInputComponent->BindAxis("MoveForward", this, &AUETaskCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AUETaskCharacter::MoveRight);


	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AUETaskCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AUETaskCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AUETaskCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AUETaskCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AUETaskCharacter::OnResetVR);


}


void AUETaskCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AUETaskCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void AUETaskCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void AUETaskCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUETaskCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AUETaskCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUETaskCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

//funtion--------------------------
void AUETaskCharacter::UseItem(UItem* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->OnUse(this); //BP event
	}
}

//Sprint ----------------
void AUETaskCharacter::Sprint()
{
	UE_LOG(LogTemp, Warning, TEXT("We are now sprint"));
	//isSprinting = true;
	GetCharacterMovement()->MaxWalkSpeed = MAXSpeed;
}

void AUETaskCharacter::StopSprinting()
{
	UE_LOG(LogTemp, Warning, TEXT("We have stopped sprint"));
	//isSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed;
}

void AUETaskCharacter::gettingHeal()
{
	Heal(0.02f);
}

//Heal and Damage----------
void AUETaskCharacter::gettingDamage()
{
	TakeDamage(20.f);
}

void AUETaskCharacter::TakeDamage(float _DamageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("We are damage for %f prints."), _DamageAmount);
	playerHealth -= _DamageAmount;

	if (playerHealth < MinHealth)
	{
		playerHealth = MinHealth;
	}
}

void AUETaskCharacter::Heal(float _HealAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("We are damage for %f prints."), _HealAmount);
	playerHealth += _HealAmount;

	if (playerHealth > MaxHealth)
	{
		playerHealth = MaxHealth;
	}
}

