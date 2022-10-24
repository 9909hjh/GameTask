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

AUETaskCharacter::AUETaskCharacter() : DefaultSpeed(600), MaxHealth(0.f), MinHealth(0.f), playerHealth(0.f), MinStamina(0.0f)
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

//스테미나 관련Tick함수
void AUETaskCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (canSprint)
	{
		PlayerStamina = FMath::FInterpConstantTo(PlayerStamina, MinStamina, DeltaSeconds, ConsumeStamina);
		if (PlayerStamina == MinStamina)
		{
			StopSprinting();
		}
	}
	else
	{
		if (PlayerStamina < MaxStamina)
		{
			PlayerStamina = FMath::FInterpConstantTo(PlayerStamina, MaxStamina, DeltaSeconds, RecoveryStamina);
		}
	}

}

//Sprint ----------------
void AUETaskCharacter::BeginPlay()
{
	Super::BeginPlay();
	// movement에 있던 기본 Speed를 DefualtSpeed로 기획자가 설정한 것으로 적용.
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
	GetCharacterMovement()->MaxWalkSpeed = MAXSpeed;
	canSprint = true;
}

void AUETaskCharacter::StopSprinting()
{
	canSprint = false;
	UE_LOG(LogTemp, Warning, TEXT("We have stopped sprint"));
	GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed; // movement에 있던 기본 Speed를 DefualtSpeed로 기획자가 설정한 것으로 적용.
}

//Heal Test : 1번을 누르면 힐이 되는 것을 보여준다.
void AUETaskCharacter::gettingHeal()
{
	Heal(20.f);
}

//Heal and Damage---------- 
// Damage Test : 2번을 누르면 Damage가 들어가는 것을 보여준다.
void AUETaskCharacter::gettingDamage()
{
	TakeDamage(20.f);
}

//데이지를 받는 부분, MinHealth로 기본으로 설정해준 0이 되면 죽게된다.
void AUETaskCharacter::TakeDamage(float _DamageAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("We are damage for %f prints."), _DamageAmount);

	_DamageAmount -= DEF;

	if (_DamageAmount < 0)
	{
		_DamageAmount = 0;
	}

	playerHealth -= _DamageAmount;

	if (playerHealth < MinHealth)
	{
		playerHealth = MinHealth;
		ToDie();
	}
}

//체력을 회복하는 부분, 기획자가 설정해준 MaxHealth로 설정해준 것으로 적용
void AUETaskCharacter::Heal(float _HealAmount)
{
	UE_LOG(LogTemp, Warning, TEXT("We are damage for %f prints."), _HealAmount);
	playerHealth += _HealAmount;

	if (playerHealth > MaxHealth)
	{
		playerHealth = MaxHealth;
	}
}

int32 AUETaskCharacter::Add_EXP(int32 _expfactor)
{
	EXP += _expfactor;
	if (EXP >= EXP_Needed)
	{
		Level++;
		LevelupBuff();
		EXP -= EXP_Needed;
		EXP_Needed *= EXP_Mult;
		EXP_Needed = FMath::Clamp(EXP_Needed, 0, 100);
		return Level;
	}
	return int32();
}

void AUETaskCharacter::LevelupBuff()
{
	MaxHealth += MaxHealthPlus;
	MaxStamina += MaxStaminaPlus;
	RecoveryStamina += RecoveryStaminaPlus;
	ConsumeStamina -= ConsumeStaminaMinus;
	MAXSpeed += MAXSpeedPlus;
	playerHealth = MaxHealth; //레벨이 오르면 체력이 차오른다.

}