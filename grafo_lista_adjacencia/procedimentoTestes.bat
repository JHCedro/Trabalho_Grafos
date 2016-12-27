@echo off

REM %% Procedimento para inicializar tabelas e executar separadamente cada caso de teste no Windows

REM Variaveis:
REM %n = numero de sementes
REM %i = arquivo de instancia atual
REM %s - semente para rodar randomizados
REM %h - heuristica usada

echo Compilando arquivos necessarios...
REM g++ -std=c++11 -O3 src/*.cpp -B include/ -o Trabalho_Grafos.exe
REM g++ -std=c++11 -O3 src/Arco.cpp src/Grafo.cpp src/GrafoHash.cpp src/GrafoLista.cpp src/main.cpp src/MenuTrabalho.cpp src/No.cpp src/NoHash.cpp src/NoLista.cpp -B include/ -o bin/Trabalho_Grafos.exe

g++ -std=c++11 src/criarTabelas.cpp -o bin/criarTabelas.exe
bin\criarTabelas.exe

set %%n=30
for %%i in (.\instanciasTestesSteiner\*) do ^
for /L %%s in (1, 1, 30) do ^
for /L %%h in (1, 1, 3) do ^
bin\Debug\Trabalho_Grafos.exe "%%i" %%h %%s %%n

pause
