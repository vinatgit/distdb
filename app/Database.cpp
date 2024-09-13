#include "absl/log/log.h"

#include "distdb/Database.h"

grpc::Status Database::add( grpc::ServerContext* context, const dbserver::Request* request, dbserver::Response* response ) {
	std::string key = request->key();
	std::vector< uint32_t > frames( request->frames_size() );
	for( size_t idx = 0; idx < frames.size(); idx++ ) {
		frames[ idx ] = request->frames( idx );
	}

	std::vector< int > data( request->data_size() );
	for( size_t idx = 0; idx < data.size(); idx++ ) {
                data[ idx ] = request->data( idx );
        }
	
	LOG(INFO) << "DATABASE: Received request for add " << key;
	{
		std::lock_guard< std::mutex > lock( mutex_ );
		uint32_t rc = index_.add( data );
		if( rc != 0 ) {
			response->set_rc( rc );
			return grpc::Status::OK;
		}

		rc = meta_.add( key, frames );
		if( rc != 0 ) {
                        response->set_rc( rc );
                        return grpc::Status::OK;
                }
	}

	response->set_rc( 0 );
	return grpc::Status::OK;
}
