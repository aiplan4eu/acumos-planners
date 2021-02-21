FROM ubuntu:18.04

LABEL maintainer="felix@laas.fr"

RUN set -eux; \
	apt-get update; \
	apt-get install -y --no-install-recommends coinor-libcbc-dev

COPY bin/popf /usr/local/bin
COPY bin/ff /usr/local/bin
COPY bin/optic-clp /usr/local/bin
COPY bin/planner_ACUMOS_bridge /usr/local/bin

EXPOSE 8061

ENTRYPOINT ["planner_ACUMOS_bridge"]
