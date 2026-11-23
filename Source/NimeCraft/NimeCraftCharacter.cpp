// Copyright Epic Games, Inc. All Rights Reserved.

#include "NimeCraftCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "NimeCraft.h"

ANimeCraftCharacter::ANimeCraftCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ANimeCraftCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ANimeCraftCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ANimeCraftCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANimeCraftCharacter::Look);

		//Mining
		EnhancedInputComponent->BindAction(MineAction, ETriggerEvent::Started, this, &ANimeCraftCharacter::DoMineStart);
		EnhancedInputComponent->BindAction(MineAction, ETriggerEvent::Completed, this, &ANimeCraftCharacter::DoMineEnd);
	}
	else
	{
		UE_LOG(LogNimeCraft, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ANimeCraftCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ANimeCraftCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ANimeCraftCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ANimeCraftCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ANimeCraftCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ANimeCraftCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void ANimeCraftCharacter::DoMineStart()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Black, FString::Printf(TEXT("Mining!")));

	TraceForward();
}

void ANimeCraftCharacter::DoMineEnd()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(4, 5.f, FColor::Magenta, FString::Printf(TEXT("Mining Ended")));
}

void ANimeCraftCharacter::TraceForward()
{
	FVector PlayerLocation;
	FRotator PlayerRotation;

	GetController()->GetPlayerViewPoint(PlayerLocation, PlayerRotation);

	FVector LineTraceStart = PlayerLocation;
	FVector LineTraceEnd = LineTraceStart + (PlayerRotation.Vector() * 500);
	FHitResult HitByLineTrace;
	FCollisionQueryParams LineTraceParams;
	bool bHit;

	bHit = GetWorld()->LineTraceSingleByChannel(HitByLineTrace, LineTraceStart, LineTraceEnd, ECC_Visibility, LineTraceParams);

	DrawDebugLine(GetWorld(), LineTraceStart, LineTraceEnd, FColor::Red, false, 2.0f);

	if (bHit)
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(5, 2.0f, FColor::Red, FString::Printf(TEXT("You hit %s"), 
			*HitByLineTrace.GetActor()->GetName()));

		DrawDebugBox(GetWorld(), HitByLineTrace.ImpactPoint, FVector(5.f, 5.f, 5.f), FColor::Red, false, 2.0f);

		if (HitByLineTrace.GetActor()->GetClass()->ImplementsInterface(UIInteractionInterface::StaticClass()))
		{
			Cast<IIInteractionInterface>(HitByLineTrace.GetActor())->PlayerInteract();
		}
	}


}
