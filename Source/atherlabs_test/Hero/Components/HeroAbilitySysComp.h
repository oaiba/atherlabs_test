// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseLogic/Components/BaseAbilitySystemComponent.h"
#include "HeroAbilitySysComp.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ATHERLABS_TEST_API UHeroAbilitySysComp : public UBaseAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHeroAbilitySysComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	// Hàm tiện ích riêng cho hero
	UFUNCTION(BlueprintCallable, Category="Hero ASC")
	void ShowAbilityHUD();

};
