/*****************************************************************
 * @file   K2Node_CreateReader.h
 * @brief   This file contains the implementation of a K2 Node dedicated to Create a Morse Reader in Blueprint
 * 
 * @author Nicolas B.
 * @date   March 2024
 * @copyright Nicolas Brugie. All rights reserved.
 *********************************************************************/
#pragma once
#pragma once

#include "CoreMinimal.h"
#include "K2Node.h"

#include "K2Node_CreateReader.generated.h"


UCLASS()
class MORSEBLUEPRINTLIB_API UK2Node_CreateReader : public UK2Node
{
    GENERATED_BODY()

public:
    //~ Begin UEdGraphNode Interface.
    virtual FLinearColor GetNodeTitleColor() const override;
    virtual void AllocateDefaultPins() override;
    virtual void PinDefaultValueChanged(UEdGraphPin* ChangedPin) override;
    //~ End UEdGraphNode Interface.

    //~ Begin UK2Node Interface
    virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
    virtual FText GetMenuCategory() const override;
    virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;
    virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
    //~ End UK2Node Interface
    
    virtual FText GetBaseNodeTitle() const;
    virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const;
    virtual FText GetNodeTitleFormat() const;
    bool IsOutObjectArchetype(UEdGraphPin* InputPin);
    
private : 
    FNodeTextCache CachedNodeTitle;
    UClass* GetProxyClassToSpawn(const TArray<UEdGraphPin*>* InPinsToSearch = NULL) const;
    void CreatePinsForClass(UClass* InClass);
    
    UEdGraphPin* GetOwnerPin() const;
    UEdGraphPin* GetDataTypeClassPin() const;
    UEdGraphPin* GetOutTopicProxyPin() const;
    UEdGraphPin* GetOutReaderPin() const;
    UEdGraphPin* GetSettingsPin() const;
    UEdGraphPin* GetThenPin() const;
    UEdGraphPin* GetBlueprintPin(const TArray<UEdGraphPin*>* InPinsToSearch /*= NULL*/) const;
};