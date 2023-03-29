#include "dVersionGameModeBase.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"

AdVersionGameModeBase::AdVersionGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
}