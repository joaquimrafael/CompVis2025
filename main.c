/*
Projeto 1 (Proj1) – Processamento de imagens
Computação Visual, Ciência da Computação Mackenzie, Turma 07N 2025.2
Grupo:
Antonio Carlos Sciamarelli Neto - 10409160
Gustavo Matta - 10410154
Joaquim Rafael Mariano Prieto Pereira - 10408805
Lucas Trebacchetti Eiras - 10401973
*/

// Includes

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

// Constants

static const char *WINDOW_TITLE = "Tela Principal";
static const char *WINDOW_TITLE2 = "Tela Secundária";
char *IMAGE_FILENAME;

enum constants
{
  DEFAULT_WINDOW_WIDTH = 0,
  DEFAULT_WINDOW_HEIGHT = 0,
};

typedef struct MyWindow MyWindow;
struct MyWindow
{
  SDL_Window *window;
  SDL_Renderer *renderer;
};

typedef struct MyImage MyImage;
struct MyImage
{
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_FRect rect;
};

// Global variables

static MyWindow g_window = { .window = NULL, .renderer = NULL };
static MyImage g_image = {
  .surface = NULL,
  .texture = NULL,
  .rect = { .x = 0.0f, .y = 0.0f, .w = 0.0f, .h = 0.0f }
};

// Function declarations

static bool MyWindow_initialize(MyWindow *window, const char *title, int width, int height, SDL_WindowFlags window_flags);
static void MyWindow_destroy(MyWindow *window);
static void MyImage_destroy(MyImage *image);

// Function implementations

bool MyWindow_initialize(MyWindow *window, const char *title, int width, int height, SDL_WindowFlags window_flags)
{
  SDL_Log("\tMyWindow_initialize(%s, %d, %d)", title, width, height);
  return SDL_CreateWindowAndRenderer(title, width, height, window_flags, &window->window, &window->renderer);
}

void MyWindow_destroy(MyWindow *window)
{
  SDL_Log(">>> MyWindow_destroy()");

  SDL_Log("\tDestruindo MyWindow->renderer...");
  SDL_DestroyRenderer(window->renderer);
  window->renderer = NULL;

  SDL_Log("\tDestruindo MyWindow->window...");
  SDL_DestroyWindow(window->window);
  window->window = NULL;

  SDL_Log("<<< MyWindow_destroy()");
}

void MyImage_destroy(MyImage *image)
{
  SDL_Log(">>> MyImage_destroy()");

  if (!image)
  {
    SDL_Log("\t*** Erro: Imagem inválida (image == NULL).");
    SDL_Log("<<< MyImage_destroy()");
    return;
  }

  if (image->texture)
  {
    SDL_Log("\tDestruindo MyImage->texture...");
    SDL_DestroyTexture(image->texture);
    image->texture = NULL;
  }

  if (image->surface)
  {
    SDL_Log("\tDestruindo MyImage->surface...");
    SDL_DestroySurface(image->surface);
    image->surface = NULL;
  }

  SDL_Log("\tRedefinindo MyImage->rect...");
  image->rect.x = image->rect.y = image->rect.w = image->rect.h = 0.0f;

  SDL_Log("<<< MyImage_destroy()");
}

static SDL_AppResult initialize(void)
{
  SDL_Log(">>> initialize()");

  SDL_Log("\tIniciando SDL...");
  if (!SDL_Init(SDL_INIT_VIDEO))
  {
    SDL_Log("\t*** Erro ao iniciar a SDL: %s", SDL_GetError());
    SDL_Log("<<< initialize()");
    return SDL_APP_FAILURE;
  }

  SDL_Log("\tCriando janela e renderizador...");
  if (!MyWindow_initialize(&g_window, WINDOW_TITLE, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, 0))
  {
    SDL_Log("\tErro ao criar a janela e/ou renderizador: %s", SDL_GetError());
    SDL_Log("<<< initialize()");
    return SDL_APP_FAILURE;
  }

  SDL_Log("<<< initialize()");
  return SDL_APP_CONTINUE;
}

static void shutdown(void)
{
  SDL_Log(">>> shutdown()");

  MyImage_destroy(&g_image);
  MyWindow_destroy(&g_window);

  SDL_Log("\tEncerrando SDL...");
  SDL_Quit();

  SDL_Log("<<< shutdown()");
}

static void render(void)
{
  SDL_SetRenderDrawColor(g_window.renderer, 128, 128, 128, 255);
  SDL_RenderClear(g_window.renderer);

  SDL_RenderTexture(g_window.renderer, g_image.texture, &g_image.rect, &g_image.rect);

  SDL_RenderPresent(g_window.renderer);
}

static void loop(void)
{
  SDL_Log(">>> loop()");

  bool mustRefresh = false;
  render();

  SDL_Event event;
  bool isRunning = true;
  while (isRunning)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_EVENT_QUIT:
        isRunning = false;
        break;

      }
    }

    if (mustRefresh)
    {
      render();
      mustRefresh = false;
    }
  }
  
  SDL_Log("<<< loop()");
}

//------------------------------------------------------------------------------
void createWindow()
{
    int imageWidth = (int)g_image.rect.w;
    int imageHeight = (int)g_image.rect.h;
    if (imageWidth > DEFAULT_WINDOW_WIDTH || imageHeight > DEFAULT_WINDOW_HEIGHT)
    {
        int top = 0;
        int left = 0;
        SDL_GetWindowBordersSize(g_window.window, &top, &left, NULL, NULL);

        SDL_Log("Redefinindo dimensões da janela, de (%d, %d) para (%d, %d), e alterando a posição para (%d, %d).",
        DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, imageWidth, imageHeight, left, top);

        SDL_SetWindowSize(g_window.window, imageWidth, imageHeight);
        SDL_SetWindowPosition(g_window.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

        SDL_SyncWindow(g_window.window);
    }
}

bool isGrayScale(SDL_Surface *surface)
{
  SDL_Log("<<< isGrayScale()");
  SDL_LockSurface(surface);
  Uint32 *pixel = (Uint32*)surface->pixels;
  int size = surface->w*surface->h;
  const SDL_PixelFormatDetails *format = SDL_GetPixelFormatDetails(surface->format);

  for(int i=0;i<size;i++)
  {
    Uint8 r,g,b,a;
    SDL_GetRGBA(pixel[i], format,NULL,&r,&g,&b,&a);
    if(!(r==g && g==b)){
      SDL_UnlockSurface(surface);
      return(false);
    }
  }

  SDL_Log("<<< isGrayScale()");
  SDL_UnlockSurface(surface);
  return(true);
}

void convertToGray(SDL_Surface *surface)
{
    SDL_Log("<<< convertToGray()");
    if (!surface) return;
    SDL_LockSurface(surface);
    Uint32 *pixel = (Uint32*)surface->pixels;
    int size = surface->w*surface->h;

    const SDL_PixelFormatDetails *format = SDL_GetPixelFormatDetails(surface->format);

    for (int i=0;i<size;i++)
    {
        Uint8 r,g,b,a;
        SDL_GetRGBA(pixel[i],format,NULL,&r,&g,&b,&a);
        double y = 0.2125*(double)r+0.7154*(double)g+0.0721*(double)b;
        Uint8 gray = (Uint8)y;

        pixel[i] = SDL_MapRGBA(format,NULL,gray,gray,gray,a);
    }

    SDL_UnlockSurface(surface);
    SDL_Log(">>> convertToGray()");
}


void loadImage(const char *filename, SDL_Renderer *renderer, MyImage *output_image)
{
  SDL_Log(">>> loadImage(\"%s\")", filename);

  if (!filename)
  {
    SDL_Log("\t*** Erro: Nome do arquivo inválido (filename == NULL).");
    SDL_Log("<<< loadImage(\"%s\")", filename);
    return;
  }

  if (!renderer)
  {
    SDL_Log("\t*** Erro: Renderer inválido (renderer == NULL).");
    SDL_Log("<<< loadImage(\"%s\")", filename);
    return;
  }

  if (!output_image)
  {
    SDL_Log("\t*** Erro: Imagem de saída inválida (output_image == NULL).");
    SDL_Log("<<< loadImage(\"%s\")", filename);
    return;
  }

  MyImage_destroy(output_image);

  SDL_Log("\tCarregando imagem \"%s\" em uma superfície...", filename);
  SDL_Surface *surface = IMG_Load(filename);
  if (!surface)
  {
    SDL_Log("\t*** Erro ao carregar a imagem: %s", SDL_GetError());
    SDL_Log("<<< loadImage(\"%s\")", filename);
    return;
  }

  SDL_Log("\tConvertendo superfície para formato RGBA32...");
  output_image->surface = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);
  SDL_DestroySurface(surface);
  if (!output_image->surface)
  {
    SDL_Log("\t*** Erro ao converter superfície para formato RGBA32: %s", SDL_GetError());
    SDL_Log("<<< load_rgba32(\"%s\")", filename);
    return;
  }

  bool isGray = isGrayScale(output_image->surface);
  isGrayScale(output_image->surface) ? SDL_Log("\tÉ cinza") : SDL_Log("\tÉ colorida");

  if(!isGray){
    convertToGray(output_image->surface);
  }


  SDL_Log("\tCriando textura a partir da superfície...");
  output_image->texture = SDL_CreateTextureFromSurface(renderer, output_image->surface);
  if (!output_image->texture)
  {
    SDL_Log("\t*** Erro ao criar textura: %s", SDL_GetError());
    SDL_Log("<<< load_rgba32(\"%s\")", filename);
    return;
  }

  SDL_Log("\tObtendo dimensões da textura...");
  SDL_GetTextureSize(output_image->texture, &output_image->rect.w, &output_image->rect.h);

  SDL_Log("<<< load_rgba32(\"%s\")", filename);
}

int main(int argc, char *argv[])
{
    atexit(shutdown);

    if(argc < 2) {
        SDL_Log("Uso: %s <arquivo de imagem>", argv[0]);
        return SDL_APP_FAILURE;
    }

    if (initialize() == SDL_APP_FAILURE)
        return SDL_APP_FAILURE;

    IMAGE_FILENAME = argv[1];

    loadImage(IMAGE_FILENAME, g_window.renderer, &g_image);

    createWindow();

    loop();

    return 0;
}