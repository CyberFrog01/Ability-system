// Copyright CyberFrog


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/MouseoverInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);

	if (!CursorHit.bBlockingHit) return;

	LastActor = CurrentActor;
	CurrentActor = CursorHit.GetActor();

	/**
	 * Line trace from curser. Scenaries:
	 * A. Last - null && Current - null
	 *	- Do nothing
	 * B. Last - null && Current - valid
	 *	- Current - highlight
	 * C. Last - valid && Current - null
	 *  - Last - unhighlight
	 * D. Last - valid && Current - valid && Last == Current
	 *	- Do nothing
	 * E. Last - valid && Current - valid && Last != Current
	 *	- Current - highlight
	 *  - Last - unhighlight
	 * 
	 */

	if (LastActor == nullptr)
	{
		//Case A
		if (CurrentActor == nullptr)
		{
			//Do nothing
		}
		//Case B
		else
		{
			CurrentActor->HighlightActor();
		}
	}
	else
	{
		//Case C
		if (CurrentActor == nullptr)
		{
			LastActor->UnHighlightActor();
		}
		else 
		{
			//Case D
			if (CurrentActor == LastActor)
			{
				//Do nothing
			}
			//Case E
			else
			{
				CurrentActor->HighlightActor();
				LastActor->UnHighlightActor();
			}
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(PlayerContext);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(PlayerContext, 0);	
	};

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAbilityAction(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld)
	
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	
}
