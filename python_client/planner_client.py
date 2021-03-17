# A Python client for the PDDL gRPC service created by Felix Ingrand (LAAS-CNRS)
#
# Author: Uwe Köckemann (Örebro University)
import sys
import grpc
import PDDL_planner_pb2_grpc
import PDDL_planner_pb2

grpcport = 8061

# Process command line arguments
planner = sys.argv[1]
f = open(sys.argv[2], "r")
domain_str = f.read()
f.close()
f = open(sys.argv[3], "r")
problem_str = f.read()
f.close()
args = ""
if len(sys.argv) > 4:
    args = sys.argv[4]

# Call planner through gRPC
with grpc.insecure_channel('localhost:%d' % (grpcport)) as channel:
    stub = PDDL_planner_pb2_grpc.PlannerStub(channel)
    # Create request
    req = PDDL_planner_pb2.PlanRequest(
        domain=domain_str,
        problem=problem_str,
        parameters=args)
    # Execute request
    if planner == "ff":
        answer = stub.planner_ff(req) 
    elif planner == "fd":
        answer = stub.planner_fd(req) 
    elif planner == "optic":
        answer = stub.planner_optic(req) 
    elif planner == "popf":
        answer = stub.planner_popf(req)
        
    plan = answer.plan
    success = answer.success
    print("Success?", success)
    print(plan)
