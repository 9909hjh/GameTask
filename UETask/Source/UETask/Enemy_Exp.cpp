// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Exp.h"
#include "UETaskCharacter.h"

// Sets default values
AEnemy_Exp::AEnemy_Exp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My EXP_ItemMesh"));
}



// Called when the game starts or when spawned
void AEnemy_Exp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy_Exp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//ÄÉ½ºÆÃ
//void AEnemy_Exp::OnHit(AActor* OtherActor)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Your Message"));
//	AUETaskCharacter* Charater = Cast<AUETaskCharacter>(OtherActor);
//	if (Charater != nullptr)
//	{
//		
//		Charater->Add_EXP(FMath::RandRange(MinEXP, MaxEXP));
//		Destroy();
//	}
//}

