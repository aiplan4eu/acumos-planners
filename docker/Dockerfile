# We start from the fd docker image

FROM aibasel/downward:latest

LABEL maintainer="felix@laas.fr"

# adding the other planner and the grpc server.

RUN set -eux; \
	apt-get update; \
	apt-get install -y --no-install-recommends coinor-libcbc-dev

COPY bin/popf /usr/local/bin
COPY bin/ff /usr/local/bin
COPY bin/optic-clp /usr/local/bin
COPY bin/planner_ACUMOS_bridge /usr/local/bin

# add the path to fast_downward.py so our gRPC bridge will find the planner.
ENV PATH=/workspace/downward/:$PATH

#expose the gRPC ACUMOS port
EXPOSE 8061

ENTRYPOINT ["planner_ACUMOS_bridge"]
