#ifndef DBSERVER_CLIENT_H
#define DBSERVER_CLIENT_H

#include <chrono>
#include <memory>
#include <string>
#include <vector>

#include <grpcpp/grpcpp.h>

#include "dbserver.grpc.pb.h"

class Client {
public:
	Client( std::shared_ptr< grpc::Channel > channel ) : stub_( dbserver::DbServer::NewStub( channel ) ) {}

	uint32_t add( const std::string& key, const std::vector< uint32_t >& frames, const std::vector< int >& data );

private:
	std::unique_ptr< dbserver::DbServer::Stub > stub_;	
};

#endif // DBSERVER_CLIENT_H
