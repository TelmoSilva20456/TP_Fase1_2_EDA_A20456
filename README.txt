============================================================
  PROJETO DE ANTENAS - FASE 1
  Autor: Telmo Silva | a20456
  Data: 2025-03-25
============================================================

	FUNCIONALIDADES IMPLEMENTADAS:

- Estrutura de dados dinâmica com listas ligadas
- Carregamento e salvamento de configurações em ficheiros
- Detecção de efeitos nefastos entre antenas
- Visualização de mapas 12x12 e 10x10
- Interface com menu (main.c)
- Versão automática (main_sem_menu.c)
- Documentação automática com Doxygen

------------------------------------------------------------
	COMO COMPILAR:

1. VERSÃO COM MENU:
    gcc main.c antenas.c -o programa_com_menu

2. VERSÃO AUTOMÁTICA (SEM MENU):
    gcc main_sem_menu.c antenas.c -o programa_sem_menu

------------------------------------------------------------
	COMO EXECUTAR:

No terminal/powershell:

    .\programa_com_menu.exe
    ou
    .\programa_sem_menu.exe

------------------------------------------------------------
	DOCUMENTAÇÃO DOXYGEN:

Para gerar a documentação:


1. Dentro da pasta do projeto, corre:
       doxygen

2. A documentação será gerada em:
       docs/html/index.html

3. Abre o ficheiro index.html com o navegador

------------------------------------------------------------
	FICHEIROS INCLUÍDOS:

- antenas.c / antenas.h ............. Lógica e estruturas
- main.c ............................. Versão com menu
- main_sem_menu.c .................... Execução automática
- antenas_base.txt ................... Exemplo de antenas
- Doxyfile ........................... Configuração Doxygen
- README.txt ......................... Este guia
