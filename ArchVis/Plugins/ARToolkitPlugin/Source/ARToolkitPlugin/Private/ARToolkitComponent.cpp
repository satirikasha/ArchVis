//
// Copyright 2015 Adam Horvath - WWW.UNREAL4AR.COM - info@unreal4ar.com - All Rights Reserved.
//

#include "ARToolkitPluginPrivatePCH.h"
#include "ARToolkitComponent.h"

#include "IARToolkitPlugin.h"
#include "ARToolkitDevice.h"



UARToolkitComponent::UARToolkitComponent(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Make sure this component ticks
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;
	bAutoActivate = true;

}



void UARToolkitComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction){
	
	
	IARToolkitPlugin::GetARToolkitDeviceSafe()->UpdateDevice();
	

}


UTexture2D* UARToolkitComponent::GetCameraFrame(){
	return IARToolkitPlugin::GetARToolkitDeviceSafe()->GetWebcamTexture();
}

void UARToolkitComponent::SetDebugMode(bool DebugMode) {
	IARToolkitPlugin::GetARToolkitDeviceSafe()->SetDebugMode(DebugMode);
}

void UARToolkitComponent::SetThresholdMode(EArLabelingThresholdMode mode) {
	IARToolkitPlugin::GetARToolkitDeviceSafe()->SetThresholdMode(mode);
}

void UARToolkitComponent::SetThreshold(uint8 threshold) {
	IARToolkitPlugin::GetARToolkitDeviceSafe()->SetThreshold(threshold);
}

void UARToolkitComponent::GetThreshold(uint8& threshold) {
	threshold = IARToolkitPlugin::GetARToolkitDeviceSafe()->GetThreshold();
}

void UARToolkitComponent::SetFilter(bool enabled, uint8 sampleRate, uint8 cutOffFreq) {
	IARToolkitPlugin::GetARToolkitDeviceSafe()->SetFilter(enabled, sampleRate, cutOffFreq);
}

void UARToolkitComponent::GetFilter(bool& enabled, uint8& sampleRate, uint8& cutOffFreq) {
	IARToolkitPlugin::GetARToolkitDeviceSafe()->GetFilter(enabled, (int&)sampleRate, (int&)cutOffFreq);
}

UMaterialInstanceDynamic* UARToolkitComponent::CreateDynamicMaterialInstance(UStaticMeshComponent* Mesh, UMaterial* SourceMaterial){
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(SourceMaterial, this);
	Mesh->SetMaterial(0, DynamicMaterial);
	return DynamicMaterial;
}

void UARToolkitComponent::SetTextureParameterValue(UMaterialInstanceDynamic* SourceMaterial, UTexture2D* Texture, FName Param){
	SourceMaterial->SetTextureParameterValue(Param, Texture);

}

void UARToolkitComponent::GetCameraPosition(FVector& CameraPosition) {
	CameraPosition = IARToolkitPlugin::GetARToolkitDeviceSafe()->GetCameraPosition();
	
}


void UARToolkitComponent::GetCameraRotation(FRotator& CameraRotation) {
	FRotator Rot = IARToolkitPlugin::GetARToolkitDeviceSafe()->GetCameraRotation();
	

	//Rotation
	FRotator rotTemp;

	rotTemp.Roll = Rot.Roll;
	rotTemp.Pitch = -Rot.Pitch;
	rotTemp.Yaw =  - Rot.Yaw;


	CameraRotation = (FQuat(rotTemp)*FQuat(FRotator(90, 0, -90))).Rotator();
	
	
}

void UARToolkitComponent::GetMarker(uint8 markerId, FVector& Position, FRotator& Rotation, bool& Visible, bool& Primary){
	FMarker* marker=IARToolkitPlugin::GetARToolkitDeviceSafe()->GetMarker(markerId);

	//Position
	Position = marker->position;

	//Rotation
	FRotator rotTemp;
	rotTemp.Yaw = marker->rotation.Yaw;
	rotTemp.Pitch = -marker->rotation.Pitch;
	rotTemp.Roll = 180-marker->rotation.Roll;
	Rotation = rotTemp;

	//Visibility
	Visible = marker->visible;

	//Primary  (controls the camera)
	Primary = marker->primary;

	//Relative to primary marker
	

	//RelativeRot.Roll = RelativeRot.Roll;
	//RelativeRot.Pitch = -RelativeRot.Pitch;
	//RelativeRot.Yaw = -RelativeRot.Yaw;
}

void UARToolkitComponent::GetMarkerNFT(uint8 markerId, FVector& Position, FRotator& Rotation, bool& Visible){
	FMarker* marker = IARToolkitPlugin::GetARToolkitDeviceSafe()->GetMarkerNFT(markerId);

	//Position
	Position = marker->position;

	//Rotation
	FRotator rotTemp;
	rotTemp.Yaw = marker->rotation.Yaw;
	rotTemp.Pitch = -marker->rotation.Pitch;
	rotTemp.Roll = 180 - marker->rotation.Roll;
	Rotation = rotTemp;

	//Visibility
	Visible = marker->visible;
}

void UARToolkitComponent::GetRelativeTransformation(uint8 MarkerID1, uint8 MarkerID2, FVector& RelativePos, FRotator& RelativeRot, bool& result) {
	result = IARToolkitPlugin::GetARToolkitDeviceSafe()->GetRelativeTransformation(MarkerID1, MarkerID2, RelativePos, RelativeRot);

	RelativeRot.Roll = RelativeRot.Roll;
	RelativeRot.Pitch = -RelativeRot.Pitch;
	RelativeRot.Yaw = -RelativeRot.Yaw;
}

void UARToolkitComponent::GetRelativeTransformationNFT(uint8 MarkerID1, uint8 MarkerID_NFT, FVector& RelativePos, FRotator& RelativeRot, bool& result) {
	result = IARToolkitPlugin::GetARToolkitDeviceSafe()->GetRelativeTransformation(MarkerID1, MarkerID_NFT, RelativePos, RelativeRot);

	RelativeRot.Roll = RelativeRot.Roll;
	RelativeRot.Pitch = -RelativeRot.Pitch;
	RelativeRot.Yaw = -RelativeRot.Yaw;
}

bool UARToolkitComponent::Init(bool showPIN, uint8 devNum, int32& WebcamResX, int32& WebcamResY, bool&FirstRunIOS){
	return IARToolkitPlugin::GetARToolkitDeviceSafe()->Init(showPIN, devNum, WebcamResX, WebcamResY, FirstRunIOS);
}

void UARToolkitComponent::Cleanup(){
	IARToolkitPlugin::GetARToolkitDeviceSafe()->Cleanup();
}

void UARToolkitComponent::TogglePause(){
    IARToolkitPlugin::GetARToolkitDeviceSafe()->TogglePause();
}

bool UARToolkitComponent::LoadMarkers(TArray<FString> markers){
	return IARToolkitPlugin::GetARToolkitDeviceSafe()->LoadMarkers(markers);
}

bool UARToolkitComponent::LoadMarkersNFT(TArray<FString> markers){
	return IARToolkitPlugin::GetARToolkitDeviceSafe()->LoadMarkersNFT(markers);
}

void UARToolkitComponent::GetCameraResolution(int32& WebcamResX, int32& WebcamResY) {
	WebcamResX=IARToolkitPlugin::GetARToolkitDeviceSafe()->GetCameraResX();
	WebcamResY = IARToolkitPlugin::GetARToolkitDeviceSafe()->GetCameraResY();
}