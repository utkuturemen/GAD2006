// Fill out your copyright notice in the Description page of Project Settings.


#include "NetBaseCharacter.h"
#include "NetGameInstance.h"

static UDataTable* SBodyParts = nullptr;

static const wchar_t* BodyPartNames[] =
{
	TEXT("Face"),
	TEXT("Hair"),
	TEXT("Chest"),
	TEXT("Hands"),
	TEXT("Legs"),
	TEXT("Beard"),
	TEXT("EyeBrow")
};

// Sets default values
ANetBaseCharacter::ANetBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PartFace = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Face"));
	PartFace->SetupAttachment(GetMesh());
	PartFace->SetLeaderPoseComponent(GetMesh());

	PartHands = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hands"));
	PartHands->SetupAttachment(GetMesh());
	PartHands->SetLeaderPoseComponent(GetMesh());

	PartLegs = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Legs"));
	PartLegs->SetupAttachment(GetMesh());
	PartLegs->SetLeaderPoseComponent(GetMesh());

	PartHair = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hair"));
	PartHair->SetupAttachment(PartFace, FName("headSocket"));

	PartBeard = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Beard"));
	PartBeard->SetupAttachment(PartFace, FName("headSocket"));
	
	PartEyeBrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EyeBrow"));
	PartEyeBrow->SetupAttachment(PartFace, FName("headSocket"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SK_Eyes(TEXT("StaticMesh'/Game/StylizedModularChar/Meshes/SM_Eyes.SM_Eyes'"));

	PartEyes = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Eyes"));
	PartEyes->SetupAttachment(PartFace, FName("headSocket"));
	PartEyes->SetStaticMesh(SK_Eyes.Object);

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_BodyParts(TEXT("DataTable'/Game/Blueprints/DT_BodyParts.DT_BodyParts'"));

	SBodyParts = DT_BodyParts.Object;
	
}

// Called when the game starts or when spawned
void ANetBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled())
	{
		UNetGameInstance* Instance = Cast<UNetGameInstance>(GWorld->GetGameInstance());
		if (Instance && Instance->PlayerInfo.Ready)
		{
			SubmitPlayerInfoToServer(Instance->PlayerInfo);

		}
	}
	
}

void ANetBaseCharacter::OnConstruction(const FTransform& Transform)
{
	UpdateBodyParts();
}

void ANetBaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANetBaseCharacter, PartSelection);
}

// Called every frame
void ANetBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANetBaseCharacter::ChangeBodyPart(EBodyPart index, int value, bool DirectSet)
{
	FSMeshAssetList* List = GetBodyPartList(index, PartSelection.isFemale);
	if (List == nullptr)return;

	int CurrentIndex = PartSelection.Indices[(int)index];

	if (DirectSet){
		CurrentIndex = value;
	}else{
		CurrentIndex += value;
	}

	int Num = List->ListSkeletal.Num() + List->ListStatic.Num();

	if (CurrentIndex < 0) CurrentIndex += Num;
	else CurrentIndex %= Num;

	PartSelection.Indices[(int)index] = CurrentIndex;

	switch (index)
	{
	case EBodyPart::BP_Face:PartFace->SetSkeletalMeshAsset(List->ListSkeletal[CurrentIndex]);break;

	case EBodyPart::BP_Hair:PartHair->SetStaticMesh(List->ListStatic[CurrentIndex]);break;

	case EBodyPart::BP_Chest:GetMesh()->SetSkeletalMeshAsset(List->ListSkeletal[CurrentIndex]);break;

	case EBodyPart::BP_Hands:PartHands->SetSkeletalMeshAsset(List->ListSkeletal[CurrentIndex]);break;

	case EBodyPart::BP_Legs:PartLegs->SetSkeletalMeshAsset(List->ListSkeletal[CurrentIndex]);break;

	case EBodyPart::BP_Beard:PartBeard->SetStaticMesh(List->ListStatic[CurrentIndex]);break;
		
	case EBodyPart::BP_EyeBrow:PartEyeBrow->SetStaticMesh(List->ListStatic[CurrentIndex]);break;

	}
	
	
}

void ANetBaseCharacter::ChangeGender(bool isFemale)
{
	PartSelection.isFemale = isFemale;
	UpdateBodyParts();
}

void ANetBaseCharacter::SubmitPlayerInfoToServer_Implementation(FSPlayerInfo Info)
{
	PartSelection = Info.BodyParts;
	if (HasAuthority())
	{
		OnRep_PlayerInfoChanged();
	}
}

void ANetBaseCharacter::OnRep_PlayerInfoChanged()
{
	UpdateBodyParts();
}

FSMeshAssetList* ANetBaseCharacter::GetBodyPartList(EBodyPart part, bool isFemale)
{
	FString Name = FString::Printf(TEXT("%s%s"), isFemale ? TEXT("Female") : TEXT("Male"), BodyPartNames[(int)part]);
	
	return SBodyParts ? SBodyParts->FindRow<FSMeshAssetList>(*Name, nullptr): nullptr;
}

void ANetBaseCharacter::UpdateBodyParts()
{
	ChangeBodyPart(EBodyPart::BP_Face, 0, false);
	ChangeBodyPart(EBodyPart::BP_Beard, 0, false);
	ChangeBodyPart(EBodyPart::BP_Chest, 0, false);
	ChangeBodyPart(EBodyPart::BP_Hair, 0, false);
	ChangeBodyPart(EBodyPart::BP_Hands, 0, false);
	ChangeBodyPart(EBodyPart::BP_Legs, 0, false);
	ChangeBodyPart(EBodyPart::BP_EyeBrow, 0, false);

}

// Called to bind functionality to input
void ANetBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}