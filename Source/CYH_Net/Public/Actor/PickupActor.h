// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/InteractionInterface.h"
#include "PickupActor.generated.h"

class USphereComponent;
class USkeletalMeshComponent;
class UWidgetComponent;

UCLASS()
class CYH_NET_API APickupActor : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	APickupActor();

public:
	virtual void OnInteraction_Implementation(AActor* InInteractionActor) override;

	inline UWidgetComponent* GetWidgetComponent() { return WidgetComponent; }

private:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPickupBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnPickupEndOverlap(
		UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);



protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> Collision = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> InteractionOverlap = nullptr;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> Mesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent = nullptr;

private:
	bool bIsPickedUp = false;
};
