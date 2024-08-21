#pragma once

#include "protocol/serverbound/handshaking/HandShake.hpp"
#include "protocol/serverbound/handshaking/LegacyServerPing.hpp"

#include "protocol/serverbound/status/StatusRequest.hpp"
#include "protocol/serverbound/status/PingRequest.hpp"
#include "protocol/clientbound/status/StatusResponse.hpp"
#include "protocol/clientbound/status/PingResponse.hpp"

#include "protocol/serverbound/login/LoginStart.hpp"
#include "protocol/serverbound/login/LoginAcknowledged.hpp"
#include "protocol/clientbound/login/LoginSuccess.hpp"

#include "protocol/serverbound/configuration/AcknowledgeFinishConfiguration.hpp"
#include "protocol/clientbound/configuration/PluginMessage.hpp"
#include "protocol/clientbound/configuration/FinishConfiguration.hpp"
#include "protocol/clientbound/configuration/RegistryData.hpp"

#include "protocol/clientbound/play/Login.hpp"

namespace milk {
	namespace serverbound {
		using namespace configuration;
		using namespace handshaking;
		using namespace login;
		using namespace status;
	}

	namespace clientbound {
		using namespace configuration;
		using namespace login;
		using namespace status;
		using namespace play;
	}
}