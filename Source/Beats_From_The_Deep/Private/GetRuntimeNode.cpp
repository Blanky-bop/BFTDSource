#include "GetRuntimeNode.h"
#include "MetasoundParamHelper.h"
#include "MetasoundStandardNodesNames.h"
#include "MetasoundStandardNodesCategories.h"
#include "MetasoundNodeRegistrationMacro.h"
#include "TimeManager.h"

#define LOCTEXT_NAMESPACE "MetasoundStandardNodes_GetRuntimeNode"

namespace Metasound
{
    FGetRuntimeOperator::FGetRuntimeOperator(const FOperatorSettings& InSettings, const FTriggerReadRef& InTriggerIn)
        : TriggerIn(InTriggerIn), OutRuntime(FTimeWriteRef::CreateNew(0.0f))
    {
    }

    void FGetRuntimeOperator::BindInputs(FInputVertexInterfaceData& InOutVertexData)
    {
        using namespace GetRuntimeVertexNames;
        InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(InputTrigger), TriggerIn);
    }

    void FGetRuntimeOperator::BindOutputs(FOutputVertexInterfaceData& InOutVertexData)
    {
        using namespace GetRuntimeVertexNames;
        InOutVertexData.BindReadVertex(METASOUND_GET_PARAM_NAME(OutputRuntime), OutRuntime);
    }

    FDataReferenceCollection FGetRuntimeOperator::GetInputs() const
    {
        checkNoEntry();
        return {};
    }

    FDataReferenceCollection FGetRuntimeOperator::GetOutputs() const
    {
        checkNoEntry();
        return {};
    }

    void FGetRuntimeOperator::Execute()
    {
        TriggerIn->ExecuteBlock(
            [](int32, int32) {}, 
            [this](int32 StartFrame, int32 EndFrame)
            {
                *OutRuntime = static_cast<FTime>(FTimeManager::GetInstance().GetRunTimeInSeconds());
            }
        );
    }

    TUniquePtr<IOperator> FGetRuntimeOperator::CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults)
    {
        using namespace GetRuntimeVertexNames;
        const FInputVertexInterfaceData& InputData = InParams.InputData;
        FTriggerReadRef TriggerIn = InputData.GetOrConstructDataReadReference<FTrigger>(
            METASOUND_GET_PARAM_NAME(InputTrigger), InParams.OperatorSettings);

        return MakeUnique<FGetRuntimeOperator>(InParams.OperatorSettings, TriggerIn);
    }

    const FVertexInterface& FGetRuntimeOperator::GetVertexInterface()
    {
        using namespace GetRuntimeVertexNames;

        static const FVertexInterface Interface(
            FInputVertexInterface(
                TInputDataVertex<FTrigger>(METASOUND_GET_PARAM_NAME_AND_METADATA(InputTrigger))
            ),
            FOutputVertexInterface(
                TOutputDataVertex<FTime>(METASOUND_GET_PARAM_NAME_AND_METADATA(OutputRuntime))
            )
        );

        return Interface;
    }

    const FNodeClassMetadata& FGetRuntimeOperator::GetNodeInfo()
    {
        auto InitNodeInfo = []() -> FNodeClassMetadata
            {
                FNodeClassMetadata Info;
                Info.ClassName = { StandardNodes::Namespace, TEXT("GetRuntime"), TEXT("") };
                Info.MajorVersion = 1;
                Info.MinorVersion = 0;
                Info.DisplayName = METASOUND_LOCTEXT("Metasound_GetRuntimeNodeDisplayName", "Get Application Runtime");
                Info.Description = METASOUND_LOCTEXT("Metasound_GetRuntimeNodeDescription", "Gets the current runtime of the application (in seconds) whenever triggered.");
                Info.Author = PluginAuthor;
                Info.PromptIfMissing = PluginNodeMissingPrompt;
                Info.DefaultInterface = GetVertexInterface();
                Info.CategoryHierarchy.Emplace(NodeCategories::Trigger);

                return Info;
            };

        static const FNodeClassMetadata Info = InitNodeInfo();
        return Info;
    }

    FGetRuntimeNode::FGetRuntimeNode(const FNodeInitData& InInitData)
        : FNodeFacade(InInitData.InstanceName, InInitData.InstanceID, TFacadeOperatorClass<FGetRuntimeOperator>())
    {
    }

    METASOUND_REGISTER_NODE(FGetRuntimeNode)
}

#undef LOCTEXT_NAMESPACE
