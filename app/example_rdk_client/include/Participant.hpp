/**
 * @file Participant.hpp
 * @copyright Copyright (C) 2016-2022 Flexiv Ltd. All Rights Reserved.
 */

#ifndef _PUBLISH_OPERATIONS_HPP_
#define _PUBLISH_OPERATIONS_HPP_

// middleware2 fast-rtps headers
#include <flexiv/middleware2/fast_rtps_node.h>

// message headers for KostalLever.idl
#include "KostalLever.h"
#include "KostalLeverPubSubTypes.h"

// message headers for PlanExecution.idl
#include "PlanExecution.h"
#include "PlanExecutionPubSubTypes.h"

// useful robot operations
#include "RobotOperations.hpp"

// alias of FastRTPSNode
typedef flexiv::middleware2::FastRTPSNode Node;

// alias of different message class generated by idl files
typedef kostal_gui_msgs::msg::KostalLever KostalMsg;
typedef plan_msgs::msg::PlanExecution PlanMsg;

// alias of different messages' serialization functions
typedef kostal_gui_msgs::msg::KostalLeverPubSubType KostalPubSubType;
typedef plan_msgs::msg::PlanExecutionPubSubType PlanPubSubType;

// alias of rdk client's publisher and subscriber with different message types
// respectively
typedef flexiv::middleware2::FastRTPSPublisher<KostalPubSubType>
    RdkClientPublisher;
typedef flexiv::middleware2::FastRTPSSubscriber<PlanPubSubType>
    RdkClientSubscriber;

namespace flexiv {

/**
 * @class Participant
 * @brief This class represent participant's actions for rdk client to publish
 * robot states and subscribe assigned workplans
 */
class Participant
{
public:
    Participant() = default;
    virtual ~Participant() = default;

    /**
     * @brief Create a publisher by passing node pointer into this function
     * @param[in] node FastRTPSNode pointer
     * @param[in] topicName the name of the topic that will be published to
     * @return the shared pointer of the rdk client publisher
     */
    std::shared_ptr<RdkClientPublisher> createPublisher(
        Node* node, std::string topicName);

    /**
     * @brief Publish robot states messages to assigned container
     * @param[in] publisher shared pointer of the RdkClientPublisher
     * @param[in] pub_msg the message that will be published to
     * @param[in] tcpPose_array array that store tcpPose
     * @param[in] flangePose_array array that store flangePose
     * @param[in] rawForceSensor_array array that store rawForceSensorData (Not
     * used yet)
     */
    void publishTcpMsg(std::shared_ptr<RdkClientPublisher> publisher,
        KostalMsg* pub_msg, std::array<double, 7>* tcpPose_array,
        std::array<double, 7>* flangePose_array,
        std::array<double, 6>* rawForceSensor_array);

    /**
     * @brief Create a subscriber by passing node pointer, topic name, message,
     * robot pointer and log pointer into this function
     * @param[in] robotHandler RobotOperations object's pointer
     * @param[in] node FastRTPSNode pointer
     * @param[in] topicName the name of the topic that will be subscribed to
     * @param[in] sub_msg the message that will be subscribed to
     * @param[in] robot robot's pointer
     * @param[in] log log's pointer
     * @return the shared pointer of the rdk client subscriber
     */
    std::shared_ptr<RdkClientSubscriber> createSubscriber(
        RobotOperations* robotHandler, Node* node, std::string topicName,
        PlanMsg* sub_msg, flexiv::Robot* robot, flexiv::Log* log);
};

} /* namespace flexiv */
#endif // _PUBLISH_OPERATIONS_HPP_