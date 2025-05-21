// Fill out your copyright notice in the Description page of Project Settings.


#include "SurveyDataLibrary.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Misc/FileHelper.h"

const FString surveyLog = "survey_log.txt";

int USurveyDataLibrary::CopyToClipboard() {
    const FString filePath = FPaths::ProjectSavedDir() / surveyLog;

    if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*filePath)) {
        return 0;
    }

    FString surveyData;

    if (!FFileHelper::LoadFileToString(surveyData, *filePath)) {
        return 0;
    }

    FPlatformApplicationMisc::ClipboardCopy(*surveyData);
    return 1;
}

void USurveyDataLibrary::LogVPLLevel(FString level, FString attempts, FString time, FString score) {
    const FString filePath = FPaths::ProjectSavedDir() / surveyLog;
    
    FString surveyData;

    if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*filePath)) {
       FFileHelper::LoadFileToString(surveyData, *filePath);
    } else {
        surveyData = "Levels:\n--//--------//--\nCompilation Errors:\n";
    }

    FString levels, errors;
    surveyData.Split(TEXT("--//--------//--"), &levels, &errors);
    levels += "- Level " + level + " Completed (" + time + " - " + score + " stars, " + attempts + " attempts)\n---//--------//--";
    surveyData = levels + errors;

    FFileHelper::SaveStringToFile(surveyData, *filePath);
}

void USurveyDataLibrary::LogJavaLevel(FString level, FString timesCompiled, FString timesRan, FString time, FString score) {
    const FString filePath = FPaths::ProjectSavedDir() / surveyLog;
    
    FString surveyData;

    if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*filePath)) {
       FFileHelper::LoadFileToString(surveyData, *filePath);
    } else {
        surveyData = "Levels:\n--//--------//--\nCompilation Errors:\n";
    }

    FString levels, errors;
    surveyData.Split(TEXT("--//--------//--"), &levels, &errors);
    levels += "- Level " + level + " Completed (" + time + " - " + score + " stars, compiled " + timesCompiled + " times and ran " + timesRan + " times)\n--//--------//--";
    surveyData = levels + errors;

    FFileHelper::SaveStringToFile(surveyData, *filePath);
}

void USurveyDataLibrary::LogCompilationError(FString errorType, FString level, FString error) {
    const FString filePath = FPaths::ProjectSavedDir() / surveyLog;
    
    FString surveyData;

    if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*filePath)) {
       FFileHelper::LoadFileToString(surveyData, *filePath);
    } else {
        surveyData = "Levels:\n--//--------//--\nCompilation Errors:\n";
    }

    FString levels, errors;
    surveyData.Split(TEXT("--//--------//--"), &levels, &errors);
    levels += "--//--------//--";
    errors += " - " + errorType + " - Level " + level + " (" + error + ")\n";
    surveyData = levels + errors;

    FFileHelper::SaveStringToFile(surveyData, *filePath);
}
