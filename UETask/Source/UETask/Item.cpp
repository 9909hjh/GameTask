// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "UETaskCharacter.h"

UItem::UItem()
{
	ItemDisplayName = FText::FromString("Item");
	UseActionText = FText::FromString("Use");
}

void UItem::Use(AUETaskCharacter* Character)
{
	if (Character)
	{
		Character->DEF += RiseDEF;
	}
}
