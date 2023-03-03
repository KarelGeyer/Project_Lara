// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/PickableItem.h"

// Add default functionality here for any IPickableItem functions that are not pure virtual.

FString IPickableItem::GetItemName()
{
	return ItemName;
}