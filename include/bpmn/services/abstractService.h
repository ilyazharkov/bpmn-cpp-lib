#pragma once
#include "./service.h"  // Only direct dependency
#include <string>


namespace bpmn {
    namespace services {
        class ServiceTask : public IService {
        public:
            std::string topic;
            std::string class_name;
            std::string expression;
            
            std::future<json> execute(ExecutionState& state) override;
            ~ServiceTask() override;
        };
    }
}
