#pragma once

#include <steemit/chain/evaluator.hpp>

#include <steemit/private_message/private_message_operations.hpp>
#include <steemit/private_message/private_message_plugin.hpp>

namespace scorum { namespace private_message {

DEFINE_PLUGIN_EVALUATOR( private_message_plugin, scorum::private_message::private_message_plugin_operation, private_message )

} }
