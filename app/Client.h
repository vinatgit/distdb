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

	std::string operation( const std::string& key ) {
        dbserver::Request request;
        request.set_key( key );

        dbserver::Response response;
        grpc::ClientContext context;
        grpc::Status status = stub_->operation( &context, request, &response );

        if( status.ok() ) {
                return response.message();
        } else {
                LOG(ERROR) << "CLIENT: Call to operation failed with code " << status.error_code() << ": " << status.error_message();
                return "RPC FAILED";
        }
	}

private:
	std::unique_ptr< dbserver::DbServer::Stub > stub_;	
};

#endif // DBSERVER_CLIENT_H
