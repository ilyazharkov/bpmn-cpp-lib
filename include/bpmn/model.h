#ifndef BPMN_MODEL_H
#define BPMN_MODEL_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "../bpmn/services/abstractService.h"

namespace bpmn {

    // Forward declarations
    class SequenceFlow;
    class StartEvent;
    class EndEvent;
    class UserTask;
    class ParallelGateway;
    class ExclusiveGateway;

    class Process {
    public:
        // Helper methods
        FlowElement* getElement(const std::string& id) const;
        void addElement(const std::unique_ptr<FlowElement> element);
        void addElement(const std::shared_ptr<FlowElement> element);
        void addSequenceFlow(const std::string& id, const std::string& sourceRef, const std::string& targetRef);
        StartEvent* getStartEvent() const;
        std::vector<services::ServiceTask*> getServiceTasks() const;
        std::vector<UserTask*> getUserTasks() const;
        bool validate() const;
        const std::vector<std::shared_ptr<SequenceFlow>> getOutgoingFlows(const std::string& element_id) const;
        
        //Getters методы
        const std::string getId() const;
        const std::string getStartEventId() const;
    private:
        std::string id;
        std::string name;

        // BPMN elements
        std::vector<std::unique_ptr<FlowElement>> elements;
        std::unordered_map<std::string, std::shared_ptr<FlowElement>> elementsById;
        std::vector<std::unique_ptr<SequenceFlow>> flows;
        std::unordered_map<std::string, std::shared_ptr<SequenceFlow>> flowsById;

        // Карты для быстрого поиска потоков по элементам
        std::unordered_map<std::string, std::vector<std::shared_ptr<SequenceFlow>>> outgoingFlows;
        std::unordered_map<std::string, std::vector<std::shared_ptr<SequenceFlow>>> incomingFlows;


        // Quick access to specific elements
        std::string start_event_id;
        std::map<std::string, FlowElement*> element_map;
    };



    class SequenceFlow : public FlowElement {
    public:
        std::string source_ref;
        std::string target_ref;
        std::string condition_expression;
    };

    class StartEvent : public FlowElement {
        // Start event specific properties
        ~StartEvent();
    };

    class EndEvent : public FlowElement {
        // End event specific properties
        ~EndEvent();
    };

    class UserTask : public FlowElement {
    public:
        std::string form_key;
        std::string assignee;
        std::map<std::string, std::string> form_fields;
        ~UserTask();
    };



    class ParallelGateway : public FlowElement {
        // Parallel gateway specific properties
        ~ParallelGateway();
    };

    class ExclusiveGateway : public FlowElement {
    public:
        std::string default_flow;  // ID of default sequence flow
        ~ExclusiveGateway();
    };

} // namespace bpmn

#endif // BPMN_MODEL_H