// Define to don't duplicate the header when included twice
#ifndef __Signal__like__RBXScriptSignal__
#define __Signal__like__RBXScriptSignal__

#include <vector>
#include <chrono>
#include <thread>
#include <functional>

template <typename... Parameters> class Signal {
	private:
	std::vector<std::function<void(Parameters...)>> Connections;

	// This class helps a connection
	// be disconnected or checks if connected
	class Handler {
		private:
		std::function<void()> __Disconnect__;

		public:
		Handler(std::function<void()> Function) {
			// Since this class cannot access the members of the main class
			// then the constructor receives an external function that does this
			// and this function will be called on the "Disconnect" (see Connect)
     			__Disconnect__ = Function;
    		};

		// Connection exists or not
		bool Connected = true;

		// Remove the function in Connections
		void Disconnect() {
			if (!Connected) return;
			__Disconnect__();
			Connected = false;
		};
	};

	protected:
	bool Idle {true}; // If it's firing or not

	public:
	Handler Connect(std::function<void(Parameters...)> const& Function) {
		// Add function to Connections
		Connections.push_back(Function);

		// Creates a new connection
		Handler Connection([this, Index = Connections.size() - 1](){
			Connections.erase(Connections.begin() + Index);
		});

		// Return the initialized connection
		return Connection;
	};

	// Yields the thread until the signal is fired
	int Wait() {
		std::chrono::steady_clock::time_point Time {std::chrono::steady_clock::now()};
		while (Idle) std::this_thread::yield();

    		// Return the elapsed time to fire (milliseconds)
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - Time).count();
	};

	// Fire all connections
	void Fire(Parameters... Arguments) {
		if (Connections.size() == 0) return;

		Idle = false;
		for (auto const& Function : Connections) Function(Arguments...);
		Idle = true;
	};
};
