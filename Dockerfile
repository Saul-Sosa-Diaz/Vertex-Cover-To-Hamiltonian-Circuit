# Usar Ubuntu como imagen base
FROM ubuntu:latest

# Instalar Julia y C++ junto con otras dependencias necesarias
RUN apt-get update && \
    apt-get install -y build-essential wget && \
    wget https://julialang-s3.julialang.org/bin/linux/x64/1.9/julia-1.9.4-linux-x86_64.tar.gz&& \
    tar -xvzf julia-1.9.4-linux-x86_64.tar.gz && \
    mv julia-1.9.4 /opt/ && \
    ln -s /opt/julia-1.9.4/bin/julia /usr/local/bin/julia

# Verificar la instalación de Julia
RUN julia --version
RUN julia -e 'using Pkg; \
              Pkg.add("Graphs"); \
              Pkg.add("GraphRecipes"); \
              Pkg.add("GraphPlot"); \
              Pkg.add("Colors"); \
              Pkg.add("JSON"); \
              Pkg.add("Plots"); \
              Pkg.add("Cairo"); \
              Pkg.add("JuMP"); \
              Pkg.add("Compose"); \
              Pkg.add("GLPK")'

# Instalar libreria para leer json
RUN apt install nlohmann-json3-dev

# Copiar el código fuente al contenedor
COPY ./src/ /proyecto_VC_HC/src
COPY ./graphInstances/ /proyecto_VC_HC/graphInstances
COPY ./inc/ /proyecto_VC_HC/inc
COPY ./makefile /proyecto_VC_HC/makefile


# Configurar el directorio de trabajo
WORKDIR /proyecto_VC_HC

# Configurar volúmenes para datos de entrada y salida
VOLUME ["/proyecto_VC_HC/img"]

CMD ["tail", "-f", "/dev/null"]
