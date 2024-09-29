#ifndef DATABASE_DATABASE_H
#define DATABASE_DATABASE_H

#include <memory>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "absl/log/log.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "dbserver.grpc.pb.h"
#include "dbserver.pb.h"
#include "Consts.h"
#include "Index.h"

class Database {
public:
	RETURN_CODE add( const std::string& path, const uint64_t& timestamp, const std::vector< uint32_t >& data );
	RETURN_CODE get( const std::string& path, uint64_t& timestamp, std::vector< uint32_t >& data ) const;
	RETURN_CODE remove( const std::string& path, const uint64_t& timestamp );

private:
	mutable std::shared_mutex mutex_;
	std::unordered_map< std::string, std::shared_ptr< Index > > data_; 
};

#endif // DATABASE_DATABASE_H
