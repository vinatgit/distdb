#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"

#include "distdb/Client.h"

ABSL_FLAG( std::string, target, "localhost:50051", "Server address" );

int main( int argc, char** argv ) {
	absl::ParseCommandLine( argc, argv );
	std::string targetStr( absl::GetFlag( FLAGS_target ) );
	Client client( grpc::CreateChannel( targetStr, grpc::InsecureChannelCredentials() ) );

	std::string opStr;
	while( 1 ) {
		std::cout << "Create message: ";
		std::cin >> opStr;
		std::string reply = client.operation( opStr );
		LOG(INFO) << "CLIENT: Received " << reply; 
	}

	return 0;
}
