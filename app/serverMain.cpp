#include <chrono>
#include <memory>
#include <string>
#include <thread>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"

#include "Database.h"

ABSL_FLAG( uint16_t, port, 50051, "Server port for the service" );

void runServer( uint16_t port ) {
	std::string serverAddress = absl::StrFormat( "0.0.0.0:%d", port );
	Database service;

	grpc::EnableDefaultHealthCheckService( true );
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();
	
	grpc::ServerBuilder builder;
	builder.AddListeningPort( serverAddress, grpc::InsecureServerCredentials() );
	builder.RegisterService( &service );

	std::unique_ptr< grpc::Server > server( builder.BuildAndStart() );
	LOG(INFO) <<  "SERVER: Listening on " << serverAddress;

	server->Wait();
}

int main( int argc, char** argv ) {
	absl::ParseCommandLine( argc, argv );
	runServer( absl::GetFlag( FLAGS_port ) );
	return 0;
}

