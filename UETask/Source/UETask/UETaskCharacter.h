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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
		class UInventoryComponent* Inventory;

private:
	bool canSprint = false;

public:
	AUETaskCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	//Sprint ----------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Sprint")
		float MAXSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Sprint")
		float DefaultSpeed;

	//Stamina-----------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Sprint | Stamina")
		float PlayerStamina;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Sprint | Stamina")
		float RecoveryStamina;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Sprint | Stamina")
		float ConsumeStamina;

	//Stamina-----------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Sprint | Stamina")
		float MaxStamina;
	UPROPERTY(VisibleAnywhere, Category = "Ability | Sprint | Stamina")
		float MinStamina;

	//Heal and Damage----------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Health")
		float MaxHealth;
	UPROPERTY(VisibleAnywhere, Category = "Ability | Health")
		float MinHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability | Health")
		float playerHealth;

	//defensive �κ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability | Defense")
		float DEF;

	//funtion--------------------------
	UFUNCTION(BlueprintCallable, Category = "Items")
		void UseItem(class UItem* Item);

	//ToDie�� ���� �̺�Ʈ �Լ�.
	UFUNCTION(BlueprintImplementableEvent)
		void ToDie();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Level")
		int32 Level;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Level")
		int32 EXP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Level")
		int32 EXP_Needed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Level")
		float EXP_Mult;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Level")
		int32 MaxEXP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | Level")
		int32 MinEXP;


	//������ ���� �κ� �Լ�.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | LevelUP")
		float MaxHealthPlus;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | LevelUP")
		float MaxStaminaPlus;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | LevelUP")
		float RecoveryStaminaPlus;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | LevelUP")
		float ConsumeStaminaMinus;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability | LevelUP")
		float MAXSpeedPlus;

	UFUNCTION(BlueprintCallable, Category = "Ability | LevelUP")
		int32 Add_EXP(int32 _expfactor);
	
	void LevelupBuff();

protected:

	//Sprint ----------------
	void Sprint();
	void StopSprinting();
	//Sprint ----------------
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	//Heal and Damage----------
	void gettingHeal();
	void gettingDamage();
	//Heal and Damage----------
	UFUNCTION(BlueprintCallable, Category = "Damage")
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

