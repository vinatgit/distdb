#include "absl/log/log.h"

#include "distdb/Client.h"

std::string Client::operation( const std::string& key ) {
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
