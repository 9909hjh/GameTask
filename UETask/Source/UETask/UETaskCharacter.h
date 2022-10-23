// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UETaskCharacter.generated.h"

UCLASS(config=Game)
class AUETaskCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//Inventory
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items", meta = (AllowPrivateAccess = "true"))
		class UInventoryComponent* Inventory;

public:
	AUETaskCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	//sprint
	bool isSprinting;
	//Sprint ----------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Sprint")
		float MAXSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Sprint")
		float DefaultSpeed;

	//Heal and Damage----------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability | Health")
		float playerHealth;

	//funtion--------------------------
	UFUNCTION(BlueprintCallable, Category = "Items")
		void UseItem(class UItem* Item);

protected:

	//Sprint ----------------
	void Sprint();
	void StopSprinting();
	//Sprint ----------------
	virtual void BeginPlay() override;

	//Heal and Damage----------
	void gettingHeal();
	void gettingDamage();
	//Heal and Damage----------
	void TakeDamage(float _DamageAmount);
	void Heal(float _HealAmount);

	void OnResetVR();
	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

