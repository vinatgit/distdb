#include <fstream>

#include "absl/log/log.h"

#include "distdb/Client.h"

uint32_t Client::add( const std::string& key, const uint64_t& timestamp, const uint64_t& fileSize, const std::vector< uint32_t >& data ) {
	dbserver::Request request;
	request.set_key( key );
	request.set_timestamp( timestamp );
	request.set_size( fileSize );
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

uint32_t Client::get( const std::string& key, uint64_t& fileSize, std::vector< uint32_t >& respData ) {
	dbserver::Request request;
        request.set_key( key );

        dbserver::Response response;
        grpc::ClientContext context;
        grpc::Status status = stub_->get( &context, request, &response );

        if( !status.ok() ) {
                LOG(ERROR) << "CLIENT: Call to add failed with code " << status.error_code() << ": " << status.error_message();
        }

	fileSize = response.size();
	respData.resize( response.data_size() );
        for( size_t idx = 0; idx < respData.size(); idx++ ) {
                respData[ idx ] = response.data( idx );
        }

        return response.rc();
}

uint32_t Client::remove( const std::string& key, const uint64_t& timestamp ) {
        dbserver::Request request;
        request.set_key( key );
	request.set_timestamp( timestamp );

        dbserver::Response response;
        grpc::ClientContext context;
        grpc::Status status = stub_->remove( &context, request, &response );

        if( !status.ok() ) {
                LOG(ERROR) << "CLIENT: Call to add failed with code " << status.error_code() << ": " << status.error_message();
        }

        return response.rc();
}

