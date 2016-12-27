@echo off

REM %% Procedimento para inicializar tabelas e executar separadamente cada caso de teste no Windows

REM Variaveis:
REM %n = numero de sementes
REM %i = arquivo de instancia atual
REM %s - semente para rodar randomizados
REM %h - heuristica usada

set %%n=30
for %%i in (.\instanciasTestesSteiner\*) do ^
for /L %%s in (2, 6, 30) do ^
for /L %%h in (1, 1, 3) do ^
bin\Trabalho_Grafos.exe "%%i" %%h %%s %%n

pause
