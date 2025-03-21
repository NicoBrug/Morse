/****************************************************************

  Generated by Eclipse Cyclone DDS IDL to C Translator
  File name: C:\Dev\DataTypes\COMPILED/msg/Nested.c
  Source: C:\Dev\DataTypes\ROS\test_msgs\msg\Nested.idl
  Cyclone DDS: V0.11.0

*****************************************************************/
#include "Nested.h"

static const uint32_t test_msgs_msg_Nested_ops [] =
{
  /* Nested */
  DDS_OP_DLC,
  DDS_OP_ADR | DDS_OP_TYPE_EXT, offsetof (test_msgs_msg_Nested, primitive_values), (3u << 16u) + 4u /* Primitives */,
  DDS_OP_RTS,

  /* Primitives */
  DDS_OP_DLC,
  DDS_OP_ADR | DDS_OP_TYPE_BLN, offsetof (test_msgs_msg_Primitives, bool_value),
  DDS_OP_ADR | DDS_OP_TYPE_1BY, offsetof (test_msgs_msg_Primitives, byte_value),
  DDS_OP_ADR | DDS_OP_TYPE_1BY | DDS_OP_FLAG_SGN, offsetof (test_msgs_msg_Primitives, char_value),
  DDS_OP_ADR | DDS_OP_TYPE_4BY | DDS_OP_FLAG_FP, offsetof (test_msgs_msg_Primitives, float32_value),
  DDS_OP_ADR | DDS_OP_TYPE_8BY | DDS_OP_FLAG_FP, offsetof (test_msgs_msg_Primitives, float64_value),
  DDS_OP_ADR | DDS_OP_TYPE_1BY, offsetof (test_msgs_msg_Primitives, int8_value),
  DDS_OP_ADR | DDS_OP_TYPE_1BY, offsetof (test_msgs_msg_Primitives, uint8_value),
  DDS_OP_ADR | DDS_OP_TYPE_2BY | DDS_OP_FLAG_SGN, offsetof (test_msgs_msg_Primitives, int16_value),
  DDS_OP_ADR | DDS_OP_TYPE_2BY, offsetof (test_msgs_msg_Primitives, uint16_value),
  DDS_OP_ADR | DDS_OP_TYPE_4BY | DDS_OP_FLAG_SGN, offsetof (test_msgs_msg_Primitives, int32_value),
  DDS_OP_ADR | DDS_OP_TYPE_4BY, offsetof (test_msgs_msg_Primitives, uint32_value),
  DDS_OP_ADR | DDS_OP_TYPE_8BY | DDS_OP_FLAG_SGN, offsetof (test_msgs_msg_Primitives, int64_value),
  DDS_OP_ADR | DDS_OP_TYPE_8BY, offsetof (test_msgs_msg_Primitives, uint64_value),
  DDS_OP_ADR | DDS_OP_TYPE_STR, offsetof (test_msgs_msg_Primitives, string_value),
  DDS_OP_RTS
};

const dds_topic_descriptor_t test_msgs_msg_Nested_desc =
{
  .m_size = sizeof (test_msgs_msg_Nested),
  .m_align = dds_alignof (test_msgs_msg_Nested),
  .m_flagset = 0u,
  .m_nkeys = 0u,
  .m_typename = "test_msgs::msg::Nested",
  .m_keys = NULL,
  .m_nops = 19,
  .m_ops = test_msgs_msg_Nested_ops,
  .m_meta = ""
};

