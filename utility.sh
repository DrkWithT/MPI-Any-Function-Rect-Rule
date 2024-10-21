# utility.sh: builds program or counts SLOC for project

if [[ $# -ne 1 ]]; then
    echo "usage: ./utility.sh [help | sloc | deb | rel | test | run]"
    exit 1
fi

choice="$1"

if [[ "$choice" = "sloc" ]]; then
    wc -l ./src/**/*.cpp ./src/Include/**/*.hpp
elif [[ "$choice" = "deb" ]]; then
    cmake --fresh -S . -B Build -DDBG_BUILD:BOOL=1 && cmake --build Build;
    cp ./Build/compile_commands.json .
elif [[ "$choice" = "rel" ]]; then
    cmake --fresh -S . -B Build -DDBG_BUILD:BOOL=0 && cmake --build Build;
    cp ./Build/compile_commands.json .
elif [[ "$choice" = "test" ]]; then
    ctest --test-dir Build -V --timeout 3
elif [[ "$choice" = "run" ]]; then
    mpirun -n 2 ./Build/src/MPIRectRule
else
    echo "usage: ./utility.sh [help | sloc | deb | rel | test | run]"
fi
