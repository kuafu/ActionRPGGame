// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tasks/GAAbilityTask.h"
#include "GAAbilityTask_TargetData.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGASOnReceiveTargetData, const FHitResult&, HitResult);

UENUM()
enum class EGASConfirmType : uint8
{
	Instant,
	WaitForConfirm
};


/**
 * 
 */
UCLASS()
class GAMEABILITIES_API UGAAbilityTask_TargetData : public UGAAbilityTask, public FTickableGameObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
		FGASOnReceiveTargetData OnConfirmed;
	UPROPERTY(BlueprintAssignable)
		FGASOnReceiveTargetData OnReceiveTargetData;

	UPROPERTY()
	class UGASAbilityTargetingObject* TargetObj;

	EGASConfirmType ConfirmType;

	float Range;
	bool bIsTickable;
	bool bDrawDebug;
	bool bDrawCorrectedDebug;
	bool bUseCorrectedTrace;
public:
	UFUNCTION(BlueprintCallable, meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", BlueprintInternalUseOnly = "true"), Category = "Game Abilities | Tasks")
		static UGAAbilityTask_TargetData* CreateTargetDataTask(UObject* WorldContextObject, 
			bool bDrawDebug,
			bool bDrawCorrectedDebug,
			bool bUseCorrectedTrace,
			EGASConfirmType ConfirmTypeIn,
			float Range);

	virtual void Activate() override;

	UFUNCTION()
		void OnConfirm();

	UFUNCTION()
		void OnCastEndedConfirm();

	/* FTickableGameObject Begin */
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return bIsTickable; }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UGAAbilityTask_TargetData, STATGROUP_Tickables); };
	/* FTickableGameObject End */

protected:
	FHitResult LineTrace();
};
