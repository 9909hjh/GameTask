// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Exp.h"

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
