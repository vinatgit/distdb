#include <chrono>
#include <fstream>
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

	while( 1 ) {
		int option;
		std::cout << "Operations:" << std::endl;
		std::cout << "Upload - 1" << std::endl;
		std::cout << "Download - 2" << std::endl;
		std::cout << "Delete - 3" << std::endl;
		std::cout << "Select operation: ";
		std::cin >> option;

		std::string path;
                std::cout << "Enter path: ";
                std::cin >> path;
		uint32_t rc = 0;
		uint64_t timestamp;

		switch( option ) {
		case 1: {
			std::ifstream fd( path.c_str(), std::ios::binary | std::ios::ate );
			if( !fd.good() ) {
				LOG(ERROR) << "File " << path << " not found";
				continue;
			}

			timestamp = std::chrono::duration_cast< std::chrono::microseconds >( std::chrono::system_clock::now().time_since_epoch() ).count();
			int fileSize = fd.tellg();
			fd.seekg( 0, std::ios::beg );
			char* buffer = new char[ fileSize ];
			fd.read( buffer, fileSize );
			auto bufferUint32 = reinterpret_cast< uint32_t* >( buffer );
			std::vector< uint32_t > data( bufferUint32, bufferUint32 + fileSize / sizeof( uint32_t ) );
			delete[] buffer;
			fd.close();

			rc = client.add( path, timestamp, data );
			break;
		}
		case 2: {
			std::string destinationDir;
			std::cout << "Enter destination directory: ";
			std::cin >> destinationDir;
			std::vector< uint32_t > data;
			rc = client.get( path, data );

			size_t backslashPos = path.rfind( '/' );
			std::string destinationPath = destinationDir + "/";
			if( backslashPos == std::string::npos ) {
				destinationPath += path;
			} else {
				destinationPath += path.substr( backslashPos + 1 );
			}
			LOG(INFO) << "Writing data to " << destinationPath;
			std::ofstream fd( destinationPath.c_str(), std::ios::binary );
			fd.write( reinterpret_cast< const char* >( data.data() ), data.size() * sizeof( uint32_t ) );
			fd.close();
			break;
		}
		case 3: {
			timestamp = std::chrono::duration_cast< std::chrono::microseconds >( std::chrono::system_clock::now().time_since_epoch() ).count();
			rc = client.remove( path, timestamp );
                        break;
		}
		default: {
			LOG(ERROR) << "Invalid option " << option;
		}	
		}
			
		LOG(INFO) << "CLIENT: Received return code = " << rc; 
	}

	return 0;
}
