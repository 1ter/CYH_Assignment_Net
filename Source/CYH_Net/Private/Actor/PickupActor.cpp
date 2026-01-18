// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PickupActor.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Character/CYH_NetCharacter.h"
#include "State/NetPlayerState.h"


APickupActor::APickupActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->InitSphereRadius(20.0f);
	Collision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	Collision->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	InteractionOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Overlap"));
	InteractionOverlap->SetupAttachment(Collision);
	InteractionOverlap->InitSphereRadius(100.0f);
	InteractionOverlap->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionOverlap->SetCollisionObjectType(ECC_WorldDynamic);
	InteractionOverlap->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionOverlap->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InteractionOverlap->SetGenerateOverlapEvents(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(Collision);
	WidgetComponent->SetVisibility(false);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

void APickupActor::BeginPlay()
{
	Super::BeginPlay();

	if (InteractionOverlap)
	{
		InteractionOverlap->OnComponentBeginOverlap.AddDynamic(this, &APickupActor::OnPickupBeginOverlap);
		InteractionOverlap->OnComponentEndOverlap.AddDynamic(this, &APickupActor::OnPickupEndOverlap);
	}

}

void APickupActor::OnPickupBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (!bIsPickedUp)
	{
		if (OtherActor && OtherActor->Implements<UInteractionInterface>())
		{
			IInteractionInterface::Execute_AddInteractionTarget(OtherActor, this);
		}
	}
}

void APickupActor::OnPickupEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!bIsPickedUp)
	{
		if (OtherActor && OtherActor->Implements<UInteractionInterface>())
		{
			IInteractionInterface::Execute_ClearInteractionTarget(OtherActor, this);
		}
	}
}

void APickupActor::OnInteraction_Implementation(AActor* InInteractionActor)
{
	if (!bIsPickedUp)
	{
		if (ACYH_NetCharacter* character = Cast<ACYH_NetCharacter>(InInteractionActor))
		{
			if (ANetPlayerState* netPlayerState = Cast<ANetPlayerState>(character->GetPlayerState()))
			{
				bIsPickedUp = true;

				netPlayerState->AddCount(1);

				Destroy();
			}
		}
	}
}


