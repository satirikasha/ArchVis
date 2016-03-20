// Fill out your copyright notice in the Description page of Project Settings.

#include "ArchVis.h"
#include "ARSceneRoot.h"


// Sets default values
AARSceneRoot::AARSceneRoot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AARSceneRoot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AARSceneRoot::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AARSceneRoot::SetActorHiddenInGame(bool bNewHidden)
{
	Super::SetActorHiddenInGame(bNewHidden);
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (int i = 0; i < AttachedActors.Num(); i++) {
		AttachedActors[i]->SetActorHiddenInGame(bNewHidden);
		GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::Cyan, AttachedActors[i]->GetName());
	}
	
}

