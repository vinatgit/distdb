#ifndef DBSERVER_CLIENT_H
#define DBSERVER_CLIENT_H

#include <chrono>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "dbserver.grpc.pb.h"

class Client {
public:
	Client( std::shared_ptr< grpc::Channel > channel ) : stub_( dbserver::DbServer::NewStub( channel ) ) {}

	std::string operation( const std::string& key );

private:
	std::unique_ptr< dbserver::DbServer::Stub > stub_;	
};

#endif // DBSERVER_CLIENT_H
