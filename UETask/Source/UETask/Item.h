// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "UObject/NoExportTypes.h"
#include "Item.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class UETASK_API UItem : public UObject
{
	GENERATED_BODY()
	

public:
	UItem();

	virtual class UWorld* GetWorld() const { return World; }

	UPROPERTY(Transient)
		class UWorld* World;

	// 아이템 종류
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText UseActionText;
	//아이템 메쉬설정
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UStaticMesh* PickupMesh;
	//인벤토리에 보이는 아이템 이미지.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		class UTexture2D* Thumbanil;
	//아이템 이름
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		FText ItemDisplayName;
	//아이템 설명
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
		FText ItemDescription;

	//방어력 증가량.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (ClampMin = 0.0f))
		float RiseDEF;

	UPROPERTY()
		class UInventoryComponent* OwningInventory;

	virtual void Use(class AUETaskCharacter* Character); //PURE_VIRTUAL(UItem, ); //순수 가상함수 상속을 할 때 사용

	//------------------------------------------------------------------

	UFUNCTION(BlueprintImplementableEvent)  //BP에서만 정의가능
		void OnUse(class AUETaskCharacter* Character);

private:
	bool Wearing = true;
};
