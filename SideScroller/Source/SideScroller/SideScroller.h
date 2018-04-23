// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


DECLARE_LOG_CATEGORY_EXTERN(SideScrollerLog, Log, All);

#define CUR_CLASS_LOG (FString(__FUNCTION__).Left(FString(__FUNCTION__).Find(TEXT(":"))))
#define CUR_LINE_LOG (FString::FromInt(__LINE__))
#define CUR_FUNC_LOG (FString(__FUNCTION__).Right(FString(__FUNCTION__).Len() - FString(__FUNCTION__).Find(TEXT("::")) - 2 ))
#define LOG_STACK (CUR_CLASS_LOG + "->" + CUR_FUNC_LOG + "(" + CUR_LINE_LOG + "):")

#define NETMODE_WORLD (((GEngine == nullptr) || (GetWorld() == nullptr)) ? TEXT("") \
        : (GEngine->GetNetMode(GetWorld()) == NM_Client) ? TEXT("[Client] ") \
        : (GEngine->GetNetMode(GetWorld()) == NM_ListenServer) ? TEXT("[ListenServer] ") \
        : (GEngine->GetNetMode(GetWorld()) == NM_DedicatedServer) ? TEXT("[DedicatedServer] ") \
        : TEXT("[Standalone] "))

#if _MSC_VER
#define FUNC_NAME    TEXT(__FUNCTION__)
#else // FIXME - GCC?
#define FUNC_NAME    TEXT(__func__)
#endif

#define TRACE(Format, ...) \
{ \
    SET_WARN_COLOR(COLOR_CYAN);\
    const FString Msg = FString::Printf(TEXT(Format), ##__VA_ARGS__); \
    if (Msg == "") \
    { \
        UE_LOG(SideScrollerLog, Log, TEXT("%s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *GetNameSafe(this));\
    } \
    else \
    { \
        UE_LOG(SideScrollerLog, Log, TEXT("%s%s() : %s"), NETMODE_WORLD, FUNC_NAME, *Msg);\
    } \
    CLEAR_WARN_COLOR();\
}