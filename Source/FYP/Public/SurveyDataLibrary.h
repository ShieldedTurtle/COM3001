// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SurveyDataLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API USurveyDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Copy Survey Data to Clipboard", Category = "Survey Data"))
		static int CopyToClipboard();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Log data for a VPL level", Category = "Survey Data"))
		static void LogVPLLevel(FString level, FString attempts, FString time, FString score);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Log data for a Java level", Category = "Survey Data"))
		static void LogJavaLevel(FString level, FString timesCompiled, FString timesRan, FString time, FString score);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Log a compiler error", Category = "Survey Data"))
		static void LogCompilationError(FString errorType, FString level, FString error);
};
