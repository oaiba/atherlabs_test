// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "BaseCharAttributeSet.generated.h"


/**
 * This macro defines a set of helper functions for accessing and initializing attributes.
 *
 * The following example of the macro:
 *		ATTRIBUTE_ACCESSORS(ULyraHealthSet, Health)
 * will create the following functions:
 *		static FGameplayAttribute GetHealthAttribute();
 *		float GetHealth() const;
 *		void SetHealth(float NewVal);
 *		void InitHealth(float NewVal);
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * Delegate used to broadcast attribute events, some of these parameters may be null on clients:
 * @param EffectInstigator	The original instigating actor for this event
 * @param EffectCauser		The physical actor that caused the change
 * @param EffectSpec		The full effect spec for this change
 * @param EffectMagnitude	The raw magnitude, this is before clamping
 * @param OldValue			The value of the attribute before it was changed
 * @param NewValue			The value after it was changed
*/
//DECLARE_MULTICAST_DELEGATE_SixParams(FGExAttributeEvent, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/, const FGameplayEffectSpec* /*EffectSpec*/, float /*EffectMagnitude*/, float /*OldValue*/, float /*NewValue*/);

/**
 * @class UBaseCharAttributeSet
 *
 * @brief Represents a base attribute set for a character in a game or application.
 *
 * This class is designed to hold and manage various attributes for a character, typically used in
 * games or simulations. It serves as a modular way to define and modify character statistics,
 * such as strength, agility, health, energy, or other attributes relevant to gameplay.
 *
 * Attributes contained within this set are often used in gameplay mechanics such as combat,
 * movement, or interaction systems. The design facilitates easy customization and extension
 * for different character types or game logic requirements.
 *
 * The class may include functionality to:
 * - Initialize default attribute values.
 * - Modify or update attributes during runtime (e.g., via buffs, debuffs, or upgrades).
 * - Query current attribute states.
 * - Integrate with a larger attribute or effects system.
 *
 * This class is typically utilized in combination with other systems such as character controllers,
 * ability systems, or inventory systems to provide a comprehensive gameplay experience.
 *
 * Derived classes can expand on this structure to introduce additional attributes or
 * game-specific logic.
 */
UCLASS()
class ATHERLABS_TEST_API UBaseCharAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UBaseCharAttributeSet();

	// Replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	// Attributes
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBaseCharAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBaseCharAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UBaseCharAttributeSet, Stamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UBaseCharAttributeSet, MaxStamina);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegenRate, Category = "Attributes")
	FGameplayAttributeData StaminaRegenRate;
	ATTRIBUTE_ACCESSORS(UBaseCharAttributeSet, StaminaRegenRate);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Poise, Category = "Attributes")
	FGameplayAttributeData Poise;
	ATTRIBUTE_ACCESSORS(UBaseCharAttributeSet, Poise);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UBaseCharAttributeSet, Armor);

private:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_StaminaRegenRate(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Poise(const FGameplayAttributeData& OldValue) const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldValue) const;
};
