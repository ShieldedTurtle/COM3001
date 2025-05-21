// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "JavaCodeCompilerLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FYP_API UJavaCodeCompilerLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Compile Java", Category = "Custom Java Code"))
		static FString CompileCode(FString fileName, FString code, FString testCode);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Test Java", Category = "Custom Java Code"))
		static FString TestCode();
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Compile Character", Category = "Custom Java Code"))
		static void CompileCharacter(FString code);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Run Character Java", Category = "Custom Java Code"))
		static FString RunCode(FString levelName);
};
