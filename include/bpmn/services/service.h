#pragma once
#include <nlohmann/json.hpp>
#include <future>
#include "../execution_state_fwd.h"  // New header
#include "../flowAbstract.h"

using json = nlohmann::json;

namespace bpmn {
    namespace services {
        class IService : public FlowElement {
        public:
            virtual ~IService() = default;
            virtual std::future<json> execute(ExecutionState& state) = 0;
        };
    }
}