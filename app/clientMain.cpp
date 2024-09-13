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

	std::string key, framesStr, dataStr;
	while( 1 ) {
		std::cout << "Enter key: ";
		std::cin >> key;
		std::cout << "Enter frames: ";
		std::cin >> framesStr;
		std::cout << "Enter data: ";
                std::cin >> dataStr;

		std::vector< uint32_t > frames;
		while( !framesStr.empty() ) {
			size_t idx = framesStr.find( ',' );
			if( idx == std::string::npos ) {
				frames.push_back( std::stoi( framesStr ) );
				break;
			}

			frames.push_back( std::stoi( framesStr.substr( 0, idx ) ) );
			framesStr = framesStr.substr( idx + 1 );
		}
		std::vector< int > data;
		while( !dataStr.empty() ) {
                        size_t idx = dataStr.find( ',' );
                        if( idx == std::string::npos ) {
                                data.push_back( std::stoi( dataStr ) );
                                break;
                        }

                        data.push_back( std::stoi( dataStr.substr( 0, idx ) ) );
                        dataStr = dataStr.substr( idx + 1 );
                }

		uint32_t rc = client.add( key, frames, data );
		LOG(INFO) << "CLIENT: Received return code = " << rc; 
	}

	return 0;
}
