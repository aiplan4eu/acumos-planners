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

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <streambuf>

#include <unistd.h>

#include <grpcpp/grpcpp.h>

#include "PDDL-planner.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using AIPlanner::PlanRequest;
using AIPlanner::PlanReply;
using AIPlanner::Planner;

class PlannerClient {
public:
  PlannerClient(std::shared_ptr<Channel> channel)
    : stub_(Planner::NewStub(channel)) {}
  
  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string planner_ff(std::string dom, std::string prob, std::string par) {
    // Data we are sending to the server.
    PlanRequest request;
    request.set_domain(dom);
    request.set_problem(prob);
    request.set_parameters(par);

    // Container for the data we expect from the server.
    PlanReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->planner_ff(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      if (reply.success()) 
	return reply.plan();
      else
	return "No plan";
    } else {
      std::cerr << "Error: " << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "No plan";
    }
  }
  std::string planner_popf(std::string dom, std::string prob, std::string par) {
    // Data we are sending to the server.
    PlanRequest request;
    request.set_domain(dom);
    request.set_problem(prob);
    request.set_parameters(par);

    // Container for the data we expect from the server.
    PlanReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->planner_popf(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      if (reply.success()) 
	return reply.plan();
      else
	return "No plan";
    } else {
      std::cerr << "Error: " << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "No plan";
    }
  }
  std::string planner_optic(std::string dom, std::string prob, std::string par) {
    // Data we are sending to the server.
    PlanRequest request;
    request.set_domain(dom);
    request.set_problem(prob);
    request.set_parameters(par);

    // Container for the data we expect from the server.
    PlanReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->planner_optic(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      if (reply.success()) 
	return reply.plan();
      else
	return "No plan";
    } else {
      std::cerr << "Error: " << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "No plan";
    }
  }

 private:
  std::unique_ptr<Planner::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint specified by
  // the argument "--target=" which is the only expected argument.
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).

  std::string target_str = "localhost:8061";

  PlannerClient planner(grpc::CreateChannel(
      target_str, grpc::InsecureChannelCredentials()));

  if (argc != 5) {
    std::cout << "We need which planner ff, optic or popf, and 3 filenames as arguments, domain, problem and parameters" << std::endl;
    return 1;
  }
  
  
  std::ifstream domainStream(argv[2]);
  std::string domain((std::istreambuf_iterator<char>(domainStream)),
		     std::istreambuf_iterator<char>());
  
  std::ifstream problemStream(argv[3]);
  std::string problem((std::istreambuf_iterator<char>(problemStream)),
		      std::istreambuf_iterator<char>());

  std::ifstream paramsStream(argv[4]);
  std::string parameters ((std::istreambuf_iterator<char>(paramsStream)),
			  std::istreambuf_iterator<char>());
  std::string res;
       
  if (!strcmp(argv[1],"ff")) {
    res = planner.planner_ff(domain, problem, parameters);
   } else if (!strcmp(argv[1],"popf")) {
    res = planner.planner_popf(domain, problem, parameters);
  } else if (!strcmp(argv[1],"optic")) {  
    res = planner.planner_optic(domain, problem, parameters);
  } else {
    std::cout << "You need to specify as first argument which planner to call: ff, optic or popf." << std::endl;
    return 1;
  }
   std::cout << "Plan received: " << res << std::endl;
 
  return 0;
}
