#include "absl/log/log.h"

#include "distdb/Consts.h"
#include "distdb/DbServer.h"

grpc::Status Server::add( grpc::ServerContext* context, const dbserver::Request* request, dbserver::Response* response ) {
	std::string key = request->key();
	uint64_t timestamp = request->timestamp();
	uint64_t fileSize = request->size();
	std::vector< uint32_t > data( request->data_size() );
	for( size_t idx = 0; idx < data.size(); idx++ ) {
                data[ idx ] = request->data( idx );
        }
	
	LOG(INFO) << "SERVER: Uploading " << key;

	RETURN_CODE rc = db_.add( key, timestamp, fileSize, data );
	response->set_rc( rc );
	return grpc::Status::OK;
}

grpc::Status Server::get( grpc::ServerContext* context, const dbserver::Request* request, dbserver::Response* response ) {
	std::string key = request->key();
        uint64_t timestamp;
	uint64_t fileSize;
        std::vector< uint32_t > data;

        LOG(INFO) << "SERVER: Downloading " << key;

        RETURN_CODE rc = db_.get( key, timestamp, fileSize, data );
	response->set_size( fileSize );
	response->set_timestamp( timestamp );
	for( auto& ele : data ) {
		response->add_data( ele );
	}
        response->set_rc( rc );
        return grpc::Status::OK;	
}

grpc::Status Server::remove( grpc::ServerContext* context, const dbserver::Request* request, dbserver::Response* response ) {
        std::string key = request->key();
	uint64_t timestamp = request->timestamp();

        LOG(INFO) << "SERVER: Deleting " << key;

        RETURN_CODE rc = db_.remove( key, timestamp );
        response->set_rc( rc );
        return grpc::Status::OK;
}

