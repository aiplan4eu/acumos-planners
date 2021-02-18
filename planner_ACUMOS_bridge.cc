/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "PDDL-planner.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using AIPlanner::PlanRequest;
using AIPlanner::PlanReply;
using AIPlanner::Planner;

// Logic and data behind the server's behavior.
class PlannerServiceImpl final : public Planner::Service {
  Status planner_ff(ServerContext* context, const PlanRequest* request,
                  PlanReply* reply) override {

    std::cout << "gRPC server got: " <<  request->domain() << " and " << request->problem() << " and " << request->parameters() << std::endl;

    std::ofstream out_domain("/tmp/domain");
    out_domain << request->domain();
    out_domain.close();

    
    std::ofstream out_fact("/tmp/problem");
    out_fact << request->problem();
    out_fact.close();

    char *command = (char *)"ff -p /tmp/ -o domain -f problem > /tmp/solution";

    
    int ret = system(command);
    
    if ( !ret ) {
      reply->set_success(true);
      
      std::ifstream plan_res("/tmp/solution");
      std::string plan_string((std::istreambuf_iterator<char>(plan_res)),
			      std::istreambuf_iterator<char>());
      plan_res.close();
      
      std::remove("/tmp/solution");
      std::remove("/tmp/domain");
      std::remove("/tmp/problem");
      
      reply->set_plan(plan_string);
      
    } else {
      reply->set_success(false);
      reply->set_plan("no plan");
      
    }
    return Status::OK;
  }
  Status planner_popf(ServerContext* context, const PlanRequest* request,
                  PlanReply* reply) override {

    std::cout << "gRPC server got: " <<  request->domain() << " and " << request->problem() << " and " << request->parameters() << std::endl;

    std::ofstream out_domain("/tmp/domain");
    out_domain << request->domain();
    out_domain.close();

    
    std::ofstream out_fact("/tmp/problem");
    out_fact << request->problem();
    out_fact.close();

    char *command = (char *)"popf /tmp/domain /tmp/problem > /tmp/solution";

    
    int ret = system(command);
    
    if ( !ret ) {
      reply->set_success(true);
      
      std::ifstream plan_res("/tmp/solution");
      std::string plan_string((std::istreambuf_iterator<char>(plan_res)),
			      std::istreambuf_iterator<char>());
      plan_res.close();

      std::remove("/tmp/domain");
      std::remove("/tmp/problem");
      std::remove("/tmp/solution");
      
      reply->set_plan(plan_string);
      
    } else {
      reply->set_success(false);
      reply->set_plan("no plan");
      
    }
    return Status::OK;
  }
  
  Status planner_optic(ServerContext* context, const PlanRequest* request,
                  PlanReply* reply) override {

    std::cout << "gRPC server got: " <<  request->domain() << " and " << request->problem() << " and " << request->parameters() << std::endl;

    std::ofstream out_domain("/tmp/domain");
    out_domain << request->domain();
    out_domain.close();

    
    std::ofstream out_fact("/tmp/problem");
    out_fact << request->problem();
    out_fact.close();

    char *command = (char *)"optic-clp -N /tmp/domain /tmp/problem > /tmp/solution";

    
    int ret = system(command);
    
    if ( !ret ) {
      reply->set_success(true);
      
      std::ifstream plan_res("/tmp/solution");
      std::string plan_string((std::istreambuf_iterator<char>(plan_res)),
			      std::istreambuf_iterator<char>());
      plan_res.close();

      std::remove("/tmp/domain");
      std::remove("/tmp/problem");
      std::remove("/tmp/solution");
      
      reply->set_plan(plan_string);
      
    } else {
      reply->set_success(false);
      reply->set_plan("no plan");
      
    }
    return Status::OK;
  }

};

int main(int argc, char** argv) {

  std::string server_address("0.0.0.0:8061");
  PlannerServiceImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;



  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();

  return 0;
}
