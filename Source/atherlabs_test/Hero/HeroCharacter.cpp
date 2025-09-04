// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"

#include "Components/HeroAbilitySysComp.h"
AHeroCharacter::AHeroCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UHeroAbilitySysComp>(TEXT("AbilitySystemComponent")))
{
	PrimaryActorTick.bCanEverTick = true;
}
// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

