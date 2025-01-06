#include "K2Node_CreateReader.h"
#include "Topic/DDSTopic.h"
#include "Topic/TopicProxy.h"
#include "Topic/DDSReader.h"
#include "API/MorseBlueprintLib.h"
#include "Core/MorseEngineSubsystem.h"
#include <Kismet2/BlueprintEditorUtils.h>
#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "KismetCompiler.h"
#include "K2Node_CallFunction.h"

#define LOCTEXT_NAMESPACE "K2_Node_Reader"

struct FReaderGetPinName
{
    static const FName& GetOwnerValuePinName()
    {
        static const FName TargetPinName(TEXT("Owner"));
        return TargetPinName;
    };

    static const FName& GetTopicSettingsPinName()
    {
        static const FName Name(TEXT("Settings"));
        return Name;
    };

    static const FName& GetOutReaderPinName()
    {
        static const FName NewValuePinName(TEXT("Reader"));
        return NewValuePinName;
    };

    static const FName& GetOutTopicProxy()
    {
        static const FName NewValuePinName(TEXT("TopicProxy"));
        return NewValuePinName;
    };

    static const FName& GetDataTypeClassPinName()
    {
        static const FName NewValuePinName(TEXT("DataType"));
        return NewValuePinName;
    };
};


FLinearColor UK2Node_CreateReader::GetNodeTitleColor() const
{
	return FLinearColor(0, 0, 255, 0);
};


FText UK2Node_CreateReader::GetMenuCategory() const
{
    return FText::FromString("Morse API");
};


void UK2Node_CreateReader::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    UClass* ActionKey = GetClass();
    if (ActionRegistrar.IsOpenForRegistration(ActionKey))
    {
        UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
        check(NodeSpawner);

        ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
    }
};

void UK2Node_CreateReader::AllocateDefaultPins()
{
    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();
    
    //Exec
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

    //Inputs
    UEdGraphNode::FCreatePinParams PinParams;
    PinParams.bIsReference = true;
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Object, UObject::StaticClass(), FReaderGetPinName::GetOwnerValuePinName(), PinParams);
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, FTopicDescription::StaticStruct(), FReaderGetPinName::GetTopicSettingsPinName());
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Class, UTopicProxy::StaticClass(), FReaderGetPinName::GetDataTypeClassPinName());

    //Output
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Object, UTopicProxy::StaticClass(), FReaderGetPinName::GetOutTopicProxy());
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Object, UDDSReader::StaticClass(), FReaderGetPinName::GetOutReaderPinName());

    Super::AllocateDefaultPins();
};

UClass* UK2Node_CreateReader::GetProxyClassToSpawn(const TArray<UEdGraphPin*>* InPinsToSearch) const
{
    UClass* UseSpawnClass = nullptr;
    const TArray<UEdGraphPin*>* PinsToSearch = InPinsToSearch ? InPinsToSearch : &Pins;
    
    UEdGraphPin* ClassPin = GetBlueprintPin(PinsToSearch);
    if (ClassPin && ClassPin->DefaultObject && ClassPin->LinkedTo.Num() == 0)
    {
        UseSpawnClass = CastChecked<UClass>(ClassPin->DefaultObject);
    }
    else if (ClassPin && ClassPin->LinkedTo.Num())
    {
        UEdGraphPin* ClassSource = ClassPin->LinkedTo[0];
        UseSpawnClass = ClassSource ? Cast<UClass>(ClassSource->PinType.PinSubCategoryObject.Get()) : nullptr;
    }
    
    return UseSpawnClass;
}

void UK2Node_CreateReader::CreatePinsForClass(UClass* InClass)
{
    check(InClass != NULL);

    const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

    for (TFieldIterator<FProperty> PropertyIt(InClass, EFieldIteratorFlags::IncludeSuper); PropertyIt; ++PropertyIt)
    {
        FProperty* Property = *PropertyIt;
        UClass* PropertyClass = CastChecked<UClass>(Property->GetOwner<UObject>());
        const bool bIsDelegate = Property->IsA(FMulticastDelegateProperty::StaticClass());
        const bool bIsExposedToSpawn = UEdGraphSchema_K2::IsPropertyExposedOnSpawn(Property);
        const bool bIsSettableExternally = !Property->HasAnyPropertyFlags(CPF_DisableEditOnInstance);

        if (!bIsDelegate)
        {
            UEdGraphPin* Pin = CreatePin(EGPD_Input, NAME_None, Property->GetFName());
            const bool bPinGood = (Pin != nullptr) && K2Schema->ConvertPropertyToPinType(Property, /*out*/ Pin->PinType);

            // Copy tooltip from the property.
            if (Pin != nullptr)
            {
                K2Schema->ConstructBasicPinTooltip(*Pin, Property->GetToolTipText(), Pin->PinToolTip);
            }
        }
    }

    // Change class of output pin
    UEdGraphPin* ResultPin = GetOutTopicProxyPin();
    ResultPin->PinType.PinSubCategoryObject = InClass;
};

FText UK2Node_CreateReader::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    if (TitleType == ENodeTitleType::ListView || TitleType == ENodeTitleType::MenuTitle)
    {
        return GetBaseNodeTitle();
    }
    else if (UClass* ClassToSpawn = GetProxyClassToSpawn())
    {
        if (CachedNodeTitle.IsOutOfDate(this))
        {
            FFormatNamedArguments Args;
            Args.Add(TEXT("ClassName"), ClassToSpawn->GetDisplayNameText());
            // FText::Format() is slow, so we cache this to save on performance
            CachedNodeTitle.SetCachedText(FText::Format(GetNodeTitleFormat(), Args), this);
        }
        
        return CachedNodeTitle;
    }
    
    return GetBaseNodeTitle();
}
FText UK2Node_CreateReader::GetNodeTitleFormat() const
{
    return NSLOCTEXT("K2Node", "Construct", "Create Reader {ClassName}");
}

bool UK2Node_CreateReader::IsOutObjectArchetype(UEdGraphPin* InputPin)
{
    if (GetDataTypeClassPin() == InputPin)
        return true;
    return false;
};

UEdGraphPin* UK2Node_CreateReader::GetOwnerPin() const
{
    UEdGraphPin* Pin = FindPin(FReaderGetPinName::GetOwnerValuePinName());
    check(Pin == NULL || Pin->Direction == EGPD_Input);
    return Pin;
};

UEdGraphPin* UK2Node_CreateReader::GetDataTypeClassPin() const
{
    UEdGraphPin* Pin = FindPin(FReaderGetPinName::GetDataTypeClassPinName());
    check(Pin == NULL || Pin->Direction == EGPD_Input);
    return Pin;
};

UEdGraphPin* UK2Node_CreateReader::GetOutTopicProxyPin() const
{
    UEdGraphPin* Pin = FindPin(FReaderGetPinName::GetOutTopicProxy());
    check(Pin == NULL || Pin->Direction == EGPD_Output);
    return Pin;
}
UEdGraphPin* UK2Node_CreateReader::GetOutReaderPin() const
{
    UEdGraphPin* Pin = FindPin(FReaderGetPinName::GetOutReaderPinName());
    check(Pin == NULL || Pin->Direction == EGPD_Output);
    return Pin;
};

UEdGraphPin* UK2Node_CreateReader::GetSettingsPin() const
{
    UEdGraphPin* Pin = FindPin(FReaderGetPinName::GetTopicSettingsPinName());
    check(Pin == NULL || Pin->Direction == EGPD_Input);
    return Pin;
};

UEdGraphPin* UK2Node_CreateReader::GetThenPin() const
{
    UEdGraphPin* Pin = FindPin(UEdGraphSchema_K2::PN_Then);
    check(Pin);
    return Pin;
}
UEdGraphPin* UK2Node_CreateReader::GetBlueprintPin(const TArray<UEdGraphPin*>* InPinsToSearch) const
{
    const TArray<UEdGraphPin*>* PinsToSearch = InPinsToSearch ? InPinsToSearch : &Pins;

    UEdGraphPin* Pin = nullptr;
    for (UEdGraphPin* TestPin : *PinsToSearch)
    {
        if (TestPin && TestPin->PinName == FReaderGetPinName::GetDataTypeClassPinName())
        {
            Pin = TestPin;
            break;
        }
    }
    check(Pin == nullptr || Pin->Direction == EGPD_Input);
    return Pin;
};

void UK2Node_CreateReader::PinDefaultValueChanged(UEdGraphPin* ChangedPin)
{
    if (ChangedPin->PinName == FReaderGetPinName::GetDataTypeClassPinName())
    {
        const UEdGraphSchema_K2* K2Schema = GetDefault<UEdGraphSchema_K2>();

        // Because the archetype has changed, we break the output link as the output pin type will change
        UEdGraphPin* ResultPin = GetOutTopicProxyPin();
        ResultPin->BreakAllPinLinks();

        /*TArray<UEdGraphPin*> OldPins = Pins;
        for (int32 i = 0; i < OldPins.Num(); i++)
        {
            UEdGraphPin* OldPin = OldPins[i];
            if (IsOutObjectArchetype(OldPin))
            {
                UE_LOG(LogTemp, Log, TEXT("is archetype"));
                OldPin->MarkAsGarbage();
                Pins.Remove(OldPin);
            };
        };*/
        
        CachedNodeTitle.MarkDirty();

        UClass* UseSpawnClass = GetProxyClassToSpawn();

        if (UseSpawnClass != NULL)
        {
            CreatePinsForClass(UseSpawnClass);
        }

        // Refresh the UI for the graph so the pin changes show up
        UEdGraph* Graph = GetGraph();
        Graph->NotifyGraphChanged();

        // Mark dirty
        FBlueprintEditorUtils::MarkBlueprintAsModified(GetBlueprint());
    }
};




FText UK2Node_CreateReader::GetBaseNodeTitle() const
{
    return LOCTEXT("CreateItemData_BaseTitle", "Create Reader");
};


void UK2Node_CreateReader::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
    AllocateDefaultPins();
    UClass* UseSpawnClass = GetProxyClassToSpawn(&OldPins);
    if (UseSpawnClass != NULL)
    {
        CreatePinsForClass(UseSpawnClass);
    }
    RestoreSplitPins(OldPins);
}

void UK2Node_CreateReader::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
    Super::ExpandNode(CompilerContext, SourceGraph);

    //Function parameters name of the blueprint function
    static FString WorldContextObject_ParamName = FString(TEXT("Owner"));
    static FString MsgType_ParamName = FString(TEXT("DataType"));
    static FString Settings_ParamName = FString(TEXT("Settings"));
    static FString OutTopicProxy_ParamName = FString(TEXT("OutTopicProxy"));
    static FString OutWriter_ParamName = FString(TEXT("OutReader"));

    //Spawn Node Blueprint Function
    UK2Node_CallFunction* const CreateFunction = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
    CreateFunction->FunctionReference.SetExternalMember(GET_FUNCTION_NAME_CHECKED(UMorseLib, CreateReaderBlueprint), UMorseLib::StaticClass());
    CreateFunction->AllocateDefaultPins();

    //Get the input pin of the actual node (input & exec parameters exposed to blueprint)
    UEdGraphPin* NodeExec = this->GetExecPin();
    UEdGraphPin* NodeThen = this->GetThenPin();
    UEdGraphPin* DataTypeClassPin = this->GetDataTypeClassPin();
    UEdGraphPin* OwnerPin = this->GetOwnerPin();
    UEdGraphPin* SettingsPin = this->GetSettingsPin();
    //Get the output pin of the actual node (output parameters exposed to blueprint)
    UEdGraphPin* SpawnTopicProxyPin = this->GetOutTopicProxyPin();
    UEdGraphPin* SpawnWriterPin = this->GetOutReaderPin();

    //Get pins of the node blueprint spawn function (typically, the "virtual" pin of the blueprint function API
    UEdGraphPin* CallCreateExec = CreateFunction->GetExecPin();
    UEdGraphPin* CallCreateOwningObjectPin = CreateFunction->FindPinChecked(WorldContextObject_ParamName);
    UEdGraphPin* CallCreateMsgClassPin = CreateFunction->FindPinChecked(MsgType_ParamName);
    UEdGraphPin* CallCreateThen = CreateFunction->GetThenPin();
    UEdGraphPin* CallCreateSpawnTopicProxy = CreateFunction->FindPinChecked(OutTopicProxy_ParamName);
    UEdGraphPin* CallCreateSpawnReader = CreateFunction->FindPinChecked(OutWriter_ParamName);
    UEdGraphPin* CallCreateSettings = CreateFunction->FindPinChecked(Settings_ParamName);

    //Branch the input of the actual node, into the blueprint function (spawned)
    CompilerContext.MovePinLinksToIntermediate(*NodeExec, *CallCreateExec);
    CompilerContext.MovePinLinksToIntermediate(*DataTypeClassPin, *CallCreateMsgClassPin);
    CompilerContext.MovePinLinksToIntermediate(*SettingsPin, *CallCreateSettings);

    //Set the owner pin
    if (OwnerPin)
    {
        CompilerContext.MovePinLinksToIntermediate(*OwnerPin, *CallCreateOwningObjectPin);
    };

    //Call execution 
    CompilerContext.MovePinLinksToIntermediate(*NodeThen, *CallCreateThen);

    //Branch output pin
    CallCreateSpawnTopicProxy->PinType = SpawnTopicProxyPin->PinType;
    CompilerContext.MovePinLinksToIntermediate(*SpawnTopicProxyPin, *CallCreateSpawnTopicProxy);

    //Branch output pin
    CallCreateSpawnReader->PinType = SpawnWriterPin->PinType;
    CompilerContext.MovePinLinksToIntermediate(*SpawnWriterPin, *CallCreateSpawnReader);

    BreakAllNodeLinks();
};


#undef LOCTEXT_NAMESPACE