#include "./Signal.hpp"
#include <iostream> // std::cout

int main() {
	// Creates a new signal with one argument and named "PlayerAdded"
	Signal<std::string> PlayerAdded;

	// Creates a new connection named "Joined"
	auto Joined = PlayerAdded.Connect([](std::string Name){
		std::cout << "Player " + Name + " has joined\n";
	});

	/* Connection public proprties:
		bool Connected - If connection's function still exists
		void Disconnect() - Deletes connection function
	*/

	// All connections will be called and receives the argument "GRIPPERTV"
	PlayerAdded.Fire("GRIPPERTV");
	// Output: Player GRIPPERTV has joined

	// Checks if Joined's connection is connected
	// Note: 0 is false and 1 is true
	std::cout << Joined.Connected << "\n";
	// Output: 1

	// After that, the connection's function will not exists
	Joined.Disconnect();

	// This mean, that now the connection ins't connected
	std::cout << Joined.Connected << "\n";
	// Output: 0

	// Now don't have any connection function
	// so this don't do nothing
	PlayerAdded.Fire("pekenoGuguMS");
	
	return 0;
}
