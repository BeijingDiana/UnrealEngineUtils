﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMComponent.h"
#include "Components/ActorComponent.h"
#include "TagMessageFSM.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FLATLINE_API UTagMessageFSM : public UFSMComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTagMessageFSM();

	void ExecuteAddedInnerFuncIfTagValid(FGameplayTag InnerTag);
	void ExecuteRemovedInnerFuncIfTagValid(FGameplayTag InnerTag);

	void ExecuteAddedOuterFuncIfTagValid(FGameplayTag OuterTag);
	void ExecuteRemovedOuterFuncIfTagValid(FGameplayTag OuterTag);

private:
	void CallAddedOuterTagFunc(FGameplayTag AddedOuterTag);
	void CallRemovedOuterTagFunc(FGameplayTag RemovedOuterTag);

	void CallAddedInnerTagFunc(FGameplayTag AddedInnerTag);
	void CallRemovedInnerTagFunc(FGameplayTag RemovedInnerTag);

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OnReceiveOuterTagAdded(FGameplayTag OuterTagAdded);
	void OnReceiveOuterTagRemoved(FGameplayTag OuterTagRemoved);
	
	void OnReceiveInnerTagAdded(FGameplayTag InnerTagAdded);
	void OnReceiveInnerTagRemoved(FGameplayTag InnerTagRemoved);

	void BindOuterTagAddedFunction(FGameplayTag AddedOuterTag, TFunction<void()> TargetFunc);
	//Bind a Function call on OuterTagAdded

	void BindOuterTagRemovedFunction(FGameplayTag RemovedOuterTag, TFunction<void()> TargetFunc);
	//Bind a Function call on OuterTagRemoved

	void BindInnerTagAddedFunction(FGameplayTag AddedInnerTag, TFunction<void()> TargetFunc);

	void BindInnerTagRemovedFunction(FGameplayTag RemovedInnerTag, TFunction<void()> TargetFunc);

	

private:

	
	TMap<FGameplayTag,TFunction<void()>> AddedOuterTagFunctionMap;

	
	
	TMap<FGameplayTag,TFunction<void()>> RemovedOuterTagFunctionMap;

	
	
	TMap<FGameplayTag,TFunction<void()>> AddedInnerTagFunctionMap;
	

	
	TMap<FGameplayTag,TFunction<void()>> RemovedInnerTagFunctionMap;
public:
	FGameplayTag SampleOuterTag;
	FGameplayTag SampleInnerTag;
	
	bool IsOuterTag(FGameplayTag TagToCheck) const
	{
		return TagToCheck.RequestDirectParent().MatchesTagExact(SampleOuterTag.RequestDirectParent());
	}

	bool IsInnerTag(FGameplayTag TagToCheck) const
	{
		return TagToCheck.RequestDirectParent().MatchesTagExact(SampleInnerTag.RequestDirectParent());
	}

};