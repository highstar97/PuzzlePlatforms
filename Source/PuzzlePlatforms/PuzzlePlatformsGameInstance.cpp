#include "PuzzlePlatformsGameInstance.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("Contsturctor"));
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Warning, TEXT("Init"));
}

void UPuzzlePlatformsGameInstance::Host()
{
	if (!ensure(GEngine != nullptr)) return;
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (!ensure(GEngine != nullptr)) return;
	GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}