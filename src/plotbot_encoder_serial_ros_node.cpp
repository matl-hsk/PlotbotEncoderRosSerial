/// Source file for PlotbotEncoderSerialRosNode class

#include "ucdr/microcdr.h"

#include "plotbot_encoder_serial_ros_node.h"

void PlotbotEncoderSerialRosNode::sendPositions()
{
  size_t const headerLen = sizeof(ros2::COBSHeader);
  size_t sendBufferLen = headerLen + payloadLen;
  uint8_t sendBuffer[sendBufferLen];

  writePayload(sendBuffer + headerLen);
  fillHeader((ros2::COBSHeader *)sendBuffer, sendBuffer + headerLen);

  packetSerial.send(sendBuffer, sendBufferLen);
}

void PlotbotEncoderSerialRosNode::fillHeader(ros2::COBSHeader *header, uint8_t const *const payload)
{
  uint16_t crc = ros2::crc16(payload, payloadLen);

  header->topic_ID = 0x3;
  header->payload_len_h = 0x0;
  header->payload_len_l = 0xC; // 12 (payload_len)
  header->crc_h = *((uint8_t *)&(crc) + 1);
  header->crc_l = *((uint8_t *)&crc);
}

void PlotbotEncoderSerialRosNode::writePayload(uint8_t *buffer)
{
  float positions[PlotbotEncoder::numAxes];
  plotbotEncoder.getPositions(positions);

  ucdrBuffer writer;
  ucdr_init_buffer(&writer, buffer, payloadLen);
  ucdr_serialize_array_float(&writer, positions, PlotbotEncoder::numAxes);
}
 