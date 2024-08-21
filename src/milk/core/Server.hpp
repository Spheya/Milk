#pragma once

#include "milk/net/Server.hpp"
#include "ServerStatus.hpp"
#include "milk/registry/Registry.hpp"
#include "milk/registry/DimensionType.hpp"
#include "milk/registry/PaintingVariant.hpp"
#include "milk/registry/WolfVariant.hpp"

namespace milk {

	class Server {
	public:
		Server(uint16_t port);

		void setupVanillaRegistries();
		void setupDefaultPacketHandlers();

		void run();
		void stop();

		EventBus& getPacketBus() noexcept;
		const EventBus& getPacketBus() const noexcept;

		EventBus& getEventBus() noexcept;
		const EventBus& getEventBus() const noexcept;

		Registry<DimensionType>& getDimensionTypeRegistry() noexcept;
		const Registry<DimensionType>& getDimensionTypeRegistry() const noexcept;
		Registry<PaintingVariant>& getPaintingVariantRegistry() noexcept;
		const Registry<PaintingVariant>& getPaintingVariantRegistry() const noexcept;
		Registry<WolfVariant>& getWolfVariantRegistry() noexcept;
		const Registry<WolfVariant>& getWolfVariantRegistry() const noexcept;

		void setServerStatusCallback(std::function<ServerStatus()> serverStatusCallback) noexcept;

	private:
		asio::io_context m_asioContext;
		net::Server m_netServer;

		EventBus m_eventBus;
		std::function<ServerStatus()> m_serverStatusCallback;

		Registry<DimensionType> m_dimensionTypeRegistry;
		Registry<PaintingVariant> m_paintingVariantRegistry;
		Registry<WolfVariant> m_wolfVariantRegistry;

		std::atomic_bool m_closeRequested = false;

	};

}