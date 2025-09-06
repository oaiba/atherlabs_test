// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeroData.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "BaseLogic/Characters/BaseCharacter.h"
#include "HeroCharacter.generated.h"

UCLASS()
class ATHERLABS_TEST_API AHeroCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHeroCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ActivateAbilityByTag(const FInputActionValue& InputActionValue, const FGameplayTag GameplayTag);
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	
	// Input Actions for abilities
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	TObjectPtr<UHeroData> HeroData;

    
};
