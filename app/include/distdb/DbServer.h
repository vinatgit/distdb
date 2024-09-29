#ifndef DATABASE_DBSERVER_H
#define DATABASE_DBSERVER_H

#include <mutex>
#include <vector>

#include "absl/log/log.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "dbserver.grpc.pb.h"
#include "dbserver.pb.h"
#include "Database.h"

class Server final : public dbserver::DbServer::Service {
public:
	grpc::Status add( grpc::ServerContext* context, const dbserver::Request* request, dbserver::Response* response ) override;
	grpc::Status get( grpc::ServerContext* context, const dbserver::Request* request, dbserver::Response* response ) override;
	grpc::Status remove( grpc::ServerContext* context, const dbserver::Request* request, dbserver::Response* response ) override;

private:
	Database db_;
};

#endif // DATABASE_DBSERVER_H
