//
// Copyright 2015 Adam Horvath - WWW.UNREAL4AR.COM - info@unreal4ar.com - All Rights Reserved.
//

#include "ARToolkitPluginPrivatePCH.h"
#include "IARToolkitPlugin.h"
#include "ARToolkitDevice.h"


class FARToolkitPlugin : public IARToolkitPlugin
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FARToolkitPlugin, ARToolkitPlugin )

void FARToolkitPlugin::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	// Attempt to create the device, and start it up.  Caches a pointer to the device if it successfully initializes
	TSharedPtr<FARToolkitDevice> ARToolkitStartup(new FARToolkitDevice);
	if (ARToolkitStartup->StartupDevice())
	{
		ARToolkitDevice = ARToolkitStartup;
	}
	//TODO: error handling	if dll cannot be loaded  

}


void FARToolkitPlugin::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	if (ARToolkitDevice.IsValid())
	{
		ARToolkitDevice->ShutdownDevice();
		ARToolkitDevice = nullptr;
	}
	
}



