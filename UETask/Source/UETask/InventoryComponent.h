// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated); // ��Ƽĳ��Ʈ ��������Ʈ�� �������� �Լ��� ���ε��� �� ������ ���ε��� ��� �Լ����� ���ÿ� ȣ���ϴ� ����� ����


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UETASK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	bool AddItem(class UItem* Item);
	bool RemoveItem(class UItem* Item);

	/**�⺻ ������ ����*/ 
	UPROPERTY(EditDefaultsOnly, Instanced)
		TArray<class UItem*> DefaultItem;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
		int32 Capacity;

	//�κ��丮�� ������Ʈ �� �� ���
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FOnInventoryUpdated OnInventoryUpdated;

	//�������� �߰� or ���� �κп� ���
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Items")
		TArray<class UItem*> Items;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
