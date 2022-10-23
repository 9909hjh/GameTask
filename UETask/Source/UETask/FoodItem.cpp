// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodItem.h"
#include "UETaskCharacter.h"

void UFoodItem::Use(AUETaskCharacter* Character)
{
	if (Character)
	{
		Character->playerHealth += HealthToHeal;
	}
}