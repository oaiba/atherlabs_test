// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "Engine/DataAsset.h"
#include "HeroData.generated.h"

/**
 * 
 */
UCLASS()
class ATHERLABS_TEST_API UHeroData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	// // Input Actions for abilities
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	// TObjectPtr<UInputAction> PrimaryAttackAction;
	//
	// UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	// TObjectPtr<UInputAction> DodgeAction;

	// This will handle ability input
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> HeroInputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TMap<TObjectPtr<UInputAction>, FGameplayTag> InputActionTags;
};
