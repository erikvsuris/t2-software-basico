
# 🛠️ Biblioteca de Gerenciamento de Memória  

Projeto de biblioteca em C para **gerenciamento de memória personalizada**, simulando alocações dinâmicas em um bloco contínuo. Ideal para aprendizado e prática de otimização de memória em sistemas embarcados e ambientes de recursos limitados.

---

## ✨ Funcionalidades  

- **Inicialização da Memória**  
  Cria um bloco contínuo para alocações.  
  Função: `mymemory_init(size_t size)`

- **Alocação Dinâmica**  
  Permite alocar blocos de memória dentro do pool inicializado.  
  Função: `mymemory_alloc(mymemory_t *memory, size_t size)`

- **Liberação de Memória**  
  Remove um bloco previamente alocado.  
  Função: `mymemory_free(mymemory_t *memory, void *ptr)`

- **Visualização do Estado Atual**  
  Lista todas as alocações e seus endereços.  
  Função: `mymemory_display(mymemory_t *memory)`

- **Estatísticas da Memória**  
  Exibe métricas como:  
  - Memória total utilizada.  
  - Maior bloco contínuo disponível.  
  - Número de fragmentos livres.  
  Função: `mymemory_stats(mymemory_t *memory)`

- **Liberação Total**  
  Libera toda a memória utilizada pela biblioteca e encerra o pool.  
  Função: `mymemory_release(mymemory_t *memory)`  

---

## 🗂️ Estrutura do Projeto  

```
📦 Projeto
├── mymemory.h  // Definições e cabeçalhos
├── mymemory.c  // Implementação da biblioteca
└── main.c      // Exemplo de uso
```

---

## 🚀 Como Usar  

### 1️⃣ Compilação  
```bash
gcc main.c mymemory.c -o mymemory
```

### 2️⃣ Execução  
```bash
./mymemory
```

---

## 📋 Exemplo de Código  

### Inicialização da Memória  
```c
mymemory_t *memory = mymemory_init(1000); // Cria um pool de 1000 bytes.
```

### Alocação  
```c
int *array = mymemory_alloc(memory, 64); // Aloca 64 bytes.
```

### Liberação  
```c
mymemory_free(memory, array); // Libera a memória do array.
```

### Exibição de Estatísticas  
```c
mymemory_stats(memory); // Exibe detalhes sobre o uso da memória.
```
