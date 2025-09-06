// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "BaseLogic/BaseData.h"
#include "BaseLogic/AttributeSet/BaseCharAttributeSet.h"
#include "BaseLogic/Components/BaseAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class ATHERLABS_TEST_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter(const FObjectInitializer& ObjectInitializer);

	// IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// A function to initialize all default abilities
	virtual void InitializeAbilities();

	// A function to initialize default attributes
	virtual void InitializeAttributes();

protected:
	// The core Ability System Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	// The Attribute Set to hold our attributes
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UBaseCharAttributeSet> AttributeSet;

	// // Default abilities to grant on spawn
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	// TArray<TSubclassOf<UGameplayEffect>> DefaultGameplayEffects;
	//
	// // Default abilities to grant on spawn
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	// TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UBaseData> CharacterData;

	// Handle to store abilities after being granted
	TArray<FGameplayAbilitySpecHandle> DefaultAbilityHandles;

protected:
	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	void GrantAbilities();
};
