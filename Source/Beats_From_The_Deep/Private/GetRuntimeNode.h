#pragma once

#include "CoreMinimal.h"
#include "MetasoundExecutableOperator.h"
#include "MetasoundNode.h"
#include "MetasoundFacade.h"
#include "MetasoundTrigger.h"
#include "MetasoundTime.h"
#include "MetasoundParamHelper.h"

#define LOCTEXT_NAMESPACE "MetasoundStandardNodes_GetRuntimeNode"

namespace Metasound
{
    namespace GetRuntimeVertexNames
    {
        METASOUND_PARAM(InputTrigger, "Get", "Trigger to update runtime.");
        METASOUND_PARAM(OutputRuntime, "Runtime", "The application runtime (seconds)");
    }

    class FGetRuntimeOperator : public TExecutableOperator<FGetRuntimeOperator>
    {
    public:
        static const FNodeClassMetadata& GetNodeInfo();
        static const FVertexInterface& GetVertexInterface();
        static TUniquePtr<IOperator> CreateOperator(const FBuildOperatorParams& InParams, FBuildResults& OutResults);

        FGetRuntimeOperator(const FOperatorSettings& InSettings, const FTriggerReadRef& InTriggerIn);

        virtual void BindInputs(FInputVertexInterfaceData& InOutVertexData) override;
        virtual void BindOutputs(FOutputVertexInterfaceData& InOutVertexData) override;
        virtual FDataReferenceCollection GetInputs() const override;
        virtual FDataReferenceCollection GetOutputs() const override;

        void Execute();

    private:
        FTriggerReadRef TriggerIn;
        FTimeWriteRef OutRuntime;
    };

    class FGetRuntimeNode : public FNodeFacade
    {
    public:
        FGetRuntimeNode(const FNodeInitData& InInitData);
        virtual ~FGetRuntimeNode() = default;
    };

} // namespace Metasound

#undef LOCTEXT_NAMESPACE
