// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ARSceneRoot.generated.h"

UCLASS()
class ARCHVIS_API AARSceneRoot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARSceneRoot();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void SetActorHiddenInGame(bool bNewHidden) override;
};
