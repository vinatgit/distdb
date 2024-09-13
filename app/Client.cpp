#include "absl/log/log.h"

#include "distdb/Client.h"

uint32_t Client::add( const std::string& key, const std::vector< uint32_t >& frames, const std::vector< int >& data ) {
	dbserver::Request request;
	request.set_key( key );
	for( auto& ele : frames ) {
                request.add_frames( ele );
        }
	for( auto& ele : data ) {
		request.add_data( ele );
	}

	dbserver::Response response;
	grpc::ClientContext context;
	grpc::Status status = stub_->add( &context, request, &response );

	if( !status.ok() ) {
		LOG(ERROR) << "CLIENT: Call to add failed with code " << status.error_code() << ": " << status.error_message();
	}

	return response.rc();
}
