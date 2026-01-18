// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Interface/InteractionInterface.h"
#include "CYH_NetCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
class UInputMappingContext;
class UInputAction;
class UUI_NameTag;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ACYH_NetCharacter : public ACharacter, public IInteractionInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	ACYH_NetCharacter();
	
	UFUNCTION(Server, Reliable)
	void Server_AddCount(int32 InCount);

	UFUNCTION(Server, Reliable)
	void Server_SetPlayerName(const FString& InName);

	UFUNCTION(Server, Reliable)
	void Server_TryInteract(AActor* InInteractionActor);

	virtual void AddInteractionTarget_Implementation(AActor* InTarget) override;
	virtual void ClearInteractionTarget_Implementation(AActor* InTarget) override;
	virtual void TryInteraction_Implementation() override;

	void UpdateNameTag(const FString& InName);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	void OnTryInteraction(const FInputActionValue& Value);
			
protected:
	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> NameWidgetComponent = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> IA_Interact = nullptr;

	UPROPERTY(EditAnywhere)
	float Distance = 200.0f;

private:
	TArray<TWeakObjectPtr<AActor>> InteractionTargets;
};

