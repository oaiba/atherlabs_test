// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseLogic/BaseData.h"
#include "DodgeAbility.generated.h"

/**
 * 
 */
UCLASS()
class ATHERLABS_TEST_API UDodgeAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UDodgeAbility();

protected:
	UFUNCTION()
	virtual void OnMontageTaskCompleted();
	
	UFUNCTION()
	virtual void OnMontageTaskInterrupted();

	UFUNCTION(BlueprintImplementableEvent, Category = "Dodge Ability", meta=(DisplayName="Calculate Dodge Montage"))
	void CalculateDodgeMontage(const FDodgeData& DodgeData, const ACharacter* Character, FDodgeOutData& OutData) const;

	virtual bool IsCharacterInAir();
	virtual bool IsCharacterMoving();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	EDodgeDirection CalculateDodgeDirection() const;
};
