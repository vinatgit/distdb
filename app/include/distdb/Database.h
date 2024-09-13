#ifndef DATABASE_SERVER_H
#define DATABASE_SERVER_H

#include <mutex>
#include <vector>

#include "absl/log/log.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "dbserver.grpc.pb.h"
#include "dbserver.pb.h"
#include "Index.h"
#include "Metadata.h"

class Database final : public dbserver::DbServer::Service {
public:
	grpc::Status add( grpc::ServerContext* context, const dbserver::Request* request, dbserver::Response* response ) override;

private:
	std::mutex mutex_;
	Index index_;
	Metadata meta_;
};

# endif // DATABASE_SERVER_H
