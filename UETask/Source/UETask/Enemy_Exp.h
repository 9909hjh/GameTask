// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy_Exp.generated.h"

class UBoxComponent;

UCLASS()
class UETASK_API AEnemy_Exp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy_Exp();

	/*UPROPERTY(EditAnywhere, Category = "EXP")
		int32 MinEXP;
	UPROPERTY(EditAnywhere, Category = "EXP")
		int32 MaxEXP;*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Enemy | Damage")
		float Damage;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ItemMesh;

	/*UPROPERTY(EditAnywhere, Category = "EXP | Item")
		UStaticMesh* EXP_ItemMesh;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*UFUNCTION()
		void OnHit(AActor* OtherActor);*/

};