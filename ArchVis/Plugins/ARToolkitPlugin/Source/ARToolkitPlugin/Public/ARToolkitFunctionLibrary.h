//
// Copyright 2015 Adam Horvath - WWW.UNREAL4AR.COM - info@unreal4ar.com - All Rights Reserved.
//

#pragma once
#include "ARToolkitFunctionLibrary.generated.h"

UENUM(BlueprintType)		
enum class EArLabelingThresholdMode : uint8
{
	MANUAL UMETA(DisplayName = "Manual"),
	AUTO_MEDIAN UMETA(DisplayName = "Auto Median"),
	AUTO_OTSU UMETA(DisplayName = "Auto Otsu"),
	AUTO_ADAPTIVE UMETA(DisplayName = "Auto Adaptive"),
	AUTO_BRACKETING UMETA(DisplayName = "Auto Bracketing")
};


USTRUCT()
struct FMarker {

	GENERATED_USTRUCT_BODY()
	//Tracking data

	UPROPERTY()
	FName				   name;

	UPROPERTY()
	FVector				   position;

	UPROPERTY()
	FRotator			   rotation;

	UPROPERTY()
	FVector				   relativePosition;

	UPROPERTY()
	FRotator			   relativeRotation;

	UPROPERTY()
	bool				   visible;

	UPROPERTY()
	bool				   primary;

	ARdouble			   matrix[3][4];
	
	//For NFT only
	int					    pageNo;
	
	ARFilterTransMatInfo*	ftmi;
	ARdouble				filterCutoffFrequency;
	ARdouble				filterSampleRate;

	bool				    valid;
	bool				    validPrev;

	bool					resetFilter;
};




