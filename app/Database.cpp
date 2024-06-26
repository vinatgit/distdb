#include "absl/log/log.h"

#include "distdb/Database.h"

grpc::Status Database::operation( grpc::ServerContext* context, const dbserver::Request* request, dbserver::Response* response ) {
	LOG(INFO) << "DATABASE: Received request for operation " << request->key();
	response->set_message( "Response" );
	return grpc::Status::OK;
}
