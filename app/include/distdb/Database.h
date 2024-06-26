#ifndef DBSERVER_SERVER_H
#define DBSERVER_SERVER_H

#include <memory>
#include <vector>

#include "absl/log/log.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "dbserver.grpc.pb.h"
#include "dbserver.pb.h"

class Database final : public dbserver::DbServer::Service {
public:
	grpc::Status operation( grpc::ServerContext* context, const dbserver::Request* request, dbserver::Response* response ) override;
};

# endif // DBSERVER_SERVER_H
