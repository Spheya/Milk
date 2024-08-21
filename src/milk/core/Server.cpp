#include "Server.hpp"

#include "milk/Protocol.hpp"
#include "milk/protocol/PacketHandler.hpp"

namespace milk {

	Server::Server(uint16_t port) :
		m_netServer(port, m_asioContext),
		m_serverStatusCallback([]() {
			ServerStatus status;
			// todo: player count
			return status; 
		}),
		m_dimensionTypeRegistry(Identifier("minecraft", "dimension_type")),
		m_paintingVariantRegistry(Identifier("minecraft", "painting_variant")),
		m_wolfVariantRegistry(Identifier("minecraft", "wolf_variant"))
	{}

	void Server::run() {
		m_closeRequested = false;
		auto asioThread = std::thread([this]() { m_asioContext.run(); });

		while (!m_closeRequested) {
			m_netServer.pollEvents();
			m_eventBus.executeEventQueue();
		}

		if (asioThread.joinable())
			asioThread.join();
	}

	void Server::stop() {
		m_closeRequested = true;
	}
	EventBus& Server::getPacketBus() noexcept {
		return m_netServer.getPacketBus();
	}

	const EventBus& Server::getPacketBus() const noexcept {
		return m_netServer.getPacketBus();
	}

	EventBus& Server::getEventBus() noexcept {
		return m_eventBus;
	}

	const EventBus& Server::getEventBus() const noexcept {
		return m_eventBus;
	}

	Registry<DimensionType>& Server::getDimensionTypeRegistry() noexcept {
		return m_dimensionTypeRegistry;
	}

	const Registry<DimensionType>& Server::getDimensionTypeRegistry() const noexcept {
		return m_dimensionTypeRegistry;
	}

	Registry<PaintingVariant>& Server::getPaintingVariantRegistry() noexcept {
		return m_paintingVariantRegistry;
	}

	const Registry<PaintingVariant>& Server::getPaintingVariantRegistry() const noexcept {
		return m_paintingVariantRegistry;
	}

	Registry<WolfVariant>& Server::getWolfVariantRegistry() noexcept {
		return m_wolfVariantRegistry;
	}

	const Registry<WolfVariant>& Server::getWolfVariantRegistry() const noexcept {
		return m_wolfVariantRegistry;
	}


	void Server::setServerStatusCallback(std::function<ServerStatus()> serverStatusCallback) noexcept {
		m_serverStatusCallback = std::move(serverStatusCallback);
	}

	void Server::setupVanillaRegistries() {
		DimensionType overworld;
		overworld.piglinSafe = false;
		overworld.natural = true;
		overworld.ambientLight = 0.0f;
		overworld.monsterSpawnBlockLightLimit = 0;
		overworld.infiniburn = "#minecraft:infiniburn_overworld";
		overworld.respawnAnchorWorks = false;
		overworld.hasSkylight = true;
		overworld.bedWorks = true;
		overworld.effects = "minecraft:overworld";
		overworld.hasRaids = true;
		overworld.logicalHeight = 384;
		overworld.coordinateScale = 1.0f;
		overworld.monsterSpawnLightLevel = 0;
		overworld.minY = -64;
		overworld.ultrawarm = false;
		overworld.hasCeiling = false;
		overworld.height = 384;
		overworld.fixedTime = 0;
		overworld.hasFixedTime = false;

		DimensionType end;
		end.piglinSafe = false;
		end.natural = false;
		end.ambientLight = 0.0f;
		end.monsterSpawnBlockLightLimit = 0;
		end.infiniburn = "#minecraft:infiniburn_end";
		end.respawnAnchorWorks = false;
		end.hasSkylight = false;
		end.bedWorks = false;
		end.effects = "minecraft:the_end";
		end.hasRaids = false;
		end.logicalHeight = 256;
		end.coordinateScale = 1.0f;
		end.monsterSpawnLightLevel = 0;
		end.minY = 0;
		end.ultrawarm = false;
		end.hasCeiling = false;
		end.height = 256;
		end.fixedTime = 6000;
		end.hasFixedTime = true;

		DimensionType nether;
		nether.piglinSafe = true;
		nether.natural = false;
		nether.ambientLight = 0.1f;
		nether.monsterSpawnBlockLightLimit = 15;
		nether.infiniburn = "#minecraft:infiniburn_nether";
		nether.respawnAnchorWorks = true;
		nether.hasSkylight = false;
		nether.bedWorks = false;
		nether.effects = "minecraft:the_nether";
		nether.hasRaids = 1;
		nether.logicalHeight = 128;
		nether.coordinateScale = 8.0f;
		nether.monsterSpawnLightLevel = 7;
		nether.minY = 0;
		nether.ultrawarm = true;
		nether.hasCeiling = true;
		nether.height = 256;
		nether.fixedTime = 18000;
		nether.hasFixedTime = true;

		m_dimensionTypeRegistry.add(Identifier("minecraft", "overworld"), overworld);
		m_dimensionTypeRegistry.add(Identifier("minecraft", "the_end"), end);
		m_dimensionTypeRegistry.add(Identifier("minecraft", "the_nether"), nether);

		WolfVariant ashen;
		ashen.wildTexture = "minecraft:entity/wolf/wolf_ashen";
		ashen.angryTexture = "minecraft:entity/wolf/wolf_ashen_angry";
		ashen.tameTexture = "minecraft:entity/wolf/wolf_ashen_tame";
		ashen.biomes = {};

		WolfVariant black;
		black.wildTexture = "minecraft:entity/wolf/wolf_black";
		black.angryTexture = "minecraft:entity/wolf/wolf_black_angry";
		black.tameTexture = "minecraft:entity/wolf/wolf_black_tame";
		black.biomes = {};

		WolfVariant chestnut;
		chestnut.wildTexture = "minecraft:entity/wolf/wolf_chestnut";
		chestnut.angryTexture = "minecraft:entity/wolf/wolf_chestnut_angry";
		chestnut.tameTexture = "minecraft:entity/wolf/wolf_chestnut_tame";
		chestnut.biomes = {};

		WolfVariant pale;
		pale.wildTexture = "minecraft:entity/wolf/wolf_pale";
		pale.angryTexture = "minecraft:entity/wolf/wolf_pale_angry";
		pale.tameTexture = "minecraft:entity/wolf/wolf_pale_tame";
		pale.biomes = {};

		WolfVariant rusty;
		rusty.wildTexture = "minecraft:entity/wolf/wolf_rusty";
		rusty.angryTexture = "minecraft:entity/wolf/wolf_rusty_angry";
		rusty.tameTexture = "minecraft:entity/wolf/wolf_rusty_tame";
		rusty.biomes = {};

		WolfVariant snowy;
		snowy.wildTexture = "minecraft:entity/wolf/wolf_snowy";
		snowy.angryTexture = "minecraft:entity/wolf/wolf_snowy_angry";
		snowy.tameTexture = "minecraft:entity/wolf/wolf_snowy_tame";
		snowy.biomes = {};

		WolfVariant spotted;
		spotted.wildTexture = "minecraft:entity/wolf/wolf_spotted";
		spotted.angryTexture = "minecraft:entity/wolf/wolf_spotted_angry";
		spotted.tameTexture = "minecraft:entity/wolf/wolf_spotted_tame";
		spotted.biomes = {};

		WolfVariant striped;
		striped.wildTexture = "minecraft:entity/wolf/wolf_striped";
		striped.angryTexture = "minecraft:entity/wolf/wolf_striped_angry";
		striped.tameTexture = "minecraft:entity/wolf/wolf_striped_tame";
		striped.biomes = {};

		WolfVariant woods;
		woods.wildTexture = "minecraft:entity/wolf/wolf_woods";
		woods.angryTexture = "minecraft:entity/wolf/wolf_woods_angry";
		woods.tameTexture = "minecraft:entity/wolf/wolf_woods_tame";
		woods.biomes = {};

		m_wolfVariantRegistry.add(Identifier("minecraft", "ashen"), ashen);
		m_wolfVariantRegistry.add(Identifier("minecraft", "black"), black);
		m_wolfVariantRegistry.add(Identifier("minecraft", "chestnut"), chestnut);
		m_wolfVariantRegistry.add(Identifier("minecraft", "pale"), pale);
		m_wolfVariantRegistry.add(Identifier("minecraft", "rusty"), rusty);
		m_wolfVariantRegistry.add(Identifier("minecraft", "snowy"), snowy);
		m_wolfVariantRegistry.add(Identifier("minecraft", "spotted"), spotted);
		m_wolfVariantRegistry.add(Identifier("minecraft", "striped"), striped);
		m_wolfVariantRegistry.add(Identifier("minecraft", "woods"), woods);

		// todo: add all vanilla paintings
		PaintingVariant painting;
		painting.assetId = "minecraft:backyard";
		painting.height = 2;
		painting.width = 2;
		m_paintingVariantRegistry.add(Identifier("milk", "painting"), painting);
	}

	void Server::setupDefaultPacketHandlers() {
		getPacketBus().subscribeImmediateHandler<IncomingPacketEvent<serverbound::Handshake>>(
			[](const IncomingPacketEvent<serverbound::Handshake>& packet) {
				switch (packet.packet.nextState) {
				case serverbound::Handshake::NextState::Status:
					packet.sender->setState(ConnectionState::Status);
					break;

				case serverbound::Handshake::NextState::Login:
					packet.sender->setState(ConnectionState::Login);
					break;

				case serverbound::Handshake::NextState::Transfer:
					packet.sender->setState(ConnectionState::Login);
					break;

				default:
					packet.sender->disconnect();
					break;
				}
			}
		);

		getPacketBus().subscribeAsyncHandler<IncomingPacketEvent<serverbound::PingRequest>>(
			[](const IncomingPacketEvent<serverbound::PingRequest>& packet) {
				clientbound::PingResponse response;
				response.payload = packet.packet.payload;
				packet.sender->send(response.serialize());
			}
		);

		getPacketBus().subscribe<IncomingPacketEvent<serverbound::StatusRequest>>(
			[this](const IncomingPacketEvent<serverbound::StatusRequest>& packet) {
				clientbound::StatusResponse response;
				response.jsonResponse = m_serverStatusCallback().stringify();
				packet.sender->send(response.serialize());
			}
		);

		getPacketBus().subscribe<IncomingPacketEvent<serverbound::LoginStart>>(
			[](const IncomingPacketEvent<serverbound::LoginStart>& packet) {
				clientbound::LoginSuccess response;
				response.uuid = packet.packet.uuid;
				response.username = packet.packet.name;
				packet.sender->send(response.serialize());

				Packet brand;
				brand.writeVarInt(clientbound::PluginMessage::packetId);
				brand.writeIdentifier(Identifier("minecraft", "brand"));
				brand.writeString("Milk", 16);
				packet.sender->send(brand);
			}
		);

		getPacketBus().subscribeImmediateHandler<IncomingPacketEvent<serverbound::LoginAcknowledged>>(
			[this](const IncomingPacketEvent<serverbound::LoginAcknowledged>& packet) {
				packet.sender->setState(ConnectionState::Configuration);
			}
		);

		getPacketBus().subscribe<IncomingPacketEvent<serverbound::LoginAcknowledged>>(
			[this](const IncomingPacketEvent<serverbound::LoginAcknowledged>& packet) {
				clientbound::RegistryData<DimensionType> dimensionTypeRegistry;
				dimensionTypeRegistry.registry = &getDimensionTypeRegistry();
				packet.sender->send(dimensionTypeRegistry.serialize());

				clientbound::RegistryData<PaintingVariant> paintingVariantRegistry;
				paintingVariantRegistry.registry = &getPaintingVariantRegistry();
				packet.sender->send(paintingVariantRegistry.serialize());

				clientbound::RegistryData<WolfVariant> wolfVariantRegistry;
				wolfVariantRegistry.registry = &getWolfVariantRegistry();
				packet.sender->send(wolfVariantRegistry.serialize());

				clientbound::FinishConfiguration configFinish;
				packet.sender->send(configFinish.serialize());
			}
		);

		getPacketBus().subscribeImmediateHandler<IncomingPacketEvent<serverbound::AcknowledgeFinishConfiguration>>(
			[](const IncomingPacketEvent<serverbound::AcknowledgeFinishConfiguration>& packet) {
				packet.sender->setState(ConnectionState::Play);
			}
		);

		getPacketBus().subscribe<IncomingPacketEvent<serverbound::AcknowledgeFinishConfiguration>>(
			[this](const IncomingPacketEvent<serverbound::AcknowledgeFinishConfiguration>& packet) {
				clientbound::Login loginPacket;
				loginPacket.entityId = 0;
				loginPacket.isHardcore = false;
				loginPacket.dimensionNames = { Identifier("milk", "debugworld") };
				loginPacket.maxPlayers = 10;
				loginPacket.viewDistance = 12;
				loginPacket.simulationDistance = 12;
				loginPacket.reducedDebugInfo = false;
				loginPacket.enableRespawnScreen = true;
				loginPacket.doLimitedCrafting = false;
				loginPacket.dimensionType = int32_t(getDimensionTypeRegistry().getEntryIndex("minecraft:overworld"));
				loginPacket.dimensionName = Identifier("milk", "debugworld");
				loginPacket.hashedSeed = 0;
				loginPacket.gameMode = GameMode::Creative;
				loginPacket.previousGameMode = GameMode::Survival;
				loginPacket.isDebug = false;
				loginPacket.isFlat = false;
				loginPacket.hasDeathLocation = false;
				loginPacket.portalCooldown = 0;
				loginPacket.enforcesSecureChat = false;
				packet.sender->send(loginPacket.serialize());
			}
		);
	}

}