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

#### Geral do código:
#### 1. Entrada do programa  
**1.1** O programa recebe o nome da imagem como argumento na linha de comando.  

#### 2. Janelas de exibição  
**2.1 Janela principal**: exibe a imagem carregada, podendo ser a versão **original** ou **equalizada**.  

**2.2 Janela secundária**: exibe:  
**2.2.1** Botão de alternância entre os modos “Original” e “Equalizado”.  
**2.2.2** Histograma com a distribuição de intensidades da imagem.  
**2.2.3** Análise de brilho e contraste obtida a partir de estatísticas da imagem.  

#### 3. Funcionalidades extras  
**3.1** Conversão automática de imagens coloridas para tons de cinza.  
**3.2** Salvamento da imagem exibida pressionando a tecla **S**, gerando o arquivo `output.png`.  
**3.3** Interatividade por botão e mudança de cursor ao passar sobre elementos interativos.  

#### Explicação Detalhada:
#### Histograma

O histograma foi implementado para mostrar a distribuição de intensidades de cinza da imagem:

- **Contagem de intensidades**: cada pixel é convertido para escala de cinza (quando necessário) e seu valor (0–255) é contabilizado.  
- **Normalização para proporção (%)**: a frequência é convertida em proporção relativa para permitir comparações entre imagens diferentes:  

`proporcao[i] = (contagem[i] / total_pixels) * 100`

**Escalonamento no gráfico**:  
- Cada intensidade (0–255) é representada por uma barra.  
- A altura da barra é proporcional à frequência normalizada, limitada a 200px de altura.  
- Isso garante que a barra mais alta ocupe todo o espaço disponível e as demais fiquem proporcionais.  

**Renderização**:  
- Eixo X → valores de intensidade (0–255).  
- Eixo Y → frequência relativa.  
- O gráfico é centralizado na janela secundária e desenhado em preto, com eixos destacados em rosa.  


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
