// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/CYH_NetCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "State/NetPlayerState.h"
#include "Components/WidgetComponent.h"
#include "Widget/UI_NameTag.h"
#include "Actor/PickupActor.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACYH_NetCharacter

ACYH_NetCharacter::ACYH_NetCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	NameWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NamePlate"));
	NameWidgetComponent->SetupAttachment(GetRootComponent());
	NameWidgetComponent->SetRelativeLocation(FVector::UpVector * 100.0f);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ACYH_NetCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (NameWidgetComponent)
	{
		if (UUI_NameTag* nameTag = Cast<UUI_NameTag>(NameWidgetComponent->GetUserWidgetObject()))
		{
			if (ANetPlayerState* playerState = GetPlayerState<ANetPlayerState>())
			{
				nameTag->UpdateName(playerState->GetMyName());
			}
		}
	}
}

void ACYH_NetCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (NameWidgetComponent)
	{
		if (APlayerController* pc = GetWorld()->GetFirstPlayerController())
		{
			FVector cameraFoward = pc->PlayerCameraManager->GetCameraRotation().Vector();
			FVector widgetFoward = cameraFoward * -1;
			NameWidgetComponent->SetWorldRotation(widgetFoward.Rotation());
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACYH_NetCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	if (!IsLocallyControlled()) { return; }

	UE_LOG(LogTemp, Warning, TEXT("스테이트 타이밍 변경 : %s"), *GetNameSafe(GetPlayerState()));

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACYH_NetCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACYH_NetCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACYH_NetCharacter::Look);

		EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &ACYH_NetCharacter::OnTryInteraction);
		EnhancedInputComponent->BindAction(IA_Cursor, ETriggerEvent::Started, this, &ACYH_NetCharacter::OnCursor);

	}
}

void ACYH_NetCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACYH_NetCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACYH_NetCharacter::OnCursor()
{
	APlayerController* playerController = Cast<APlayerController>(GetController());

	bCursorOn = !bCursorOn;
	playerController->bShowMouseCursor = bCursorOn;

	if (bCursorOn)
	{
		playerController->SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		playerController->SetInputMode(FInputModeGameOnly());
	}
}

void ACYH_NetCharacter::UpdateNameTag(const FString& InName)
{
	if (NameWidgetComponent)
	{
		if (UUI_NameTag* nametag = Cast<UUI_NameTag>(NameWidgetComponent->GetUserWidgetObject()))
		{
			nametag->UpdateName(InName);
		}
	}
}

void ACYH_NetCharacter::OnTryInteraction(const FInputActionValue& Value)
{
	Execute_TryInteraction(this);
}

void ACYH_NetCharacter::Server_AddCount_Implementation(int32 InCount)
{
	if (ANetPlayerState* playerState = GetPlayerState<ANetPlayerState>())
	{
		playerState->AddCount(InCount);
	}
}

void ACYH_NetCharacter::Server_SetPlayerName_Implementation(const FString& InName)
{
	if (ANetPlayerState* playerState = GetPlayerState<ANetPlayerState>())
	{
		playerState->SetMyName(InName);
	}
}

void ACYH_NetCharacter::Server_TryInteract_Implementation(AActor* InInteractionActor)
{
	if (InInteractionActor)
	{
		if (InInteractionActor->Implements<UInteractionInterface>())
		{
			IInteractionInterface::Execute_OnInteraction(InInteractionActor, this);
		}
	}
}

void ACYH_NetCharacter::AddInteractionTarget_Implementation(AActor* InTarget)
{
	if (InTarget)
	{
		if (InTarget->Implements<UInteractionInterface>())
		{
			InteractionTargets.AddUnique(InTarget);
		}

		if (IsLocallyControlled())
		{
			if (APickupActor* pickupActor = Cast<APickupActor>(InTarget))
			{
				pickupActor->GetWidgetComponent()->SetVisibility(true);
			}
		}
	}
}

void ACYH_NetCharacter::ClearInteractionTarget_Implementation(AActor* InTarget)
{
	if (InTarget)
	{
		if (InTarget->Implements<UInteractionInterface>())
		{
			InteractionTargets.RemoveSingle(InTarget);
		}

		if (IsLocallyControlled())
		{
			if (APickupActor* pickupActor = Cast<APickupActor>(InTarget))
			{
				pickupActor->GetWidgetComponent()->SetVisibility(false);
			}
		}
	}
}

void ACYH_NetCharacter::TryInteraction_Implementation()
{
	if (IsLocallyControlled())
	{
		FVector start = GetActorLocation() + FVector(0, 0, 0.f);
		FVector forward = GetActorForwardVector();
		FVector end = start + (forward * Distance);

		FHitResult hit;
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);

		DrawDebugLine(GetWorld(), start, end, FColor::Green, false, 2.f);

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			hit,
			start,
			end,
			ECC_Visibility,
			params
		);

		if (bHit)
		{
			if (AActor* target = hit.GetActor())
			{
				if (target->Implements<UInteractionInterface>())
				{
					if (InteractionTargets.Contains(target))
					{
						Server_TryInteract(target);
					}
				}
			}
		}

	}
}

