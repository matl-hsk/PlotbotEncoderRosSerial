/// Header file for PlotbotEncoderSerialRosNode class
#ifndef PLOTBOT_ENCODER_SERIAL_ROS_NODE_H
#define PLOTBOT_ENCODER_SERIAL_ROS_NODE_H

#include <Arduino.h>
#include <PacketSerial.h>
#include <Ticker.h>

#include "plotbot_encoder.h"
#include "ros_defines.h"

/// @brief Plotbot with simple encoder on each axis that sends
/// the position data as ROS2 message via serial so that it can
/// be relayed via ros2_serial_example
class PlotbotEncoderSerialRosNode
{
public:
  /// @brief Setup the PlotbotEncoderSerialRosNode.
  void setup()
  {
    plotbotEncoder.setup();
    sendPositionsTicker.attach_ms(
        100, +[](PlotbotEncoderSerialRosNode *node)
             { node->sendPositions(); },
        this); // send position with 10Hz todo: evaluate this
    updateEncoderTicker.attach_ms(
        10,
        +[](PlotbotEncoderSerialRosNode *node)
        { node->plotbotEncoder.update(); },
        this);
  }

  /// @brief Send the positions of the axes as cobs encoded ROS message for
  /// further relay via ros2_serial_example node
  void sendPositions();

private:
  /// @brief Fill the header of the to be transmitted message.
  /// @param header Header with topic ID, payload length and crc checksum.
  /// @param payload Message payload (cdr encoded payload (axes positions))
  void fillHeader(ros2::COBSHeader *header, uint8_t const *const payload);

  /// @brief Get the axes positions, cdr decode/serialize them and write the
  /// result to the specified buffer.
  /// @param buffer Array of 12 bytes into which the serialized float array
  /// with axes positions should be written to.
  void writePayload(uint8_t *buffer);

private:
  /// Plotbot encoder to get positions
  PlotbotEncoder plotbotEncoder;

  /// Serial communication with COBS encoded messages
  PacketSerial packetSerial;

  /// Timer to send plotbot axis positions as ROS topic via serial
  Ticker sendPositionsTicker;

  /// Timer to regularly update the encoder of the plotbotEncoder
  Ticker updateEncoderTicker;

  /// Length of the payload of the message (4bytes for each axis)
  static size_t const payloadLen = PlotbotEncoder::numAxes * 4;
};

#endif
