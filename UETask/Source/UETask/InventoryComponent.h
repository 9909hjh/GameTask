// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated); // 멀티캐스트 델리게이트는 여러개의 함수를 바인딩할 수 있으며 바인딩된 모든 함수들을 동시에 호출하는 기능을 제공


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UETASK_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	bool AddItem(class UItem* Item);
	bool RemoveItem(class UItem* Item);

	/**기본 아이템 설정*/ 
	UPROPERTY(EditDefaultsOnly, Instanced)
		TArray<class UItem*> DefaultItem;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
		int32 Capacity;

	//인벤토리를 업데이트 할 떄 사용
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
		FOnInventoryUpdated OnInventoryUpdated;

	//아이템을 추가 or 삭제 부분에 사용
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Items")
		TArray<class UItem*> Items;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
