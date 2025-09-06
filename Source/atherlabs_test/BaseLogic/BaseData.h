// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet/BaseCharAttributeSet.h"
#include "Engine/DataAsset.h"
#include "BaseData.generated.h"

/**
 * 
 */
UCLASS()
class ATHERLABS_TEST_API UBaseData : public UDataAsset
{
	GENERATED_BODY()
public:
	
	// Default abilities to grant on spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayEffect>> DefaultGameplayEffects;

	// Default abilities to grant on spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

};

UENUM(BlueprintType)
enum class EDodgeDirection : uint8
{
	None = 0 UMETA(DisplayName = "No Direction", Tooltip = "No dodge direction selected"),
	Forward = 1 UMETA(DisplayName = "Forward", Tooltip = "Dodge in forward direction"),
	ForwardRight = 2 UMETA(DisplayName = "Forward Right", Tooltip = "Dodge diagonally forward and right"),
	Right = 3 UMETA(DisplayName = "Right", Tooltip = "Dodge to the right"),
	BackwardRight = 4 UMETA(DisplayName = "Backward Right", Tooltip = "Dodge diagonally backward and right"),
	Backward = 5 UMETA(DisplayName = "Backward", Tooltip = "Dodge backward"),
	BackwardLeft = 6 UMETA(DisplayName = "Backward Left", Tooltip = "Dodge diagonally backward and left"),
	Left = 7 UMETA(DisplayName = "Left", Tooltip = "Dodge to the left"),
	ForwardLeft = 8 UMETA(DisplayName = "Forward Left", Tooltip = "Dodge diagonally forward and left")
};

USTRUCT(BlueprintType)
struct FDodgeData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	bool bIsInAir = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	bool bIsMoving = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	EDodgeDirection DodgeDirection = EDodgeDirection::Forward;
	
};

USTRUCT(BlueprintType)
struct FDodgeOutData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	UAnimMontage* DodgeMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	float DodgeStartTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dodge")
	float DodgePlayRate = 1.0f;
	
};