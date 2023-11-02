// Fill out your copyright notice in the Description page of Project Settings.


#include "COAAvatar.h"

ACOAAvatar::ACOAAvatar() :
Stamina(0.0f),
MaxStamina(100.0f),
StaminaGainRate(5.0f), 
StaminaDrainRate(25.0f),
RunSpeed(500.0f)
{
	

	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	SpringArm->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = false;
	bUseControllerRotationYaw = false;
}



void ACOAAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent ->BindAxis("Turn",this,&ACharacter::AddControllerYawInput);
	PlayerInputComponent ->BindAxis("Lookup",this,&ACharacter::AddControllerPitchInput);

	PlayerInputComponent ->BindAxis("MoveForward",this,&ACOAAvatar::MoveForward);
	PlayerInputComponent ->BindAxis("MoveRight",this,&ACOAAvatar::MoveRight);
	
	PlayerInputComponent ->BindAction("Run",IE_Pressed,this, &ACOAAvatar::RunPressed);
	PlayerInputComponent ->BindAction("Run",IE_Released,this, &ACOAAvatar::RunRealesed);
	
}

void ACOAAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Super::Tick(DeltaTime);
	

	Health = FMath::Min(MaxHealth, Health + HealingRate * DeltaTime);
	
	/* if (IsRunning)
	{
		if (Stamina <= 0)
		{
			StaminaDrained = true;
			RunRealesed();
		}
		else
		{
			Stamina -= StaminaDrainRate * DeltaTime;
		}
	}
	else if(StaminaDrained == true && GetCharacterMovement()->MovementMode != EMovementMode::MOVE_Walking)
	{
		Stamina += StaminaGainRate * DeltaTime;
	}


	if (Stamina >= MaxStamina)
	{
		StaminaDrained = false;
		Stamina = MaxStamina;
	}
	else if(!IsRunning && Stamina <= MaxStamina)
	{
		Stamina += StaminaGainRate * DeltaTime;
	}

	 */


	if (GetCharacterMovement()->MovementMode ==MOVE_Walking)
	{
		if (!StaminaDrained&&IsRunning) 
		{
			if (!GetCharacterMovement() ->Velocity.IsNearlyZero(0.01f))
			{
				Stamina=FMath::Max(0.0f,Stamina-StaminaDrainRate*DeltaTime);
				if (Stamina==0.0f)
				{
					StaminaDrained=true;
					UpdateMovementParams();
				}
			}
			
		}	else{
			Stamina=FMath::Min(MaxStamina,Stamina + StaminaGainRate * DeltaTime);
			if (Stamina >= MaxStamina)
			{
				StaminaDrained=false;
				UpdateMovementParams();
			}
		}
	}
	GEngine -> AddOnScreenDebugMessage(0, 1.0f, FColor::Yellow,
		FString::Printf(TEXT("%f"), Stamina));
	
}

void ACOAAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACOAAvatar::OnConstruction(const FTransform& Transform)
{
	Stamina = MaxStamina;
	IsRunning=false;
}

void ACOAAvatar::MoveForward(float Amount)
{
	FRotator ControlRotation = GetControlRotation();
	
	FVector ForwardDirection=FRotationMatrix(FRotator(0.0f,ControlRotation.Yaw,0.0f))
	.GetUnitAxis(EAxis::X);

	AddMovementInput(ForwardDirection,Amount);
}

void ACOAAvatar::MoveRight(float Amount)
{
	FRotator ControlRotation = GetControlRotation();
	
	FVector RightDirection = FRotationMatrix(FRotator(0.0f,ControlRotation.Yaw,0.0f))
	.GetUnitAxis(EAxis::Y);

	AddMovementInput(RightDirection,Amount);
}

void ACOAAvatar::RunPressed()
{
		IsRunning = true;
		UpdateMovementParams();
	
}

void ACOAAvatar::RunRealesed()
{
	
	IsRunning = false;
	UpdateMovementParams();
}

void ACOAAvatar::UpdateMovementParams()
{
	GetCharacterMovement()->MaxWalkSpeed =
		IsRunning && !StaminaDrained ? RunSpeed : WalkSpeed;
}

void ACOAAvatar::SetStamina(float NewStamina)
{
	Stamina = NewStamina;
}

float ACOAAvatar::GetStamina()
{
	return Stamina;
}
