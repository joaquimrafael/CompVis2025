# Projeto 1 (Proj1) – Processamento de imagens

## Computação Visual, Ciência da Computação Mackenzie, Turma 07N 2025.2

## Índice

* [Grupo](#grupo)
* [Descrição geral do projeto](#descrição-geral-do-projeto)
* [Funcionamento do projeto](#funcionamento-do-projeto)
* [Contribuições individuas](#contribuições-individuas)
  * [Antonio](#antonio)
  * [Gustavo](#gustavo)
  * [Joaquim](#joaquim)
  * [Lucas](#lucas)
* [Compilação e Execução](#compilação-e-execução)
  * [MacOS](#macos)
  * [Windows](#windows)

### Grupo

* Antonio Carlos Sciamarelli Neto - 10409160
* Gustavo Matta - 10410154
* Joaquim Rafael Mariano Prieto Pereira - 10408805
* Lucas Trebacchetti Eiras - 10401973

### Descrição geral do projeto

Este projeto tem como proposito desenvolver um software de processamento de imagens em linguagem C, usando a biblioteca
SDL (Simple DirectMedia Layer) em sua versão 3.

### Funcionamento do projeto

### Contribuições individuas

#### Antonio

* Documentacao
* Criacao do histograma
* Escalas de cinza
* Configuracao do botao
* Refinamento

#### Gustavo

* Documentacao
* Consulta Teorica
* Carregamento da imagem
* Salvamento da imagem output
* Code review

#### Joaquim

* Arquitetura do projeto
* Criacao do repositorio e organizacao dos arquivos
* Carregamento da Imagem e adaptacao do tamanho da janela
* Criacao da janela secundaria
* Calculo do histograma e equalizacao
* Salvamento da imagem output
* Interacao com o botao
* Mostrar Caracteristicas da imagem
* Code Review e refinamentos

#### Lucas

* Conversao e dectacao tons de cinza
* Geracao da janela secundaria
* Criacao do histograma
* Equalizacao
* Configuracao do botao
* Configuracao dos eventos
* Code Review e refinamentos

### Compilação e Execução

#### MacOS

* Compilar: gcc -o meu_app.exe main.c $(pkgconf --cflags --libs sdl3 sdl3-image sdl3-ttf)
* Executar: ./meu_app.exe <nome_do_arquivo>

#### Windows

* Compilar & Executar: 
* Baixar bibliotecas SDL3, SDL3_image, SDL_ttf e adicionar as respectivas .dll(s) na pasta do projeto
* Comando de compilação: gcc main.c -I<path_para_includes> -L<path_para_libs> -lSDL3 -lSDL3_image -lSDL3_ttf
* ./main.exe img/<imagem_escolhida>
