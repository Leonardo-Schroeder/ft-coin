#!/bin/bash

# build-memory.sh - Script de compilação para a versão "somente memória" do ft-coin
#
# Uso:
# ./build-memory.sh        - Compila e linka o projeto.
# ./build-memory.sh clean  - Remove os arquivos gerados pela compilação.

# --- Configuração ---

CXX="g++"

# Flags do compilador:
# -DMEMORY_ONLY: Define a flag que ativa o modo "somente memória" no código.
CXXFLAGS="-std=c++11 -Wall -Wextra -pedantic -g -DMEMORY_ONLY"

# NÃO PRECISAMOS MAIS DAS FLAGS DO MARIADB
# INCLUDES=""
# LDFLAGS=""
# LDLIBS=""

# Novo nome para o executável de saída
TARGET="ft-coin-memory"

OBJ_DIR="obj"

# Lista de arquivos fonte SEM as implementações do MariaDB e a conexão
SRCS=(
    "Start.cpp"
    "Menu.cpp"
    "Controller.cpp"
    "Help/HelpService.cpp"
    "Report/ReportService.cpp"
    "Wallet/Wallet.cpp"
    "Wallet/WalletService.cpp"
    "Wallet/WalletDAOMemory.cpp"
    "Movement/Movement.cpp"
    "Movement/MovementService.cpp"
    "Movement/MovementDAOMemory.cpp"
    "Oracle/Oracle.cpp"
    "Oracle/OracleDAOMemory.cpp"
)

OBJS=()
for src in "${SRCS[@]}"; do
    OBJS+=("$OBJ_DIR/$(basename "$src" .cpp).o")
done

# --- Lógica do Script (sem alterações) ---

set -e

clean() {
    echo "Limpando arquivos de compilação..."
    rm -rf "$OBJ_DIR" "$TARGET"
    echo "Limpeza concluída."
}

if [ "$1" == "clean" ]; then
    clean
    exit 0
fi

echo "Iniciando a compilação do projeto '$TARGET' (modo somente memória)..."

mkdir -p "$OBJ_DIR"
mkdir -p "$OBJ_DIR/Wallet" "$OBJ_DIR/Movement" "$OBJ_DIR/Oracle" "$OBJ_DIR/Report" "$OBJ_DIR/Help"

echo "-----------------------------------------"
for i in "${!SRCS[@]}"; do
    src=${SRCS[$i]}
    obj=${OBJS[$i]}
    echo "Compilando: $src -> $obj"
    $CXX $CXXFLAGS -c "$src" -o "$obj"
done
echo "-----------------------------------------"

echo "Linkando o executável: $TARGET"
# O comando de linkagem agora é muito mais simples
$CXX $CXXFLAGS -o "$TARGET" "${OBJS[@]}"

echo "-----------------------------------------"
echo "Build concluído com sucesso!"
echo "Execute o programa com: ./$TARGET"