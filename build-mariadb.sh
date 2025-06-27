#!/bin/bash

# build.sh - Script de compilação para o projeto ft-coin
#
# Uso:
# ./build.sh        - Compila e linka o projeto.
# ./build.sh clean  - Remove os arquivos gerados pela compilação.

# --- Configuração ---

# O compilador C++
CXX="g++"

# Flags do compilador:
# -std=c++11: Usa o padrão C++11, como solicitado.
# -Wall -Wextra -pedantic: Ativa um conjunto rigoroso de avisos para garantir código de alta qualidade.
# -g: Inclui informações de debug para permitir o uso de um depurador como o gdb.
CXXFLAGS="-std=c++11 -Wall -Wextra -pedantic -g"

# Caminhos de include (cabeçalhos)
INCLUDES="-I/usr/include/mysql"

# Flags do Linker (caminhos de bibliotecas)
LDFLAGS="-L/usr/lib64"

# Bibliotecas a serem linkadas
LDLIBS="-lmariadb"

# Nome do executável de saída
TARGET="ft-coin"

# Diretório para os arquivos objeto
OBJ_DIR="obj"

# Lista de todos os arquivos fonte .cpp do projeto
SRCS=(
    "Start.cpp"
    "Menu.cpp"
    "DatabaseConnection.cpp"
    "Controller.cpp"
    "Help/HelpService.cpp"
    "Report/ReportService.cpp"
    "Wallet/Wallet.cpp"
    "Wallet/WalletService.cpp"
    "Wallet/WalletDAOMemory.cpp"
    "Wallet/WalletDAOMariaDB.cpp"
    "Movement/Movement.cpp"
    "Movement/MovementService.cpp"
    "Movement/MovementDAOMemory.cpp"
    "Movement/MovementDAOMariaDB.cpp"
    "Oracle/Oracle.cpp"
    "Oracle/OracleDAOMemory.cpp"
    "Oracle/OracleDAOMariaDB.cpp"
)

# Gera a lista de arquivos objeto a partir da lista de fontes
OBJS=()
for src in "${SRCS[@]}"; do
    # Extrai o nome base do arquivo e adiciona ao diretório de objetos com extensão .o
    OBJS+=("$OBJ_DIR/$(basename "$src" .cpp).o")
done

# --- Lógica do Script ---

# Para o script se qualquer comando falhar
set -e

# Função para limpar os arquivos gerados
clean() {
    echo "Limpando arquivos de compilação..."
    rm -rf "$OBJ_DIR" "$TARGET"
    echo "Limpeza concluída."
}

# Verifica se o primeiro argumento é "clean"
if [ "$1" == "clean" ]; then
    clean
    exit 0
fi

# Compilação e Linkagem
echo "Iniciando a compilação do projeto '$TARGET'..."

# Cria o diretório de objetos se ele não existir
mkdir -p "$OBJ_DIR"
# Cria subdiretórios para manter a estrutura
mkdir -p "$OBJ_DIR/Wallet" "$OBJ_DIR/Movement" "$OBJ_DIR/Oracle" "$OBJ_DIR/Report" "$OBJ_DIR/Help"


# --- Fase de Compilação ---
# Compila cada arquivo .cpp em um arquivo .o
echo "-----------------------------------------"
for i in "${!SRCS[@]}"; do
    src=${SRCS[$i]}
    obj=${OBJS[$i]}
    echo "Compilando: $src -> $obj"
    $CXX $CXXFLAGS $INCLUDES -c "$src" -o "$obj"
done
echo "-----------------------------------------"


# --- Fase de Linkagem ---
# Linka todos os arquivos .o para criar o executável final
echo "Linkando o executável: $TARGET"
$CXX $CXXFLAGS $LDFLAGS -o "$TARGET" "${OBJS[@]}" $LDLIBS

echo "-----------------------------------------"
echo "Build concluído com sucesso!"
echo "Execute o programa com: ./$TARGET"