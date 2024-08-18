#pragma once

#include <unordered_map>
#include <typeindex>
#include <functional>
#include <vector>

#include <concurrentqueue.h>

namespace milk {

	class EventBus {
	public:
		/**
		 * @brief Subscribe an event handler to the bus
		 * @tparam T The type of the event you want to handle
		 * @param handler The callback function that handles the event
		*/
		template<typename T>
		void subscribe(std::function<void(const T&)> handler);

		/**
		 * @brief Subscribe an asynchronous event handler to the bus
		 * @tparam T The type of the event you want to handle
		 * @param handler The callback function that handles the event
		*/
		template<typename T>
		void subscribeAsyncHandler(std::function<void(const T&)> handler);

		/**
		 * @brief Subscribe an event handler to the bus that will get called IMMEDIATELY when the event
		 * gets invoked, and will be ran on the same thread that the event gets invoked from. Usage of
		 * this is not recommended unless its absolutely neccesary that the event will be handled right
		 * away.
		 * @tparam T The type of the event you want to handle
		 * @param handler The callback function that handles the event
		*/
		template<typename T>
		void subscribeImmediateHandler(std::function<void(const T&)> handler);

		/**
		 * @brief Notifies all event handlers about the event, this notification might not happen right away.
		 * @tparam T The type of the event you want to invoke
		 * @param event The event you want to invoke
		*/
		template<typename T>
		void invoke(const T& event);

		/**
		 * @brief Calls the handlers of all queued up events
		*/
		void executeEventQueue();

	private:
		struct EventHandler {
			virtual ~EventHandler() = default;
		};

		template<typename T>
		struct EventHandlerImpl : public EventHandler {
			explicit EventHandlerImpl(std::function<void(const T&)> callback);
			std::function<void(const T&)> callback;
		};

		struct QueuedEvent {
			virtual ~QueuedEvent() = default;
			virtual void invoke() = 0;
		};

		template<typename T>
		struct QueuedEventImpl : public QueuedEvent {
			QueuedEventImpl(const T& event, std::vector<std::unique_ptr<EventHandler>>* handlers);
			void invoke();

		private:
			T m_event;
			std::vector<std::unique_ptr<EventHandler>>* m_handlers;
		};

	private:
		std::unordered_map<std::type_index, std::vector<std::unique_ptr<EventHandler>>> m_handlers;
		std::unordered_map<std::type_index, std::vector<std::unique_ptr<EventHandler>>> m_asyncHandlers;
		std::unordered_map<std::type_index, std::vector<std::unique_ptr<EventHandler>>> m_immediateHandlers;

		moodycamel::ConcurrentQueue<std::unique_ptr<QueuedEvent>> m_eventQueue;
	};

	template<typename T>
	inline void EventBus::subscribe(std::function<void(const T&)> handler) {
		m_handlers[std::type_index(typeid(T))].emplace_back(std::make_unique<EventHandlerImpl<T>>(handler)); // todo: thread-safe
	}

	template<typename T>
	inline void EventBus::subscribeAsyncHandler(std::function<void(const T&)> handler) {
		m_asyncHandlers[std::type_index(typeid(T))].emplace_back(std::make_unique<EventHandlerImpl<T>>(handler)); // todo: thread-safe
	}

	template<typename T>
	inline void EventBus::subscribeImmediateHandler(std::function<void(const T&)> handler) {
		m_immediateHandlers[std::type_index(typeid(T))].emplace_back(std::make_unique<EventHandlerImpl<T>>(handler)); // todo: thread-safe
	}

	template<typename T>
	inline void EventBus::invoke(const T& event) {
		auto handlers = m_handlers.find(std::type_index(typeid(T)));
		auto asyncHandlers = m_asyncHandlers.find(std::type_index(typeid(T)));
		auto immediateHandlers = m_immediateHandlers.find(std::type_index(typeid(T)));

		if (immediateHandlers != m_immediateHandlers.end())
			for (auto& handler : immediateHandlers->second)
				static_cast<EventHandlerImpl<T>*>(handler.get())->callback(event);

		if (asyncHandlers != m_asyncHandlers.end())
			for (auto& handler : asyncHandlers->second)
				static_cast<EventHandlerImpl<T>*>(handler.get())->callback(event);

		if (handlers != m_handlers.end())
			m_eventQueue.enqueue(std::make_unique<QueuedEventImpl<T>>(event, &handlers->second));
	}

	inline void milk::EventBus::executeEventQueue() {
		std::unique_ptr<QueuedEvent> event;
		while (m_eventQueue.try_dequeue(event))
			event->invoke();
	}

	template<typename T>
	inline EventBus::EventHandlerImpl<T>::EventHandlerImpl(std::function<void(const T&)> callback) :
		callback(callback)
	{}

	template<typename T>
	inline EventBus::QueuedEventImpl<T>::QueuedEventImpl(const T& event, std::vector<std::unique_ptr<EventHandler>>* handlers) :
		QueuedEvent(),
		m_event(event),
		m_handlers(handlers)
	{}

	template<typename T>
	inline void EventBus::QueuedEventImpl<T>::invoke() {
		for (auto& handler : *m_handlers)
			static_cast<EventHandlerImpl<T>*>(handler.get())->callback(m_event);
	}

}