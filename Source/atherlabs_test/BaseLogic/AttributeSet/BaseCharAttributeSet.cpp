// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "GameplayEffectTypes.h"
#include "Net/UnrealNetwork.h"

UBaseCharAttributeSet::UBaseCharAttributeSet()
{
	Health = 100.f;
	MaxHealth = 100.f;
	Stamina = 100.f;
	MaxStamina = 100.f;
	StaminaRegenRate = 5.f;
	Poise = 0.f;
	Armor = 0.f;
}

void UBaseCharAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBaseCharAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBaseCharAttributeSet, Stamina, COND_None, REPNOTIFY_Always);
}

void UBaseCharAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UBaseCharAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// If we applied damage (Health was modified by a negative magnitude)
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// handle death, clamp, etc.
		if (Health.GetCurrentValue() <= 0.f)
		{
			// Broadcast death event / tag
		}
	}
}

void UBaseCharAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue) const
{
}

void UBaseCharAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const
{
}

void UBaseCharAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldValue) const
{
}

void UBaseCharAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldValue) const
{
}

void UBaseCharAttributeSet::OnRep_StaminaRegenRate(const FGameplayAttributeData& OldValue) const
{
}

void UBaseCharAttributeSet::OnRep_Poise(const FGameplayAttributeData& OldValue) const
{
}

void UBaseCharAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldValue) const
{
}
