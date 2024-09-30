#ifndef DATABASE_CLIENT_H
#define DATABASE_CLIENT_H

#include <chrono>
#include <memory>
#include <string>
#include <vector>

#include <grpcpp/grpcpp.h>

#include "dbserver.grpc.pb.h"

class Client {
public:
	Client( std::shared_ptr< grpc::Channel > channel ) : stub_( dbserver::DbServer::NewStub( channel ) ) {}

	uint32_t add( const std::string& key, const uint64_t& timestamp, const uint64_t& fileSize, const std::vector< uint32_t >& data );
	uint32_t get( const std::string& key, uint64_t& fileSize, std::vector< uint32_t >& respData );
	uint32_t remove( const std::string& key, const uint64_t& timestamp );
private:
	std::unique_ptr< dbserver::DbServer::Stub > stub_;	
};

#endif // DATABASE_CLIENT_H
